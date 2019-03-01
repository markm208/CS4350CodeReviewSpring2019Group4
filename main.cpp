#include <iostream> //do not include anything other than this

using namespace std;

int main()
{

	
    return 0;
}


//Checks to see if the passed in character is a + or - sign 
bool itIsPlusOrMinus(char plusOrMinus)
{
	if (plusOrMinus == 43 || plusOrMinus == 45)
	{
		return true;
	}
	return false;
}

//check to see if the passed in character is a number
bool itIsANumber(char aNum)
{
	if (aNum >= 48 && aNum <= 57)
	{
		return true;
	}
	return false;
}

//Checks for '/0' character
bool itIsTheEnd(char end)
{
	if (end == 0)
	{
		return true;
	}
	return false;

}

//checks to see if the passed in character is a '.'
bool itIsADot(char dot)
{
	if (dot == 46)
	{
		return true;
	}
	return false;
}

//checks for white space
bool itIsWhiteSpace(char whiteSpace)
{

	if (whiteSpace == 32)
	{
		return true;
	}
	return false;
}

//Wrapper function for encapsulating all the other valid character checks
bool itIsOkVal(char okVal)
{
	if (itIsADot(okVal) || itIsANumber(okVal) || itIsPlusOrMinus(okVal) || itIsTheEnd(okVal) || itIsWhiteSpace(okVal))
	{
		return true;
	}

	return false;
}


//Because .size() is off the table this function returns the size in number of elements
int getLength(char numString[])
{
	int i;
	for (i = 0; !(itIsTheEnd(numString[i])); i++);
	return i + 1;
}

//gets the denominator
int getDenom(int pos1, int pos2)
{
	int iterations = pos2 - pos1;
	int denom = 1;
	for (int i = 0; i <= iterations; i++)
	{
		denom *= 10;
	}
	return denom;
}

//assuming we can't use atoi() so toInt makes chars into their integer equivalent
int toInt(char anInt)
{
	int x = (int)anInt - '0';

	return x;
}

//Gets the numerator
int getNum(int pos1, int pos2, char numString[])
{
	int iterations = pos2 - pos1;
	int num = 0;
	for (int i = 0; i <= iterations; i++)
	{
		num = num + toInt(numString[pos1 + i]) * getDenom(pos1 + i + 1, pos2);
	}
	return num;

}



//new functions go here
//assuming good input is like a solitary 0.0 to X.X and bad input anything else
bool mantissa(char numString[], int& numerator, int& denominator)
{
	//Initializes counters and makes preliminary correct size check.
	numerator = 0;
	denominator = 0;
	int numOfElemInAr = getLength(numString);
	if (numOfElemInAr < 4) return false;
	int indexOfDot = -33;
	int indexOfLastGoodVal = -33;

	/*
	   Does a couple things:
		1.Checks for good values like numbers, +-, ., , and thus also checks for bad values like anything else Commas are also illegal if that wasn't clear
		2.Gets index of the X[.]X  symbols first appearance and stores it in indexOfDot
		3.Gets index of the end of the mantissa so the first whitespace after the last integer following the dot or the \0 character. Whichever comes first
	*/
	for (int i = 0; i < numOfElemInAr; i++)
	{
		if (itIsOkVal(numString[i]))
		{
			if (itIsADot(numString[i]))
			{
				indexOfDot = i;
			}
			if (itIsTheEnd(numString[i]))
			{
				indexOfLastGoodVal = i;
			}
		}
		else
		{
			return false;
		}
	}

	//Check for index of Dot if no dot in char array then bad input 
	if (indexOfDot < 0)
	{
		return false;
	}
	//Check for trailing white spaces that might throw last good value index
	//iterate backwards as long as they exist until a number is found
	while (!itIsANumber(numString[indexOfLastGoodVal]))
	{
		indexOfLastGoodVal -= 1;
	}
	//Gets Scaled denom
	denominator = getDenom(indexOfDot + 1, indexOfLastGoodVal);
	//Gets numerator
	numerator = getNum(indexOfDot + 1, indexOfLastGoodVal, numString);

	//for testing
	//cout << numerator << "/" << denominator << endl;
}


void testMantissa()
{
	int numerator;
	int denominator;
	char idealInput[] = "123.456";
	char has1TrailingWS[] = "123.456 ";
	char multTrailingWS[] = "123.456  ";
	char shortIdealInput[] = "123.0";
	char longIdealInput[] = "123.45600";
	char leadingWSInput[] = " 123.456";
	char badInput[] = "123.45A";
	char badInput2[] = "a23.456";
	char badInput3[] = "1";

	try
	{
		if (mantissa(idealInput, numerator, denominator))
		{
			cout << "mantissa works as intended for ideal input" << endl;
		}
		else
		{
			cout << "Logic Error in ideal input processing" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in IdealInput processing" << endl;
	}
	try
	{
		if (mantissa(has1TrailingWS, numerator, denominator))
		{
			cout << "mantissa works as intended for ideal input with 1 trailing ws" << endl;
		}
		else
		{
			cout << "Logic Error in ideal input processing with 1 ws" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in IdealInput processing with 1 ws" << endl;
	}
	try
	{
		if (mantissa(multTrailingWS, numerator, denominator))
		{
			cout << "mantissa works as intended for ideal input with mult trailing ws" << endl;
		}
		else
		{
			cout << "Logic Error in ideal input processing with mult ws" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in IdealInput processing with mult ws" << endl;
	}
	try
	{
		if (mantissa(shortIdealInput, numerator, denominator))
		{
			cout << "mantissa works as intended for short ideal input" << endl;
		}
		else
		{
			cout << "Logic Error in short ideal input" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in short IdealInput processing" << endl;
	}
	try
	{
		if (mantissa(longIdealInput, numerator, denominator))
		{
			cout << "mantissa works as intended for long ideal input" << endl;
		}
		else
		{
			cout << "Logic Error in long ideal input processing" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in long ideal input processing" << endl;
	}
	try
	{
		if (mantissa(leadingWSInput, numerator, denominator))
		{
			cout << "mantissa works as intended for leadingWS input" << endl;
		}
		else
		{
			cout << "Logic Error in leading ws input" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in leading ws input" << endl;
	}
	try
	{
		if (mantissa(badInput, numerator, denominator))
		{
			cout << "Logic error in intentionally bad input1" << endl;
		}
		else
		{
			cout << "Logic Error in intentionally bad input1" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in Intenionally bad input1" << endl;
	}
	try
	{
		if (mantissa(badInput2, numerator, denominator))
		{
			cout << "Logic error in intentionally bad input2" << endl;
		}
		else
		{
			cout << "Logic Error in intentionally bad input2" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in Intenionally bad input2" << endl;
	}
	try
	{
		if (mantissa(badInput3, numerator, denominator))
		{
			cout << "Logic error in intentionally bad input3" << endl;
		}
		else
		{
			cout << "Logic Error in intentionally bad input3" << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Run Time Error in Intenionally bad input3" << endl;
	}
}