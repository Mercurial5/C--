#include <stdexcept>
#include <typeinfo>
#include <optional>
#include <string>

#include "Binder.h"

#include "BoundExpression.h"
#include "BoundLiteralExpression.h"
#include "BoundUnaryExpression.h"
#include "BoundBinaryExpression.h"

#include "BoundUnaryOperatorType.h"
#include "BoundBinaryOperatorType.h"

#include "BoundUnaryOperator.h"
#include "BoundBinaryOperator.h"

#include "ExpressionType.h"
#include "TokenType.h"

#include "Parser.h"

#include "Utilities.h"


Binder::Binder(std::string line) {
	Parser parser(line);
	this->root = parser.parse();
	this->diagnostics = parser.diagnostics;
}

std::shared_ptr<BoundExpression> Binder::bind() {
	return this->bind_expression(this->root);
}

std::shared_ptr<BoundExpression> Binder::bind_expression(std::shared_ptr<Expression> expression) {
	switch (expression->type)
	{
	case LiteralExpressionType: return this->bind_literal_expression(this->cast<LiteralExpression>(expression));
	case UnaryExpressionType: return this->bind_unary_expression(this->cast<UnaryExpression>(expression));
	case BinaryExpressionType: return this->bind_binary_expression(this->cast<BinaryExpression>(expression));
	default: throw std::invalid_argument("Unexpected expression type in bind_expression");
	}
}

std::shared_ptr<BoundExpression> Binder::bind_literal_expression(std::shared_ptr<LiteralExpression> expression) {
	if (!expression) {
		throw std::invalid_argument("Received null expression in bind_literal_expression");
	}

	return std::make_shared<BoundLiteralExpression>(expression->value);
}

std::shared_ptr<BoundExpression> Binder::bind_unary_expression(std::shared_ptr<UnaryExpression> expression) {
	if (!expression) {
		throw std::invalid_argument("Received null expression in bind_unary_expression");
	}

	std::shared_ptr<BoundExpression> bound_expression = this->bind_expression(expression->expression);

	std::optional<std::shared_ptr<BoundUnaryOperator>> bound_operator_optional =
		BoundUnaryOperator::bind(expression->operator_token->type, bound_expression->type());

	if (!bound_operator_optional.has_value()) {
		return bound_expression;
	}

	std::shared_ptr<BoundUnaryOperator> bound_operator = bound_operator_optional.value();
	return std::make_shared<BoundUnaryExpression>(bound_operator, bound_expression);
}

std::shared_ptr<BoundExpression> Binder::bind_binary_expression(std::shared_ptr<BinaryExpression> expression) {
	if (!expression) {
		throw std::invalid_argument("Received null expression in bind_binary_expression");
	}

	std::shared_ptr<BoundExpression> left = this->bind_expression(expression->left);
	std::shared_ptr<BoundExpression> right = this->bind_expression(expression->right);


	std::optional<std::shared_ptr<BoundBinaryOperator>> bound_operator_optional =
		BoundBinaryOperator::bind(expression->operator_token->type, left->type(), right->type());

	if (!bound_operator_optional.has_value()) {
		return left;
	}

	std::shared_ptr<BoundBinaryOperator> bound_operator = bound_operator_optional.value();
	return std::make_shared<BoundBinaryExpression>(left, bound_operator, right);
}
