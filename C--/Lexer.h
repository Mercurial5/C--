#pragma once

#include <optional>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"

#include "DiagnosticBag.h"


class Lexer {
public:
	DiagnosticBag diagnostics;

	Lexer(const std::string);
	std::vector<std::shared_ptr<Token>> tokenize();

	std::optional<int> parse_int(std::string);

private:
	std::string text;
	int position;

	Token get_token();
	bool is_token_skipable(const Token&);


	// utilities

	// Returns character of a current + offset position
	char peek(int = 0);

	// Increment position and return previous position
	int next();

	// Eats all character while compare function is true
	int eat_until(int __cdecl (int));
};