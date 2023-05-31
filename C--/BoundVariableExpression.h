#pragma once

#include <typeinfo>
#include <string>

#include "BoundExpression.h"

class BoundVariableExpression : public BoundExpression {
public:
	std::string name;
	const std::type_info* _type;

	BoundVariableExpression(std::string, const std::type_info*);
	virtual const std::type_info& type() override;
};

