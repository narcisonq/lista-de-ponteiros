#include <stdio.h>
#include <string.h>

void inverter(char* ptr_inv, char* ptr_str, int i, int len) {
    if (i >= len)
        return;

    *(ptr_inv + len - i - 1) = *(ptr_str + i + 1);

    inverter(ptr_inv, ptr_str, i + 1, len);
}

int main() {
    char str[50]; // String
    char str_inv[50]; // String invertida
    char *ptr_str = str;
    char *ptr_inv = str_inv;
    int i = -1;

    scanf(" %49s", str); // sem espaço

    inverter(ptr_inv, ptr_str, i, strlen(str) - 1);
    *(ptr_inv + strlen(str)) = '\0';

    printf("O inverso da string: %s\n\n", str_inv);

    return 0;
}
