#include <typeinfo>
#include <memory>
#include <vector>

#include "BoundUnaryOperator.h"
#include "BoundUnaryOperatorType.h"

#include "TokenType.h"

std::vector<std::shared_ptr<BoundUnaryOperator>> BoundUnaryOperator::operators = {
	std::make_shared<BoundUnaryOperator>(PlusToken, Identity, typeid(int)),
	std::make_shared<BoundUnaryOperator>(MinusToken, Identity, typeid(int)),

	std::make_shared<BoundUnaryOperator>(ExclamationToken, LogicalNegation, typeid(bool))
};

BoundUnaryOperator::BoundUnaryOperator(TokenType token_type, BoundUnaryOperatorType bound_unary_operator, const std::type_info& type) :
	BoundUnaryOperator(token_type, bound_unary_operator, type, type) {}

BoundUnaryOperator::BoundUnaryOperator(TokenType token_type, BoundUnaryOperatorType bound_unary_operator, const std::type_info& operand_type,
	const std::type_info& result_type) : token_type(token_type), operator_type(bound_unary_operator), operand_type(operand_type), result_type(result_type) {}

std::optional<std::shared_ptr<BoundUnaryOperator>> BoundUnaryOperator::bind(TokenType token_type, const std::type_info& operand_type)
{
	for (const std::shared_ptr<BoundUnaryOperator>& op : BoundUnaryOperator::operators) {
		if (op->token_type == token_type && op->operand_type == operand_type) {
			return op;
		}
	}

	return std::nullopt;
}
