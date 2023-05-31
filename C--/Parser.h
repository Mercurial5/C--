#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ExpressionTree.h"
#include "Expression.h"

#include "Token.h"
#include "TokenType.h"

#include "DiagnosticBag.h"

class Parser {
	std::vector<std::shared_ptr<Token>> tokens;
	int position;
public:
	DiagnosticBag diagnostics;

	Parser(std::string);
	std::shared_ptr<ExpressionTree> parse();

private:
	std::shared_ptr<Expression> parse_expression();
	std::shared_ptr<Expression> parse_assignment_expression();
	std::shared_ptr<Expression> parse_binary_expression(int = 0);
	std::shared_ptr<Expression> parse_primary();

	Token peek(int = 0);
	Token match(TokenType);
	Token current();
	Token next();

};