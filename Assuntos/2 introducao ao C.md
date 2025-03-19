## Introdução à linguagem de programação C - primeiro programa em C

Um programa em uma linguagem de programação é um texto, que deve ser colocado em um arquivo para que possa ser traduzido por um programa (chamado compilador) para um programa equivalente em linguagem de máquina.
Esse programa em linguagem de máquina também é colocado em um arquivo (não o mesmo), para que possa ser carregado para a memória pelo sistema operacional para então ser executado pelo processador.

Para que a tradução não seja complicada demais, uma linguagem de programação é bastante "chata" sobre como o programa deve ser escrito e formatado.

Um programa na linguagem C é dividido em subprogramas chamados **funções**.
Os comandos que representam ações a serem executadas pelo processador necessariamente devem estar em alguma função. A execução de um programa C é entendida como a execução dos comandos de uma função.

Cada função de um programa é identificada por seu nome.
Um programa C pode ter quantas funções quiser, cada uma com um nome diferente.

Uma das funções é especial, e deve ter o nome `main`. 
Essa é a função principal do programa, e são os comandos dessa função que serão executados quando o programa for executado.
As outras funções só serão executadas se um comando na função `main` causar sua execução.
Por enquanto, faremos programas só com uma função (que obrigatoriamente deverá ser chamada `main`).

Uma função é constituída de 4 partes:
- **tipo** (vamos ver mais tarde para que serve, por enquanto basta sabermos que para a função `main` o tipo tem que ser `int`);
- **nome** (pode ser uma sequência qualquer (quase) de caracteres, mas por enquando vai ser `main`)
- **argumentos**, entre parênteses (por enquanto não vamos usar argumentos, mas os parênteses são obrigatórios)
- **corpo**, entre chaves, é aqui que vão os comandos.

Um programa pode não ter nenhum comando. Portanto, o menor programa C possível é um texto com:
```c
int main(){}
```
que instrui o computador para não fazer nada. Não é exatamente um programa útil...

O corpo da função (dentro das chaves) é composto por **declarações** e **sentenças**, que representam as ações que devem ser executadas pelo programa. Uma sentença pode ser **simples** ou **composta**. Vamos deixar as compostas para mais tarde. Toda sentença simples em C é terminada pelo caractere `;` e geralmente se organiza uma sentença por linha.
A ordem das sentenças é importante, porque elas serão executadas uma por vez, na ordem em que aparecem. Quando a última sentença da função main terminar de ser executada, o programa termina.

Uma declaração reserva uma posição de memória para conter algum valor que será usado pelo programa. Quando se programa em linguagem de máquina, se tem a preocupação de se encontrar uma posição de memória que não seja usada por mais nenhuma parte do programa (ou por outro programa) toda vez que se necessite guardar algum valor.
Em C, dá-se um nome para cada posição de memória que conterá algum valor que o programa irá manipular. Cabe ao compilador encontrar uma posição livre para associar ao nome dado pelo programador. Além do nome, o compilador precisa saber o que será colocado nessa posição, para saber quanto de memória será necessário. Essa informação se chama **tipo** do dado. Uma posição de memória com nome e tipo dados pelo programador é chamada de **variável**. O comando que diz para o compilador que necessitamos de uma variável é chamado de **declaração de variável**. Essa declaração é composta pelo *tipo* seguido do *nome* e termina por `;` (como toda sentença).
Por enquanto iremos usar a memória para guardar valores que irão representar números inteiros. O tipo de dados usado para isso é chamado de **int** em C. Então, para declarar a variável chamada *xis* do tipo *int* usamos:
```c
  int xis;
```
Um nome de variável sempre inicia por uma letra minúscula e continua com letras minúsculas ou maiúsculas, dígitos `0` a `9` ou o caractere `_`. Não pode ter nenhum outro caractere (nem espaço). Pode ter quantos caracteres quiser.

O nome `a9` é válido, o nome `9a` não é. O nome `a_b` é válido, o nome `a-b` não é, nem `a b`.

Colocar um valor em uma posição de memória em C chama-se *atribuir um valor a uma variável*. A sentença que representa essa ação é chamada de *atribuição*, e é formada por 4 partes:
- o nome da variável que irá receber o valor;
- o caractere `=`;
- o valor que será colocado na variável;
- o caractere `;`.

Uma sentença para colocar o valor 37 na posição de memória associada à variável *xis* é:
```c
  xis = 37;
```

O valor que foi codificado na sentença acima é chamado genericamente de *constante*. Uma constante numérica inteira (como o *37* acima) é formada por uma sequência de dígitos entre `0` e `9`, com o primeiro diferente de `0`; podendo ainda ser precedido de `-` ou `+`.

Além de constantes, pode-se informar o valor a ser atribuído a uma variável com outra variável. Por exemplo:
```c
  int xis;
  int ips;
  xis = 37;
  ips = xis;
```
No final desse trecho, as variáveis *xis* e *ips* conteriam o valor 37.

O lado direito de uma atribuição (o que está depois do `=`) contém uma *expressão*, que, além de variáveis e constantes pode ainda conter *operadores aritméticos*.
Os operadores aritméticos de C para valores inteiros são:
- `+` para soma (`5 + 2` vale `7`);
- `-` para subtração (`5 - 2` vale `3`);
- `*` para multiplicação (`5 * 2` vale `10`);
- `/` para divisão (`5 / 2` vale `2`);
- `%` para resto da divisão (`5 % 2` vale `1`).
Podemos então ter atribuições como:
```c
  ips = xis * 10;
  ips = 25 + xis / 2;
  ips = 12 / (xis - 5);
  media = (n1 + n2) / 2;
```
A ordem de cálculo é primeiro as operações multiplicativas (`*/%`), depois as aditivas (`+-`), então `5 + 2 / 2` vale `6`. Essa ordem pode ser alterada com o uso de parênteses: `(5 + 2) / 2` vale `3`.

Podemos fazer uma calculadora!

Para que os valores possam ser vistos, devemos enviá-los a um dispositivo de saída.
A linguagem C não possui comandos para isso!
Felizmente, a linguagem é extensível, e tem extensão para realizar entrada e saída.
Para se poder usar alguma extensão como essa, precisamos informar o compilador, com comandos que pedem para incluir cada extensão que desejamos usar, um por linha. Essas linhas geralmente ficam no início do arquivo C, antes mesmo das funções.
A extensão que nos interessa chama-se `stdio.h` (de *standard input/output* ou entrada e saída padrão).
Para incluí-la, tem que ter, no início do programa, uma linha com:
```c
  #include <stdio.h>
```
Tendo incluído essa extensão, temos acesso a um grande número de funções para realizar entrada e saída. Entre elas, uma das mais básicas é `putchar`, que permite enviar um caractere para o terminal.
A forma de usar é `putchar` seguido pelo valor do caractere que se quer enviar entre parênteses seguido por `;`.
Por exemplo, a sentença
```c
  putchar(65);
```
causará o envio do caractere de código 65 para o terminal. O terminal irá imprimir o caractere `A`, que corresponde a esse código. Quase todos os computadores atualmente usam o código ASCII para codificar os caracteres. Caso tenha curiosidade, pode ver esses códigos por exemplo na [wikipédia](https://pt.wikipedia.org/wiki/ASCII).

Para não precisar saber esses códigos, é possível também colocar o caractere desejado entre apóstrofos:
```c
  putchar('A');
```

O programa completo para imprimir um `A` é então:
```c
  #include <stdio.h>

  int main()
  {
    putchar('A');
  }
```

Para ser compilado, esse texto deve ser colocado em um arquivo, com um nome que termine em `.c`. Por exemplo, `p1.c`.
No ambiente linux, uma compilador para a linguagem C bem conhecido se chama `gcc`. Para executá-lo para compilar o programa C contido no arquivo `p1.c` e colocar o programa em linguagem de máquina equivalente no arquivo `p1`, podemos usar o comando:
```c
  gcc p1.c -o p1
```

Para executar o programa, damos o seguinte comando:
```sh
  ./p1
```

Irá aparecer o caractere `A` na tela do terminal.

### Exercícios

1. Crie um arquivo com o programa acima, compile-o e execute-o.
2. Altere o programa para escrever seu nome. A função putchar só escreve um caractere; tem que chamá-la várias vezes.
