#pragma once

#include <optional>
#include <string>
#include <vector>
#include <memory>
#include <any>

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


	void read_number_token(int, TokenType&, std::any&);
	void read_whitespace_token(int, TokenType&);
	void read_identifier_or_keyword_token(int, TokenType&);

	// utilities

	// Returns character of a current + offset position
	char peek(int = 0);

	// Eats all character while compare function is true
	int eat_until(int __cdecl (int));
};