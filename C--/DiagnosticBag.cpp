#include <typeinfo>
#include <vector>
#include <string>

#include "DiagnosticBag.h"

#include "Token.h"
#include "TokenType.h"

#include "Utilities.h"

void DiagnosticBag::report(TextSpan span, std::string message) {
	this->diagnostics.push_back(Diagnostic(span, message));
}

void DiagnosticBag::extend(const DiagnosticBag& bag) {
	this->diagnostics.insert(this->diagnostics.begin(), bag.diagnostics.begin(), bag.diagnostics.end());
}

bool DiagnosticBag::empty() {
	return this->diagnostics.empty();
}

Diagnostic* DiagnosticBag::begin() {
	return this->diagnostics.data();
}

Diagnostic* DiagnosticBag::end() {
	return this->diagnostics.data() + this->diagnostics.size();
}

void DiagnosticBag::report_invalid_number(int start, int length, std::string raw, const std::type_info& type) {
	TextSpan span(start, length);
	std::string message = "The number <" + raw + "> is not valid <" + type.name() + '>';

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
	std::string message = "Unexpected Token. Expected <" + Utilities::token_name(expected) + ">, Actual <" + Utilities::token_name(actual) + '>';

	this->report(span, message);
}

void DiagnosticBag::report_undefined_unary_operator(Token operator_token, const std::type_info& type) {
	std::string message = "Unary operator `" + operator_token.raw + "` is not defined for <" + type.name() + '>';

	this->report(operator_token.span, message);
}

void DiagnosticBag::report_undefined_binary_operator(Token operator_token, const std::type_info& left_type, const std::type_info& right_type) {
	std::string message = "Binary operator `" + operator_token.raw + "` is not defined for <" + left_type.name() + "> and <" + right_type.name() + '>';

	this->report(operator_token.span, message);
}
