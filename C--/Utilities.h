#pragma once

#include <string>
#include <memory>
#include <map>

#include "ExpressionType.h"
#include "Expression.h"

#include "TokenType.h"

#include "BoundUnaryOperatorType.h"
#include "BoundBinaryOperatorType.h"

class Utilities
{

public:
	static std::string token_name(TokenType);
	static std::string expression_name(ExpressionType);
	static std::string bound_unary_operator_name(BoundUnaryOperatorType);
	static std::string bound_binary_operator_name(BoundBinaryOperatorType);
	static void print_expression(std::shared_ptr<Expression>, std::string = "");

private:
	static std::map<int, std::string> TOKEN_TYPE_MAPPER;
	static std::map<int, std::string> EXPRESSION_TYPE_MAPPER;
	static std::map<int, std::string> BOUND_UNARY_OPERATOR_TYPE_MAPPER;
	static std::map<int, std::string> BOUND_BINARY_OPERATOR_TYPE_MAPPER;

};

