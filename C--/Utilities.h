#pragma once

#include <map>
#include <string>

#include "ExpressionType.h"
#include "TokenType.h"

class Utilities
{

public:
	static std::string token_name(TokenType);
	static std::string expression_name(ExpressionType);

private:
	static std::map<int, std::string> TOKEN_TYPE_MAPPER;
	static std::map<int, std::string> EXPRESSION_TYPE_MAPPER;

};

