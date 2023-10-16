#pragma once

#include <iostream>
#include <string>
#include "BigDecimalInt.h"
using namespace std;


class BigReal
{
private:
	BigDecimalInt integer;
	BigDecimalInt fraction;
	char signNumber;

public:
	BigReal();						// Default constructor
	BigReal(double realNumber = 0.0);
	BigReal(string realNumber);
	BigReal(BigDecimalInt bigInteger);
	BigReal(const BigReal& other);			// Copy constructor
	BigReal(BigReal&& other);				//Move Constructor
	BigReal& operator=(const BigReal&);		//Assignment Operator
	BigReal& operator=(const BigReal&&);	//Move Assignment

	int FirstNum() const;

	BigReal operator+(const BigReal&);
	BigReal operator-(const BigReal&);

	bool operator<(const BigReal&);
	bool operator>(const BigReal&);
	bool operator==(const BigReal&);
	int size();
	int sign();
	friend ostream& operator<<(ostream&, const BigReal&);
	friend istream& operator>>(istream&, BigReal&);
};

