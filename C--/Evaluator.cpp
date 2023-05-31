#include <stdexcept>
#include <algorithm>
#include <memory>
#include <string>
#include <map>
#include <any>

#include "Evaluator.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

#include "BoundLiteralExpression.h"
#include "BoundVariableExpression.h"
#include "BoundAssignmentExpression.h"

#include "BoundUnaryExpression.h"
#include "BoundUnaryOperatorType.h"

#include "BoundBinaryExpression.h"
#include "BoundBinaryOperatorType.h"


#include "Utilities.h"

Evaluator::Evaluator(std::map<std::string, std::any>& variables) {
	this->variables = &variables;
}


std::any Evaluator::evaluate_expression(std::shared_ptr<BoundExpression> expression) {
	if (expression->expression_type == BoundLiteralExpressionType) {
		std::shared_ptr<BoundLiteralExpression> bound_literal_expression = std::dynamic_pointer_cast<BoundLiteralExpression>(expression);

		// Only if bound literal expression is not nullptr (Dynamic cast was successfull)
		if (bound_literal_expression) {
			return bound_literal_expression->value;
		}
	}

	if (expression->expression_type == BoundVariableExpressionType) {
		std::shared_ptr<BoundVariableExpression> bound_variable_expression = std::dynamic_pointer_cast<BoundVariableExpression>(expression);

		if (bound_variable_expression) {
			return (*this->variables)[bound_variable_expression->name];
		}
	}

	if (expression->expression_type == BoundAssignmentExpressionType) {
		std::shared_ptr<BoundAssignmentExpression> bound_assignment_expression = std::dynamic_pointer_cast<BoundAssignmentExpression>(expression);

		if (bound_assignment_expression) {
			std::any value = this->evaluate_expression(bound_assignment_expression->expression);
			(*this->variables)[bound_assignment_expression->name] = value;
			return value;
		}
	}


	if (expression->expression_type == BoundUnaryExpressionType) {
		std::shared_ptr<BoundUnaryExpression> bound_unary_expression = std::dynamic_pointer_cast<BoundUnaryExpression>(expression);

		// Only if unary expression is not nullptr (Dynamic cast was successfull)
		if (bound_unary_expression) {
			std::any result = this->evaluate_expression(bound_unary_expression->expression);

			switch (bound_unary_expression->op->operator_type)
			{
			case Identity:
				return std::any_cast<int>(result);
			case Negation:
				return -std::any_cast<int>(result);
			case LogicalNegation:
				return !std::any_cast<bool>(result);
			default:
				std::string op_name = Utilities::bound_unary_operator_name(bound_unary_expression->op->operator_type);
				throw std::invalid_argument("Unexpected unary operator " + op_name + " for " + result.type().name());
			}
		}
	}

	if (expression->expression_type == BoundBinaryExpressionType) {
		std::shared_ptr<BoundBinaryExpression> bound_binary_expression = std::dynamic_pointer_cast<BoundBinaryExpression>(expression);

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (bound_binary_expression) {
			std::any left = this->evaluate_expression(bound_binary_expression->left);
			std::any right = this->evaluate_expression(bound_binary_expression->right);

			switch (bound_binary_expression->op->operator_type) {
			case Addition:
				if (left.type() == typeid(bool) && right.type() == typeid(int)) {
					return std::any_cast<bool>(left) + std::any_cast<int>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(bool)) {
					return std::any_cast<int>(left) + std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) + std::any_cast<bool>(right);
				}

				return std::any_cast<int>(left) + std::any_cast<int>(right);
			case Subtraction:
				if (left.type() == typeid(bool) && right.type() == typeid(int)) {
					return std::any_cast<bool>(left) - std::any_cast<int>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(bool)) {
					return std::any_cast<int>(left) - std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) - std::any_cast<bool>(right);
				}

				return std::any_cast<int>(left) - std::any_cast<int>(right);
			case Multiplication:
				if (left.type() == typeid(bool) && right.type() == typeid(int)) {
					return std::any_cast<bool>(left) * std::any_cast<int>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(bool)) {
					return std::any_cast<int>(left) * std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) * std::any_cast<bool>(right);
				}

				return std::any_cast<int>(left) * std::any_cast<int>(right);
			case Division:
				if (left.type() == typeid(bool) && right.type() == typeid(int)) {
					return std::any_cast<bool>(left) / std::any_cast<int>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(bool)) {
					return std::any_cast<int>(left) / std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) / std::any_cast<bool>(right);
				}

				return std::any_cast<int>(left) / std::any_cast<int>(right);
			case LogicalAnd:
				return std::any_cast<bool>(left) && std::any_cast<bool>(right);
			case LogicalOr:
				return std::any_cast<bool>(left) || std::any_cast<bool>(right);
			case Equal:
				if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) == std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(int)) {
					return std::any_cast<int>(left) == std::any_cast<int>(right);
				}
			case NotEqual:
				if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
					return std::any_cast<bool>(left) != std::any_cast<bool>(right);
				}
				else if (left.type() == typeid(int) && right.type() == typeid(int)) {
					return std::any_cast<int>(left) != std::any_cast<int>(right);
				}
			default:
				std::string op_name = Utilities::bound_binary_operator_name(bound_binary_expression->op->operator_type);
				throw std::invalid_argument("Unexpected binary operator " + op_name + " for " + left.type().name() + " and " + right.type().name());
			}
		}
	}

	throw new std::invalid_argument("Invalid expression");
}
