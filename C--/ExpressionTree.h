#pragma once
#include <memory>
#include <string>

#include "Expression.h"
#include "Token.h"

#include "DiagnosticBag.h"

class ExpressionTree {
public:
	DiagnosticBag diagnostics;
	std::shared_ptr<Expression> root;
	std::shared_ptr<Token> end_of_file_token;

	ExpressionTree(DiagnosticBag, std::shared_ptr<Expression>, std::shared_ptr<Token>);

	static std::shared_ptr<ExpressionTree> parse(std::string);
};

