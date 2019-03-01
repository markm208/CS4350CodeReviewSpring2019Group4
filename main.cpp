#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int &c);
int atoi(char * string);

int main(int args, char *argv[])
{
	// driver for the program
	int c = 0;
	char numberToTest[] = "-43.25";
	cout << characteristic(numberToTest, c) << endl;
	cout << c << endl;

	return 0;
}

//new functions go here

bool characteristic(char numString[], int &c)
{
	// first, we're going to want to filter the char array to remove all potential space additions
	// because we are also looping through the array to remove spaces, we may as well store the size
	// of the array for ease of use later

	int arraySize = 0;
	int iterator = 0;

	while (numString[iterator] != '\0')
	{
		if (numString[iterator] != ' ')
		{
			arraySize++;
		}
		iterator++;
	}
	// add the null terminator to the arraySize
	arraySize++;

	// iterate through the array and store all digit characters in a new array;
	// digitArray will store the values of all of the digits that we find from the numString[]
	char * digitArray = new char[arraySize];

	int iterator2 = 0;

	while (numString[iterator2] != '\0')
	{
		if (numString[iterator2] != ' ')
		{
			// if the iterator has reached a digit in the string, we can use the tail array to jump to the digit so it can only store digits.
			*digitArray = numString[iterator2];
			// increment both the digitArray pointer and the iterator so that it is pointing to the next spot in the char[];
			digitArray++;
			iterator2++;
		}
		else
		{
			// the char is not important so we just increment
			iterator2++;
		}
	}
	// now we should add a null terminator to our digitArray;
	//*digitArray = '\0';

	// currently, our digitArray holds the number without spaces, so we should check to see if it is a valid number.

	// we can loop through the array to check the values and determine if it is valid or not

	int iterator3 = 0;
	while (digitArray[iterator3] != '\0')
	{
		if (digitArray[iterator3] == '.')
		{
			return true;
		}
		else if (digitArray[iterator3] < '0' || digitArray[iterator3] > '9')
		{
			return false;
		}
		// else just increment the iterator to loop through char[]
		iterator3++;
	}

	// if we haven't return false by this point, then the value is a good input, and we can change the value of c to our atoi function return
	c = atoi(numString);
	return true;

}

int atoi(char * string)
{
	int result = 0;
	int sign = 1;
	int decimal = '.';
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
		// if the string finds a decimal point, cut it off and return what it has so far stored in the result.
		if (string[i] == decimal)
		{
			break;
		}
		// to handle blank space
		if (string[i] == ' ')
		{
			// skip over the char
			i++;
		}
		if (string[i] > '9' || string[i] < '0')
		{
			// not a digit so return 0;
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