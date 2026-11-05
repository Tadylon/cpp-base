#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>

#include "print_obj.h"

int main()
{

    {
        FILE* txt = std::fopen("a.txt", "r");
    
        if (txt == nullptr) {
            std::cout << "fail to open this file !" << std::endl;
            return -1;
        }
        
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), txt) != NULL) {
            std::cout << buffer;   // fgets 保留换行符，所以不用加 endl
        }
        fclose(txt);
    }

    {
        FILE* out = std::fopen("a.txt", "a+");
        if (out) {
            fprintf(out, "User: %s, Mark: %d\n", "wine", 88);
            fputs("this a text to append !\n", out);
            fclose(out);
        }
    }
    return 0;
}