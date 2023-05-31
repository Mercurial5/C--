#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <any>

#include "BoundExpression.h"

class Evaluator {
public:
	std::map<std::string, std::any>* variables;
	std::vector<std::string> diagnostics;

	Evaluator(std::map<std::string, std::any>&);
	std::any evaluate_expression(std::shared_ptr<BoundExpression>);
};