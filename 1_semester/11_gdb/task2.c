#include <stdio.h>  
  
typedef struct 
{  
    int num;  
    char str[];      
} NumberRepr;  
  
void format(NumberRepr* number)  
{      
    sprintf(number->str, "%d", number->num);  
}   

int main()  
{  
    NumberRepr number = { .num = 102500 };  
    format(&number);  
    printf("str: %s\n", number.str);      
    printf("num: %d\n", number.num);  
    return 0;  
}  
