#include <stdio.h>
#include <string.h>

void inverter(char* ptr_inv, char* ptr_str, char* str, char* str_inv){
    int i = - 1;
    

    for (i; i < (int)strlen(str)-1; i++) {
    *(ptr_inv + strlen(str) - i - 2) = *(ptr_str + i+1);   //fazer isso sem mudar nenhum valor foi foda, mas é só se ligar aonde começa e termina tudo
    }

    
    *(ptr_inv + strlen(str)) = '\0';

}


int main( ){
char str[50]; // String
char str_inv[50]; // String invertida
char *ptr_str = str;
char *ptr_inv = str_inv;
int i = -1;
scanf(" %49s", str); // sem espaço
// scanf(" %[^\n]", str);//com espacço


inverter(ptr_inv, ptr_str, str, str_inv);
    
*(ptr_inv + strlen(str)) = '\0';

printf("O inverso da string: %s\n\n", str_inv);

return 0;
}
