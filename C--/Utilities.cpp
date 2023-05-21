#include <string>
#include <map>

#include "Utilities.h"


std::map<int, std::string> Utilities::TOKEN_TYPE_MAPPER = {
		{NumberToken, "NumberToken"},
		{PlusToken, "PlusToken"},
		{MinusToken, "MinusToken"},
		{StarToken, "StarToken"},
		{SlashToken, "SlashToken"},
		{OpenParenthesisToken, "OpenParenthesisToken"},
		{CloseParenthesisToken, "CloseParenthesisToken"},
		{WhiteSpaceToken, "WhiteSpaceToken"},
		{EndOfFileToken, "EndOfFileToken"},
		{BadToken, "BadToken"}
};

std::map<int, std::string> Utilities::EXPRESSION_TYPE_MAPPER = {
		{ LiteralExpressionType, "LiteralExpressionType" },
		{ UnaryExpressionType, "UnaryExpressionType" },
		{ BinaryExpressionType, "BinaryExpressionType" },
		{ ParenthesizedExpressionType, "ParenthesizedExpressionType" },
		{ BadExpressionType, "BadExpressionType" }
};

std::string Utilities::token_name(TokenType token_type) {
	return Utilities::TOKEN_TYPE_MAPPER[token_type];
}

std::string Utilities::expression_name(ExpressionType expression_type) {
	return Utilities::EXPRESSION_TYPE_MAPPER[expression_type];
}
