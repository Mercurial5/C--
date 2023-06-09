#include "VariableSymbol.h"

VariableSymbol::VariableSymbol(std::string name, const std::type_info& type) {
	this->name = name;
	this->type = &type;
}
