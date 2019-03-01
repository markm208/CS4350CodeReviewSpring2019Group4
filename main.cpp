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

void characteristicToResult(int characteristic, char*& result, int len){

    int powerOfCharacteristic = 10;
    for(int i = 0; i < len; i++){
        powerOfCharacteristic *= 10;
    }
    int num = 0;

    for(int i = 10; i < powerOfCharacteristic; i *= 10){
        
    }

}