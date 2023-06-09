#pragma once

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>
#include <utility>

#include <TokenType.h>
#include <Lexer.h>

class LexerTests : public testing::TestWithParam<std::pair<TokenType, std::string>> {
public:
    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<Lexer> pair_lexer;

    void SetUp() override;
    //void SetUpPairs() override;
};
