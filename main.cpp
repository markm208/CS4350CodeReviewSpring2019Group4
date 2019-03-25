#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int &c);
int atoi(char * string);
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2);
char* intToCstr(int characteristic, int numerator, int denominator, char* result, int len);
char* reverseCstr(char* str, int length);

void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(char number[]);

void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	testMath();
    
    return 0;
}
//--
void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123, 456, 1000);
	shouldConvert("    123.456", 123, 456, 1000);
	shouldConvert("123.456    ", 123, 456, 1000);
	shouldConvert("    123.456    ", 123, 456, 1000);

	shouldConvert("+123.456", 123, 456, 1000);
	shouldConvert("   +123.456", 123, 456, 1000);
	shouldConvert("+123.456   ", 123, 456, 1000);
	shouldConvert("   +123.456   ", 123, 456, 1000);

	shouldConvert("-123.456", -123, 456, 1000);
	shouldConvert("   -123.456", -123, 456, 1000);
	shouldConvert("-123.456   ", -123, 456, 1000);
	shouldConvert("    -123.456   ", -123, 456, 1000);

	shouldConvert("0.456", 0, 456, 1000);
	shouldConvert("   0.456", 0, 456, 1000); 
	shouldConvert("0.456   ", 0, 456, 1000);
	shouldConvert("   0.456   ", 0, 456, 1000);

	shouldConvert("-0.456", 0, -456, 1000);
	shouldConvert("   -0.456", 0, -456, 1000);
	shouldConvert("-0.456   ", 0, -456, 1000);
	shouldConvert("   -0.456   ", 0, -456, 1000);

	shouldConvert(".456", 0, 456, 1000);
	shouldConvert("    .456", 0, 456, 1000);
	shouldConvert(".456   ", 0, 456, 1000);
	shouldConvert("   .456   ", 0, 456, 1000);

	shouldConvert("-.456", 0, -456, 1000);
	shouldConvert("    -.456", 0, -456, 1000);
	shouldConvert("-.456   ", 0, -456, 1000);
	shouldConvert("   -.456   ", 0, -456, 1000);

	shouldConvert("123456", 123456, 0, 10);
	shouldConvert("   123456", 123456, 0, 10);
	shouldConvert("123456   ", 123456, 0, 10);
	shouldConvert("   123456   ", 123456, 0, 10);

	shouldConvert("-123456", -123456, 0, 10);
	shouldConvert("   -123456", -123456, 0, 10);
	shouldConvert("-123456   ", -123456, 0, 10);
	shouldConvert("   -123456   ", -123456, 0, 10);

	shouldConvert("000123.456", 123, 456, 1000);
	shouldConvert("123.45600000", 123, 456, 1000);
	shouldConvert("00000123.45600000", 123, 456, 1000);

	shouldConvert("-000123.456", -123, 456, 1000);
	shouldConvert("-123.45600000", -123, 456, 1000);
	shouldConvert("-00000123.45600000", -123, 456, 1000);

	shouldConvert("123.00000456", 123, 456, 100000000);
	shouldConvert("-123.00000456", -123, 456, 100000000);
}
//--
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}

			if (expectedNumerator != n)
			{
				cout << "expected numerator: " << expectedNumerator << " "
					<< "actual numerator: " << n << endl;

			}

			if (expectedDenominator != d)
			{
				cout << "expected denominator: " << expectedDenominator << " "
					<< "actual denominator: " << d << endl;
			}
		}
	}
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}
//--
void shouldNotConvert(char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}
//--
void testMath()
{
	//add
	testAdd();
	testSubtract();
	testMultiply();
	testDivide();
}
//--
void testAdd()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (add(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 + 0 = "0"
	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//1 + 1 = "2"
	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 + -1.5 = "-.5"
	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, -5, 10);

	//1.125 + 1.6R = "2.79"
	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 79, 100);

	//1.125 + 1.6R = "2.7916666"
	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 7916666, 10000000);
}

//new functions go here

bool characteristic(char numString[], int &c)
{
	// first, we're going to want to filter the char array to remove all potential space additions
	// because we are also looping through the array to remove spaces, we may as well store the size
	// of the array for ease of use later

	int sizeWithoutSpaces = 0;
	int iterator = 0;

    // before we mess with any pointers, we're going to want to assign a value to c by sending over the numString to our atoi() function
    c = atoi(numString);

    // when we iterate through the char[], we won't want to use the actual numString because that will change the pointer to point to
    // the end of the char[]

    char * head = numString;

	while (head[iterator] != '\0')
	{
		if (head[iterator] != ' ')
		{
			sizeWithoutSpaces++;
		}
		iterator++;
	}

	// iterate through the array and store all digit characters in a new array;
	// digitArray will store the values of all of the digits that we find from the numString[]
	char * digitArray = new char[sizeWithoutSpaces];

    // reset head * location to the beginning of numString to use as iterator
    head = numString;

    // here we have two iterators, one to keep track of the iteration through numString (iterator2)
    // and the other add to the correct index of digitArray (digitArrayInc)
	int iterator2 = 0;
    int digitArrayInc = 0;

	while (head[iterator2] != '\0')
	{
		if (head[iterator2] != ' ')
		{
			// if the iterator has reached a digit in the string, we can use the tail array to jump to the digit so it can only store digits.
			digitArray[digitArrayInc] = head[iterator2];
			// increment both the char[] pointer and the iterator in order to loop through the entire cstring
            digitArrayInc++;
			iterator2++;
		}
		else
		{
			// the char is not important so we just increment the iterator
			iterator2++;
		}
	}

	// currently, our digitArray holds the number without spaces, so we should check to see if it is a valid number.

	// we can loop through the array to check the values and determine if it is valid or not

	int iterator3 = 0;
    bool unary = false;
	while (digitArray[iterator3] != '\0')
	{
        // check the first char and see if it is a unary symbol, it is only allowed as the first char
        if (digitArray[0] == '+' || digitArray[0] == '-' && unary == false)
        {
            // switch the value of the bool to true so we will never step into here again
            // by switching the bool, it acts as a flag by saying a unary symbol was provided as the first char
            // but don't let it occur anymore
            unary = true;
            iterator3++;
            continue;
        }
		if (digitArray[iterator3] == '.')
		{
            // if we find a decimal value before any bad input, then we know it is a valid characteristic
			return true;
		}
		else if (digitArray[iterator3] < '0' || digitArray[iterator3] > '9')
		{
            // if we do not have any digit values at this point, then we know it is not a valid characteristic
            // set c to 0 as a default
            c = 0;
			return false;
		}
		// else just increment the iterator to loop through char[]
		iterator3++;
	}

	// if we haven't return false by this point, then the value is a good input, and we can change the value of c to our atoi function return
	// make sure we free the memory that we created on the heap
	delete[] digitArray;
	return true;

}

int atoi(char * string)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	// loop through the string until it isn't null
	while (string[i] != '\0')
	{
		// if the string has a negative sign in it, then make the int negative
		if (string[i] == '-')
		{
			sign = -1;
			i++;
		}
        // make sure that if the first char is a '+' that we ignore it, but make sure it's only the first
        if (string[i] == '+')
        {
            //skip over
            i++;
        }
		// if the string finds a decimal point, cut it off and return what it has so far stored in the result.
		if (string[i] == '.')
		{
			break;
		}
        // to handle blank space
		if (string[i] == ' ')
		{
			// skip over the char
			i++;
            continue;
		}
		else if (string[i] > '9' || string[i] < '0')
		{
			// not a digit so return 0;
            cout << "Char:" << string[i] << "h" << endl;
			return 0;
		}

		// take the value of result, multiply it by ten to move it over a decimal space, then take off the '0' character
		// acquired from multiplying by ten.
		result = ((result * 10) + string[i]) - '0';
		i++;
	}
	// return whatever the result was multiplied by the sign in order to return negative values as well
	return result * sign;
}

//--
void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123, 456, 1000);
	shouldConvert("    123.456", 123, 456, 1000);
	shouldConvert("123.456    ", 123, 456, 1000);
	shouldConvert("    123.456    ", 123, 456, 1000);

	shouldConvert("+123.456", 123, 456, 1000);
	shouldConvert("   +123.456", 123, 456, 1000);
	shouldConvert("+123.456   ", 123, 456, 1000);
	shouldConvert("   +123.456   ", 123, 456, 1000);

	shouldConvert("-123.456", -123, 456, 1000);
	shouldConvert("   -123.456", -123, 456, 1000);
	shouldConvert("-123.456   ", -123, 456, 1000);
	shouldConvert("    -123.456   ", -123, 456, 1000);

	shouldConvert("0.456", 0, 456, 1000);
	shouldConvert("   0.456", 0, 456, 1000); 
	shouldConvert("0.456   ", 0, 456, 1000);
	shouldConvert("   0.456   ", 0, 456, 1000);

	shouldConvert("-0.456", 0, -456, 1000);
	shouldConvert("   -0.456", 0, -456, 1000);
	shouldConvert("-0.456   ", 0, -456, 1000);
	shouldConvert("   -0.456   ", 0, -456, 1000);

	shouldConvert(".456", 0, 456, 1000);
	shouldConvert("    .456", 0, 456, 1000);
	shouldConvert(".456   ", 0, 456, 1000);
	shouldConvert("   .456   ", 0, 456, 1000);

	shouldConvert("-.456", 0, -456, 1000);
	shouldConvert("    -.456", 0, -456, 1000);
	shouldConvert("-.456   ", 0, -456, 1000);
	shouldConvert("   -.456   ", 0, -456, 1000);

	shouldConvert("123456", 123456, 0, 10);
	shouldConvert("   123456", 123456, 0, 10);
	shouldConvert("123456   ", 123456, 0, 10);
	shouldConvert("   123456   ", 123456, 0, 10);

	shouldConvert("-123456", -123456, 0, 10);
	shouldConvert("   -123456", -123456, 0, 10);
	shouldConvert("-123456   ", -123456, 0, 10);
	shouldConvert("   -123456   ", -123456, 0, 10);

	shouldConvert("000123.456", 123, 456, 1000);
	shouldConvert("123.45600000", 123, 456, 1000);
	shouldConvert("00000123.45600000", 123, 456, 1000);

	shouldConvert("-000123.456", -123, 456, 1000);
	shouldConvert("-123.45600000", -123, 456, 1000);
	shouldConvert("-00000123.45600000", -123, 456, 1000);

	shouldConvert("123.00000456", 123, 456, 100000000);
	shouldConvert("-123.00000456", -123, 456, 100000000);
}
//--
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		if (c == expectedCharacteristic) && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}

			if (expectedNumerator != n)
			{
				cout << "expected numerator: " << expectedNumerator << " "
					<< "actual numerator: " << n << endl;

			}

			if (expectedDenominator != d)
			{
				cout << "expected denominator: " << expectedDenominator << " "
					<< "actual denominator: " << d << endl;
			}
        }
    }
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}
//--
void shouldNotConvert(char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c))// && mantissa(number, n, d))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}
//--
void testMath()
{
	//add
	testAdd();
	testSubtract();
	testMultiply();
	testDivide();
}
//--
void testAdd()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (add(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 + 0 = "0"
	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//1 + 1 = "2"
	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 + -1.5 = "-.5"
	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, -5, 10);

	//1.125 + 1.6R = "2.79"
	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 79, 100);

	//1.125 + 1.6R = "2.7916666"
	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 7916666, 10000000);


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
bool itIsSpace(char whiteSpace)
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
	if (itIsADot(okVal) || itIsANumber(okVal) || itIsPlusOrMinus(okVal) || itIsTheEnd(okVal) || itIsSpace(okVal))
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

//Gets the numerator via taking two positions that are roughly correlated with the upper and lower bounds of the
//numerator in the string. Then goes through the numString and takes the numerator out of it by going through
//piecemeal and ensuring proper tens place via using getdenom with proper inputs. Sums each part piecemeal as well
//then returns the final number. In essence if you have an array with [1234.44] it goes through and takes it out and makes it
// 123444.
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

//checks for multiple dots or unary signs
bool thereAreMultDotsOrUns(char numString[])
{
	int unsCount = 0;
	int dotsCount = 0;
	foreach(char x : numString)
	{
		if (x == '+' || x == '-') unsCount++;
		if (x == '.') dotsCount++;
	}

	if (unsCount > 1 || dotsCount > 1) return true;

	return false
}


//new functions go here
//assuming good input is like a solitary -X.X to X.X and bad input anything else
bool mantissa(char numString[], int& numerator, int& denominator)
{
	//Checks for a bad case
	if (thereAreMultDotsOrUns(numString)) return false;
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
	//1.125 + 1.6R = "2.79166666666666666"
	add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "2.79166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in add()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
void testSubtract()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (subtract(INT_MIN, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 - 0 = "0"
	subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 0, 10);

	//1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 5, 10);

	//1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -54, 100);

	//1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5416666, 10000000);

	//1.125 - 1.6R = "-.54166666666666666"
	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "-.54166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in subtract()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
//--
void testMultiply()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (multiply(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 * 0 = "0"
	multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//3 * 2 = "6"
	multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 6, 0, 10);

	//3 * -1.5 = "-4.5"
	multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, -4, 5, 10);

	//1.125 * 1.6R = "1.87"
	multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 87, 100);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 875, 1000);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 875, 1000);
}
//--
void testDivide()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (divide(INT_MAX, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//cannot divide by zero
	if (divide(10, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: cannot divide by zero" << endl;
	}

	//0 / 1 = "0"
	divide(0, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//6 / 3 = "2"
	divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 / -1.5 = "-.66"
	divide(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -66, 100);
	
	//1 / -1.5 = "-.6666666"
	divide(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -6666666, 10000000);
	
	//1 / -1.5 = "-.66666666666666666"
	divide(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	char expectedResult1[] = "-.66666666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult1[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in divide()." << endl
				<< "Expected: " << expectedResult1 << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}

	//1.125 / 1.6R = "0.67"
	divide(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 67, 100);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 675, 1000);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 675, 1000);
}
//new functions go here

void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2){
    n1 *= d2;   //multiply the numerators
    n2 *= d1;   //by the other fraction's denominator
    
    d1 *= d2;   //multiply the denominators
    d2 = d1;    //together
}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    
    convertToCmnDenom(n1, d1, n2, d2);

    int cSum = c1 + c2; //add the integers together
    int nSum = n1 + n2; //add the numerators together

    cSum += nSum/d1; //add any overflow from the fraction
    nSum -= (nSum/d1)*d1; //subtract that overflow from the fraction

    result = intToCstr(cSum, nSum, d1, result, len);

    if(result != NULL){
        return true;
    }
    else{
        return false;
    }
};

//this function converts the mixed fraction into a c string
char* intToCstr(int characteristic, int numerator, int denominator, char* result, int len) {
	int i = 0;
	bool isNegative = false;

	if (characteristic == 0 && numerator == 0)	//checks to see if the number is just 0
	{
		result[0] = '0';
		result[1] = '\0';
		return result;
	}

	result[i] = '.';	//insert the decimal
	i++;

	if (characteristic < 0) //if the characteristic is negative
	{
		isNegative = true;
		characteristic = -characteristic;
	}

	while (characteristic != 0)
	{
		int remainder = characteristic % 10;	//find the remainder

		if (remainder > 9) {
			result[i] = (remainder - 10) + 'a';
		}
		else {	//if the remainder is lower than 9, it is added to the array
			result[i] = remainder + '0';	//using the ascii value
		}

		i++;
		characteristic = characteristic / 10;	//divide the characteristic by 10
	}

	if (isNegative) {
		result[i] = '-';	// if the characteristic is negative
		i++;	//append a - onto the end and increment i
	}


	result[i] = '\0'; // Append string terminator 

	//now reverse the string
	result = reverseCstr(result, i);

	for (int decimalPlace = i; decimalPlace < len; decimalPlace++) {
		result[decimalPlace] = (numerator % denominator) + '0';
	}

	return result;
}

//reverses c string
char* reverseCstr(char* str, int length) {
	int i = 0;
	int end = length - 1;
	while (i < end) {
		swap(*(str + i), *(str + end));
		i++;
		end--;
	}

	return str;
}
