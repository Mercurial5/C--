#include "BoundVariableExpression.h"

#include "BoundExpression.h"
#include "BoundExpressionType.h"

BoundVariableExpression::BoundVariableExpression(std::string name, const std::type_info* type) : BoundExpression(BoundVariableExpressionType) {
	this->name = name;
	this->_type = type;
	
}

const std::type_info& BoundVariableExpression::type() {
	return *this->_type;
}
