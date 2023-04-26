#pragma once

#include <map>
#include <string>

enum TokenType {
	NumberToken,

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
