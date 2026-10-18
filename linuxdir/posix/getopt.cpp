#include <iostream>
#include <unistd.h>
#include <cstring>
#include <bits/getopt_core.h>

int main(int argc, char *argv[])
{
    int opt = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    char s1[32] = {0};
    char s2[32] = {0};
    while ((opt = getopt(argc, argv, "ab:c::")) != -1)
    {
        switch(opt)
        {
            case 'a':
                a = 1;
                break;
            case 'b':
                b = 1;
                std::strcpy(s1, optarg);
                break;
            case 'c':
                c = 1;
                std::strcpy(s2, optarg);
                break;
            default:
                break;
        }
    }

    if (a == 1)
        printf("option a\n");
    if (b == 1)
        printf("option b:%s\n", s1);
    if (c == 1)
        printf("option c:%s\n", s2);
    return 0;
}