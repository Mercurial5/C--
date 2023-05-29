#include <typeinfo>
#include <string>

#include "DiagnosticBag.h"

void DiagnosticBag::report(TextSpan span, std::string message) {
	this->diagnostics.push_back(Diagnostic(span, message));
}

void DiagnosticBag::report_invalid_number(int start, int length, std::string raw, const std::type_info& type) {
	TextSpan span(start, length);
	std::string message = "The number " + raw + " is not valid " + type.name();
	this->report(span, message);
}

void DiagnosticBag::report_bad_character(int start, char character) {
	TextSpan span(start, 1);
	std::string message = "Bad character input: " + character;
	this->report(span, message);
}
