#pragma once

#include <string>
#include <any>

#include "TokenType.h"

class Token {
public:
	TokenType type;
	int position;
	std::string raw;
	std::any value;

	Token(TokenType, int, std::string, std::any);
	Token(TokenType, int, char, std::any);
};
