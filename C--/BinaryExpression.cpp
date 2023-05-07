#include "BinaryExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> left, std::unique_ptr<Token> operator_token, std::unique_ptr<Expression> right) : 
	Expression(BinaryExpressionType) {
	this->left = std::move(left);
	this->operator_token = std::move(operator_token);
	this->right = std::move(right);
}
