#pragma once

#include <memory>
#include <any>

#include "Token.h"

#include "Expression.h"
#include "ExpressionType.h"


class LiteralExpression : public Expression {

public:
	std::shared_ptr<Token> number_token;

	LiteralExpression(std::shared_ptr<Token>);
};
