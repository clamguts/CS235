#ifndef OPERATIONS_H
#define OPERATIONS_H

class Operations 
{
private:
	int operand1 = 0;
	int operand2 = 0;
public:

	Operations(int num1 = 0, int num2 = 0) {}
	~Operations() {}

	int add(int operand1, int operand2)
	{
		int value = operand1 + operand2;
		return value;
	}

	int subtract(int operand1, int operand2)
	{
		int value = 0;
		value = operand2 - operand1;
		return value;
		
	}

	int multiply(int operand1, int operand2)
	{
		int value = operand1 * operand2;
		return value;
	}

	int divide(int operand1, int operand2)
	{
		int value = 0;
		value = operand2 / operand1;
		return value;
	}

	int modulo(int operand1, int operand2)
	{
		int value = 0;
		value = operand2 % operand1;
		return value;
	}

};
#endif // !OPERATIONS_H

