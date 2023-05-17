#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Expression.h"

#include "Token.h"
#include "TokenType.h"

class Parser {
	std::vector<std::unique_ptr<Token>> tokens;
	int position;
public:
	std::vector<std::string> diagnostics;

	Parser(std::string);
	std::unique_ptr<Expression> parse();

private:
	std::unique_ptr<Expression> parse_expression(int = 0);
	std::unique_ptr<Expression> parse_primary();

	Token match(TokenType);
	Token current();
	Token next();

};