#include "Diagnostic.h"

Diagnostic::Diagnostic(TextSpan span, std::string message) : span(span), message(message) {}

std::ostream& operator<<(std::ostream& out, const Diagnostic& diagnostic) {
	return out << diagnostic.message;
}
