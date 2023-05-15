#include <iostream>
#include <vector>

#include "Parser.h"
#include "Evaluator.h"

#include "ExpressionType.h"
#include "Expression.h"
#include "NumberExpression.h"
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
	{ NumberExpressionType, "NumberExpressionType" },
	{ BinaryExpressionType, "BinaryExpressionType" },
	{ ParenthesizedExpressionType, "ParenthesizedExpressionType" },
	{ BadExpressionType, "BadExpressionType" }
};

void print_expression(unique_ptr<Expression> expression, string indent = "") {
	cout << indent << EXPRESSION_TYPE_MAPPER[expression->type] << ':' << endl;
	indent += '\t';

	if (expression->type == NumberExpressionType) {
		NumberExpression* number_expression_raw_ptr = dynamic_cast<NumberExpression*>(expression.get());

		// Only if number expression is not nullptr (Dynamic cast was successfull)
		if (number_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			unique_ptr<NumberExpression> number_expression(number_expression_raw_ptr);
			cout << indent << number_expression->value << endl;
		}
	}
	else if (expression->type == BinaryExpressionType) {
		BinaryExpression* binary_expression_raw_ptr = dynamic_cast<BinaryExpression*>(expression.get());
		
		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (binary_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			unique_ptr<BinaryExpression> binary_expression(binary_expression_raw_ptr);
			print_expression(std::move(binary_expression->left), indent);
			cout << indent << "Operator Token:" << endl;
			cout << indent + '\t' << binary_expression->operator_token->raw << endl;
			print_expression(std::move(binary_expression->right), indent);
		}
	}
	else if (expression->type == ParenthesizedExpressionType) {
		ParenthesizedExpression* parenthesized_expression_raw_ptr = dynamic_cast<ParenthesizedExpression*>(expression.get());

		// Only if parenthesized expression is not nullptr (Dynamic cast was successfull)
		if (parenthesized_expression_raw_ptr) {
			// Remove pointer to the object to create new unique_ptr
			expression.release();

			unique_ptr<ParenthesizedExpression> parenthesized_expression(parenthesized_expression_raw_ptr);
			print_expression(std::move(parenthesized_expression->expression), indent);
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
		unique_ptr<Expression> root = parser.parse();

		if (parser.diagnostics.empty()) {
			Evaluator evaluator;

			cout << "= " << evaluator.evaluate_expression(move(root)) << endl;
		}
		else {
			for (auto& diagnostic : parser.diagnostics) {
				cout << diagnostic << endl;
			}
		}
		
	}
}