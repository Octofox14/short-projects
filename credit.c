#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define AMEX 1
#define MASTERCARD 2
#define VISA 3
#define INVALID 4

/**********************************
    Author: Robert Levesque
    Written: Sept. 2016
    
    This program was written for an edX CS50 Assignment.
    The objective is to take a credit card number provided by the user, and write a program
    that will validate the credit card number and identify the card issuer, (VISA, AMEX or Mastercard)
    given rules for credit card numbers provided in the assignment, ie "All Visa numbers start with 4".
    
**********************************/    
    //Valid Card numbers taken from exercise:
    
    //AMEX
    //card_number = 378282246310005;
    
    //VISA 16
    //card_number = 4012888888881881;
    
    //VISA 13
    //card_number = 4111111111111;
    
    //MASTERCARD
    //card_number = 5105105105105100;


long long card_number;
int nDigits;

int card_type;
bool stop = false;


int largest_two(long long cNumber, int digits)
{
    return floor( cNumber / pow(10, (digits-2)) );
}

int largest_digit(long long cNumber, int digits)
{
    return floor( cNumber / pow(10, (digits-1)) );
}

int main(void)
{
    printf("Number: ");
    
    //card_number = GetLongLong();
    while ( stop == false )
    {
        card_number = GetLongLong();
        
        if (card_number == LLONG_MAX || card_number <= 0)
            printf("Retry: ");
        else
            stop = true;
    }
    

    

    //get length of card number    
    nDigits = floor(log10(card_number)) + 1;
    
    //Store CC digits in number array
    
    if ( card_type != INVALID )
    {
        int numArray[nDigits];
        
        int count = 0;
        
        long long n = card_number;
        
        while (n != 0){
            numArray[count] = n % 10;
            n /= 10;
            count++;
        }
        

        //Checksum algorithm
        count = 1;
        int sum = 0;
      
        
        while (count < nDigits)
        {
            if ( numArray[count]*2 >= 10)
            {
                int sumArray[2];
                
                sumArray[0] = (numArray[count]*2) % 10;
                sumArray[1] = (numArray[count]*2 - sumArray[0]) / 10;
                
                /* debug
                printf("%i", sumArray[0] );
                printf(" +* ");
                printf("%i", sumArray[1]);
                */
                sum += sumArray[1];
                sum += sumArray[0];
            }
            else 
            {
                /*debug
                printf("%i", numArray[count]*2);
                printf(" + ");
                */
                
                sum += numArray[count]*2;
            }
            
            count += 2;
        }
            /*debug
            printf(" = ");
            printf("%i", sum);
            */
        count = 0;
            /* debug
            printf("\n");
            
            printf("%i", sum);
            printf(" + ");
            */
            
        while(count < nDigits)
        {
            sum += numArray[count];
            
            /*debug
            printf("%i", numArray[count]);
            printf(" + ");
            */
            
            count += 2;
        }
            /*debug
            printf(" = ");
            printf("%i", sum);
            */
            
        if ( sum % 10 != 0)
        {
            card_type = INVALID;
        }
        
    }
        
        //check card type based on number of digits, starting numbers
    if (card_type != INVALID)
    {
        if ( nDigits == 15 )
        {
            if ( largest_two( card_number, nDigits ) == 34 || largest_two( card_number, nDigits ) == 37)
                card_type = AMEX;
            else
                card_type = INVALID;
        }
        else if ( nDigits == 13 )
        {
            
            if ( largest_digit( card_number, nDigits ) == 4 )
                card_type = VISA;
            else
                card_type = INVALID;
        }
        else if ( nDigits == 16 )
        {
            
            if ( largest_digit( card_number, nDigits ) == 4 )
                card_type = VISA;
            else if ( largest_two( card_number, nDigits ) >= 51 && largest_two( card_number, nDigits ) <= 55)
            {
                card_type = MASTERCARD;
            }
            else
                card_type = INVALID;
        }
    }
    
   
    //Print out card type
    
    if ( card_type == AMEX)
        printf("AMEX");
    else if ( card_type == VISA)
        printf("VISA");
    else if ( card_type == MASTERCARD)
        printf("MASTERCARD");
    else
        printf("INVALID");
        
    printf("\n");
    
}
