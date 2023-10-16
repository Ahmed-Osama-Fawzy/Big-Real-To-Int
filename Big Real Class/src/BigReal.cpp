#include "BigReal.h"

BigReal::BigReal()
{
	integer = BigDecimalInt("0");
	fraction = BigDecimalInt("0");
	signNumber = '+';
}

BigReal::BigReal(double realNumber)
{
	string s = to_string(realNumber);
	if (s[0] == '-')
	{
		signNumber = '-';
		s = s.substr(1);
	}
	else
		signNumber = '+';

	int pointIndex = (int) s.find('.');
	integer = BigDecimalInt(s.substr(0, pointIndex));
	fraction = BigDecimalInt(s.substr(pointIndex + 1));

}

BigReal::BigReal(BigDecimalInt bigInteger)
{
	integer = bigInteger;
	fraction = BigDecimalInt("0");

	if (bigInteger.sign() == 0)
		signNumber = '-';
	else
		signNumber = '+';
}

bool checkValidInput(string input)
{
	regex pattern("^[+-]?[0-9]+[.][0-9]+$");
	return regex_match(input, pattern);
}


BigReal::BigReal(string realNumber)
{
	if (!checkValidInput(realNumber))
	{
		cout << "Invalid input" << endl;
		return;
	}


	if (realNumber[0] == '-')
	{
		signNumber = '-';
		realNumber = realNumber.substr(1);
	}
	else
	{
		if (realNumber[0] == '+')
			realNumber = realNumber.substr(1);

		signNumber = '+';
	}

	int pointIndex = (int) realNumber.find('.');
	integer = BigDecimalInt(realNumber.substr(0, pointIndex));
	fraction = BigDecimalInt(realNumber.substr(pointIndex + 1));
}

BigReal::BigReal(const BigReal& other)
{
	integer = other.integer;
	fraction = other.fraction;
}

BigReal::BigReal(BigReal&& other)
{
	integer = other.integer;
	fraction = other.fraction;
}

BigReal& BigReal::operator=(const BigReal& other)
{
	integer = other.integer;
	fraction = other.fraction;
	return *this;
}

BigReal& BigReal::operator=(const BigReal&& other)
{
	integer = other.integer;
	fraction = other.fraction;
	return *this;
}

int BigReal::FirstNum() const
{
	BigReal temp = *this;
	string num = temp.integer.getNumber();
	return (int) num[0] - '0';
}

BigReal BigReal::operator+(const BigReal& other)
{
	BigReal Other(0.0);
	Other.integer = other.integer;
	Other.fraction = other.fraction;
	Other.signNumber = other.signNumber;

	BigDecimalInt integerSum;
    BigDecimalInt fractionSum;
	BigReal sum(0.0);

    if(signNumber == Other.signNumber){ // +

        sum.signNumber = signNumber ;
		integerSum = integer + Other.integer;
		fractionSum = fraction + Other.fraction;

    }

	else if (signNumber == '+' &&  Other.signNumber == '-') { // -

        if(integer.FirstNumber() > Other.integer.FirstNumber()){
			sum.signNumber = '+' ;
		}

		else if (integer.FirstNumber() < Other.integer.FirstNumber()) {
			sum.signNumber = '-' ;
		}
		else {
			sum.signNumber = '+' ;
		}
		integerSum = integer - Other.integer;
		fractionSum = fraction - Other.fraction;
    }

	else //(signNumber == '-' &&  Other.signNumber == '+') { // -
	{
		if(integer.FirstNumber() < Other.integer.FirstNumber()){
			sum.signNumber = '+' ;
		}

		else if(integer.FirstNumber() > Other.integer.FirstNumber()) {
			sum.signNumber = '-' ;
		}

		else {
			sum.signNumber = '+' ;
		}
		integerSum = Other.integer - integer;
		fractionSum = Other.fraction - fraction;
    }
	//if(fraction.LeftNumber() + Other.fraction.LeftNumber() > 9 ){
		sum.integer = integerSum;
		sum.fraction = fractionSum;
	//}
	return sum;
}

BigReal BigReal::operator-(const BigReal& other)
{
	BigDecimalInt integerSum;
	BigDecimalInt fractionSum;
	BigReal sum('0');

	if(signNumber == '+' &&  other.signNumber == '-'){ //  +

		sum.signNumber = '+' ;
		sum.signNumber = signNumber ;
		integerSum = integer + other.integer;
		fraction + other.fraction;
    }

	else if (signNumber == '-' &&  other.signNumber == '+') { // +
		sum.signNumber = '-' ;
		sum.signNumber = signNumber ;
		integerSum = integer + other.integer;
		fraction + other.fraction;
    }

	else if (signNumber == '+' &&  other.signNumber == '+') { // -
        if(integer.FirstNumber() > other.integer.FirstNumber()){
			sum.signNumber = '+' ;
		}

		else if(integer.FirstNumber() < other.integer.FirstNumber()){
			sum.signNumber = '-' ;
		}

		else {
			sum.signNumber = '+' ;
		}

		integerSum = integer - other.integer;
		fractionSum = fraction - other.fraction;
    }

	else if (signNumber == '-' &&  other.signNumber == '-') { // -

		if(integer.FirstNumber() < other.integer.FirstNumber()){
			sum.signNumber = '+' ;
		}

		else if(integer.FirstNumber() > other.integer.FirstNumber()){
			sum.signNumber = '-' ;
		}

		else {
			sum.signNumber = '+' ;
		}
		integerSum = other.integer - integer;
		fractionSum = other.fraction - fraction;
    }
	sum.integer = integerSum;
	sum.fraction = fractionSum;
	return sum;
}

bool BigReal::operator<(const BigReal& other)
{
	if (integer < other.integer)
		return true;

	if (*this == other)
		return false;

	if (integer == other.integer)
		return (fraction < other.fraction);

	return false;
}

bool BigReal::operator>(const BigReal& other)
{
	if (*this < other)
		return false;

	if (*this == other)
		return false;

	return true;
}

bool BigReal::operator==(const BigReal& other)
{
	if (integer == other.integer && fraction == other.fraction)
		return true;

	return false;
}

int BigReal::size()
{
	return integer.size() + fraction.size();
}

int BigReal::sign()
{
	return integer.sign();
}

ostream& operator<<(ostream& out, const BigReal& real)
{
	if (real.signNumber == '-')
		out << "-";
	out << real.integer << "." << real.fraction;
	return out;
}

istream& operator>>(istream& in, BigReal& real)
{
	string input;
	in >> input;
	if (!checkValidInput(input))
	{
		cout << "Invalid input" << endl;
		return in;
	}
	int pointIndex = (int) input.find('.');
	real.integer = BigDecimalInt(input.substr(0, pointIndex - 1));
	real.fraction = BigDecimalInt(input.substr(pointIndex + 1));
	return in;
}
