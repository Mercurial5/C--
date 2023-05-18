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

std::shared_ptr<Expression> Parser::parse() {
	std::shared_ptr<Expression> expression = this->parse_expression();
	
	return expression;
}

std::shared_ptr<Expression> Parser::parse_expression() {
	std::shared_ptr<Expression> expression = this->parse_term();

	return expression;
}

std::shared_ptr<Expression> Parser::parse_term() {
	std::shared_ptr<Expression> left = this->parse_factor();

	while (this->current().type == PlusToken || this->current().type == MinusToken) {
		std::shared_ptr<Token> operator_token = std::make_shared<Token>(this->next());
		std::shared_ptr<Expression> right = this->parse_factor();
		left = std::make_shared<BinaryExpression>(left, operator_token, right);
	}

	return left;
}

std::shared_ptr<Expression> Parser::parse_factor() {
	std::shared_ptr<Expression> left = this->parse_primary();

	while (this->current().type == StarToken || this->current().type == SlashToken) {
		std::shared_ptr<Token> operator_token = std::make_shared<Token>(this->next());
		std::shared_ptr<Expression> right = this->parse_primary();
		std::shared_ptr<Expression> binary_expression(new BinaryExpression(left, operator_token, right));
		left = binary_expression; // move the BinaryExpression object to the left Expression object
	}

	return left;
}

std::shared_ptr<Expression> Parser::parse_primary() {
	if (this->current().type == NumberToken) {
		return std::make_shared<LiteralExpression>(std::make_shared<Token>(this->next()));
	}

	if (this->current().type == OpenParenthesisToken) {
		Token open = this->next();
		std::shared_ptr<Expression> expression = this->parse_expression();
		Token close = this->match(CloseParenthesisToken);
		return std::make_shared<ParenthesizedExpression>(std::make_shared<Token>(open), expression, std::make_shared<Token>(close));
	}

	Token bad_token = this->next();

	std::string message = "Bad Token. Expected primary, got " + std::to_string(bad_token.type);
	this->diagnostics.push_back(message);

	return std::make_shared<BadExpression>(std::make_shared<Token>(bad_token));
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
