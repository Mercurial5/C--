#include <typeinfo>
#include <memory>

#include "BoundBinaryExpression.h"

#include "BoundExpression.h"

BoundBinaryExpression::BoundBinaryExpression(std::shared_ptr<BoundExpression> left, std::shared_ptr<BoundBinaryOperator> op, std::shared_ptr<BoundExpression> right) : 
    BoundExpression(BoundBinaryExpressionType) {
    this->left = left;
    this->op = op;
    this->right = right;
}

const std::type_info& BoundBinaryExpression::type() {
    return this->op->result_type;
}
