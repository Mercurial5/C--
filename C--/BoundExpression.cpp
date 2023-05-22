#include <typeinfo>

#include "BoundExpression.h"

BoundExpression::BoundExpression(BoundExpressionType expression_type) {
	this->expression_type = expression_type;
}
