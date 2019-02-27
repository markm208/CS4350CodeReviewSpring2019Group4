//Lesya Protasova
#include <iostream>
using namespace std;

bool isZero(int num)
{
	return num == 0;
}

//returns true is num is negative, false if num is positive or zero
bool isNegative(int num)
{
	return num < 0;
}

void improperToMixed(int inputNumer, int inputDenom, int& retWhole, int& retNumer)
{
	retWhole = inputNumer / inputDenom;
	retNumer = inputNumer % inputDenom;
}

int lengthOfInt(int num)
{
	int retVal = 0;

	while (true)
	{
		retVal++;
		num = num / 10;
		if (num == 0)
		{
			break;
		}
	}

	return retVal;
}

//the first number is c1 + (n1 / d1), the second number is c2 + (n2 / d2)
//result is where the product goes, and len is the number of characters (including \0) we can put in result
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	//for testing: print all inputs
	cout << "multiplying " << c1 << " + (" << n1 << " / " << d1 << ") by ";
	cout << c2 << " + (" << n2 << " / " << d2 << ") with output length " << len - 1 << endl;

	//check if any denominators are zero. if so, that's undefined, so we have an error (return false)
	if (isZero(d1) || isZero(d2))
	{
		return false;
	}

	//check if any of the fractions are negative. they should not be, only the characteristics can be negative
	if (isNegative(n1) || isNegative(d1) || isNegative(n2) || isNegative(d2))
	{
		return false;
	}

	//check if any mantissas are over 1. they should not be
	if (n1 > d1 || n2 > d2)
	{
		return false;
	}

	//check for potential int overflow or underflow
	//???

	//do the multiply. the algorithm is (char1 * char2) + (char1 * mant2) + (char2 * mant1) + (mant1 * mant2)
	//these portions of the product will be called prod1, prod2, prod3, and prod4 respectively
	int prod1 = c1 * c2;
	int numerOfProd2 = c1 * n2;
	int denomOfProd2 = d2;
	int numerOfProd3 = c2 * n1;
	int denomOfProd3 = d1;
	int numerOfProd4 = n1 * n2;
	int denomOfProd4 = d1 * d2;

	//prod1 is a whole number. let's add prod2, 3, and 4 together into one fraction so we can extract any additional whole numbers from it
	int numerProd234 = (numerOfProd2 * d1) + (numerOfProd3 * d2) + numerOfProd4;
	int denomProd234 = denomOfProd4;

	//use a helper function to extract a mixed fraction from our improper fraction
	int wholeProd234;
	improperToMixed(numerProd234, denomProd234, wholeProd234, numerProd234);

	//add wholeProd234 and prod1 to get the complete characteristic. the rest will be the decimal
	int completeChar = prod1 + wholeProd234;

	//set up the result string with all 0s and a /0 so we know when we reach the end. make sure our result has enough space for len chars
	if (sizeof(result) < len)
	{
		result[len - 1] = (char) '/0';
	}
	else
	{
		return false;
	}

	//see if the length of completeChar is longer than len - 1. fail if so
	int compCharLen = lengthOfInt(completeChar);
	if (compCharLen > len - 1)
	{
		return false;
	}

	//input the characteristic
	int place = 10;
	for (int index = compCharLen - 1; index >= 0; index--, place *= 10)
	{
		result[index] = 48 + (completeChar % place);
	}

	//input a decimal
	result[compCharLen] = '.';

	//convert the remaining fraction into a decimal to however many places we have left
	//???

	//put the decimals into result
	//???

	return true;
}

int main()
{
	cout << "hello" << endl;

	int c1, n1, d1;
	int c2, n2, d2;
	char result[10] = { 0 };
	int len = 10;

	//first, some tests that return false. this one will attempt 1 -2/3 * 1 1/2
	c1 = 1;
	n1 = -2;
	d1 = 3;
	c2 = 1;
	n2 = 1;
	d2 = 2;
	if (multiply(c1, n1, d1, c2, n2, d2, result, len))
	{
		cout << "Valid inputs" << endl;
	}
	else
	{
		cout << "Invalid inputs" << endl;
	}

	//attempt 10 3/0 * 12 2/3
	c1 = 10;
	n1 = 3;
	d1 = 0;
	c2 = 12;
	n2 = 2;
	d2 = 3;
	if (multiply(c1, n1, d1, c2, n2, d2, result, len))
	{
		cout << "Valid inputs" << endl;
	}
	else
	{
		cout << "Invalid inputs" << endl;
	}

	//attempt 5 3/2 * 4 2/3
	c1 = 5;
	n1 = 3;
	d1 = 2;
	c2 = 4;
	n2 = 2;
	d2 = 3;
	if (multiply(c1, n1, d1, c2, n2, d2, result, len))
	{
		cout << "Valid inputs" << endl;
	}
	else
	{
		cout << "Invalid inputs" << endl;
	}

	//and now the normal tests. attempt 3 0/10 * 3 0/10
	c1 = 3;
	n1 = 0;
	d1 = 10;
	c2 = 3;
	n2 = 0;
	d2 = 10;
	if (multiply(c1, n1, d1, c2, n2, d2, result, len))
	{
		cout << "Valid inputs. Result is: " << result << endl;
	}
	else
	{
		cout << "Invalid inputs" << endl;
	}

	//attempt 3 0/10 * 12 0/10
	c1 = 3;
	n1 = 0;
	d1 = 10;
	c2 = 12;
	n2 = 0;
	d2 = 10;
	if (multiply(c1, n1, d1, c2, n2, d2, result, len))
	{
		cout << "Valid inputs. Result is: " << result << endl;
	}
	else
	{
		cout << "Invalid inputs" << endl;
	}

	system("pause");
	return 0;
}