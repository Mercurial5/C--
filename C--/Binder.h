#pragma once

#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include <optional>

#include "BoundExpression.h"
#include "BoundUnaryOperatorType.h"
#include "BoundBinaryOperatorType.h"

#include "ExpressionTree.h"
#include "Expression.h"
#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"

#include "Token.h"

#include "DiagnosticBag.h"

class Binder {
public:
	DiagnosticBag diagnostics;
	std::shared_ptr<BoundExpression> bind(std::shared_ptr<Expression>);
	Binder(DiagnosticBag);

private:
	std::shared_ptr<BoundExpression> bind_expression(std::shared_ptr<Expression>);
	std::shared_ptr<BoundExpression> bind_literal_expression(std::shared_ptr<LiteralExpression>);
	std::shared_ptr<BoundExpression> bind_unary_expression(std::shared_ptr<UnaryExpression>);
	std::shared_ptr<BoundExpression> bind_binary_expression(std::shared_ptr<BinaryExpression>);
	std::shared_ptr<BoundExpression> bind_parenthesized_expression(std::shared_ptr<ParenthesizedExpression>);
	
	template <typename CastTo, typename CastFrom>
	std::shared_ptr<CastTo> cast(std::shared_ptr<CastFrom> obj) {
		return std::dynamic_pointer_cast<CastTo>(obj);
	}

};