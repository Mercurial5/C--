#pragma once

#include <any>

#include "DiagnosticBag.h"

class EvaluationResult {
public:
	DiagnosticBag diagnostics;
	std::any value;

	EvaluationResult(DiagnosticBag, std::any);
};

