#include "ParenthesizedExpression.h"

#include "Expression.h"

#include "Token.h"


ParenthesizedExpression::ParenthesizedExpression(std::unique_ptr<Token> open_token, std::unique_ptr<Expression> expression, std::unique_ptr<Token> close_token) : 
	Expression(ParenthesizedExpressionType) {
	this->open_token = std::move(open_token);
	this->expression = std::move(expression);
	this->close_token = std::move(close_token);
}
