#include <algorithm>
#include <memory>
#include <string>
#include <map>
#include <any>

#include "VariableSymbol.h"

VariableSymbol::VariableSymbol(std::string name, const std::type_info& type) {
	this->name = name;
	this->type = &type;
}

std::map<std::shared_ptr<VariableSymbol>, std::any>::iterator VariableSymbol::find(std::map<std::shared_ptr<VariableSymbol>, std::any>* variables, std::string name) {
	auto finder = [&name](std::pair<std::shared_ptr<VariableSymbol>, std::any> i) { return i.first->name == name; };

	return std::find_if(begin(*variables), end(*variables), finder);
}
