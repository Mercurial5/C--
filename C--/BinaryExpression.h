#pragma once

#include <memory>

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

class BinaryExpression : public Expression {
public:
	std::unique_ptr<Expression> left;
	std::unique_ptr<Expression> right;
	std::unique_ptr<Token> operator_token;

	BinaryExpression(std::unique_ptr<Expression>, std::unique_ptr<Token>, std::unique_ptr<Expression>);
};