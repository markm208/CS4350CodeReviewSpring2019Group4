#include <iostream> //do not include anything other than this

using namespace std;

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
