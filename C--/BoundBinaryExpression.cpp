#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(std::shared_ptr<BoundExpression> left, BoundBinaryOperatorType operator_type, std::shared_ptr<BoundExpression> right) : 
    BoundExpression(BoundBinaryExpressionType) {
    this->left = left;
    this->operator_type = operator_type;
    this->right = right;
}

const std::type_info& BoundBinaryExpression::type() {
    return this->left->type();
}
