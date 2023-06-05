#include <memory>
#include <string>
#include <map>
#include <any>

#include "Compilation.h"
#include "Binder.h"
#include "Evaluator.h"
#include "EvaluationResult.h"

#include "BoundExpression.h"

#include "VariableSymbol.h"

Compilation::Compilation(std::shared_ptr<ExpressionTree> tree) {
	this->tree = tree;
}

EvaluationResult Compilation::evaluate(std::map<std::shared_ptr<VariableSymbol>, std::any>& variables) {
	Binder binder(this->tree->diagnostics, variables);
	std::shared_ptr<BoundExpression> bound_expression = binder.bind(this->tree->root);

	if (!binder.diagnostics.empty()) {
		return EvaluationResult(binder.diagnostics, std::any());
	}

	Evaluator evaluator(variables);
	std::any value = evaluator.evaluate_expression(bound_expression);

	return EvaluationResult(DiagnosticBag(), value);
}
