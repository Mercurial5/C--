#include "BoundLiteralExpression.h"

BoundLiteralExpression::BoundLiteralExpression(std::any value) : BoundExpression(BoundLiteralExpressionType) {
    this->value = value;
}

const std::type_info& BoundLiteralExpression::type() {
    return this->value.type();
}
