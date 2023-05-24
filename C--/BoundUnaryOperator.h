#pragma once

#include <typeinfo>
#include <optional>
#include <vector>

#include "TokenType.h"
#include "BoundUnaryOperatorType.h"


class BoundUnaryOperator {
	static std::vector<std::shared_ptr<BoundUnaryOperator>> operators;
public:
	TokenType token_type;
	BoundUnaryOperatorType operator_type;
	const std::type_info& operand_type;
	const std::type_info& result_type;

	BoundUnaryOperator(TokenType, BoundUnaryOperatorType, const std::type_info&);
	BoundUnaryOperator(TokenType, BoundUnaryOperatorType, const std::type_info&, const std::type_info&);
	static std::optional<std::shared_ptr<BoundUnaryOperator>> bind(TokenType, const std::type_info&);
};

