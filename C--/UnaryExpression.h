#pragma once

#include <memory>

#include "Expression.h"
#include "Token.h"

class UnaryExpression : public Expression {
public:
	std::shared_ptr<Token> operator_token;
	std::shared_ptr<Expression> expression;

	UnaryExpression(std::shared_ptr<Token>, std::shared_ptr<Expression>);
};

