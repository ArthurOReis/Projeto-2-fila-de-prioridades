# Projeto 2: fila de prioridades

* Código exemplo do `main.c`:
```C
    int clientes_quantidade_classes(char *str) {
        char str_temp[10];
        strcpy(str_temp, str);

        for (int i = 0; str[i] != '\0'; i++) {
            str[i] -= 17; /* Transforma o caractere em um inteiro, para acessar o índice da lista da classe correspondente, exemplo: A => 0; B => 1; C => 2... */
        }
        return atoi(str);
}
```