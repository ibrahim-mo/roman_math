/* 
 * File:   roman_math.c
 * Author: Ibrahim Almohandes
 *
 * Created on September 16, 2016, 7:20 PM
 */

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Converts decimal (integer) to roman number (as C-string)
*/
char* decimal_to_roman(int num) {
    int size=0, num1000s=0, num100s=0, num10s=0, i;
    char *result=NULL, hundreds[5], tens[5], ones[5];
    int rem = num;

    //Contiguous Ms on the left
    num1000s = rem / 1000;
    if (num1000s > 0) {
        size = num1000s;
        result = (char*) malloc(size+1);
        for (i=0; i < num1000s; i++)
            result[i] = 'M';
        rem %= 1000;
    }
    //CM, DC*, CD, C+
    num100s = rem / 100;
    hundreds[0] = '\0';
    if (num100s > 0) {
        if (num100s == 9) {
            strcpy(hundreds, "CM");
            size += 2;
        }
        else if (num100s >= 5) {
            hundreds[0] = 'D';
            size++;
            for (i=0; i < num100s-5; i++)
                hundreds[i+1] = 'C';
            hundreds[i+1] = '\0';
            size += i;
        }
        else if (num100s == 4) {
            strcpy(hundreds, "CD");
            size += 2;
        }
        else {
            for (i=0; i < num100s; i++)
                hundreds[i] = 'C';
            hundreds[i] = '\0';
            size += i;
        }
        rem %= 100;
    }
    //XC, LX*, XL, X+
    num10s = rem / 10;
    tens[0] = '\0';
    if (num10s > 0) {
        if (num10s == 9) {
            strcpy(tens, "XC");
            size += 2;
        }
        else if (num10s >= 5) {
            tens[0] = 'L';
            size++;
            for (i=0; i < num10s-5; i++)
                tens[i+1] = 'X';
            tens[i+1] = '\0';
            size += i;
        }
        else if (num10s == 4) {
            strcpy(tens, "XL");
            size += 2;
        }
        else {
            for (i=0; i < num10s; i++)
                tens[i] = 'X';
            tens[i] = '\0';
            size += i;
        }
        rem %= 10;
    }
    //IX, VI*, IV, I+
    ones[0] = '\0';
    if (rem > 0) {
        if (rem == 9) {
            strcpy(ones, "IX");
            size += 2;
        }
        else if (rem >= 5) {
            ones[0] = 'V';
            size++;
            for (i=0; i < rem-5; i++)
                ones[i+1] = 'I';
            ones[i+1] = '\0';
            size += i;
        }
        else if (rem == 4) {
            strcpy(ones, "IV");
            size += 2;
        }
        else {
            for (i=0; i < rem; i++)
                ones[i] = 'I';
            ones[i] = '\0';
            size += i;
        }
    }
    //combining all number segments
    if (size > num1000s || size == 0) { //input number can be 0
        result = (char*) realloc(result, size+1);
        i = 0;
        int idx=num1000s;
        while(hundreds[i] != '\0') {
            result[idx] = hundreds[i++];
            idx++;
        }
        i = 0;
        while(tens[i] != '\0') {
            result[idx] = tens[i++];
            idx++;
        }
        i = 0;
        while(ones[i] != '\0') {
            result[idx] = ones[i++];
            idx++;
        }
    }
    result[size] = '\0'; //Add the NULL character

    //printf("Converted decimal %d to roman %s!\n", num, result);
    return result;
}

/*
 * Converts roman number (as C-string) to decimal (integer)
 * Assuming input is a valid roman number
*/
int roman_to_decimal(const char *roman) {
    int num = 0;
    int i = 0;

    while (i < strlen(roman)) {
        if (strncmp(roman+i, "CM", 2) == 0) {
            num += 900;
            i += 2;
            continue;
        }
        if (strncmp(roman+i, "CD", 2) == 0) {
            num += 400;
            i += 2;
            continue;
        }
        if (strncmp(roman+i, "XC", 2) == 0) {
            num += 90;
            i += 2;
            continue;
        }
        if (strncmp(roman+i, "XL", 2) == 0) {
            num += 40;
            i += 2;
            continue;
        }
        if (strncmp(roman+i, "IX", 2) == 0) {
            num += 9;
            i += 2;
            continue;
        }
        if (strncmp(roman+i, "IV", 2) == 0) {
            num += 4;
            i += 2;
            continue;
        }
        if (roman[i] == 'M')
            num += 1000;
        else if (roman[i] == 'D')
            num += 500;
        else if (roman[i] == 'C')
            num += 100;
        else if (roman[i] == 'L')
            num += 50;
        else if (roman[i] == 'X')
            num += 10;
        else if (roman[i] == 'V')
            num += 5;
        else //if (roman[i] == 'I')
            num += 1;
        i++;
    }

    //printf("Converted roman %s to decimal %d!\n", roman, num);
    return num;
}

// Both add_roman() and subtract_roman() assume user passes valid roman numbers as arguments, except:
// 1. NULL input(s) are handled properly (by returning NULL) to prevent crashes
// 2. An empty string input is equivalent to zero (if both inputs are empty, return will be empty)
// 3. For subtraction: if a < b, return NULL

/*
 * Addition of two roman numbers: a + b
 * Both inputs and return are C-strings
*/
char* add_roman(const char *a, const char *b) {
    if (!a || !b)
        return NULL;

    int num = roman_to_decimal(a) + roman_to_decimal(b);

    return decimal_to_roman(num);
}

/*
 * Subtraction of two roman numbers a - b
 * Both inputs and return are C-strings
 * Assuming a >= b
*/
char* subtract_roman(const char *a, const char *b) {
    if (!a || !b)
        return NULL;

    int num = roman_to_decimal(a) - roman_to_decimal(b);
    if (num < 0) //-ve not supported
        return NULL;

    return decimal_to_roman(num);
}
