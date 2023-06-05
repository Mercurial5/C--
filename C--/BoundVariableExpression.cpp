#include "BoundVariableExpression.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

BoundVariableExpression::BoundVariableExpression(std::shared_ptr<VariableSymbol> variable) : BoundExpression(BoundVariableExpressionType) {
	this->variable = variable;
}

const std::type_info& BoundVariableExpression::type() {
	return *this->variable->type;
}
