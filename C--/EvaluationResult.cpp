#include "EvaluationResult.h"

EvaluationResult::EvaluationResult(DiagnosticBag diagnostics, std::any value) {
	this->diagnostics.extend(diagnostics);
	this->value = value;
}
