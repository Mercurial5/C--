#pragma once

#include <memory>
#include <string>
#include <map>
#include <any>

#include "ExpressionTree.h"
#include "EvaluationResult.h"


class Compilation {
	std::shared_ptr<ExpressionTree> tree;

public:
	Compilation(std::shared_ptr<ExpressionTree>);

	EvaluationResult evaluate(std::map<std::string, std::any>&);
};

