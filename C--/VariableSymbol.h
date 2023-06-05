#pragma once

#include <typeinfo>
#include <string>

class VariableSymbol {
public:
	std::string name;
	const std::type_info* type;

	VariableSymbol(std::string, const std::type_info&);
};

