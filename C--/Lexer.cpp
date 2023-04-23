#include "Lexer.h"

Lexer::Lexer(const std::string text) {
	this->text = text;
	this->position = 0;
}

std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> tokens;
	while (this->position < this->text.size()) {
		Token token = this->get_token();
		if (this->is_token_skipable(token)) continue;

		tokens.push_back(token);
	}

	tokens.push_back(Token(EndOfFileToken, this->position, "", nullptr));

	return tokens;
}

Token Lexer::get_token()
{
	if (isdigit(this->current())) {
		int start = this->position;
		int length = this->eat_until(isdigit);
		std::string raw = this->text.substr(start, length);
		int value = stoi(raw);
		return Token(NumericToken, start, raw, &value);
	}

	if (isspace(this->current())) {
		int start = this->position;
		int length = this->eat_until(isspace);
		// Is there a point of this? I didn't saw it, so it stays in comment
		// std::string raw = this->text.substr(start, length);
		return Token(WhiteSpaceToken, start, "", nullptr);
	}

	char current = this->current();
	switch (current) {
	case '+': return Token(PlusToken, this->next(), current, nullptr);
	case '-': return Token(MinusToken, this->next(), current, nullptr);
	case '*': return Token(StartToken, this->next(), current, nullptr);
	case '/': return Token(SlashToken, this->next(), current, nullptr);
	case '(': return Token(OpenParenthesisToken, this->next(), current, nullptr);
	case ')': return Token(CloseParenthesisToken, this->next(), current, nullptr);
	}

	return Token(BadToken, this->next(), current, nullptr);
}

bool Lexer::is_token_skipable(const Token& token)
{
	return token.type == WhiteSpaceToken;
}

char Lexer::current()
{
	return this->text[this->position];
}

int Lexer::next() {
	return this->position++;
}

int Lexer::eat_until(int __cdecl compare(int)) {
	int start = this->position;

	while (compare(this->current())) {
		this->next();
	}

	int length = this->position - start;
	return length;
}
