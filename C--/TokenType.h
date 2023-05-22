#pragma once

#include <map>
#include <string>

enum TokenType {
	NumberToken,

	TrueKeywordToken,
	FalseKeywordToken,

	IdentifierToken,


	// Operators
	PlusToken,
	MinusToken,
	StarToken,
	SlashToken,

	// Logical operators
	ExclamationMarkToken,
	AmpersandAmpersandToken,
	PipePipeToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
