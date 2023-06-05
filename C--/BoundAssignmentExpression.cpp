#include "BoundAssignmentExpression.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

BoundAssignmentExpression::BoundAssignmentExpression(std::shared_ptr<VariableSymbol> variable, std::shared_ptr<BoundExpression> bound_expression) : 
	BoundExpression(BoundAssignmentExpressionType) {
	this->variable = variable;
	this->expression = bound_expression;
}

const std::type_info& BoundAssignmentExpression::type() {
	return this->expression->type();
}
