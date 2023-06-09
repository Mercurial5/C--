#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ExpressionTree.h"
#include "Expression.h"
#include "LiteralExpression.h"
#include "ParenthesizedExpression.h"
#include "NameExpression.h"

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

	std::shared_ptr<LiteralExpression> parse_boolean_literal_expression();
	std::shared_ptr<LiteralExpression> parse_number_literal_expression();
	std::shared_ptr<ParenthesizedExpression> parse_parenthesized_expression();
	std::shared_ptr<NameExpression> parse_name_expression();

	Token peek(int = 0);
	Token match(TokenType);
	Token current();
	Token next();

};