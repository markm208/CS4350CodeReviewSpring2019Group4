#include <iostream> //do not include anything other than this

using namespace std;



bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    float new_num = 0;
    int new_n1 = 0;
    int new_n2 = 0;
    int new_d2 = 0;
    int new_d1 = 0;
    // see if the characteristic is 0 and if not add the denominator times the characteristic to the numerator
    if (c1 != 0)
    {
        new_n1 = n1 + (d1 * c1);
    }
    // see if the characteristic is 0 and if not add the denominator times the characteristic to the numerator
    if(c2 != 0)
    {
        new_n2 = n2 + (d2 * c2);
    }
    //if the two denominators are equal subtract the numerator that is the smallest from the biggest and make it the new numerator
    if(d1 == d2)
    {
        if(n1 == n2)
        {
            new_num = 0;
        }
        if(n1 > n2)
        {
            new_num = n1 - n2;
            new_num = new_num / d1;
        }
        if(n2 > n1)
        {
            new_num = n2 - n1;
            new_num = new_num / d1;
        }
    }
    else
    {
        //check if d2 goes into d1 evenly then divide d1 by d2 to find what number is the common denominator
        if(d1 % d2 == 0)
        {
            new_d2 = d1;
            //then subtract the numerators after checking them
            if(n1 > n2)
            {
                new_num = n1 - n2;
                new_num = new_num / new_d2;
            }
            if(n2 > n1)
            {
                new_num = n2 - n1;
                new_num = new_num / new_d2;
            }
        }
        //check if d1 goes into d2 evenly then divide d2 by d1 to find what number is the common denominator
        if(d2 % d1 == 0)
        {
            new_d1 = d2;
            //then subtract the numerators after checking them
            if(n1 > n2)
            {
                new_num = n1 - n2;
                new_num = new_num / new_d1;
            }
            if(n2 > n1)
            {
                new_num = n2 - n1;
                new_num = new_num / new_d1;
            }
        }
        //if the denominators don't go into each other evenly find the common denominator
        else
        {
            int com_dom = d1 * d2;
            //while the denominators go into the com_dom whithout remaniders cut the com_dom in half
            new_n1 = n1 * d2;
            new_n2 = n2 * d1;

            if(new_n1 > new_n2)
            {
                new_num = (new_n1 - new_n2) / com_dom;
                
            }
            if(new_n2 > new_n1)
            {
                new_num = (new_n2 - new_n1) / com_dom;
                
            }

           

        }
        result[sizeof(new_num)] = '0' + new_num;
    }
    
}


//new functions go here