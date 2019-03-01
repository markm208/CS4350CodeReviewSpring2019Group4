#include <iostream> //do not include anything other than this

using namespace std;

void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2);
void characteristicToResult(int characteristic, char*& result, int len);

int main()
{

    char sum[5];
    add(1,1,3,2,7,8,sum,5);
    cout<<"This is the sum: "<<sum<<endl;
    return 0;
}

//new functions go here
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    
    convertToCmnDenom(n1, d1, n2, d2);

    int cSum = c1 + c2; //add the integers together
    int nSum = n1 + n2; //add the numerators together

    cSum += nSum/d1; //add any overflow from the fraction
    nSum -= (nSum/d1)*d1; //subtract that overflow from the fraction

    characteristicToResult(cSum, result, len);

}

void convertToCmnDenom(int& n1, int& d1, int& n2, int& d2){
    n1 *= d2;   //multiply the numerators
    n2 *= d1;   //by the other fraction's denominator
    
    d1 *= d2;   //multiply the denominators
    d2 = d1;    //together
}

char* intToCstr(int characteristic, int numerator, int denominator, char* result, int len) {
	int i = 0;
	bool isNegative = false;

	if (characteristic == 0)	//checks to see if the characteristic is just 0
	{
		result[i] = '0';
		i++;
		result[i] = '.';
		i++;
		result[i] = '\0';
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

	cout << result << endl;

	//now reverse the string
	result = reverseCstr(result, i);

	for (int decimalPlace = i; decimalPlace < len; decimalPlace++) {
		result[decimalPlace] = (numerator % denominator) + '0';
	}

	return result;
}

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