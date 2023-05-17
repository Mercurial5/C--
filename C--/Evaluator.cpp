#include <stdexcept>
#include <memory>

#include "Evaluator.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "TokenType.h"

#include "BinaryExpression.h"
#include "LiteralExpression.h"
#include "ParenthesizedExpression.h"


Evaluator::Evaluator() {}


int Evaluator::evaluate_expression(Expression* expression) {
	if (expression->type == LiteralExpressionType) {
		LiteralExpression* number_expression = dynamic_cast<LiteralExpression*>(expression);

		// Only if number expression is not nullptr (Dynamic cast was successfull)
		if (number_expression) {
			return std::any_cast<int>(number_expression->value);
		}
	}

	if (expression->type == BinaryExpressionType) {
		BinaryExpression* binary_expression = dynamic_cast<BinaryExpression*>(expression);

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (binary_expression) {
			int left = this->evaluate_expression(binary_expression->left.get());
			int right = this->evaluate_expression(binary_expression->right.get());

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
		ParenthesizedExpression* parenthesized_expression = dynamic_cast<ParenthesizedExpression*>(expression);

		// Only if parenthesized expression is not nullptr (Dynamic cast was successfull)
		if (parenthesized_expression) {
			return this->evaluate_expression(parenthesized_expression->expression.get());
		}
	}

	throw new std::invalid_argument("Invalid expression");
}
