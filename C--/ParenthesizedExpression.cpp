#include "ParenthesizedExpression.h"

#include "Expression.h"

#include "Token.h"

typedef std::unique_ptr<Token> UPT;
typedef std::unique_ptr<Expression> UPE;

ParenthesizedExpression::ParenthesizedExpression(UPT open_token, UPE expression, UPT close_token) : Expression(ParenthesizedExpressionType) {
	this->open_token = std::move(open_token);
	this->expression = std::move(expression);
	this->close_token = std::move(close_token);
}
