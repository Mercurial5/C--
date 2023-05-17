#include <memory>

#include "LiteralExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

LiteralExpression::LiteralExpression(std::unique_ptr<Token> token) : Expression(LiteralExpressionType) {
	this->value = token->value;
	this->number_token = std::move(number_token);
}
