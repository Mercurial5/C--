#include "NameExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

NameExpression::NameExpression(std::shared_ptr<Token> identifier_token) : Expression(NameExpressionType) {
	this->identifier_token = identifier_token;
}
