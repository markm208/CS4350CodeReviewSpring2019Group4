#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int chara1, int numer1, int denom1,
    int chara2, int numer2, int denom2,
    char result[], int len);

int main()
{
    // testing:
    char result[10];
    if (!divide(5, 0, 1, 2, 0, 1, result, 5))
    {
        cout << "Failed to divide" << endl;
    }
    else
    {
        cout << result << endl;
    }
    if (!divide(5, 5, 6, 2, 0, 1, result, 10))
    {
        cout << "Failed to divide" << endl;
    }
    else
    {
        cout << result << endl;
    }
    if (!divide(5, 0, 1, 2, 1, 2, result, 5))
    {
        cout << "Failed to divide" << endl;
    }
    else
    {
        cout << result << endl;
    }
    if (!divide(-100, 0, 1, 1, 0, 1, result, 5))
    {
        cout << "Failed to divide" << endl;
    }
    else
    {
        cout << result << endl;
    }
    if (!divide(-100, 0, 1, 1, 0, 1, result, 4))
    {
        cout << "Failed to divide (good)" << endl;
    }
    else
    {
        cout << "Error: " << result << endl;
    }
    return 0;
}

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
    return 0;
}

int length(int chara)
{
    // returns the number of digits required to represent chara in decimal
    int retval = 0;
    int accum = 1;

    if (chara == 0)
    {
        return 1;
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
            chara1 = -chara1-1;
            numer1 = denom1-numer1;
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
            chara2 = -chara2-1;
            numer2 = denom2-numer2;
        }
        negative = !negative;
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
    }
    // check if quotient can fit in len chars
    if ((negative ? (length(quotient_chara)+1) : length(quotient_chara)) >= len)
    {
        return false;
    }
    int loc = 0; // current location in string
    if (negative)
    {
        result[0] = '-';
        loc++;
    }
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
    }
    result[loc] = '\0';
    return true;
}
