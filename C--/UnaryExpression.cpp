#include <memory>

#include "UnaryExpression.h"
#include "Expression.h"
#include "Token.h"


UnaryExpression::UnaryExpression(std::shared_ptr<Token> operator_token, std::shared_ptr<Expression> expression) : Expression(UnaryExpressionType) {
	this->operator_token = operator_token;
	this->expression = expression;
}