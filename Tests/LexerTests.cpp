#include <memory>
#include <string>
#include <vector>

#include "LexerTests.h"

#include <TokenType.h>
#include <Lexer.h>

void LexerTests::SetUp() {
    TokenType token_type = GetParam().first;
    std::string input = GetParam().second;

    this->lexer = std::make_shared<Lexer>(input);
}

TEST_P(LexerTests, TestToken) {
    TokenType expectedType = GetParam().first;

    std::vector<std::shared_ptr<Token>> tokens = lexer->tokenize();

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens[0]->type, expectedType);
    ASSERT_EQ(tokens[1]->type, EndOfFileToken);
}

std::vector<std::pair<TokenType, std::string>> token_data = {
    {NumberToken, "123"},
    {IdentifierToken, "variable"},
    {PlusToken, "+"},
    {MinusToken, "-"},
    {StarToken, "*"},
    {SlashToken, "/"},
    {OpenParenthesisToken, "("},
    {CloseParenthesisToken, ")"},
    {TrueKeywordToken, "truly"},
    {FalseKeywordToken, "falsy"},
    {DoubleAmpersandToken, "&&"},
    {DoublePipeToken, "||"},
    {DoubleEqualToken, "=="},
    {ExclamationEqualToken, "!="},
    {WhiteSpaceToken, " "},
    {WhiteSpaceToken, "  "},
    {WhiteSpaceToken, "\r"},
    {WhiteSpaceToken, "\n"},
    {WhiteSpaceToken, "\r\n"}
};

std::vector<std::pair<TokenType, std::string>> separators = {
    {WhiteSpaceToken, " "},
    {WhiteSpaceToken, "  "},
    {WhiteSpaceToken, "\r"},
    {WhiteSpaceToken, "\n"},
    {WhiteSpaceToken, "\r\n"}
};

INSTANTIATE_TEST_CASE_P(Tokens, LexerTests, testing::ValuesIn(token_data));
