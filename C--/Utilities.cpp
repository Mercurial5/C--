#include <iostream>
#include <string>
#include <map>

#include "Utilities.h"

#include "Expression.h"
#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"

#include "BoundUnaryOperatorType.h"
#include "BoundBinaryOperatorType.h"


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

std::map<int, std::string> Utilities::BOUND_UNARY_OPERATOR_TYPE_MAPPER = {
	{Identity, "Identity"},
	{Negation, "Negation"}
};

std::map<int, std::string> Utilities::BOUND_BINARY_OPERATOR_TYPE_MAPPER = {
	{Addition, "Addition"},
	{Subtraction, "Subtraction"},
	{Multiplication, "Multiplication"},
	{Division, "Division"}
};

std::string Utilities::token_name(TokenType token_type) {
	return Utilities::TOKEN_TYPE_MAPPER[token_type];
}

std::string Utilities::expression_name(ExpressionType expression_type) {
	return Utilities::EXPRESSION_TYPE_MAPPER[expression_type];
}

std::string Utilities::bound_unary_operator_name(BoundUnaryOperatorType bound_unary_operator_type)
{
	return Utilities::BOUND_UNARY_OPERATOR_TYPE_MAPPER[bound_unary_operator_type];
}

std::string Utilities::bound_binary_operator_name(BoundBinaryOperatorType bound_binary_operator_type)
{
	return Utilities::BOUND_BINARY_OPERATOR_TYPE_MAPPER[bound_binary_operator_type];
}

void Utilities::print_expression(std::shared_ptr<Expression> expression, std::string indent) {
	std::cout << indent << Utilities::expression_name(expression->type) << ':' << std::endl;
	indent += '\t';

	if (expression->type == LiteralExpressionType) {
		std::shared_ptr<LiteralExpression> literal_expression = dynamic_pointer_cast<LiteralExpression>(expression);

		// Only if number expression is not nullptr (Dynamic cast was successfull)
		if (literal_expression) {
			std::cout << indent << literal_expression->token->raw << std::endl;
		}
	}
	else if (expression->type == UnaryExpressionType) {
		std::shared_ptr<UnaryExpression> unary_expression = dynamic_pointer_cast<UnaryExpression>(expression);

		if (unary_expression) {
			std::cout << indent << "Operator Token:" << std::endl;
			std::cout << indent << '\t' << unary_expression->operator_token->raw << std::endl;
			print_expression(unary_expression->expression, indent);
		}
	}
	else if (expression->type == BinaryExpressionType) {
		std::shared_ptr<BinaryExpression> binary_expression = dynamic_pointer_cast<BinaryExpression>(expression);

		// Only if binary expression is not nullptr (Dynamic cast was successfull)
		if (binary_expression) {
			print_expression(binary_expression->left, indent);
			std::cout << indent << "Operator Token:" << std::endl;
			std::cout << indent + '\t' << binary_expression->operator_token->raw << std::endl;
			print_expression(binary_expression->right, indent);
		}
	}
	else if (expression->type == ParenthesizedExpressionType) {
		std::shared_ptr<ParenthesizedExpression> parenthesized_expression = dynamic_pointer_cast<ParenthesizedExpression>(expression);

		// Only if parenthesized expression is not nullptr (Dynamic cast was successfull)
		if (parenthesized_expression) {
			print_expression(parenthesized_expression->expression, indent);
		}
	}
	else if (expression->type == BadExpressionType) {
		std::cout << indent << "Bad Expression." << std::endl;
	}
}
