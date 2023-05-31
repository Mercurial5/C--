#pragma once

#include <memory>
#include <string>

#include "BoundExpression.h"

class BoundAssignmentExpression : public BoundExpression {
public:
	std::string name;
	std::shared_ptr<BoundExpression> expression;

	BoundAssignmentExpression(std::string, std::shared_ptr<BoundExpression>);
	
	virtual const std::type_info& type() override;

};

