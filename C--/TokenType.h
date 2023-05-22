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
	ExclamationToken,
	AmpersandAmpersandToken,
	PipePipeToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
