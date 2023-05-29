#pragma once

#include <vector>

#include "TextSpan.h"
#include "Diagnostic.h"

class DiagnosticBag {
	std::vector<Diagnostic> diagnostics;

	void report(TextSpan, std::string);
public:
	
};

