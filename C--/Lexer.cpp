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
	TokenType token_type = BadToken;
	std::any value;

	switch (this->peek()) {
	case '\0':
		token_type = EndOfFileToken;
		break;
	case '+':
		token_type = PlusToken;
		this->position++;
		break;
	case '-':
		token_type = MinusToken;
		this->position++;
		break;
	case '*':
		token_type = StarToken;
		this->position++;
		break;
	case '/':
		token_type = SlashToken;
		this->position++;
		break;
	case '(':
		token_type = OpenParenthesisToken;
		this->position++;
		break;
	case ')':
		token_type = CloseParenthesisToken;
		this->position++;
		break;
	case '&':
		if (this->peek(1) == '&') {
			token_type = DoubleAmpersandToken;
			this->position += 2;
			break;
		}
		this->position++;
		break;
	case '|':
		if (this->peek(1) == '|') {
			token_type = DoublePipeToken;
			this->position += 2;
			break;
		}
		this->position++;
		break;
	case '=':
		if (this->peek(1) == '=') {
			token_type = DoubleEqualToken;
			this->position += 2;
		}
		else {
			token_type = EqualToken;
		}
		this->position++;
		break;
	case '!':
		if (this->peek(1) == '=') {
			token_type = ExclamationEqualToken;
			this->position += 2;
		}
		else {
			token_type = ExclamationToken;
		}
		this->position++;
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		this->read_number_token(start, token_type, value);
		break;
	case ' ':
	case '\t':
	case '\n':
	case '\r':
		this->read_whitespace_token(start, token_type);
		break;
	default:
		if (isalpha(this->peek())) {
			this->read_identifier_or_keyword_token(start, token_type, value);
		}
		else if (isspace(this->peek())) {
			this->read_whitespace_token(start, token_type);
		}
		else {
			this->diagnostics.report_bad_character(this->position, this->peek());
		}
		break;
	}

	std::optional<std::string> text_optional = ParserRules::get_token_text(token_type);
	std::string text;

	if (!text_optional.has_value()) {
		int length = this->position - start;
		text = this->text.substr(start, length);
	}
	else {
		text = text_optional.value();
	}


	return Token(token_type, start, text, value);
}

bool Lexer::is_token_skipable(const Token& token) {
	return token.type == WhiteSpaceToken;
}

void Lexer::read_number_token(int start, TokenType& token_type, std::any& value) {
	int length = this->eat_until(isdigit);
	std::string raw = this->text.substr(start, length);

	std::optional<int> value_optional = this->parse_int(raw);

	if (!value_optional.has_value()) {
		this->diagnostics.report_invalid_number(start, length, raw, typeid(int));
	}
	else {
		token_type = NumberToken;
		value = value_optional.value();
	}
}

void Lexer::read_whitespace_token(int start, TokenType& token_type) {
	int length = this->eat_until(isspace);
	// Is there a point of this? I didn't saw it, so it stays in comment
	// std::string raw = this->text.substr(start, length);
	token_type = WhiteSpaceToken;
}

void Lexer::read_identifier_or_keyword_token(int start, TokenType& token_type, std::any& value) {
	int length = this->eat_until(isalpha);

	std::string raw = this->text.substr(start, length);
	token_type = ParserRules::get_token_type_by_keyword(raw);

	switch (token_type)
	{
	case TrueKeywordToken:
		value = true;
		break;
	case FalseKeywordToken:
		value = false;
		break;
	}

}

char Lexer::peek(int offset) {
	int position = this->position + offset;
	if (position >= this->text.size()) {
		return '\0';
	}

	return this->text[position];
}

int Lexer::eat_until(int __cdecl compare(int)) {
	int start = this->position;

	while (compare(this->peek())) {
		this->position++;
	}

	int length = this->position - start;
	return length;
}
