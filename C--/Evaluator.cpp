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


int Evaluator::evaluate_expression(std::shared_ptr<BoundExpression> expression) {
	if (expression->expression_type == BoundLiteralExpressionType) {
		std::shared_ptr<BoundLiteralExpression> bound_literal_expression = std::dynamic_pointer_cast<BoundLiteralExpression>(expression);

		// Only if bound literal expression is not nullptr (Dynamic cast was successfull)
		if (bound_literal_expression) {
			return std::any_cast<int>(bound_literal_expression->value);
		}
	}

	if (expression->expression_type == BoundUnaryExpressionType) {
		std::shared_ptr<BoundUnaryExpression> bound_unary_expression = std::dynamic_pointer_cast<BoundUnaryExpression>(expression);

		// Only if unary expression is not nullptr (Dynamic cast was successfull)
		if (bound_unary_expression) {
			int result = this->evaluate_expression(bound_unary_expression->expression);

			switch (bound_unary_expression->operator_type) {
			case Identity:
				return result;
			case Negation:
				return -result;
			default:
				throw std::invalid_argument("Unexpected unary operator " + Utilities::bound_unary_operator_name(bound_unary_expression->operator_type));
			}
		}
	}

	if (expression->expression_type == BoundBinaryExpressionType) {
		std::shared_ptr<BoundBinaryExpression> bound_binary_expression = std::dynamic_pointer_cast<BoundBinaryExpression>(expression);

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (bound_binary_expression) {
			int left = this->evaluate_expression(bound_binary_expression->left);
			int right = this->evaluate_expression(bound_binary_expression->right);

			switch (bound_binary_expression->operator_type) {
			case Addition: return left + right;
			case Subtraction: return left - right;
			case Multiplication: return left * right;
			case Division: return left / right;
			default:
				throw std::invalid_argument("Unexpected binary operator " + Utilities::bound_binary_operator_name(bound_binary_expression->operator_type));
			}
		}
	}

	throw new std::invalid_argument("Invalid expression");
}
