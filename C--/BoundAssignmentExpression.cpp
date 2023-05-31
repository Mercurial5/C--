#include "BoundAssignmentExpression.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

BoundAssignmentExpression::BoundAssignmentExpression(std::string name, std::shared_ptr<BoundExpression> bound_expression) : BoundExpression(BoundAssignmentExpressionType) {
	this->name = name;
	this->expression = bound_expression;
}

const std::type_info& BoundAssignmentExpression::type() {
	return this->expression->type();
}
