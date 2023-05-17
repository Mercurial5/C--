#pragma once
#include <memory>

#include "Expression.h"

class Evaluator {
private:
	std::unique_ptr<Expression> root;
public:
	Evaluator();
	int evaluate_expression(Expression*);
};