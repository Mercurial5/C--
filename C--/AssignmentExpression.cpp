#include "AssignmentExpression.h"

#include "ExpressionType.h"

AssignmentExpression::AssignmentExpression(std::shared_ptr<Token> identifier_token, std::shared_ptr<Token> equal_token, std::shared_ptr<Expression> expression) : 
	Expression(AssignmentExpressionType) {
	this->identifier_token = identifier_token;
	this->equal_token = equal_token;
	this->expression = expression;
}
