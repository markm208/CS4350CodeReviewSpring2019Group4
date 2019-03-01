#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int &c);
int atoi(char * string);

int main(int args, char *argv[])
{
	// driver for the program
	int c = 0;
	char numberToTest[] = "-443.25";
	cout << "Returned: " << characteristic(numberToTest, c) << endl;
	cout << c << endl;

	return 0;
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
	char * iterate = new char[sizeWithoutSpaces];
    char * digitArray = iterate;

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