#include "BinaryExpression.h"

#include "Expression.h"
#include "ExpressionType.h"

#include "Token.h"

typedef std::unique_ptr<Expression> UPE;
typedef std::unique_ptr<Token> UPT;

BinaryExpression::BinaryExpression(UPE left, UPT operator_token, UPE right) : Expression(BinaryExpressionType) {
	this->left = std::move(left);
	this->operator_token = std::move(operator_token);
	this->right = std::move(right);
}
