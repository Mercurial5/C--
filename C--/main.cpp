#include <iostream>
#include <vector>

#include "Parser.h"

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

int main() {
	while (true) {
		string line;
		cout << "> ";
		getline(cin, line);

		Parser parser = Parser(line);
		vector<unique_ptr<Expression>> expressions = parser.parse();

		cout << "Expressions:" << endl;
		for (unique_ptr<Expression> &expression : expressions) {
			cout << "\tExpression type - " << EXPRESSION_TYPE_MAPPER[expression->type] << endl;
		}
	}
}