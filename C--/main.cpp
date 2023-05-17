#include <iostream>
#include <vector>

#include "Parser.h"
#include "Evaluator.h"

#include "ExpressionType.h"
#include "Expression.h"
#include "LiteralExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"

#include "TokenType.h"
#include "Token.h"

using namespace std;


// For log purposes only. Will remove later
map<int, string> TOKEN_TYPE_MAPPER = {
	{NumberToken, "NumberToken"},
	{PlusToken, "PlusToken"},
	{MinusToken, "MinusToken"},
	{StarToken, "StarToken"},
	{SlashToken, "SlashToken"},
	{OpenParenthesisToken, "OpenParenthesisToken"},
	{CloseParenthesisToken, "CloseParenthesisToken"},
	{WhiteSpaceToken, "WhiteSpaceToken"},
	{EndOfFileToken, "EndOfFileToken"},
	{BadToken, "BadToken"}
};

map<int, string> EXPRESSION_TYPE_MAPPER = {
	{ LiteralExpressionType, "LiteralExpressionType" },
	{ BinaryExpressionType, "BinaryExpressionType" },
	{ ParenthesizedExpressionType, "ParenthesizedExpressionType" },
	{ BadExpressionType, "BadExpressionType" }
};

void print_expression(Expression* expression, string indent = "") {
	cout << indent << EXPRESSION_TYPE_MAPPER[expression->type] << ':' << endl;
	indent += '\t';

	if (expression->type == LiteralExpressionType) {
		LiteralExpression* number_expression = dynamic_cast<LiteralExpression*>(expression);

		// Only if number expression is not nullptr (Dynamic cast was successfull)
		if (number_expression) {
			cout << indent << std::any_cast<int>(number_expression->value) << endl;
		}
	}
	else if (expression->type == BinaryExpressionType) {
		BinaryExpression* binary_expression = dynamic_cast<BinaryExpression*>(expression);
		
		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (binary_expression) {
			print_expression(binary_expression->left.get(), indent);
			cout << indent << "Operator Token:" << endl;
			cout << indent + '\t' << binary_expression->operator_token->raw << endl;
			print_expression(binary_expression->right.get(), indent);
		}
	}
	else if (expression->type == ParenthesizedExpressionType) {
		ParenthesizedExpression* parenthesized_expression = dynamic_cast<ParenthesizedExpression*>(expression);

		// Only if parenthesized expression is not nullptr (Dynamic cast was successfull)
		if (parenthesized_expression) {
			print_expression(parenthesized_expression->expression.get(), indent);
		}
	}
	else if (expression->type == BadExpressionType) {
		cout << indent << "Bad Expression." << endl;
	}
}


int main() {
	while (true) {
		string line;
		cout << "> ";
		getline(cin, line);

		Parser parser = Parser(line);
		std::shared_ptr<Expression> root = parser.parse();

		if (parser.diagnostics.empty()) {
			Evaluator evaluator;

			print_expression(root.get());

			cout << "= " << evaluator.evaluate_expression(root.get()) << endl;
		}
		else {
			for (auto& diagnostic : parser.diagnostics) {
				cout << diagnostic << endl;
			}
		}
		
	}
}