#include <memory>

#include "Compilation.h"
#include "Binder.h"
#include "Evaluator.h"
#include "EvaluationResult.h"

#include "BoundExpression.h"

Compilation::Compilation(std::shared_ptr<ExpressionTree> tree) {
	this->tree = tree;
}

EvaluationResult Compilation::evaluate() {
	Binder binder(this->tree->diagnostics);
	std::shared_ptr<BoundExpression> bound_expression = binder.bind(this->tree->root);

	if (!binder.diagnostics.empty()) {
		return EvaluationResult(binder.diagnostics, std::any());
	}

	Evaluator evaluator;
	std::any value = evaluator.evaluate_expression(bound_expression);

	return EvaluationResult(DiagnosticBag(), value);
}
