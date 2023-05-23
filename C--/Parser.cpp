#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Expression.h"

#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"
#include "BadExpression.h"

#include "Lexer.h"
#include "Parser.h"

#include "Token.h"
#include "TokenType.h"

#include "ParserRules.h"


Parser::Parser(std::string text) {
	Lexer lexer = Lexer(text);
	this->tokens = lexer.tokenize();
	this->diagnostics = lexer.diagnostics;
	this->position = 0;
}

std::shared_ptr<Expression> Parser::parse() {
	std::shared_ptr<Expression> expression = this->parse_expression();

	return expression;
}

std::shared_ptr<Expression> Parser::parse_expression(int parent_precedence) {
	int unary_operator_precedence = ParserRules::get_unary_operator_precedence(this->current().type);

	std::shared_ptr<Expression> left;
	if (unary_operator_precedence >= parent_precedence && unary_operator_precedence != 0) {
		std::shared_ptr<Token> operator_token = std::make_shared<Token>(this->next());
		std::shared_ptr<Expression> expression = this->parse_expression(unary_operator_precedence);
		std::shared_ptr<Expression> unary_expression(new UnaryExpression(operator_token, expression));
		left = unary_expression;
	}
	else {
		left = this->parse_primary();
	}


	while (true) {
		int precedence = ParserRules::get_binary_operator_precedence(this->current().type);

		if (precedence == 0 || precedence <= parent_precedence) {
			break;
		}

		std::shared_ptr<Token> operator_token = std::make_shared<Token>(this->next());
		std::shared_ptr<Expression> right = this->parse_expression(precedence);

		std::shared_ptr<Expression> binary_expression(new BinaryExpression(left, operator_token, right));
		left = binary_expression;
	}

	return left;
}

std::shared_ptr<Expression> Parser::parse_primary() {
	if (this->current().type == NumberToken || this->current().type == TrueKeywordToken || this->current().type == FalseKeywordToken) {
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
