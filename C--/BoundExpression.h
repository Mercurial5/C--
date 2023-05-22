#pragma once

#include <typeinfo>

#include "BoundExpressionType.h"

class BoundExpression {
public:
	BoundExpressionType expression_type;
	BoundExpression(BoundExpressionType);
	virtual const std::type_info& type() = 0;
};

