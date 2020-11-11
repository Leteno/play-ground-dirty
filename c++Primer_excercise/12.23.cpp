
#include <iostream>
#include <memory>
#include "string.h"

typedef std::unique_ptr<char[]> char_arr_ptr;

char_arr_ptr concat(char* ch1, char* ch2) {
    int len1 = strlen(ch1), len2 = strlen(ch2);
    char_arr_ptr result(new char[len1 + len2 + 1]);

    char* ptr = result.get();
    for (int i = 0; i < len1; i++, ptr++) {
        *ptr = ch1[i];
    }
    for (int i = 0; i < len2; i++, ptr++) {
        *ptr = ch2[i];
    }
    *ptr = '\0';
    return result;
}

int main() {
    char* ch1 = "Hello";
    char* ch2 = "World";
    char_arr_ptr result1 = concat(ch1, ch2);
    std::cout << "result1 " << result1.get() << std::endl;

    return 0;
}