#pragma once

#include <optional>
#include <string>

#include "TokenType.h"

class ParserRules
{
public:
	static int get_unary_operator_precedence(TokenType);
	static int get_binary_operator_precedence(TokenType);
	static TokenType get_token_type_by_keyword(std::string);
	static std::optional<std::string> get_token_text(TokenType);
};

