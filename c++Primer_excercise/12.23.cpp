
#include <iostream>
#include <memory>
#include <string>
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

std::unique_ptr<std::string> concat2(std::string& str1, std::string& str2) {
    std::unique_ptr<std::string> result(new std::string);
    result.get()->append(str1);
    result.get()->append(str2);
    return result;
}

int main() {
    char* ch1 = "Hello";
    char* ch2 = "World";
    char_arr_ptr result1 = concat(ch1, ch2);
    std::cout << "result1 " << result1.get() << std::endl;

    std::string str1 = "Greeting ", str2 = "Mr.Zheng";
    std::unique_ptr<std::string> result2 = concat2(str1, str2);
    std::cout << "result2 " << result2.get()->c_str() << std::endl;

    return 0;
}