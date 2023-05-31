#pragma once


enum ExpressionType {
	LiteralExpressionType,
	NameExpressionType,
	UnaryExpressionType,
	BinaryExpressionType,
	ParenthesizedExpressionType,
	AssignmentExpressionType,

	BadExpressionType
};
