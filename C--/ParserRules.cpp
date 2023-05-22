#include "ParserRules.h"

#include "TokenType.h"

int ParserRules::get_unary_operator_precedence(TokenType token_type) {
	switch (token_type)
	{
	case PlusToken:
	case MinusToken:
		return 3;

	default:
		return 0;
	}
}

int ParserRules::get_binary_operator_precedence(TokenType token_type) {
	switch (token_type)
	{
	case StarToken:
	case SlashToken:
		return 2;

	case PlusToken:
	case MinusToken:
		return 1;

	default:
		return 0;
	}
}

TokenType ParserRules::get_token_type_by_keyword(std::string keyword) {
	if (keyword == "truly") {
		return TrueKeywordToken;
	}
	else if (keyword == "falsy") {
		return FalseKeywordToken;
	}

	return IdentifierToken;
}
