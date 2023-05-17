#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Expression.h"
#include "LiteralExpression.h"
#include "ParenthesizedExpression.h"
#include "BinaryExpression.h"
#include "BadExpression.h"

#include "Lexer.h"
#include "Parser.h"

#include "Token.h"
#include "TokenType.h"


Parser::Parser(std::string text) {
	Lexer lexer = Lexer(text);
	this->tokens = lexer.tokenize();
	this->position = 0;
}

std::unique_ptr<Expression> Parser::parse() {
	std::unique_ptr<Expression> expression = this->parse_expression();
	return std::move(expression);
}

std::unique_ptr<Expression> Parser::parse_expression() {
	std::unique_ptr<Expression> expression = this->parse_term();

	return expression;
}

std::unique_ptr<Expression> Parser::parse_term() {
	std::unique_ptr<Expression> left = this->parse_factor();

	while (this->current().type == PlusToken || this->current().type == MinusToken) {
		std::unique_ptr<Token> operator_token = std::make_unique<Token>(this->next());
		std::unique_ptr<Expression> right = this->parse_factor();
		left = std::make_unique<BinaryExpression>(std::move(left), std::move(operator_token), std::move(right));
	}

	return left;
}

std::unique_ptr<Expression> Parser::parse_factor() {
	std::unique_ptr<Expression> left = this->parse_primary();

	while (this->current().type == StarToken || this->current().type == SlashToken) {
		std::unique_ptr<Token> operator_token = std::make_unique<Token>(this->next());
		std::unique_ptr<Expression> right = this->parse_primary();
		std::unique_ptr<Expression> binary_expression(new BinaryExpression(std::move(left), std::move(operator_token), std::move(right)));
		left = std::move(binary_expression); // move the BinaryExpression object to the left Expression object
	}

	return left;
}

std::unique_ptr<Expression> Parser::parse_primary() {
	if (this->current().type == NumberToken) {
		return std::make_unique<LiteralExpression>(std::make_unique<Token>(this->next()));
	}

	if (this->current().type == OpenParenthesisToken) {
		Token open = this->next();
		std::unique_ptr<Expression> expression = this->parse_expression();
		Token close = this->match(CloseParenthesisToken);
		return std::make_unique<ParenthesizedExpression>(std::make_unique<Token>(open), std::move(expression), std::make_unique<Token>(close));
	}

	Token bad_token = this->next();

	std::string message = "Bad Token. Expected primary, got " + std::to_string(bad_token.type);
	this->diagnostics.push_back(message);

	return std::make_unique<BadExpression>(std::make_unique<Token>(bad_token));
}

Token Parser::match(TokenType expression_type) {
	if (this->current().type == expression_type) {
		return this->next();
	}

	std::string message = "Bad Token. Expected " + std::to_string(expression_type) + ", but instead got " + std::to_string(this->current().type);
	this->diagnostics.push_back(message);

	return Token(expression_type, 0, "", nullptr);
}

Token Parser::current() {
	if (this->position >= this->tokens.size()) {
		return *this->tokens[this->tokens.size() - 1];
	}

	return *this->tokens[this->position];
}

Token Parser::next() {
	if (this->position >= this->tokens.size()) {
		return *this->tokens[this->tokens.size() - 1];
	}

	return *this->tokens[this->position++];
}
