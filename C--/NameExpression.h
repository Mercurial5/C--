#pragma once

#include <memory>

#include "Expression.h"
#include "Token.h"

class NameExpression : public Expression {
public:
	std::shared_ptr<Token> identifier_token;

	NameExpression(std::shared_ptr<Token>);
};

