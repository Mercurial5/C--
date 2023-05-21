#pragma once


enum ExpressionType {
	LiteralExpressionType,
	UnaryExpressionType,
	BinaryExpressionType,
	ParenthesizedExpressionType,

	BadExpressionType,
	// Expressions MUST use this ONLY when they are not assigned to a value yet. 
	EmptyExpressionType 
};
