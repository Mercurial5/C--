#include <typeinfo>
#include <memory>
#include <optional>

#include "BoundBinaryOperator.h"

#include "BoundBinaryOperatorType.h"

#include "TokenType.h"


std::vector<std::shared_ptr<BoundBinaryOperator>> BoundBinaryOperator::operators = {
	std::make_shared<BoundBinaryOperator>(PlusToken, Addition, typeid(int)),
	std::make_shared<BoundBinaryOperator>(PlusToken, Addition, typeid(int), typeid(bool), typeid(int)),
	std::make_shared<BoundBinaryOperator>(PlusToken, Addition, typeid(bool), typeid(int), typeid(int)),
	std::make_shared<BoundBinaryOperator>(PlusToken, Addition, typeid(bool), typeid(bool), typeid(int)),

	std::make_shared<BoundBinaryOperator>(MinusToken, Subtraction, typeid(int)),
	std::make_shared<BoundBinaryOperator>(MinusToken, Subtraction, typeid(int), typeid(bool), typeid(int)),
	std::make_shared<BoundBinaryOperator>(MinusToken, Subtraction, typeid(bool), typeid(int), typeid(int)),
	std::make_shared<BoundBinaryOperator>(MinusToken, Subtraction, typeid(bool), typeid(bool), typeid(int)),

	std::make_shared<BoundBinaryOperator>(StarToken, Multiplication, typeid(int)),
	std::make_shared<BoundBinaryOperator>(StarToken, Multiplication, typeid(int), typeid(bool), typeid(int)),
	std::make_shared<BoundBinaryOperator>(StarToken, Multiplication, typeid(bool), typeid(int), typeid(int)),
	std::make_shared<BoundBinaryOperator>(StarToken, Multiplication, typeid(bool), typeid(bool), typeid(int)),

	std::make_shared<BoundBinaryOperator>(SlashToken, Division, typeid(int)),
	std::make_shared<BoundBinaryOperator>(SlashToken, Division, typeid(int), typeid(bool), typeid(int)),
	std::make_shared<BoundBinaryOperator>(SlashToken, Division, typeid(bool), typeid(int), typeid(int)),
	std::make_shared<BoundBinaryOperator>(SlashToken, Division, typeid(bool), typeid(bool), typeid(int)),

	std::make_shared<BoundBinaryOperator>(DoubleEqualToken, Equal, typeid(int), typeid(bool)),
	std::make_shared<BoundBinaryOperator>(ExclamationEqualToken, NotEqual, typeid(int), typeid(bool)),

	std::make_shared<BoundBinaryOperator>(DoubleAmpersandToken, LogicalAnd, typeid(bool)),
	std::make_shared<BoundBinaryOperator>(DoublePipeToken, LogicalOr, typeid(bool)),
	std::make_shared<BoundBinaryOperator>(DoublePipeToken, LogicalOr, typeid(bool)),
	std::make_shared<BoundBinaryOperator>(DoubleEqualToken, Equal, typeid(bool)),
	std::make_shared<BoundBinaryOperator>(ExclamationEqualToken, NotEqual, typeid(bool)),
};

BoundBinaryOperator::BoundBinaryOperator(TokenType token_type, BoundBinaryOperatorType bound_binary_operator_type, const std::type_info& type) :
	BoundBinaryOperator(token_type, bound_binary_operator_type, type, type, type) {}

BoundBinaryOperator::BoundBinaryOperator(TokenType token_type, BoundBinaryOperatorType bound_binary_operator_type, const std::type_info& operator_type,
	const std::type_info& result_type) :
	BoundBinaryOperator(token_type, bound_binary_operator_type, operator_type, operator_type, result_type) {}

BoundBinaryOperator::BoundBinaryOperator(TokenType token_type, BoundBinaryOperatorType bound_binary_operator_type, const std::type_info& left_type,
	const std::type_info& right_type, const std::type_info& result_type) :
	token_type(token_type), operator_type(bound_binary_operator_type), left_type(left_type), right_type(right_type), result_type(result_type) {}

std::optional<std::shared_ptr<BoundBinaryOperator>> BoundBinaryOperator::bind(TokenType token_type, const std::type_info& left_type, const std::type_info& right_type)
{
	for (std::shared_ptr<BoundBinaryOperator> op : BoundBinaryOperator::operators) {
		if (op->token_type == token_type && op->left_type == left_type && op->right_type == right_type) {
			return op;
		}
	}

	return std::nullopt;
}
