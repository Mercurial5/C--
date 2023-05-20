#pragma once

#include <memory>

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

class BinaryExpression : public Expression {
public:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
	std::shared_ptr<Token> operator_token;

	BinaryExpression(std::shared_ptr<Expression>, std::shared_ptr<Token>, std::shared_ptr<Expression>);
};