#pragma once

#include <typeinfo>
#include <optional>
#include <memory>
#include <vector>

#include "TokenType.h"

#include "BoundBinaryOperatorType.h"


class BoundBinaryOperator {
	static std::vector<std::shared_ptr<BoundBinaryOperator>> operators;
public:
	TokenType token_type;
	BoundBinaryOperatorType operator_type;
	const std::type_info& left_type;
	const std::type_info& right_type;
	const std::type_info& result_type;

	BoundBinaryOperator(TokenType, BoundBinaryOperatorType, const std::type_info&);
	BoundBinaryOperator(TokenType, BoundBinaryOperatorType, const std::type_info&, const std::type_info&, const std::type_info&);

	static std::optional<std::shared_ptr<BoundBinaryOperator>> bind(TokenType, const std::type_info&, const std::type_info&);
};

