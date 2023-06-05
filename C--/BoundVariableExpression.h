#pragma once

#include <typeinfo>
#include <memory>
#include <string>

#include "BoundExpression.h"

#include "VariableSymbol.h"

class BoundVariableExpression : public BoundExpression {
public:
	std::shared_ptr<VariableSymbol> variable;

	BoundVariableExpression(std::shared_ptr<VariableSymbol>);
	virtual const std::type_info& type() override;
};

