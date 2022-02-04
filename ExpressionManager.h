#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include "ExpressionInterface.h"
#include "Operations.h"
using namespace std;

class ExpressionManager : public ExpressionManagerInterface
{
private:
	vector<string> expressions;
public:
	ExpressionManager() 
	{
		string line = "";
	}
	~ExpressionManager(void) {}

	void getExpression(string line)
	{
		expressions.push_back(line);
	}

	void stackCleanUp(stack<string> myStack)
	{
		while (!myStack.empty())
		{
			myStack.pop();
		}
	}

	bool isBalanced()
	{
		stack<string> openingOps;
		bool balanced = true;

		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			string currParen = expressions.at(i);
			if (currParen == "(" || currParen == "[" || currParen == "{")
			{
				openingOps.push(currParen);
			}
			else if (currParen == ")" || currParen == "]" || currParen == "}")
			{
				if (currParen == ")" && openingOps.top() == "(")
				{
					openingOps.pop();
				}
				else if (currParen == "]" && openingOps.top() == "[")
				{
					openingOps.pop();
				}
				else if (currParen == "}" && openingOps.top() == "{")
				{
					openingOps.pop();
				}
			}
		}
		if (!openingOps.empty())
		{
			stackCleanUp(openingOps);
			balanced = false;
		}

		return balanced;
	}

	bool isNumber(string elem)
	{
		return isdigit(elem[0]);
	}

	bool isIllegal(string elem)
	{
		if (!isNumber(elem) && !isOperator(elem))
		{
			return true;
		}
		return false;
	}

	bool isOperator(string op)
	{
		bool isOp = true;
		if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "("
			|| op == ")" || op == "[" || op == "]" || op == "{" || op == "}")
		{
			isOp = true;
			return isOp;
		}
		else
		{
			isOp = false;
			return isOp;
		}
	}

	int precedence(string op)
	{
		int precedence = 0;
		if (!isOperator(op))
		{
			return precedence;
		}
		if (op == "(" || op == "[" || op == "{")
		{
			precedence = 0;
			return precedence;
		}
		else if (op == "+" || op == "-")
		{
			precedence = 1;
			return precedence;
		}
		else if (op == "*" || op == "/" || op == "%")
		{
			precedence = 2;
			return precedence;
		}
	}

	friend ostream& operator<< (ostream& os, vector<ExpressionManager>& expressions)
	{
		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			ExpressionManager currentVal = expressions.at(i);
			os << currentVal.toString();
		}
		return os;
	}

	/** Return the integer value of the infix expression */
	virtual int value(void)
	{

		istringstream str(postfix());
		stack<int> operands;
		int answer = 0;
		int num1 = 0;
		int num2 = 0;
		string substr;
		Operations op;

		while (str >> substr)
		{
			//Get operands and convert to int
			if (!isOperator(substr))
			{
				operands.push(stoi(substr));
				continue;
			}
			//Set operation nums according to size of operands stack
			if (operands.size() == 1)
			{
				num1 = operands.top();
				operands.pop();
			}
			//Do operations
			if (!operands.empty())
			{
				num1 = operands.top();
				operands.pop();
				num2 = operands.top();
				operands.pop();
				op = Operations(num1, num2);

				if (substr == "+")
				{
					answer = op.add(num1, num2);
					operands.push(answer);
					continue;
				}
				else if (substr == "-")
				{
					answer = op.subtract(num1, num2);
					operands.push(answer);
					continue;
				}
				else if (substr == "*")
				{
					answer = op.multiply(num1, num2);
					operands.push(answer);
					continue;
				}
				else if (substr == "/")
				{
					answer = op.divide(num1, num2);
					operands.push(answer);
					continue;
				}
				else if (substr == "%")
				{
					answer = op.modulo(num1, num2);
					operands.push(answer);
					continue;
				}
			}

		}
		//Check for clear stack
		while (!operands.empty())
		{
			operands.pop();
		}
		return answer;
	}


	virtual string infix(void)
	{
		string infix = "";
		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			infix += expressions.at(i);
		}
		return infix;
	}

	/** Return a postfix representation of the infix expression */
	virtual string postfix(void)
	{
		string postfix = "";
		stack<string> opStack;

		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			string currItem = expressions.at(i);
			//Add operators to operator stack according to precedence
			if (currItem == "+" || currItem == "-" || currItem == "/" || currItem == "*" || currItem == "%")
			{
				while (!opStack.empty() &&
					(precedence(currItem) <= precedence(opStack.top())))
				{
					postfix += opStack.top();
					postfix += " ";
					opStack.pop();
				}
				opStack.push(currItem);
			}
			//Check for opening
			else if (currItem == "(" || currItem ==  "[" || currItem == "{")
			{
				opStack.push(currItem);
			}
			//Deal with closing, pop off if there's a match
			else if (currItem == ")" || currItem == "]" || currItem == "}")
			{
				if (currItem == ")")
				{
					while (opStack.top() != "(")
					{
						postfix += opStack.top();
						postfix += " ";
						opStack.pop();
					}
					opStack.pop();
				}
				else if (currItem == "]")
				{
					while (opStack.top() != "[")
					{
						postfix += opStack.top();
						postfix += " ";
						opStack.pop();
					}
					opStack.pop();
				}
				else if (currItem == "}")
				{
					while (opStack.top() != "{")
					{
						postfix += opStack.top();
						postfix += " ";
						opStack.pop();
					}
					opStack.pop();
				}
			}
			//Concatenate other stuff to postfix
			else 
			{
				postfix += currItem;
				postfix += " ";
			}
		}
		//Concatenate remaining operators to postfix
		while (!opStack.empty())
		{
			postfix += opStack.top();
			postfix += " ";
			opStack.pop();
		}
		return postfix;
	}


	/** Return a prefix representation of the infix expression */
	virtual string prefix(void)
	{
		string prefix = "";
		stack<string> operatorStack;
		stack<string> operandStack;

		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			string currItem = expressions.at(i);
			//Check for opening
			if (currItem == "(" || currItem == "{" || currItem == "[")
			{
				operatorStack.push(currItem);
			}
			//Deal with closing, pop and add to operand stack if there's a match
			else if (currItem == ")" || currItem == "]" || currItem == "}")
			{
				if (currItem == ")")
				{
					while (!operatorStack.empty() &&
						operatorStack.top() != "(")
					{

						string operand1 = operandStack.top();
						operandStack.pop();

						string operand2 = operandStack.top();
						operandStack.pop();

						string oper = operatorStack.top();
						operatorStack.pop();

						string tmp = oper + " " + operand2 + " "+ operand1;
						operandStack.push(tmp);
					}
					operatorStack.pop();
				}
				else if (currItem == "]")
				{
					while (!operatorStack.empty() && operatorStack.top() != "[")
					{

						string operand1 = operandStack.top();
						operandStack.pop();

						string operand2 = operandStack.top();
						operandStack.pop();

						string oper = operatorStack.top();
						operatorStack.pop();

						string tmp = oper + " " + operand2 + " " + operand1;
						operandStack.push(tmp);
					}
					operatorStack.pop();
				}
				else if (currItem == "}")
				{
					while (!operatorStack.empty() &&
						operatorStack.top() != "{")
					{

						string operand1 = operandStack.top();
						operandStack.pop();

						string operand2 = operandStack.top();
						operandStack.pop();

						string oper = operatorStack.top();
						operatorStack.pop();

						string tmp = oper + " " + operand2 + " " + operand1;
						operandStack.push(tmp);
					}
					operatorStack.pop();
				}
			}
			//Push operands to operand stack
			else if (!isOperator(currItem))
			{
				operandStack.push(currItem);
			}
			//Create string, at to operand stack
			else
			{
				while (!operatorStack.empty() &&
					precedence(currItem) <=
					precedence(operatorStack.top()))
				{

					string operand1 = operandStack.top();
					operandStack.pop();

					string operand2 = operandStack.top();
					operandStack.pop();

					string oper = operatorStack.top();
					operatorStack.pop();

					string tmp = oper + " " + operand2 + " " + operand1;
					operandStack.push(tmp);
				}

				operatorStack.push(currItem);
			}
		}
		//Do this until operator stack is empty
		while (!operatorStack.empty()) {
			string operand1 = operandStack.top();
			operandStack.pop();

			string operand2 = operandStack.top();
			operandStack.pop();

			string oper = operatorStack.top();
			operatorStack.pop();

			string tmp = oper +  " " + operand2 + " " + operand1 + " ";
			operandStack.push(tmp);
		}
		return operandStack.top();
	}

	/** Return the infix vector'd expression items */
	virtual string toString(void) const
	{
		ostringstream outExpression;
		for (unsigned int i = 0; i < expressions.size(); ++i)
		{
			outExpression << expressions.at(i) << " ";
		}
		return outExpression.str();
	}
};

#endif // EXPRESSION_MANAGER_H

