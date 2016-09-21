#include <stdio.h>
#include <stdlib.h>
#include "roman_math.h"

int main(void) {

    char* result1 = add_roman("CCCLVI", "MMMCDXXIX");  // 356 + 3429 = 3785
    char* result2 = subtract_roman("MMMMMDCCCLXXXIV", "CDXLII"); // 5884 - 442 = 5442
    
    printf("%s\n", result1); // MMMDCCLXXXV
    printf("%s\n", result2); // MMMMMCDXLII

    free(result1);
    free(result2);
    
    return 0;
}
