#include <stdio.h>
#include <unistd.h>

int main(void){ 

    printf("Dose NOTEXISTS.FIL exits?\n");
    printf("%s",access("NOTEXISTS.FIL",0)==0? "YES":"NO");
    putchar('\n');
    return 0;
    
}




