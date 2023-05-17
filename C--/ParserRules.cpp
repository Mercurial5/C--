#include "ParserRules.h"

#include "TokenType.h"

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