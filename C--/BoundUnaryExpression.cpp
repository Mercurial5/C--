#include <memory>

#include "BoundExpression.h"
#include "BoundUnaryExpression.h"

#include "BoundUnaryOperator.h"

BoundUnaryExpression::BoundUnaryExpression(std::shared_ptr<BoundUnaryOperator> op, std::shared_ptr<BoundExpression> expression) : 
	BoundExpression(BoundUnaryExpressionType) {
	this->op = op;
	this->expression = expression;
}

const std::type_info& BoundUnaryExpression::type()
{
	return this->op->result_type;
}
