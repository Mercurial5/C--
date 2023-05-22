#pragma once

#include <memory>
#include <typeinfo>

#include "BoundExpression.h"
#include "BoundUnaryOperatorType.h"

class BoundUnaryExpression : public BoundExpression {
public:
	BoundUnaryOperatorType operator_type;
	std::shared_ptr<BoundExpression> expression;

	BoundUnaryExpression(BoundUnaryOperatorType, std::shared_ptr<BoundExpression>);
	virtual const std::type_info& type() override;
};

