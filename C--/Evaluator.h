#pragma once
#include <memory>

#include "BoundExpression.h"

class Evaluator {
public:
	Evaluator();
	int evaluate_expression(std::shared_ptr<BoundExpression>);
};