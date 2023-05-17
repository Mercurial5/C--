#pragma once

#include "TokenType.h"

class ParserRules
{
public:
	static int get_binary_operator_precedence(TokenType);
};

