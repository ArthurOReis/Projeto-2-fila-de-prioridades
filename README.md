# Projeto 2: fila de prioridades

* Código exemplo do `char *converte_para_classe()`:
```C
char *converte_para_classe(int index){
    char *classe_num = malloc(3);
    if (classe_num == NULL) return NULL;

    sprintf(classe_num, "%d", index);
    for (int i = 0; classe_num[i] != '\0'; i++) {
        classe_num[i] += 17; /* Transforma o inteiro em um caractere, para acessar a chave do hash que é a classe dos clientes, exemplo: 0 => A; 1 => B; 2 => C... */
    }

    return classe_num;
    }
```
Implementamos essa função para poder converter um valor inteiro de 0 até 5 para uma string de "A" até "f"

* Código exemplo do `int clientes_quantidade_classes(char *str)`:
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
Essa função é o inverso da "converte_para_classe", pois passamos uma string "a" até "f" e obtemos o seu correspondente de 0 até 5