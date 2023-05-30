#include <memory>

#include "ExpressionTree.h"
#include "Expression.h"
#include "Token.h"

#include "DiagnosticBag.h"

#include "Parser.h"

ExpressionTree::ExpressionTree(DiagnosticBag diagnostics, std::shared_ptr<Expression> root, std::shared_ptr<Token> end_of_file_token) {
	this->diagnostics.extend(diagnostics);
	this->root = root;
	this->end_of_file_token = end_of_file_token;
}

std::shared_ptr<ExpressionTree> ExpressionTree::parse(std::string line) {
	Parser parser(line);

	return parser.parse();
}
