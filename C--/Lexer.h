#pragma once

#include <string>
#include <vector>

#include "Token.h"


class Lexer {
public:
	Lexer(const std::string);
	std::vector<Token> tokenize();

private:
	std::string text;
	int position;

	Token get_token();
	bool is_token_skipable(const Token&);


	// utilities

	// Returns character of a current position
	char current();

	// Increment position and return previous position
	int next();

	// Eats all character while compare function is true
	int eat_until(int __cdecl (int));
};