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

#include "ParserRules.h"


Parser::Parser(std::string text) {
	Lexer lexer = Lexer(text);
	this->tokens = lexer.tokenize();
	this->position = 0;
}

std::unique_ptr<Expression> Parser::parse() {
	std::unique_ptr<Expression> expression = this->parse_expression();
	return std::move(expression);
}

std::unique_ptr<Expression> Parser::parse_expression(int parent_precedence) {
	std::unique_ptr<Expression> left = this->parse_primary();

	while (true) {
		int precedence = ParserRules::get_binary_operator_precedence(this->current().type);

		if (precedence == 0 || precedence <= parent_precedence) {
			break;
		}

		std::unique_ptr<Token> operator_token = std::make_unique<Token>(this->next());
		std::unique_ptr<Expression> right = this->parse_expression(precedence);

		std::unique_ptr<Expression> binary_expression(new BinaryExpression(std::move(left), std::move(operator_token), std::move(right)));
		left = std::move(binary_expression);
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
