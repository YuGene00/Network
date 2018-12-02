#ifndef STRING_TO_NUMBER_CONVERTER_H
#define STRING_TO_NUMBER_CONVERTER_H

typedef struct ConvertedNumber {
	bool isNumber;
	int number;

	ConvertedNumber(bool isNumber = false, int number = 0) {
		this->isNumber = isNumber;
		this->number = number;
	}

	operator int() const {
		return number;
	}
} ConvertedNumber;

class StringToNumberConverter
{
public:
	ConvertedNumber Convert(char* string);

private:
	bool IsNumber(char character);
	int ConvertToInt(char character);
};

#endif // !STRING_TO_NUMBER_CONVERTER_H
