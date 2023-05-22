#include <memory>

#include "LiteralExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

LiteralExpression::LiteralExpression(std::shared_ptr<Token> token) : LiteralExpression(token, token->value) {}

LiteralExpression::LiteralExpression(std::shared_ptr<Token> token, std::any value) : Expression(LiteralExpressionType) {
	this->token = token;
	this->value = value;
}
