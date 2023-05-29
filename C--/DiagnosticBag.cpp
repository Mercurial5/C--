#include "DiagnosticBag.h"

void DiagnosticBag::report(TextSpan span, std::string message) {
	this->diagnostics.push_back(Diagnostic(span, message));
}
