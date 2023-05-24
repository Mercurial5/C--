#pragma once

#include <memory>

#include "BoundExpression.h"
#include "BoundBinaryOperator.h"

class BoundBinaryExpression : public BoundExpression {
public:
	std::shared_ptr<BoundExpression> left;
	std::shared_ptr<BoundBinaryOperator> op;
	std::shared_ptr<BoundExpression> right;

	BoundBinaryExpression(std::shared_ptr<BoundExpression>, std::shared_ptr<BoundBinaryOperator>, std::shared_ptr<BoundExpression>);
	virtual const std::type_info& type() override;

};

