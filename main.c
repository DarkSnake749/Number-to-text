/* 
----- Important note -----

Each printing function return 0 (false) or 1 (true). 
It means if it need to skip the current power (the big_number charts) because of the zeroes.

--------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0

const char *digits[]     = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *exceptions[] = {"ten", "eleven", "twelve"};
const char *two_digits[] = {"twen", "thir", "four", "fif", "six", "seven", "eigh", "nine"};
const char *big_number[] = {
    "thousand",
    "million",
    "billion",
    "trillion",
    "quadrillion",
    "quintillion",
    "sextillion",
    "septillion",
    "octillion",
    "nonillion",
    "decillion",
    "undecillion",
    "duodecillion",
    "tredecillion",
    "quattuordecillion",
    "quindecillion",
    "sexdecillion",
    "septendecillion",
    "octodecillion",
    "novemdecillion",
    "vigintillion"
};

typedef struct digit_list
{
    char *digits;
    int digit_count;
    int extension;
} d_list;

int convert(char digit) {
    return digit - '0';
}

int one(d_list *num, int idx) 
{
    int int_num = convert( num->digits[idx] );

    // Skip if 0
    if ( int_num == 0) {
        return true;
    }

    printf("%s ", digits[int_num]);
    return false;
}

int two(d_list *num, int idx) 
{
    int first = convert( num->digits[idx] );
    int second = convert( num->digits[idx + 1] );

    // Skip if 0
    if ( first == 0 ) {
        return one(num, idx + 1);
    }

    // Verify for exceptions
    if ( first == 1 ) {
        if ( second < 3 ) {
            printf("%s ", exceptions[second]);
            return false;
        }

        printf("%steen ", two_digits[second - 2]);
        return false;
    }

    printf("%sty ", two_digits[first - 2]);
    one(num, idx + 1);
    return 0;
}

int three(d_list *num, int idx) {
    int need_to_skip = one(num, idx);

    if ( !need_to_skip ) {
        printf("hundred ");
        two(num, idx + 1);
        return false;
    } 

    return two(num, idx + 1);
}

int log_10(int x) {
    if ( x == 0) {
        return 0;
    }
    double nf = log10( (double)x );
    return (int)nf;
}

int main(int argc, char **argsv) 
{   
    if ( argc == 1 ) {
        printf("%s\n", digits[0]);
        return 0;
    }

    d_list number;
    number.digits = argsv[1];
    number.digit_count = strlen(argsv[1]);
    number.extension = number.digit_count % 3;
    int current_count = (number.digit_count - number.extension) / 3;
    if ( current_count > 22 ) {
        current_count = 22;
    }

    int count_to_skip_for_zero = current_count + 1;

    if ( 
        number.digits[0] < '0' || number.digits[0] > '9' ||
        ( number.digit_count > 1 && ( number.digits[0] < '0' || number.digits[0] > '9' )) ||
        ( number.digit_count > 2 && ( number.digits[0] < '0' || number.digits[0] > '9' ))
    ) {
        printf("Error: data computed was not a digit.\n");
        return 1;
    } 

    int need_to_skip = true;
    switch ( number.extension ) 
    {
    case 1:
        need_to_skip = one(&number, 0);
        break;
    
    case 2:
        need_to_skip = two(&number, 0);
        break;
    }
    
    if ( !need_to_skip ) {
        printf("%s ", big_number[current_count-1]);
    } else {
        count_to_skip_for_zero--;
    }
    
    need_to_skip = false;
    int i = number.extension;
    while ( i < number.digit_count) {
        if ( 
            number.digits[i]   < '0' || number.digits[i]   > '9' ||
            number.digits[i+1] < '0' || number.digits[i+1] > '9' ||
            number.digits[i+2] < '0' || number.digits[i+2] > '9'
        ) {
            printf("Error: data computed was not a digit.\n");
            return 1;
        }

        if ( current_count == 0 ) {
            current_count = 22;
        }

        need_to_skip = three(&number, i);

        if ( !need_to_skip && current_count != 1) {
            printf("%s ", big_number[current_count-2]);
        } else if ( need_to_skip ) {
            count_to_skip_for_zero--;
        }

        current_count -= 1;
        i += 3;
    }

    if ( count_to_skip_for_zero <= 0 ) {
        printf("%s", digits[0]);
    } 

    printf("\n");
    return 0;
}