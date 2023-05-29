#pragma once
#include <ostream>
#include <string>

#include "TextSpan.h"

class Diagnostic {
public:
	TextSpan span;
	std::string message;

	Diagnostic(TextSpan, std::string);

	friend std::ostream& operator<<(std::ostream& out, const Diagnostic& diagnostic);
};

