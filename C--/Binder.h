#pragma once

#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include <optional>

#include "BoundExpression.h"
#include "BoundUnaryOperatorType.h"
#include "BoundBinaryOperatorType.h"

#include "Expression.h"
#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

#include "Token.h"

#include "DiagnosticBag.h"

class Binder {
public:
	DiagnosticBag diagnostics;
	Binder(std::string);
	std::shared_ptr<BoundExpression> bind();

private:
	std::shared_ptr<Expression> root;

	std::shared_ptr<BoundExpression> bind_expression(std::shared_ptr<Expression>);
	std::shared_ptr<BoundExpression> bind_literal_expression(std::shared_ptr<LiteralExpression>);
	std::shared_ptr<BoundExpression> bind_unary_expression(std::shared_ptr<UnaryExpression>);
	std::shared_ptr<BoundExpression> bind_binary_expression(std::shared_ptr<BinaryExpression>);
	
	template <typename CastTo, typename CastFrom>
	std::shared_ptr<CastTo> cast(std::shared_ptr<CastFrom> obj) {
		return std::dynamic_pointer_cast<CastTo>(obj);
	}

};