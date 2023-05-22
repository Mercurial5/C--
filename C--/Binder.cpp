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
	std::optional<BoundUnaryOperatorType> operator_type_optional = this->bind_unary_operator_type(expression->operator_token, bound_expression->type());
	if (!operator_type_optional.has_value()) {
		return bound_expression;
	}

	BoundUnaryOperatorType operator_type = operator_type_optional.value();
	return std::make_shared<BoundUnaryExpression>(operator_type, bound_expression);
}

std::shared_ptr<BoundExpression> Binder::bind_binary_expression(std::shared_ptr<BinaryExpression> expression) {
	if (!expression) {
		throw std::invalid_argument("Received null expression in bind_binary_expression");
	}

	std::shared_ptr<BoundExpression> left = this->bind_expression(expression->left);
	std::shared_ptr<BoundExpression> right = this->bind_expression(expression->right);
	std::optional<BoundBinaryOperatorType> operator_type_optional = this->bind_binary_operator_type(expression->operator_token, left->type(), right->type());
	if (!operator_type_optional.has_value()) {
		return left;
	}

	BoundBinaryOperatorType operator_type = operator_type_optional.value();
	return std::make_shared<BoundBinaryExpression>(left, operator_type, right);
}

std::optional<BoundUnaryOperatorType> Binder::bind_unary_operator_type(std::shared_ptr<Token> operator_token, const std::type_info& type) {
	if (type != typeid(int)) {
		std::string message = "Unary operator " + Utilities::token_name(operator_token->type) + " is not defined for type " + type.name();
		this->diagnostics.push_back(message);
		return std::nullopt;
	}

	switch (operator_token->type) {
	case PlusToken:
		return Identity;
	case MinusToken:
		return Negation;

	default:
		throw std::invalid_argument("Unexpected operator_token type in bind_unary_operator_type");
	}

}

std::optional<BoundBinaryOperatorType> Binder::bind_binary_operator_type(std::shared_ptr<Token> operator_token, const std::type_info& left_type, const std::type_info& right_type) {
	if (left_type != typeid(int) || right_type != typeid(int)) {
		std::string message = "Binary operator " + Utilities::token_name(operator_token->type) + " is not defined for types (" + left_type.name() + ", " + right_type.name() + ")";
		this->diagnostics.push_back(message);
		return std::nullopt;
	}
	switch (operator_token->type) {
	case PlusToken:
		return Addition;
	case MinusToken:
		return Subtraction;
	case StarToken:
		return Multiplication;
	case SlashToken:
		return Division;

	default: throw std::invalid_argument("Unexpected operator_token type in bind_binary_operator_type");
	}

}
