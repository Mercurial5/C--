#pragma once

#include <memory>

#include "ExpressionTree.h"
#include "EvaluationResult.h"


class Compilation {
	std::shared_ptr<ExpressionTree> tree;

public:
	Compilation(std::shared_ptr<ExpressionTree>);

	EvaluationResult evaluate();
};

