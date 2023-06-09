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

#include "VariableSymbol.h"

#include "Utilities.h"

Evaluator::Evaluator(std::map<std::shared_ptr<VariableSymbol>, std::any>& variables) {
	this->variables = &variables;
}

std::any Evaluator::evaluate_expression(std::shared_ptr<BoundExpression> expression) {
	switch (expression->expression_type)
	{
	case BoundLiteralExpressionType:
		return this->evaluate_literal_expression(std::dynamic_pointer_cast<BoundLiteralExpression>(expression));
	case BoundVariableExpressionType:
		return this->evaluate_variable_expression(std::dynamic_pointer_cast<BoundVariableExpression>(expression));
	case BoundAssignmentExpressionType:
		return this->evaluate_assignment_expression(std::dynamic_pointer_cast<BoundAssignmentExpression>(expression));
	case BoundUnaryExpressionType:
		return this->evaluate_unary_expression(std::dynamic_pointer_cast<BoundUnaryExpression>(expression));
	case BoundBinaryExpressionType:
		return this->evaluate_binary_expression(std::dynamic_pointer_cast<BoundBinaryExpression>(expression));
	default:
		throw std::invalid_argument("Unexpected bound expression " + Utilities::bound_expression_name(expression->expression_type));
		break;
	}
}

std::any Evaluator::evaluate_literal_expression(std::shared_ptr<BoundLiteralExpression> expression) {
	if (expression) {
		return expression->value;
	}

	throw std::invalid_argument("Could not cast BoundExpression to BoundLiteralExpression");
}

std::any Evaluator::evaluate_variable_expression(std::shared_ptr<BoundVariableExpression> expression) {
	if (expression) {
		return (*this->variables)[expression->name];
	}

	throw std::invalid_argument("Could not cast BoundExpression to BoundVariableExpression");
}

std::any Evaluator::evaluate_assignment_expression(std::shared_ptr<BoundAssignmentExpression> expression) {
	if (expression) {
		std::any value = this->evaluate_expression(expression->expression);
		(*this->variables)[expression->name] = value;
		return value;
	}

	throw std::invalid_argument("Could not cast BoundExpression to BoundAssignmentExpression");
}

std::any Evaluator::evaluate_unary_expression(std::shared_ptr<BoundUnaryExpression> expression) {
	if (expression) {
		std::any result = this->evaluate_expression(expression->expression);

		switch (expression->op->operator_type)
		{
		case Identity:
			return std::any_cast<int>(result);
		case Negation:
			return -std::any_cast<int>(result);
		case LogicalNegation:
			return !std::any_cast<bool>(result);
		default:
			std::string op_name = Utilities::bound_unary_operator_name(expression->op->operator_type);
			throw std::invalid_argument("Unexpected unary operator " + op_name + " for " + result.type().name());
		}
	}
	throw std::invalid_argument("Could not cast BoundExpression to BoundUnaryExpression");
}

std::any Evaluator::evaluate_binary_expression(std::shared_ptr<BoundBinaryExpression> expression) {
	if (expression) {
		std::any left = this->evaluate_expression(expression->left);
		std::any right = this->evaluate_expression(expression->right);

		switch (expression->op->operator_type) {
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
			std::string op_name = Utilities::bound_binary_operator_name(expression->op->operator_type);
			throw std::invalid_argument("Unexpected binary operator " + op_name + " for " + left.type().name() + " and " + right.type().name());
		}
	}

	throw std::invalid_argument("Could not cast BoundExpression to BoundBinaryExpression");
}
