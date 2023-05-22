#include <memory>

#include "LiteralExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

LiteralExpression::LiteralExpression(std::shared_ptr<Token> token) : Expression(LiteralExpressionType) {
	this->number_token = token;
}
