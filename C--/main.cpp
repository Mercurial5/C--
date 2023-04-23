#include <iostream>
#include <vector>

#include "Lexer.h"

#include "TokenType.h"
#include "Token.h"

using namespace std;


// For log purposes only. Will remove later
map<int, string> TOKEN_TYPE_MAPPER = {
	{NumericToken, "NumericToken"},
	{PlusToken, "PlusToken"},
	{MinusToken, "MinusToken"},
	{StartToken, "StartToken"},
	{SlashToken, "SlashToken"},
	{OpenParenthesisToken, "OpenParenthesisToken"},
	{CloseParenthesisToken, "CloseParenthesisToken"},
	{WhiteSpaceToken, "WhiteSpaceToken"},
	{EndOfFileToken, "EndOfFileToken"},
	{BadToken, "BadToken"}
};


int main() {
	while (true) {
		string line;
		cout << "> ";
		getline(cin, line);

		Lexer lexer = Lexer(line);
		vector<Token> tokens = lexer.tokenize();

		cout << "Tokens:" << endl;
		for (Token token : tokens) {
			cout << "\tToken type - " << TOKEN_TYPE_MAPPER[token.type] << endl;
			cout << "\tToken position - " << token.position << endl;
			cout << "\tToken raw string - " << token.raw << endl << endl;
		}
	}
}