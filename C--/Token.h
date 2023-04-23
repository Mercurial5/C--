#pragma once

#include <string>

#include "TokenType.h"

class Token {
public:
	TokenType type;
	int position;
	std::string raw;
	void* value;

	Token(TokenType, int, std::string, void*);
	Token(TokenType, int, char, void*);
};
