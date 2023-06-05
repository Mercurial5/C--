#pragma once

#include <memory>
#include <string>

#include "BoundExpression.h"

#include "VariableSymbol.h"

class BoundAssignmentExpression : public BoundExpression {
public:
	std::shared_ptr<VariableSymbol> variable;
	std::shared_ptr<BoundExpression> expression;

	BoundAssignmentExpression(std::shared_ptr<VariableSymbol>, std::shared_ptr<BoundExpression>);
	
	virtual const std::type_info& type() override;

};

