#include <stdio.h>
#include <string.h>
int main( ){
char str[50]; // String
char str_inv[50]; // String invertida
char *ptr_str = str;
char *ptr_inv = str_inv;
int i = -1;
scanf(" %49s", str); // sem espaço
// scanf(" %[^\n]", str);//com espacço

//printf("\n%d\n\n", strlen(str));
  


for (i; i < (int)strlen(str)-1; i++) {
    *(ptr_inv + strlen(str) - i - 2) = *(ptr_str + i+1);   //fazer isso sem mudar nenhum valor foi foda, mas é só se ligar aonde começa e termina tudo
}

    // Null-terminate the inverted string
*(ptr_inv + strlen(str)) = '\0';

printf("O inverso da string: %s\n\n", str_inv);

return 0;
}
