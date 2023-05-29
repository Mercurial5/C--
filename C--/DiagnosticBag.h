#pragma once

#include <typeinfo>
#include <vector>

#include "TextSpan.h"
#include "Diagnostic.h"

#include "Token.h"

class DiagnosticBag {
	std::vector<Diagnostic> diagnostics;

	void report(TextSpan, std::string);
public:
	void extend(const DiagnosticBag& diagnostics);

	void report_invalid_number(int, int, std::string, const std::type_info&);
	void report_bad_character(int, char);

	void report_bad_token(Token);
	void report_unexpected_token(TextSpan, TokenType, TokenType);

	void report_undefined_unary_operator(Token, const std::type_info&);
	void report_undefined_binary_operator(Token, const std::type_info&, const std::type_info&);
};

