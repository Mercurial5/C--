#include <stdexcept>
#include <memory>

#include "Evaluator.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "TokenType.h"

#include "BinaryExpression.h"
#include "NumberExpression.h"
#include "ParenthesizedExpression.h"


Evaluator::Evaluator() {}


int Evaluator::evaluate_expression(std::unique_ptr<Expression> expression) {
	if (expression->type == NumberExpressionType) {
		NumberExpression* number_expression_raw_ptr = dynamic_cast<NumberExpression*>(expression.get());

		// Only if number expression is not nullptr (Dynamic cast was successfull)
		if (number_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			std::unique_ptr<NumberExpression> number_expression(number_expression_raw_ptr);
			return number_expression->value;
		}
	}

	if (expression->type == BinaryExpressionType) {
		BinaryExpression* binary_expression_raw_ptr = dynamic_cast<BinaryExpression*>(expression.get());

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (binary_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			std::unique_ptr<BinaryExpression> binary_expression(binary_expression_raw_ptr);

			int left = this->evaluate_expression(std::move(binary_expression->left));
			int right = this->evaluate_expression(std::move(binary_expression->right));

			switch (binary_expression->operator_token->type)
			{
			case PlusToken: return left + right;
			case MinusToken: return left - right;
			case StarToken: return left * right;
			case SlashToken: return left / right;
			default:
				break;
			}
		}
	}

	if (expression->type == ParenthesizedExpressionType) {
		ParenthesizedExpression* parenthesized_expression_raw_ptr = dynamic_cast<ParenthesizedExpression*>(expression.get());

		// Only if parenthesized expression is not nullptr (Dynamic cast was successfull)
		if (parenthesized_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			std::unique_ptr<ParenthesizedExpression> parenthesized_expression(parenthesized_expression_raw_ptr);
			return this->evaluate_expression(std::move(parenthesized_expression->expression));
		}
	}

	throw new std::invalid_argument("Invalid expression");
}
