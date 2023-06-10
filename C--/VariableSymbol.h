#pragma once

#include <typeinfo>
#include <memory>
#include <string>
#include <map>
#include <any>

class VariableSymbol {
public:
	std::string name;
	const std::type_info* type;

	VariableSymbol(std::string, const std::type_info&);
	static std::map<std::shared_ptr<VariableSymbol>, std::any>::iterator find(std::map<std::shared_ptr<VariableSymbol>, std::any>*, std::string);
};

