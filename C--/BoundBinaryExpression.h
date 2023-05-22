#pragma once

#include <memory>

#include "BoundExpression.h"
#include "BoundBinaryOperatorType.h"

class BoundBinaryExpression : public BoundExpression {
public:
	std::shared_ptr<BoundExpression> left;
	BoundBinaryOperatorType operator_type;
	std::shared_ptr<BoundExpression> right;

	BoundBinaryExpression(std::shared_ptr<BoundExpression>, BoundBinaryOperatorType, std::shared_ptr<BoundExpression>);
	virtual const std::type_info& type() override;

};

