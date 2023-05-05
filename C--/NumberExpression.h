#pragma once

#include <memory>

#include "Token.h"

#include "Expression.h"
#include "ExpressionType.h"


class NumberExpression : public Expression {

public:
	std::unique_ptr<Token> number_token;
	int value;

	NumberExpression(std::unique_ptr<Token>);

};

