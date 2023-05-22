#pragma once

#include <any>

#include "BoundExpression.h"

class BoundLiteralExpression: public BoundExpression {
public:
	std::any value;

	BoundLiteralExpression(std::any);
	virtual const std::type_info& type() override;
};

