#include "BinaryExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

BinaryExpression::BinaryExpression(std::shared_ptr<Expression> left, std::shared_ptr<Token> operator_token, std::shared_ptr<Expression> right) :
	Expression(BinaryExpressionType) {
	this->left = left;
	this->operator_token = operator_token;
	this->right = right;
}
