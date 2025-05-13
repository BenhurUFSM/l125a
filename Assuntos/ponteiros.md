## Referências (ponteiros)

Uma referência é um dado que permite o acesso indireto a um outro dado.
Tendo uma referência para uma variável é possível obter-se o valor dessa variável ou alterar esse valor, mesmo sem ter acesso direto a essa variável.
Um dos principais usos de referências é permitir que uma função possa alterar uma variável de uma outra função, de forma controlada, porque a função detentora da variável passa explicitamente a referência à sua variável para a outra função.
Já usamos referências quando chamamos a função `scanf`.

Nas chamadas a `scanf`, para permitir que a função `scanf` possa alterar as variáveis onde se espera que ela coloque os valores convertidos da entrada, ela necessita de referências para essas variáveis. Por isso a necessidade de se usar o caractere `&` antes do nome de uma variável que vai ser alterada pelo `scanf`. O `&` é um operador que opera sobre uma variável, produzindo uma referência para ela.

Para ser usada, uma referência deve ser colocada em uma variável.
Uma variável que pode receber uma referência para outra é chamada de **ponteiro**.
Por exemplo, se `p` for um ponteiro e `v` for uma outra variável, pode-se alterar esse ponteiro para que ele referencie a variável `v` com o comando
```c
   p = &v;
```
Quando um ponteiro tem uma referência para uma determinada variável, por vezes diz-se que o ponteiro "aponta" para a variável.
Tendo o ponteiro `p` apontando para a variável `v`, pode-se acessar a variável apontada através do operador de "dereferenciação", representado em C pelo caractere `*` (é, o mesmo usado para representar a multiplicação).
Então, para se colocar em `w` o valor da variável `v` que é apontada pelo ponteiro `p`, usa-se o comando:
```c
   w = *p;
```
Para se alterar o valor da variável `v` apontada pelo ponteiro `p`, também usa-se o operador de dereferenciação:
```c
   *p = 42;
```
Uma variável do tipo ponteiro aponta para uma outra variável, que pode ter qualquer tipo da linguagem.
Um ponteiro é "tipado", ele aponta para valores de um determinado tipo.
Para cada tipo existente na linguagem, existe um tipo de ponteiro correspondente.
Quando se declara uma variável como sendo um ponteiro, deve-se também fornecer a informação de qual o tipo de dado para o qual esse ponteiro aponta.
Para se declarar `p` como um ponteiro que aponta para valores do tipo `int`, usa-se:
```c
   int *p;
```
Ou seja, o tipo, seguido de asterisco (de novo!), seguido do nome da variável ponteiro.
Um ponteiro só pode apontar para uma variável desse tipo.

### Passagem de argumentos por referência

Como foi dito, um dos principais usos de ponteiros é para permitir que uma função altere variáveis de outra. 
Para exemplificar, digamos que queremos uma função que calcula a raiz de uma equação de segundo grau, mas queremos também saber se o cálculo deu certo (digamos que se a equação não tem raiz ou se tem mais de uma o cálculo não deu certo). Temos nesse caso duas informações a retornar, o valor da raiz e a informação de ter sido bem sucedido ou não. 
Podemos usar um ponteiro para retornar a raiz e usar o retorno normal da função para informar se tudo deu certo. A função poderia ser algo assim:
```c
   bool raiz_unica2g(float a, float b, float c, float *r)
   {
     float delta = b*b - 4*a*c;
     if (delta == 0) {
       *r = -b/(2*a);
       return true;
     } else {
       return false;
     }
   }
```
A chamada para essa função poderia ser algo como:
```c
  float raiz;
  if (raiz_unica2g(10, 3, 4, &raiz)) {
    printf("a única raiz real da equação 10x² + 3x + 4 é %.2f\n", raiz);
  } else {
    printf("a equação 10x² + 3x + 4 não tem uma só raiz real!\n");
  }
```

* * *

#### Exercícios

1. Faça uma função que calcula as raízes reais de uma equação do segundo grau. Ela deve receber os coeficientes como argumento e retornar as duas raízes através de ponteiros também recebidos como argumento. Deve ainda retornar um bool, que informa se as raízes são reais ou complexas (nesse último caso, que acontece quando se teria que calcular a raiz quadrada de um número negativo, as raízes não são calculadas, e os valores apontados pelos ponteiros são mantidos inalterados). A raiz quadrada pode ser calculada usando a função `sqrt()` (disponível em *math.h*). Faça um programa que usa essa função para encontrar raízes de equações do segundo grau com coeficientes digitados pelo usuário.
1. Faça uma função que recebe 2 ponteiros para inteiros e faz com que o inteiro apontado pelo segundo ponteiro não seja menor que o apontado pelo primeiro. Em outras palavras, se o primeiro for o maior, eles devem ser trocados. A função deve retornar um `bool`, que deve ser `true` se foi necessário trocá-los e `false` se eles já estavam na ordem certa. Dá para ordenar os dados em um vetor usando essa função com o seguinte (algoritmo da bolha):
```c
void ordena(int t, int v[t])
{
  int ntrocas;
  int n = t - 1;
  do {
    ntrocas = 0;
    for (int i = 0; i < n; i++) {
      if (troca(&v[i], &v[i+1])) ntrocas++;
    }
    n--;
  } while (ntrocas > 0);
}
```
Faça um programa para testar se a função acima funciona.
