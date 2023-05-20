#pragma once

#include <memory>

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

class BadExpression : public Expression {
	std::shared_ptr<Token> token;
public:
	BadExpression(std::shared_ptr<Token>);
};