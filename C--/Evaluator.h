#pragma once
#include <memory>

#include "Expression.h"

class Evaluator {
private:
	std::shared_ptr<Expression> root;
public:
	Evaluator();
	int evaluate_expression(std::shared_ptr<Expression>);
};