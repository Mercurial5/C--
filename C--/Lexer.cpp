#include <string>
#include <vector>
#include <memory>

#include "Lexer.h"
#include "Token.h"

#include "ParserRules.h"

#include "TextSpan.h"

Lexer::Lexer(const std::string text) {
	this->text = text;
	this->position = 0;
}

std::vector<std::shared_ptr<Token>> Lexer::tokenize() {
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

std::optional<int> Lexer::parse_int(std::string str) {
	try {
		int value = stoi(str);
		return value;
	}
	catch (std::out_of_range) {
		return std::nullopt;
	}
}

Token Lexer::get_token() {
	int start = this->position;
	if (isdigit(this->peek())) {
		int length = this->eat_until(isdigit);
		std::string raw = this->text.substr(start, length);

		std::optional<int> value_optional = this->parse_int(raw);

		int value = 0;
		if (!value_optional.has_value()) {
			this->diagnostics.report_invalid_number(start, length, raw, typeid(int));
		}
		else {
			value = value_optional.value();
		}

		return Token(NumberToken, start, raw, std::make_any<int>(value));
	}

	if (isspace(this->peek())) {
		int length = this->eat_until(isspace);
		// Is there a point of this? I didn't saw it, so it stays in comment
		// std::string raw = this->text.substr(start, length);
		return Token(WhiteSpaceToken, start, "", nullptr);
	}

	if (isalpha(this->peek())) {
		int length = this->eat_until(isalpha);

		std::string raw = this->text.substr(start, length);
		TokenType type = ParserRules::get_token_type_by_keyword(raw);
		bool value = type == TrueKeywordToken;
		return Token(type, start, raw, std::make_any<bool>(value));
	}

	char current = this->peek();
	switch (current) {
	case '+': return Token(PlusToken, this->next(), current, nullptr);
	case '-': return Token(MinusToken, this->next(), current, nullptr);
	case '*': return Token(StarToken, this->next(), current, nullptr);
	case '/': return Token(SlashToken, this->next(), current, nullptr);
	case '(': return Token(OpenParenthesisToken, this->next(), current, nullptr);
	case ')': return Token(CloseParenthesisToken, this->next(), current, nullptr);
	case '!': {
		if (this->peek(1) == '=') {
			this->next(); this->next();
			return Token(ExclamationEqualToken, start, "!=", nullptr);
		}
		else {
			return Token(ExclamationToken, this->next(), current, nullptr);
		}
	}
	case '&': {
		if (this->peek(1) == '&') {
			this->next(); this->next();
			return Token(DoubleAmpersandToken, start, "&&", nullptr);
		}
		break;
	}
	case '|': {
		if (this->peek(1) == '|') {
			this->next(); this->next();
			return Token(DoublePipeToken, start, "||", nullptr);
		}
		break;
	}
	case '=': {
		if (this->peek(1) == '=') {
			this->next(); this->next();
			return Token(DoubleEqualToken, start, "==", nullptr);
		}
		else {
			return Token(EqualToken, this->next(), current, nullptr);
		}
	}
	}

	this->diagnostics.report_bad_character(this->position, current);
	return Token(BadToken, this->next(), current, nullptr);
}

bool Lexer::is_token_skipable(const Token& token) {
	return token.type == WhiteSpaceToken;
}

char Lexer::peek(int offset) {
	int position = this->position + offset;
	if (position >= this->text.size()) {
		return '\0';
	}

	return this->text[position];
}

int Lexer::next() {
	return this->position++;
}

int Lexer::eat_until(int __cdecl compare(int)) {
	int start = this->position;

	while (compare(this->peek())) {
		this->next();
	}

	int length = this->position - start;
	return length;
}
