#include "ParenthesizedExpression.h"

#include "Expression.h"

#include "Token.h"


ParenthesizedExpression::ParenthesizedExpression(std::shared_ptr<Token> open_token, std::shared_ptr<Expression> expression, std::shared_ptr<Token> close_token) :
	Expression(ParenthesizedExpressionType) {
	this->open_token = open_token;
	this->expression = expression;
	this->close_token = close_token;
}
