#pragma once

#include <typeinfo>
#include <vector>

#include "TextSpan.h"
#include "Diagnostic.h"

class DiagnosticBag {
	std::vector<Diagnostic> diagnostics;

	void report(TextSpan, std::string);
public:
	void extend(const DiagnosticBag& diagnostics);

	void report_invalid_number(int, int, std::string, const std::type_info&);
	void report_bad_character(int, char);
	
};

