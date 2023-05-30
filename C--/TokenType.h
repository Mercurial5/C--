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
	EqualToken,

	// Logical operators
	ExclamationToken,
	DoubleAmpersandToken,
	DoublePipeToken,
	DoubleEqualToken,
	ExclamationEqualToken,

	OpenParenthesisToken,
	CloseParenthesisToken,

	WhiteSpaceToken,
	EndOfFileToken,

	BadToken
};
