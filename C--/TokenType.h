#pragma once

#include <map>
#include <string>

enum TokenType {
	NumericToken,

	PlusToken,
	MinusToken,
	StartToken,
	SlashToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
