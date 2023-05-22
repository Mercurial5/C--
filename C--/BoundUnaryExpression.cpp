#include <memory>

#include "BoundExpression.h"
#include "BoundUnaryExpression.h"

BoundUnaryExpression::BoundUnaryExpression(BoundUnaryOperatorType operator_type, std::shared_ptr<BoundExpression> expression) : BoundExpression(BoundUnaryExpressionType)
{
	this->operator_type = operator_type;
	this->expression = expression;
}

const std::type_info& BoundUnaryExpression::type()
{
	return this->expression->type();
}
