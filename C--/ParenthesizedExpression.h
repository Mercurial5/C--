#pragma once

#include <memory>

#include "Expression.h"
#include "Token.h"

class ParenthesizedExpression : public Expression {
public:
	std::shared_ptr<Token> open_token;
	std::shared_ptr<Expression> expression;
	std::shared_ptr<Token> close_token;

	ParenthesizedExpression(std::shared_ptr<Token>, std::shared_ptr<Expression>, std::shared_ptr<Token>);
};