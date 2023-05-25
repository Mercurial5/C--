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
	EqualsEqualsToken,
	ExclamationEqualsToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
