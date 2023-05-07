#include <memory>

#include "NumberExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

NumberExpression::NumberExpression(std::unique_ptr<Token> token) : Expression(NumberExpressionType) {
	this->value = std::any_cast<int>(token->value);
	this->number_token = std::move(number_token);
}
