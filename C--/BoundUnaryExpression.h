#pragma once

#include <memory>
#include <typeinfo>

#include "BoundExpression.h"
#include "BoundUnaryOperator.h"

class BoundUnaryExpression : public BoundExpression {
public:
	std::shared_ptr<BoundUnaryOperator> op;
	std::shared_ptr<BoundExpression> expression;

	BoundUnaryExpression(std::shared_ptr<BoundUnaryOperator>, std::shared_ptr<BoundExpression>);
	virtual const std::type_info& type() override;
};

