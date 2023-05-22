#include <iostream>
#include <vector>

#include "Parser.h"
#include "Binder.h"
#include "Evaluator.h"

#include "TokenType.h"
#include "Token.h"

#include "ExpressionType.h"
#include "Expression.h"

#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ParenthesizedExpression.h"

#include "BoundExpression.h"

#include "Utilities.h"

int main() {
	while (true) {
		std::string line;
		std::cout << "> ";
		std::getline(std::cin, line);

		Binder binder = Binder(line);
		std::shared_ptr<BoundExpression> root = binder.bind();

		if (binder.diagnostics.empty()) {
			//Utilities::print_expression(root);

			Evaluator evaluator;
			std::cout << "= " << evaluator.evaluate_expression(root) << std::endl;
		}
		else {
			for (auto& diagnostic : binder.diagnostics) {
				std::cout << diagnostic << std::endl;
			}
		}
		
	}
}