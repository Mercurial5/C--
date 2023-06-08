#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <any>

#include "BoundExpression.h"
#include "BoundLiteralExpression.h"
#include "BoundVariableExpression.h"
#include "BoundAssignmentExpression.h"
#include "BoundUnaryExpression.h"
#include "BoundBinaryExpression.h"

class Evaluator {
public:
	std::map<std::string, std::any>* variables;
	std::vector<std::string> diagnostics;

	Evaluator(std::map<std::string, std::any>&);
	std::any evaluate_expression(std::shared_ptr<BoundExpression>);
private:
	std::any evaluate_literal_expression(std::shared_ptr<BoundLiteralExpression>);
	std::any evaluate_variable_expression(std::shared_ptr<BoundVariableExpression>);
	std::any evaluate_assignment_expression(std::shared_ptr<BoundAssignmentExpression>);
	std::any evaluate_unary_expression(std::shared_ptr<BoundUnaryExpression>);
	std::any evaluate_binary_expression(std::shared_ptr<BoundBinaryExpression>);
};