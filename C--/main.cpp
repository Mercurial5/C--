#include <iostream>
#include <vector>
#include <any>

#include "Parser.h"
#include "Binder.h"
#include "Evaluator.h"

#include "TokenType.h"
#include "Token.h"

#include "ExpressionTree.h"
#include "ExpressionType.h"
#include "Expression.h"

#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"

#include "BoundExpression.h"

#include "Compilation.h"

#include "Utilities.h"

#include <windows.h>

int main() {
	std::map<std::string, std::any> variables;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {
		std::string line;
		std::cout << "> ";
		std::getline(std::cin, line);

		std::shared_ptr<ExpressionTree> tree = ExpressionTree::parse(line);

		Compilation compilation(tree);
		EvaluationResult result = compilation.evaluate(variables);

		if (!result.diagnostics.empty()) {
			for (auto& diagnostic : result.diagnostics) {
				std::string prefix = line.substr(0, diagnostic.span.start);
				std::string error = line.substr(diagnostic.span.start, diagnostic.span.length);
				std::string suffix = line.substr(diagnostic.span.end);

				std::cout << std::endl << diagnostic << std::endl;

				std::cout << '\t' << prefix;

				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << error;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				
				std::cout << suffix << std::endl;
				
			}
			continue;
		}

		Utilities::print_expression(tree->root);
		
		if (result.value.type() == typeid(bool)) {
			std::cout << "= " << std::boolalpha << std::any_cast<bool>(result.value) << std::endl;
		}
		else if (result.value.type() == typeid(int)) {
			std::cout << "= " << std::any_cast<int>(result.value) << std::endl;
		}
		else {
			std::cout << "This type is not supported" << std::endl;
		}
	}
}