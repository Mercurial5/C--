#include <stdexcept>
#include <memory>

#include "Evaluator.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

#include "BoundLiteralExpression.h"

#include "BoundUnaryExpression.h"
#include "BoundUnaryOperatorType.h"

#include "BoundBinaryExpression.h"
#include "BoundBinaryOperatorType.h"

#include "Utilities.h"

Evaluator::Evaluator() {}


std::any Evaluator::evaluate_expression(std::shared_ptr<BoundExpression> expression) {
	if (expression->expression_type == BoundLiteralExpressionType) {
		std::shared_ptr<BoundLiteralExpression> bound_literal_expression = std::dynamic_pointer_cast<BoundLiteralExpression>(expression);

		// Only if bound literal expression is not nullptr (Dynamic cast was successfull)
		if (bound_literal_expression) {
			return bound_literal_expression->value;
		}
	}

	if (expression->expression_type == BoundUnaryExpressionType) {
		std::shared_ptr<BoundUnaryExpression> bound_unary_expression = std::dynamic_pointer_cast<BoundUnaryExpression>(expression);

		// Only if unary expression is not nullptr (Dynamic cast was successfull)
		if (bound_unary_expression) {
			std::any result = this->evaluate_expression(bound_unary_expression->expression);

			if (result.type() != typeid(int)) {
				std::string message = "Unary expressions are only avialable for integers";
				this->diagnostics.push_back(message);
				return result;
			}

			int result_int = std::any_cast<int>(result);

			switch (bound_unary_expression->operator_type) {
			case Identity:
				return result_int;
			case Negation:
				return -result_int;
			default:
				throw std::invalid_argument("Unexpected unary operator " + Utilities::bound_unary_operator_name(bound_unary_expression->operator_type));
			}
		}
	}

	if (expression->expression_type == BoundBinaryExpressionType) {
		std::shared_ptr<BoundBinaryExpression> bound_binary_expression = std::dynamic_pointer_cast<BoundBinaryExpression>(expression);

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (bound_binary_expression) {
			std::any left = this->evaluate_expression(bound_binary_expression->left);
			std::any right = this->evaluate_expression(bound_binary_expression->right);

			if (left.type() != typeid(int) || right.type() != typeid(int)) {
				std::string message = "Binary expressions are only avialable for integers";
				this->diagnostics.push_back(message);
				return left;
			}

			int left_int = std::any_cast<int>(left);
			int right_int = std::any_cast<int>(right);

			switch (bound_binary_expression->operator_type) {
			case Addition: return left_int + right_int;
			case Subtraction: return left_int - right_int;
			case Multiplication: return left_int * right_int;
			case Division: return left_int / right_int;
			default:
				throw std::invalid_argument("Unexpected binary operator " + Utilities::bound_binary_operator_name(bound_binary_expression->operator_type));
			}
		}
	}

	throw new std::invalid_argument("Invalid expression");
}
