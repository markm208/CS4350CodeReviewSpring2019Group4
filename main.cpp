#include <iostream> //do not include anything other than this

using namespace std;

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2);
char* intToCstr(int characteristic, int numerator, int denominator, char* result, int len);
char* reverseCstr(char* str, int length);

int main()
{
    char result[4];

    add(1,1,4,2,5,6,result, 4);

    cout<<"1 1/4 + 2 5/6 = "<<result<<endl;

	add(1,1,2,0,1,2,result, 4);
	cout<<result<<endl;
    
    return 0;
}

//new functions go here
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

}

void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2){
    n1 *= d2;   //multiply the numerators
    n2 *= d1;   //by the other fraction's denominator
    
    d1 *= d2;   //multiply the denominators
    d2 = d1;    //together
}

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