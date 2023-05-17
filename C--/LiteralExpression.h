#pragma once

#include <memory>
#include <any>

#include "Token.h"

#include "Expression.h"
#include "ExpressionType.h"


class LiteralExpression : public Expression {

public:
	std::unique_ptr<Token> number_token;
	std::any value;

	LiteralExpression(std::unique_ptr<Token>);	
};
