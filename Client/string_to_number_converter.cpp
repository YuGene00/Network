#include "string_to_number_converter.h"

ConvertedNumber StringToNumberConverter::Convert(char* string)
{
	char firstChar = string[0];
	if (firstChar == 0)
		return ConvertedNumber();

	int result = 0;
	bool containsNumber = false;
	bool isNegative = firstChar == '-';
	int index = isNegative || (firstChar == '+') ? 1 : 0;

	while (IsNumber(string[index])) {
		result = result * 10 + ConvertToInt(string[index]);

		containsNumber = true;
		++index;
	}

	result *= isNegative ? -1 : 1;
	return ConvertedNumber(containsNumber, result);
}

bool StringToNumberConverter::IsNumber(char character)
{
	return '0' <= character <= '9';
}

int StringToNumberConverter::ConvertToInt(char character)
{
	if (!IsNumber(character))
		return -1;

	return character - '0';
}

