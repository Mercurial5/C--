#include "Token.h"

Token::Token(TokenType type, int position, std::string raw, void* value) {
	this->type = type;
	this->position = position;
	this->raw = raw;
	this->value = value;
}

Token::Token(TokenType type, int position, char raw, void* value) : Token(type, position, (std::string() + raw), value) {}
