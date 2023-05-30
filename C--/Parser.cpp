#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "ExpressionTree.h"
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
	this->diagnostics.extend(lexer.diagnostics);
	this->position = 0;
}

std::shared_ptr<ExpressionTree> Parser::parse() {
	std::shared_ptr<Expression> root = this->parse_expression();
	Token end_of_file_token = this->match(EndOfFileToken);

	return std::make_shared<ExpressionTree>(this->diagnostics, root, std::make_shared<Token>(end_of_file_token));
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
	switch (this->current().type) {
	case TrueKeywordToken:
	case FalseKeywordToken:
		return std::make_shared<LiteralExpression>(std::make_shared<Token>(this->next()));

	case OpenParenthesisToken: {
		Token open = this->next();
		std::shared_ptr<Expression> expression = this->parse_expression();
		Token close = this->match(CloseParenthesisToken);
		return std::make_shared<ParenthesizedExpression>(std::make_shared<Token>(open), expression, std::make_shared<Token>(close));
	}

	default: {
		Token current = this->match(NumberToken);
		return std::make_shared<LiteralExpression>(std::make_shared<Token>(current));
	}
	}
}

Token Parser::match(TokenType expression_type) {
	if (this->current().type == expression_type) {
		return this->next();
	}

	this->diagnostics.report_unexpected_token(this->current().span, this->current().type, expression_type);
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
