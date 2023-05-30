#include "Token.h"

#include "TextSpan.h"

Token::Token(TokenType type, int position, std::string raw, std::any value) : span(position, raw.size()) {
	this->type = type;
	this->position = position;
	this->raw = raw;
	this->value = value;
}

Token::Token(TokenType type, int position, char raw, std::any) : Token(type, position, (std::string() + raw), value) {}
