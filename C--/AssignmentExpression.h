#pragma once

#include <memory>

#include "Expression.h"
#include "Token.h"

class AssignmentExpression : public Expression {
public:
	std::shared_ptr<Token> identifier_token;
	std::shared_ptr<Token> equal_token;
	std::shared_ptr<Expression> expression;

	AssignmentExpression(std::shared_ptr<Token>, std::shared_ptr<Token>, std::shared_ptr<Expression>);
};

