#include <typeinfo>
#include <string>

#include "DiagnosticBag.h"

#include "Token.h"
#include "TokenType.h"

#include "Utilities.h"

void DiagnosticBag::report(TextSpan span, std::string message) {
	this->diagnostics.push_back(Diagnostic(span, message));
}

void DiagnosticBag::extend(const DiagnosticBag& bag) {
	this->diagnostics.insert(begin(this->diagnostics), begin(bag.diagnostics), end(bag.diagnostics));
}

void DiagnosticBag::report_invalid_number(int start, int length, std::string raw, const std::type_info& type) {
	TextSpan span(start, length);
	std::string message = "The number <" + raw + " > is not valid <" + type.name() + '>';

	this->report(span, message);
}

void DiagnosticBag::report_bad_character(int start, char character) {
	TextSpan span(start, 1);
	std::string message = "Bad character input: <" + character + '>';

	this->report(span, message);
}

void DiagnosticBag::report_bad_token(Token token) {
	TextSpan span(token.span);
	std::string message = "Bad Token. Expected primary, got <" + Utilities::token_name(token.type) + '>';

	this->report(span, message);
}

void DiagnosticBag::report_unexpected_token(TextSpan span, TokenType actual, TokenType expected) {
	std::string message = "Unexpected Token. Expected <" + Utilities::token_name(expected) + ", Actual<" + Utilities::token_name(actual) + '>';

	this->report(span, message);
}
