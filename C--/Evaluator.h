#pragma once
#include <memory>
#include <vector>
#include <string>
#include <any>

#include "BoundExpression.h"

class Evaluator {
public:
	std::vector<std::string> diagnostics;

	Evaluator();
	std::any evaluate_expression(std::shared_ptr<BoundExpression>);
};