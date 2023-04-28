#pragma once

#include <memory>

#include "Expression.h"
#include "Token.h"

class ParenthesizedExpression : public Expression {
public:
	std::unique_ptr<Token> open_token;
	std::unique_ptr<Expression> expression;
	std::unique_ptr<Token> close_token;

	ParenthesizedExpression(std::unique_ptr<Token>, std::unique_ptr<Expression>, std::unique_ptr<Token>);
};