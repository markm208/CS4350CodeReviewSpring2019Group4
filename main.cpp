#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int chara1, int numer1, int denom1,
    int chara2, int numer2, int denom2,
    char result[], int len);

int compare(int chara1, int numer1, int denom1,
    int chara2, int numer2, int denom2)
{
    // returns -1 if in1<in2,
    // 0 if in1==in2,
    // 1 if in1>in2
    if (chara1 < chara2)
    {
        return -1;
    }
    if (chara1 > chara2)
    {
        return 1;
    }
    if (numer1*denom2 < numer2*denom1)
    {
        return -1;
    }
    if (numer1*denom2 > numer2*denom1)
    {
        return 1;
    }
}

void shouldConvertText(char number[], char expected[]);

bool characteristic(char numString[], int &c);
int atoi(char * string);
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
bool shouldConvertInternal(char number[], char expected[])
{
    for (int i = 0; ; i++)
    {
        if (number[i] != expected[i])
            return false;
        if (number[i] == 0 && expected[i] == 0)
            return true;
    }
}
//--
void shouldConvertText(char number[], char expected[])
{
    if (shouldConvertInternal(number, expected))
        cout << "Good: " << number << " " << expected << endl;
    else
        cout << "Bad: " << number << " " << expected << endl;
}
void testMath()
{
	//divide
	testDivide();
}
//--
int length(int chara)
{
    // returns the number of digits required to represent chara in decimal
    int retval = 0;
    int accum = 1;
    if (chara == 0)
    {
        return 1;
    }
    if (chara >= 1000000000)
    {
        return 10;
    }
    if (chara <= -1000000000)
    {
        return 11;
    }
    if (chara < 0)
    {
        // not reached in this file
        chara = -chara;
        retval++;
    }
    while (accum <= chara)
    {
        accum *= 10;
        retval++;
    }
    return retval;
}

int pow10(int shift)
{
    // return 10^shift - we can't include pow()
    int retval = 1;
    if (shift < 0)
    {
        return 0;
    }
    while (shift)
    {
        // count down from shift to 0,
        // multiplying retval by 10 each time
        retval *= 10;
        shift--;
    }
    return retval;
}

bool divide(int chara1, int numer1, int denom1,
    int chara2, int numer2, int denom2,
    char result[], int len)
{
    int shift = 0; // we always add or subtract input2*(10^shift)
    int quotient_chara = 0;
    bool negative = false;

    // check for division by 0:
    if (chara2 == 0 && numer2 == 0)
    {
        return false;
    }

    // check for negatives early on to simplify operations:
    if (chara1 < 0)
    {
        if (!numer1)
        {
            chara1 = -chara1;
        }
        else
        {
//          chara1 = -chara1-1;
//          numer1 = denom1-numer1;
            chara1 = -chara1; // (-1, 1, 2) = -1.5, not -1 + .5
        }
        negative = !negative;
    }
    if (chara2 < 0)
    {
        if (!numer2)
        {
            chara2 = -chara2;
        }
        else
        {
//          chara2 = -chara2-1;
//          numer2 = denom2-numer2;
            chara2 = -chara2;
        }
        negative = !negative;
    }

    // check early for results that won't fit
    if (length(chara1/(chara2+1)) > (negative ? (len-2) : (len-1)))
    {
        return false;
    }

    // scale in2 until in2<=in1 and 10*in2>in1:
    // note: 10*(chara, numer, denom)
    // = (10*chara+(10*numer)/denom, (10*numer)%denom, denom),
    // (1/10)*(chara, numer, denom)
    // = (chara/10, numer+(chara%10)*denom, 10*denom)
    switch (compare(chara1, numer1, denom1, chara2, numer2, denom2))
    {
    case 0:
        shift = 0;
        break;
    case 1:
        while (compare(chara1, numer1, denom1,
            10*chara2+(10*numer2)/denom2, (10*numer2)%denom2, denom2) != -1)
        {
            chara2 = 10*chara2+(10*numer2)/denom2;
            numer2 = (10*numer2)%denom2;
            shift++;
        }
        break;
    case -1:
        while (compare(chara1, numer1, denom1,
            chara2/10, numer2+(chara2%10)*denom2, 10*denom2) == -1)
        {
            numer2 = numer2+(chara2%10)*denom2;
            chara2 /= 10;
            // don't increase denom2 unless we have to
            if (numer2 % 10)
            {
                numer1 *= 10;
                denom1 *= 10;
                denom2 *= 10;
            }
            else
            {
                numer2 /= 10;
            }
            shift--;
        }
        numer2 = numer2+(chara2%10)*denom2;
        chara2 /= 10;
        if (numer2 % 10)
        {
            numer1 *= 10;
            denom1 *= 10;
            denom2 *= 10;
        }
        else
        {
            numer2 /= 10;
        }
        shift--;
        break;
    default:
        exit(1); // never reached
    }

    for ( ; shift >= 0; shift--)
    {
        while (compare(chara1, numer1, denom1,
            chara2, numer2, denom2) != -1)
        {
            chara1 -= chara2;
            if (denom1 % denom2 == 0)
            {
                numer1 -= numer2*(denom1/denom2);
            }
            else
            {
                numer1 = numer1*denom2;
                numer2 = numer2*denom1;
                denom1 = denom2 = denom1*denom2;
                numer1 -= numer2*(denom1/denom2);
            }
            if (numer1 < 0)
            {
                numer1 += denom1;
                chara1 -= 1;
            }
            quotient_chara += pow10(shift);
        }
        // divide in2 by 10:
        numer2 = numer2+(chara2%10)*denom2;
        chara2 /= 10;
        if (numer2 % 10)
        {
            numer1 *= 10;
            denom1 *= 10;
            denom2 *= 10;
        }
        else
        {
            numer2 /= 10;
        }
        shift--;
        // decrease numers, denoms if possible
        if (!chara1 && !chara2)
        {
            while (numer1 && numer2 && !(numer1 % 10) && !(numer2 % 10))
            {
                numer1 /= 10;
                numer2 /= 10;
            }
            while (!(denom1 % 10) && !(denom2 % 10))
            {
                denom1 /= 10;
                denom2 /= 10;
            }
        }
    }
    // check if quotient can fit in len chars
    if ((negative ? (length(quotient_chara)+1) : length(quotient_chara)) >= len)
    {
        return false;
    }
    int loc = 0; // current location in string
    if (quotient_chara == 0 && chara1 == 0 && denom1 == 0) // -0 == 0
    {
        negative = false;
    }
    if (negative)
    {
        result[0] = '-';
        loc++;
    }
    int quotient_chara_orig = quotient_chara;
    for (int digit = pow10(length(quotient_chara)); digit > 0; digit /= 10)
    {
        // after the last assignment to result[loc],
        // digit is set to (int)1/10 = 0
        result[loc] = '0'; // ASCII digit zero, not escape character \0
        while(digit <= quotient_chara)
        {
            quotient_chara -= digit;
            result[loc]++;
        }
        // check if first digit is 0
        // if it isn't, continue
        if (loc != (negative ? 1 : 0) || result[loc] != '0')
        {
            loc++;
        }
        
    }
    if (quotient_chara_orig == 0 && !negative)
    {
        // write "0" - otherwise 0/1 outputs ""
        result[loc] = '0';
        loc++;
    }
    if ((len-loc < 2) || (chara1 == 0 && numer1 == 0))
    {
        result[loc] = '\0'; // escape character
        return true;
    }
    // continue adding digits to the end:
    result[loc] = '.';
    loc++;
    while ((chara1 || numer1) && (loc < len-1))
    {
        result[loc] = '0';
        while (compare(chara1, numer1, denom1, chara2, numer2, denom2) != -1)
        {
            chara1 -= chara2;
            if (denom1 % denom2 == 0)
            {
                numer1 -= numer2*(denom1/denom2);
            }
            else
            {
                numer1 = numer1*denom2;
                numer2 = numer2*denom1;
                denom1 = denom2 = denom1*denom2;
                numer1 -= numer2*(denom1/denom2);
            }
            if (numer1 < 0)
            {
                numer1 += denom1;
                chara1 -= 1;
            }
            result[loc]++;
        }
        // divide in2 by 10:
        numer2 = numer2+(chara2%10)*denom2;
        chara2 /= 10;
        if (numer2 % 10)
        {
            numer1 *= 10;
            denom1 *= 10;
            denom2 *= 10;
        }
        else
        {
            numer2 /= 10;
        }
        shift--;
        loc++;
        if (!chara1 && !chara2)
        {
            while (numer1 && numer2 && !(numer1 % 10) && !(numer2 % 10))
            {
                numer1 /= 10;
                numer2 /= 10;
            }
            while (!(denom1 % 10) && !(denom2 % 10))
            {
                denom1 /= 10;
                denom2 /= 10;
            }
        }
    }
    result[loc] = '\0';
    return true;
}
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
	shouldConvertText(shortArray, "0");
	divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvertText(mediumArray, "0");
	divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvertText(largeArray, "0");

	//6 / 3 = "2"
	divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvertText(shortArray, "2");
	divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvertText(mediumArray, "2");
	divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvertText(largeArray, "2");

	//1 / -1.5 = "-.66"
	divide(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvertText(shortArray, "-.66");
	
	//1 / -1.5 = "-.6666666"
	divide(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvertText(mediumArray, "-.6666666");
	
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
	shouldConvertText(shortArray, "0.67");

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvertText(mediumArray, "0.675");

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvertText(largeArray, "0.675");
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
	if (characteristic(number, c))// && mantissa(number, n, d))
	{
		if (c == expectedCharacteristic)// && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			// if (expectedCharacteristic != c)
			// {
			// 	cout << "expected characteristic: " << expectedCharacteristic << " "
			// 		<< "actual characteristic: " << c << endl;
			// }

			// if (expectedNumerator != n)
			// {
			// 	cout << "expected numerator: " << expectedNumerator << " "
			// 		<< "actual numerator: " << n << endl;

			// }

			// if (expectedDenominator != d)
			// {
			// 	cout << "expected denominator: " << expectedDenominator << " "
			// 		<< "actual denominator: " << d << endl;
			// }
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
// void testMath()
// {
// 	//add
// 	testAdd();
// 	testSubtract();
// 	testMultiply();
// 	testDivide();
// }
// //--
// void testAdd()
// {
// 	const int SHORT_ARRAY_LENGTH = 5;
// 	char shortArray[SHORT_ARRAY_LENGTH];

// 	const int MEDIUM_ARRAY_LENGTH = 10;
// 	char mediumArray[MEDIUM_ARRAY_LENGTH];

// 	const int LARGE_ARRAY_LENGTH = 20;
// 	char largeArray[LARGE_ARRAY_LENGTH];

// 	//should not be enough space in the array for the result
// 	if (add(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
// 	{
// 		cout << "Error: not enough space in array" << endl;
// 	}

// 	//0 + 0 = "0"
// 	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, 0, 10);
// 	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, 0, 10);
// 	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, 0, 10);

// 	//1 + 1 = "2"
// 	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 2, 0, 10);
// 	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 2, 0, 10);
// 	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 2, 0, 10);

// 	//1 + -1.5 = "-.5"
// 	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, -5, 10);
// 	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, -5, 10);
// 	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, -5, 10);

// 	//1.125 + 1.6R = "2.79"
// 	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 2, 79, 100);

// 	//1.125 + 1.6R = "2.7916666"
// 	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 2, 7916666, 10000000);

// 	//1.125 + 1.6R = "2.79166666666666666"
// 	add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
// 	//can't use the convert function because the num/denom would overflow
// 	char expectedResult[] = "2.79166666666666666";
// 	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
// 	{
// 		if (expectedResult[i] != largeArray[i])
// 		{
// 			cout << "Error: mismatch in C strings in add()." << endl
// 				<< "Expected: " << expectedResult << " "
// 				<< "Actual: " << largeArray
// 				<< endl;
// 		}
// 	}
// }
// //--
// void testSubtract()
// {
// 	const int SHORT_ARRAY_LENGTH = 5;
// 	char shortArray[SHORT_ARRAY_LENGTH];

// 	const int MEDIUM_ARRAY_LENGTH = 10;
// 	char mediumArray[MEDIUM_ARRAY_LENGTH];

// 	const int LARGE_ARRAY_LENGTH = 20;
// 	char largeArray[LARGE_ARRAY_LENGTH];

// 	//should not be enough space in the array for the result
// 	if (subtract(INT_MIN, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
// 	{
// 		cout << "Error: not enough space in array" << endl;
// 	}

// 	//0 - 0 = "0"
// 	subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, 0, 10);
// 	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, 0, 10);
// 	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, 0, 10);

// 	//2 - 1 = "1"
// 	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 1, 0, 10);
// 	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 1, 0, 10);
// 	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 1, 0, 10);

// 	//1 - -1.5 = "2.5"
// 	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 2, 5, 10);
// 	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 2, 5, 10);
// 	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 2, 5, 10);

// 	//1.125 - 1.6R = "-.54"
// 	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, -54, 100);

// 	//1.125 - 1.6R = "-.5416666"
// 	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, -5416666, 10000000);

// 	//1.125 - 1.6R = "-.54166666666666666"
// 	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
// 	//can't use the convert function because the num/denom would overflow
// 	char expectedResult[] = "-.54166666666666666";
// 	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
// 	{
// 		if (expectedResult[i] != largeArray[i])
// 		{
// 			cout << "Error: mismatch in C strings in subtract()." << endl
// 				<< "Expected: " << expectedResult << " "
// 				<< "Actual: " << largeArray
// 				<< endl;
// 		}
// 	}
// }
// //--
// void testMultiply()
// {
// 	const int SHORT_ARRAY_LENGTH = 5;
// 	char shortArray[SHORT_ARRAY_LENGTH];

// 	const int MEDIUM_ARRAY_LENGTH = 10;
// 	char mediumArray[MEDIUM_ARRAY_LENGTH];

// 	const int LARGE_ARRAY_LENGTH = 20;
// 	char largeArray[LARGE_ARRAY_LENGTH];

// 	//should not be enough space in the array for the result
// 	if (multiply(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
// 	{
// 		cout << "Error: not enough space in array" << endl;
// 	}

// 	//0 * 0 = "0"
// 	multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, 0, 10);
// 	multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, 0, 10);
// 	multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, 0, 10);

// 	//3 * 2 = "6"
// 	multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 6, 0, 10);
// 	multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 6, 0, 10);
// 	multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 6, 0, 10);

// 	//3 * -1.5 = "-4.5"
// 	multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, -4, 5, 10);
// 	multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, -4, 5, 10);
// 	multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, -4, 5, 10);

// 	//1.125 * 1.6R = "1.87"
// 	multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 1, 87, 100);

// 	//1.125 * 1.6R = "1.875"
// 	multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 1, 875, 1000);

// 	//1.125 * 1.6R = "1.875"
// 	multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 1, 875, 1000);
// }
// //--
// void testDivide()
// {
// 	const int SHORT_ARRAY_LENGTH = 5;
// 	char shortArray[SHORT_ARRAY_LENGTH];

// 	const int MEDIUM_ARRAY_LENGTH = 10;
// 	char mediumArray[MEDIUM_ARRAY_LENGTH];

// 	const int LARGE_ARRAY_LENGTH = 20;
// 	char largeArray[LARGE_ARRAY_LENGTH];

// 	//should not be enough space in the array for the result
// 	if (divide(INT_MAX, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
// 	{
// 		cout << "Error: not enough space in array" << endl;
// 	}

// 	//cannot divide by zero
// 	if (divide(10, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
// 	{
// 		cout << "Error: cannot divide by zero" << endl;
// 	}

// 	//0 / 1 = "0"
// 	divide(0, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, 0, 10);
// 	divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, 0, 10);
// 	divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, 0, 10);

// 	//6 / 3 = "2"
// 	divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 2, 0, 10);
// 	divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 2, 0, 10);
// 	divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 2, 0, 10);

// 	//1 / -1.5 = "-.66"
// 	divide(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, -66, 100);
	
// 	//1 / -1.5 = "-.6666666"
// 	divide(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, -6666666, 10000000);
	
// 	//1 / -1.5 = "-.66666666666666666"
// 	divide(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
// 	char expectedResult1[] = "-.66666666666666666";
// 	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
// 	{
// 		if (expectedResult1[i] != largeArray[i])
// 		{
// 			cout << "Error: mismatch in C strings in divide()." << endl
// 				<< "Expected: " << expectedResult1 << " "
// 				<< "Actual: " << largeArray
// 				<< endl;
// 		}
// 	}

// 	//1.125 / 1.6R = "0.67"
// 	divide(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
// 	shouldConvert(shortArray, 0, 67, 100);

// 	//1.125 / 1.6R = "0.675"
// 	divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
// 	shouldConvert(mediumArray, 0, 675, 1000);

// 	//1.125 / 1.6R = "0.675"
// 	divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
// 	shouldConvert(largeArray, 0, 675, 1000);
// }
