/* 
 * File:   roman_math.c
 * Author: Ibrahim Almohandes
 *
 * Created on September 16, 2016, 7:20 PM
 */
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* uncompact(const char* a) {
    int n = strlen(a);
    char *str = malloc(n + 10);
    int i=0, j=0;
    while (i < n) {
        if (strncmp(a+i, "CM", 2)==0) { // CM -> DCCCC
            strcpy(str+j, "DCCCC");
            i += 2;
            j += 5;
        }
        else if (strncmp(a+i, "CD", 2)==0) { // CD -> CCCC
            strcpy(str+j, "CCCC");
            i += 2;
            j += 4;
        }
        else if (strncmp(a+i, "XC", 2)==0) { // XC -> LXXXX
            strcpy(str+j, "LXXXX");
            i += 2;
            j += 5;
        }
        else if (strncmp(a+i, "XL", 2)==0) { // XL -> XXXX
            strcpy(str+j, "XXXX");
            i += 2;
            j += 4;
        }
        else if (strncmp(a+i, "IX", 2)==0) { // IX -> VIIII
            strcpy(str+j, "VIIII");
            i += 2;
            j += 5;
        }
        else if (strncmp(a+i, "IV", 2)==0) { // IV -> IIII
            strcpy(str+j, "IIII");
            i += 2;
            j += 4;
        }
        else {
            str[j] = a[i];
            i++;
            j++;
        }
    }
    str[j] = '\0';
    return str;
}

static char* compact(const char* a) {
    int n = strlen(a);
    char *str = malloc(n + 1);
    int i=0, j=0;
    while (i < n) {
        if (strncmp(a+i, "DCCCC", 5)==0) { // DCCCC -> CM
            strcpy(str+j, "CM");
            i += 5;
            j += 2;
        }
        else if (strncmp(a+i, "CCCC", 4)==0) { // CCCC -> CD
            strcpy(str+j, "CD");
            i += 4;
            j += 2;
        }
        else if (strncmp(a+i, "LXXXX", 5)==0) { // LXXXX -> XC
            strcpy(str+j, "XC");
            i += 5;
            j += 2;
        }
        else if (strncmp(a+i, "XXXX", 4)==0) { // XXXX -> XL
            strcpy(str+j, "XL");
            i += 4;
            j += 2;
        }
        else if (strncmp(a+i, "VIIII", 5)==0) { // VIIII -> IX
            strcpy(str+j, "IX");
            i += 5;
            j += 2;
        }
        else if (strncmp(a+i, "IIII", 4)==0) { // IIII -> IV
            strcpy(str+j, "IV");
            i += 4;
            j += 2;
        }
        else {
            str[j] = a[i];
            i++;
            j++;
        }
    }
    str[j] = '\0';
    return str;
}

static void shift_left(char *str, int pos, int count) {
    int n = strlen(str);
    char* tmp = malloc(n-pos-count+1);
    strncpy(tmp, str+pos+count, n-pos-count);
    tmp[n-pos-count] = '\0';
    strcpy(str+pos, tmp);
    free(tmp);
}

/*
 * Addition of two roman numbers (both inputs and return are C-strings)
 * Steps:
 * 1. uncompact the two numbers by substituting for any subtractives
 * 2. concatenate the two values together
 * 3. sort the symbols in order from left-to-right
 * 4. starting from right, group symbols that can make a larger one and substitute them
 * 5. compact the result by substituting any subtractives
*/
char* add_roman(const char *a, const char *b) {
    if (!a || !b)
        return NULL;

    //step 1: uncompact a & b
    char *str1 = uncompact(a);
    char *str2 = uncompact(b);
    //printf("Step1: %s, %s\n", str1, str2);

    //step2: concatenate the strings
    int n = strlen(str1) + strlen(str2);
    char *str = malloc(n + 1);
    strcpy(str, str1);
    strcat(str, str2);
    free(str1);
    free(str2);
    //printf("Step2: %s\n", str);

    //step 3: order the symbols from left (highest) to right (lowest)
    char symbols[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    int i=0, k;
    for (k=0; k<7; k++) {
        char symbol = symbols[k];
        int j=i;
        while(j<n) {
            if (str[j]==symbol) { //swap symbols
                char tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
                i++;
            }
            j++;
        }
    }
    //printf("Step3: %s\n", str);

    //step4: group into larger symbols (strating from right)
    i = n-1;
    int cnt_I=0, cnt_X=0, cnt_C=0, cnt_V=0, cnt_L=0, cnt_D=0;
    while (i >= 0 && str[i] != 'M') {
        if (str[i]=='I') { // left-most IIIII -> V
            cnt_I++;
            if (cnt_I >= 5 && (i==0 || str[i-1] != 'I')) {
                str[i] = 'V';
                shift_left(str, i+1, 4);
                cnt_V++;
            }
        }
        else if (str[i]=='X') { // left-most XXXXX -> L
            cnt_X++;
            if (cnt_X >= 5 && (i==0 || str[i-1] != 'X')) {
                str[i] = 'L';
                shift_left(str, i+1, 4);
                cnt_L++;
            }
        }
        else if (str[i]=='C') { // left-most CCCCC -> D
            cnt_C++;
            if (cnt_C >= 5 && (i==0 || str[i-1] != 'C')) {
                str[i] = 'D';
                shift_left(str, i+1, 4);
                cnt_D++;
            }
        }
        else if (str[i]=='V') { // left-most VV -> X
            cnt_V++;
            if (cnt_V >= 2 && (i==0 || str[i-1] != 'V')) {
                str[i] = 'X';
                shift_left(str, i+1, 1);
                cnt_X++;
            }
        }
        else if (str[i]=='L') { // left-most LL -> C
            cnt_L++;
            if (cnt_L >= 2 && (i==0 || str[i-1] != 'L')) {
                str[i] = 'C';
                shift_left(str, i+1, 1);
                cnt_C++;
            }
        }
        else if (str[i]=='D') { // left-most DD -> M
            cnt_D++;
            if (cnt_D >= 2 && (i==0 || str[i-1] != 'D')) {
                str[i] = 'M';
                shift_left(str, i+1, 1);
                break;
            }
        }
        i--;
    }
    //printf("Step4: %s\n", str);

    //step 5: compact the result
    char* result = compact(str);
    free(str);

    return result;
}

static void cross_out(char* a, char* b) {
    //cross out common symbols
    int n1 = strlen(a);
    int n2 = strlen(b);
    int i=n1-1, j=n2-1;
    int cnt=0;
    while (i >= 0 && j >= 0) {
        while (i >= 0 && j >= 0 && a[i] == b[j]) {
            cnt++;
            i--;
            j--;
        }
        if (cnt > 0) {
            shift_left(a, i+1, cnt);
            shift_left(b, j+1, cnt);
            cnt = 0;
        }
        int last_i = i;
        while (i>=0 && j>=0 && a[i] != b[j]) {
            i--;
            if (i < 0 && j >=0 ) {
                i = last_i;
                j--;
            }
        }
    }
}

static void replace(char *s, int pos, const char* t) {
    int n = strlen(s);
    int m = strlen(t);
    int i;
    for (i=n-1; i>pos; i--) //from pos, shift chars right by m
        s[i+m-1] = s[i];
    s[n+m-1] = '\0';
    strncpy(s+pos, t, m);
}

static void expand_to(char* a, char c) {
    int i = strlen(a)-1;
    while (i >= 0) {
        if (a[i] == c)
            break;
        if (a[i] == 'I' ||
            (a[i] == 'V' && c != 'I') ||
            (a[i] == 'X' && c != 'V' && c != 'I') ||
            (a[i] == 'L' && c != 'X' && c != 'V' && c != 'I') ||
            (a[i] == 'C' && c != 'L' && c != 'X' && c != 'V' && c != 'I') ||
            (a[i] == 'D' && c != 'C' && c != 'L' && c != 'X' && c != 'V' && c != 'I')) {
            i--;
            continue;
        }
        if (a[i] == 'V') {
            replace(a, i, "IIIII");
            i += 4;
        }
        else if (a[i] == 'X') {
            replace(a, i, "VV");
            i += 1;
        }
        else if (a[i] == 'L') {
            replace(a, i, "XXXXX");
            i += 4;
        }
        else if (a[i] == 'C') {
            replace(a, i, "LL");
            i += 1;
        }
        else if (a[i] == 'D') {
            replace(a, i, "CCCCC");
            i += 4;
        }
        else { //if (a[i] == 'M')
            replace(a, i, "DD");
            i += 1;
        }
    }
}


/*
 * Subtraction of two roman numbers (both inputs and return are C-strings)
 * Assume a >= b already
 * Steps:
 * 1. uncompact the two numbers by substituting for any subtractives
 * 2. cross out common symbols from second as follows:
 *    - if symbol appears in first, simply corss it out from both
 *    - else: from right, expand first larger symbol in first into multiples of the symbol in second
 *    - repeat the above sub-steps till second is empty
 * 3. compact the result by substituting any subtractives
*/
char* subtract_roman(const char *a, const char *b) {
    if (!a || !b)
        return NULL;

    //step 1: uncompact a & b
    char *str1 = uncompact(a);
    char *str2 = uncompact(b);
    //printf("Step1: %s, %s\n", str1, str2);

    //step 2: cross out common symbols
    char *str = malloc(strlen(str1) + 17); //make str big enough for expansion
    strcpy(str, str1);
    free(str1);
    while (strcmp(str2, "") != 0) { //stop when second is empty
        cross_out(str, str2);
        if (strcmp(str2, "") == 0) //done
            break;
        expand_to(str, str2[strlen(str2)-1]);
    }
    //printf("Step2: %s\n", str);

    //step 3: compact the result
    char* result = compact(str);
    free(str);

    return result;
}
