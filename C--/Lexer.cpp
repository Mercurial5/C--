#include <string>
#include <vector>
#include <memory>


#include "Lexer.h"
#include "Token.h"

Lexer::Lexer(const std::string text) {
	this->text = text;
	this->position = 0;
}

std::vector<std::shared_ptr<Token>> Lexer::tokenize()
{
	std::vector<std::shared_ptr<Token>> tokens;
	while (this->position < this->text.size()) {
		Token token = this->get_token();
		if (this->is_token_skipable(token)) continue;

		tokens.push_back(std::make_shared<Token>(token));
	}

	Token end_of_file = Token(EndOfFileToken, this->position, "", nullptr);
	tokens.push_back(std::make_shared<Token>(end_of_file));

	return tokens;
}

Token Lexer::get_token()
{
	if (isdigit(this->current())) {
		int start = this->position;
		int length = this->eat_until(isdigit);
		std::string raw = this->text.substr(start, length);
		int value = stoi(raw);
		return Token(NumberToken, start, raw, std::make_any<int>(value));
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
	case '*': return Token(StarToken, this->next(), current, nullptr);
	case '/': return Token(SlashToken, this->next(), current, nullptr);
	case '(': return Token(OpenParenthesisToken, this->next(), current, nullptr);
	case ')': return Token(CloseParenthesisToken, this->next(), current, nullptr);
	}

	std::string message = "Bad character at position " + std::to_string(this->position);
	this->diagnostics.push_back(message);
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
