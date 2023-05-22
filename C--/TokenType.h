#pragma once

#include <map>
#include <string>

enum TokenType {
	NumberToken,

	TrueKeywordToken,
	FalseKeywordToken,

	IdentifierToken,

	PlusToken,
	MinusToken,
	StarToken,
	SlashToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
