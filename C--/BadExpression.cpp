#include <memory>

#include "BadExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"


BadExpression::BadExpression(std::unique_ptr<Token> token) : Expression(BadExpressionType) {
	this->token = std::move(token);
}