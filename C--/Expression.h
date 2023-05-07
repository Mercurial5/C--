#pragma once

#include "ExpressionType.h"

class Expression {
public:
	ExpressionType type;

	Expression(ExpressionType);

	virtual ~Expression();
};

