## Passagem de argumentos para a função `main`

A função `main` é a primeira a ser executada por um programa.
Pode-se considerar que ela está sendo chamada pelo sistema operacional, e já vimos que ela retorna um valor do tipo int ao sistema, que indica se o programa foi bem sucedido (valor 0) ou se teve algum problema (qualquer outro valor).

Ela também recebe argumentos do sistema.
O primeiro argumento é um inteiro, o segundo um vetor.
O primeiro contém o tamanho do vetor.
O vetor é um vetor de ponteiros para char, cada um desses ponteiros apontando para uma string.
Essas strings correspondem à linha de comando que foi usada para executar o programa.
Por exemplo, se o programa foi executado com
```c
  ./programa
```
os argumentos que main receberá serão `1` (para dizer que o tem uma string) e o primeiro elemento do vetor conterá a string "./programa".
Se o programa for chamado com
```c
  ./programa 53
```
os argumentos que main receberá serão `2` (para dizer que tem duas strings), o primeiro elemento do vetor conterá a string "./programa", e o segundo conterá "53".

Para obter o 53 do exemplo anterior em uma variável int, o código de main poderia ser:
```c
int main(int argc, char *argv[])
{
  int arg;

  if (argc != 2) {
    printf("Esse programa deve ser executado com um argumento:\n");
    printf("  %s n\n", argv[0]);
    return 1;
  }
  if (sscanf(argv[1], "%d", &arg) != 1) {
    printf("O argumento deve ser um número.\n");
    return 2;
  }
  printf("Obrigado por fornecer o valor %d como argumento.\n", arg);
  // ...
}
```
