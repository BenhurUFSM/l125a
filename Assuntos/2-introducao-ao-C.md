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

<a id="mpp"></a>
### Meu primeiro programa em C

Juntando isso tudo, podemos fazer nosso primeiro programa em C.
O programa irá imprimir o caractere `A` na tela.
Não é muita coisa, mas serve para começar...
O texto completo desse programa é:
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

Para executar o programa, necessitamos que o conteúdo desse arquivo seja colocado na memória e a CPU instruída a executar suas instruções. Quem faz isso é o sistema operacional. No caso do linux, isso pode ser feito com o seguinte comando:
```sh
  ./p1
```

O programa será executado, e irá aparecer o caractere `A` na tela do terminal.

Alguns caracteres não podem ser codificados diretamente dessa forma, dentro das aspas. Por exemplo, a próprio caractere que representa a aspa. Para isso, se criou uma forma alternativa de codificar certos caracteres, com o uso do caractera `\`. Então, para imprimir o caractere `'`, usa-se `putchar('\'');`, e para a barra imvertida, usa-se `'\\'`.

Alguns caracteres de controle são também codificados dessa forma. O mais útil deles é o caractere que representa o final de uma linha, que quando impresso causa a movimentação do cursor para o início da linha seguinte. A forma de codificá-lo é com `'\n'`. O comando `putchar('\n');` causa mudança de linha no terminal. Para mais detalhes sobre esses caracteres, pode olhar [aqui](https://en.wikipedia.org/wiki/Escape_sequences_in_C), por exemplo.

* * *

### Exercícios

1. Crie um arquivo com o programa acima, compile-o e execute-o.
2. Altere o programa para escrever seu nome. A função `putchar` só escreve um caractere; tem que chamá-la várias vezes. A função `putchar` não é boa para caracteres acentuados.

### Programa da média

O programa exemplo que usamos com linguagem de montagem foi um programa para calcular a média de 2 números. Como fazer isso em C? O cálculo da média em C é simples:
```c
  media = (n1 + n2) / 2;
```
Então, podemos fazer um programa simples para calcular a média de 2 números:
```c
#include <stdio.h>

// programa para calcular a média de 2 números
// quanto encontra "//", o compilador ignora até o final da linha
// isso é chamado de "comentário", e serve para os humanos que lerão o programa

int main()
{
  int n1;
  int n2;  // as duas variáveis poderiam ser declaradas juntas, com "int n1, n2;"
  int media;

  n1 = 8;
  n2 = 6;

  media = (n1 + n2) / 2;
}
```

Compilando e executando esse programa, parece que ele não faz nada. Ele calcula a média, mas não tem um comando para mostrar o resultado.
Se colocarmos `putchar(media);`, estaremos comandando a escrita do caractere que tem o código correspondente ao valor da média, que não é o que queremos.
Queremos que ele escreva o caractere que corresponde ao valor da média: se a média for 0, que imprima o caractere '0', se for 1, que imprima '1', e assim por diante. Se olharmos a tabela de códigos de caracteres, vamos ver que o código do caractere '0' não é 0. Por "sorte", os códigos dos caracteres que representam os dígitos na tabela estão em ordem: o código do '1' está 1 além do código do '0', o código do '5' está 5 além do '0' etc.
Então, para imprimir o caractere que corresponde ao valor `x`, devemos imprimir o caractere que tem o código que fica `x` além do código do caractere '0'.
O código do caractere '0' pode ser obtido por `'0'`, então podemos imprimir o caractere correspondente ao valor `x` imprimindo o caractere com o código `'0' + x`.

O programa da média fica então:
```c
#include <stdio.h>

// programa para calcular *e imprimir* a média de 2 números

int main()
{
  int n1, n2;
  int media;

  n1 = 8;
  n2 = 6;

  media = (n1 + n2) / 2;

  putchar('0' + media);
}
```

Esse programa tem uma só chamada à função `putchar`, o que quer dizer que ele vai imprimir só um caractere. Para valores da média até 9 tudo bem, mas o que acontece se a média for maior?
Altere o programa e veja!

Para imprimir números maiores, precisamos imprimir mais caracteres, precisamos mais chamadas a `putchar`. Precisamos calcular o código de cada caractere a imprimir.
Usando a mesma técnica de anter, para números de dois dígitos precisamos dois valores, entre 0 e 9, para somar com o valor de '0' para obter o código de cada caractere a imprimir. Por exemplo, para imprimir o valor 37, precisamos obter o valor 3 e o valor 7, para posteriormente obter o código dos dois caracteres, '3' e '7'.

Esses valores podem ser obtidos com uma operação de divisão: dividindo 37 por 10, obtém-se 3 e o resto é 7. 53 dividido por 10 é 5, resto 3, etc.

Transformando em um programa:
```c
#include <stdio.h>

// programa para calcular *e imprimir* a média de 2 números,
// mesmo que sejam necessários 2 dígitos

int main()
{
  int n1, n2;
  int media;

  n1 = 85;
  n2 = 61;

  media = (n1 + n2) / 2;

  int d1, d2;

  d1 = media / 10;  // obtém a dezena
  d2 = media % 10;  // obtém o unidade

  putchar('0' + d1);
  putchar('0' + d2);

  putchar('\n'); // pula a linha
}
```

E se o número a imprimir tiver 3 dígitos?
Podemos separar ele em dois: um contendo a unidade o outro contendo o restante (a centena e a dezena). Imprimimos primeiro a centena e dezena como um número de 2 dígitos, e depois a unidade como um número de 1 dígito. Por exemplo, para imprimir o número 128, imprimimos o número 12 com 2 dígitos seguido pelo número 8 com um dígito. Para obter o 12, divide-se 128 por 10, o 8 tá no resto da divisão. Em código:
```c
#include <stdio.h>

// programa para calcular *e imprimir* a média de 2 números,
// mesmo que sejam necessários 3 dígitos

int main()
{
  int n1, n2;
  int media;

  n1 = 185;
  n2 = 61;

  media = (n1 + n2) / 2;

  int mcd, mu; // centena+dezena e unidade da média

  mcd = media / 10;
  mu = media % 10;

  // imprime mcd com 2 dígitos
  int d1, d2;

  d1 = mcd / 10;
  d2 = mcd % 10;

  putchar('0' + d1);
  putchar('0' + d2);

  // imprime mu com 1 dígito
  putchar('0' + mu);

  putchar('\n'); // pula a linha
}
```

Nosso programa está ficando complicado; se ainda não foi o caso, não deve precisar adicionar muita coisa para que ele fique incompreensível.
É necessário alguma forma de melhorar a organização do programa, já que queremos poder fazer programas mais complexos que esse.
Uma das ferramentas mais poderosas para nos capacitar a lidar com a complexidade que um programa pode ter é a abstração. Uma forma de se conseguir isso é com o uso de funções.

### Funções

Uma função é um subprograma.
Ela realiza uma subconjunto de operações, que pode ser tratada como uma operação mais complexa.
O grande poder dela é que quando se desenvolve uma função, o programador se concentra em como essa operação mais complexa é implementada, não precisando se ocupar sobre quem, quando ou por que essa operação vai ser necessária, só precisa se ocupar em saber o que deve ser feito.
Depois de feito e de saber que está funcionando, o programador pode usar essa operação sem precisar se preocupar em como ele é implementada.

Um exemplo bem simples de função para o nosso programa acima seria uma função que sabe imprimir um dígito. Para implementá-la, precisamos saber que para isso é necessário descobrir o código do caractere que representa o dígito que se quer escrever, e como calcular esse valor a partir do dígito. Depois disso feito, sempre que quisermos escrever um dígito podemos usar essa função sem precisar pensar nos detalhes de como se faz esse cálculo.
Quando uma função é usada por outra em um programa C se diz que a função está sendo **chamada** pela outra.

Todas as funções de um programa C têm a mesma forma que vimos para a `main`:
- um tipo, que é o tipo do valor calculado pela função. Se a função não calcula nenhum valor para quem a chama, esse tipo deve ser `void`.
- um nome, que pode ser qualquer, desde que não conflite com outro nome do programa. O nome é usado para chamar a função.
- os parâmetros, que são variáveis que recebem valores necessários para a função realizar sua operação. São opcionais, e colocados entre parênteses.
- o corpo, que contém os comandos (declarações de variáveis e sentenças) que quando executadas realizam a operação que se espera da função.

Por exemplo, a função `putdig` abaixo é uma função que imprime um dígito. Ela deve receber como parâmetro (a variável `dig` entre parênteses) o valor do dígito a imprimir, e usa a função `putchar` para imprimir o caractere correspondente a esse dígito.
```c
void putdig(int dig)
{
  putchar('0' + dig);
}
```

Para chamar essa função, usamos uma sentença com uma chamada a ela, com o argumento (o valor que será colocado no parâmetro `dig`) entre parênteses. Por exemplo:
```c
  putdig(5);
```
irá imprimir o dígito '5'. A chamada de uma função funciona assim: a função chamadora executa a sentença anterior à chamada da função; então, calcula o valor do argumento; então, é criada a variável que contém o parâmetro da função e tem uma atribuição do valor do argumento para essa variável; a função chamadora é então suspensa e a função chamada inicia sua execução; quando a função chamada executar seu último comando, destroi suas variáveis (inclusive argumento) e a função chamadora continua sua execução. É um pouco mais complicado para funções que calculam valores, veremos mais tarde.

Como dito acima, na ativação de uma função (quando ela vai iniciar sua execução) tem uma atribuição do valor do argumento da função chamadora para a variável parâmetro da função chamada.
Funciona como um comando de atribuição, mas a variável que recebe a atribuição está em uma função e a expressão que fornece o valor para a atribuição está em outra. Então, nos parênteses da função chamadora podemos ter uma expressão qualquer, por exemplo:
```c
  int x;
  x = 52;
  putdig(x / 10);
```
vai imprimir '5'. O exemplo abaixo vai imprimir '5' e depois '2':
```c
  int x;
  x = 52;
  putdig(x / 10);
  putdig(x % 10);
```
O exemplo acima imprime um número de 2 dígitos, poderíamos transformar em uma função:
```c
```
e poderíamos imprimir o 52 com uma chamada a essa nova função:
```c
  put2dig(52);
```

Usando funções, nosso programa de média pode ficar mais legível:
```c
#include <stdio.h>

// programa para calcular *e imprimir* a média de 2 números,
// mesmo que sejam necessários 2 dígitos

void putdig(int dig)
{
  putchar('0' + dig);
}

void put2dig(int num)
{
  putdig(num / 10);
  putdig(num % 10);
}

void pulalinha()
{
  putchar('\n');
}

int main()
{
  int n1, n2;
  int media;

  n1 = 85;
  n2 = 61;

  media = (n1 + n2) / 2;

  put2dig(media);

  pulalinha();
}
```
Para imprimir com 3 dígitos poderíamos fazer:
```c
void put3dig(int num)
{
  put2dig(num / 10);
  putdig(num % 10);
}
```

### Exercícios

1. Altere o programa da média para imprimir números com 6 dígitos. Tem que ter uma função para cada número de dígitos.
2. Faça uma função para imprimir um número em binário com 4 dígitos. Use a mesma técnica.
3. Faça um programa para testar suas funções, imprimindo os números de 0 a 15, em decimal (2 casas) e em binário com 4 casas, com um número por linha. O programa deve imprimir assim:
   ```
   00 0000
   01 0001
   02 0010
   ...
   15 1111
   ```
   Dica: faça uma função que recebe um número como argumento e imprime esse número em decimal, um espaço em branco, o número em binário e pula linha.

   A única função externa ao programa que se pode usar é `putchar`.


<a id="melhor"></a>
### Melhor controle sobre a impressão de números

Com as funções da aula anterior, conseguimos imprimir números, mas ainda tem algumas restrições inconvenientes:
- os números têm uma quantidade fixa de dígitos, com zeros iniciais que podem dificultar a leitura;
- temos que decidir previamente a quantidade de dígitos, e chamar a função correspondente, e talvez essa função não exista (se temos só até a função que imprimes números de 6 dígitos, não temos como imprimir números maiores);
- não funciona com números negativos.

Vamos atacar esses problemas.
Todas nossas funções têm o mesmo aspecto, que pode ser generalizado em algo como:
```c
void put6dig(int x)
{
  put5dig(x / 10);
  putchar('0' + x % 10);
}
```
ou seja, cada função chama a anterior para imprimir o número sem o último dígito, e depois imprime seu último dígito.
Na última função, put1dig, omitimos a chamada para imprimir os demais dígitos, porque (em princípio) ela só tem um dígito a imprimir:
```c
void put1dig(int x)
{
  putchar('0' + x % 10);
}
```
Como cada função tem uma chamada a putchar, cada função vai imprimir um dígito. Quando se chama put3dig, ela vai chamar put2dig, que vai chamar put1dig. Cada uma delas vai imprimir um dígito, então teremos 3 dígitos impressos, independente do número recebido como argumento.
Para não imprimir os zeros no início, teríamos que suprimir a impressão, ou não chamar a função que imprime os dígitos que não são necessários.
Se cada função evitar de chamar a função que imprime x/10 de não houver nada a imprimir a não ser um dígito, evitaríamos a impressão dos dígitos 0.
Para isso, necessitamos uma forma de condicionar a chamada a essa função somente aos casos em que ela teria dígitos não 0 a imprimir.

O comando `if` serve justamente para esses casos, ele seleciona se um grupo de comandos vai ou não ser executado, baseado no resultado de uma expressão. Ele tem essa forma:
```c
  if (expressão) {
    comandos
  }
```
Ele calcula o valor da expressão, que deve fornecer um valor lógico (que pode ser verdadeiro ou falso). Se o valor for falso, o comando `if` termina e a execução prossegue após o `}`.
Se o valor for verdadeiro, os comandos dentro das chaves são executados antes de prosseguir.

Para produzir valores lógicos, podemos usar os `operadores de comparação`, que comparam os valores de duas expressões numéricas e produzem verdadeiro ou falso de acordo com essa comparação. Esses operadores são:
- `<` - `a < b` será verdadeiro se o valor de `a` for menor que o de `b`, e falso caso contrário;
- `>` - maior;
- `<=` - menor ou igual;
- `>=` - maior ou igual;
- `==` - igual (cuidado para não confundir com `=`, que é atribuição);
- `!=` - diferente.

No nosso caso, não queremos chamar a função que imprime dígitos se ela só for imprimir zeros, ou só queremos chamá-la se o número que temos a imprimir for pelo menos 10:
```c
void put6dig(int x)
{
  if (x >= 10) {
    put5dig(x / 10);
  }
  putchar('0' + x % 10);
}
```
Colocando isso em cada função, não vai haver chamadas a funções que imprimiriam só zeros, e nossa impressão fica mais "limpa". Isso resolve nosso primeiro problema.

Resolve também parcialmente nosso segundo problema, porque podemos chamar put6dig para qualquer número e ele vai ser impresso com o número de dígitos necessário (até 6); não precisamos escolher uma função que imprime menos dígitos.
Se o número tiver mais de 6 dígitos, vai chegar em put1dig com um valor maior que 10, e essa função vai simplesmente imprimir o dígito menos significativo desse número, ignorando os demais.
Precisamos alterar essa função para que ela imprima os demais dígitos, em vez de ignorá-los, caso receba um número maior. Para imprimir os demais dígitos, podemos usar uma função já existente, que imprime um número qualquer até 6 dígitos:
```c
void put1dig(int x)
{
  if (x >= 10) {
    put6dig(x / 10);
  }
  putchar('0' + x % 10);
}
```

O que acontece agora é que todas nossas funções estão muito parecidas, e qualquer uma delas pode ser chamada para imprimir números de qualquer tamanho, inclusive a put1dig!
Então, a put1dig, em vez de chamar a put6dig para imprimir os dígitos restantes, poderia chamar qualquer dessas funções, inclusive a put1dig!
Com isso, as outras funções não seriam mais necessárias, e a put1dig pode ter seu nome alterado para `putnum`, por exemplo, para ressaltar sua capacidade de imprimir qualquer número:
```c
void putnum(int x)
{
  if (x >= 10) {
    putnum(x / 10);
  }
  putchar('0' + x % 10);
}
```
Isso resolve nosso segundo problema.

Para a impressão de números negativos, a solução é mais simples: se o número a imprimir for negativo, basta imprimir um `-` e depois a versão positiva do número. Assim:
```c
void putnum(int x)
{
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x >= 10) {
    putnum(x / 10);
  }
  putchar('0' + x % 10);
}
```

### Impressão de sequências de caracteres

Imprimir vários caracteres em sequência usando putchar é tedioso.
A biblioteca de funções de entrada e saída tem funções para facilitar esse trabalho.
Uma delas é `puts`, que recebe uma sequência de caracteres entre aspas e os envia à saída, seguidos por um caractere de fim de linha.
Por exemplo:
```c
  puts("Oi, mundo!");
```

### Exercícios

Faça um programa com uma função para imprimir cada um dos desenhos abaixo, e a função `main` que chama todas elas.
As funções devem usar a função `puts` (talvez mais de uma vez) para realizar a impressão.

Um ratinho:
```
<:3)~~~
```
Um gatinho:
```
=^..^=
```
Um ratão:
```
 _   _
(_)_(_)
 (o o)
==\o/==
```
Um gatão:
```
 /\_/\
( o.o )
 > ^ <
```

Que vai acontecer se alterarmos a função `putnum` para, em vez de chamar `putchar` na sua última linha, chamar `ratinho`, e depois chamarmos `putnum(128)`?

Faça uma função `ratinhos` que recebe um número como argumentos e imprime tantos ratinhos (por exemplo, `ratinhos(12)` deve imprimir 12 ratinhos). Baseie-se na função putnum, não pode usar comandos não vistos em aula. Não precisa se preocupar com casos como receber número negativo ou zero.

<a id="a6"></a>
### Entrada de caracteres - getchar

A função `getchar()` lê um caractere do teclado e retorna o código desse caractere.
Uma chamada a uma função que retorna um valor pode ser usada para fornecer um dado em uma expressão.
Por exemplo, o comando
```c
  x = getchar();
```
irá fazer a chamada da função getchar e atribuir o valor retornado pela função à variável `x`.

A função `getchar` retorna o código do caractere digitado. Para converter esse código no valor numérico de um dígito (supondo que se queira que o usuário digite um número), devemos subtrair o valor do código do dígito `0`, semelhante ao que fizemos com `putchar`.
Por exemplo, o comando abaixo colocará na variável `x` o valor do dígito digitado pelo usuário (se for digitado um dígito);
```c
  x = getchar() - '0';
```
Podemos esconder esses detalhes em uma função que lê um dígito. Uma função que lê um caractere do teclado e retorna o valor do dígito digitado.
Essa é uma função que não recebe argumentos, e que calcula (e retorna) um valor.
Então é uma função que deve ter um tipo de retorno (`int`).
Uma função que não seja do tipo `void` deve produzir um valor. Para que o valor seja retornado à função chamadora, devemos usar o comando `return`. Quando executa esse comando, a função em execução termina e retorna à função chamadora. Comandos após o `return` não são executados.
A função que lê um dígito poderia então ser assim:
```c
  int getdig()
  {
    dig = getchar() - '0';
    return dig;
  }
```
E uma chamada a ela poderia ser assim:
```c
  x = getdig();
```
Podemos ignorar os caracteres indesejados até que seja digitado um dígito:
```c
int getdig()
{
  int dig;
  dig = getchar() - '0';
  if (dig < 0) {
    // o caractere digitado é menor que '0', ignora e retorna o valor da função que
    //   lê um dígito válido
    return getdig();
  }
  if (dig > 9) {
    return getdig();
  }
  // o caractere digitado era um dígito válido!
  return dig;
}
```

Mas essa função lê o valor de somente um dígito.
Gostaríamos de poder ler valores com mais dígitos.
Para converter os valores de dois dígitos no valor que esses dois dígitos juntos representam, devemos somá-los, respeitando o peso que eles têm devido à posição (o primeiro dígito é o das dezenas, vale 10 vezes mais).
```c
  int get2dig()
  {
    int d1, d2;
    int num;
    d1 = getdig();
    d2 = getdig();
    num = d1 * 10 + d2;
    return num;
  }
```
Uma função parecida, para ler um número de 3 dígitos, usando a anterior e colocando tudo em uma só expressão:
```c
int get3dig()
{
  return get2dig() * 10 + getdig();
}
```

É um pouco mais complicado de fazer como fizemos com a escrita de números, para fazer uma função que leia um número com qualquer número de dígitos. Vamos deixar para mais tarde, quando tivermos mais alguns comandos da linguagem. Vamos nos contentar por enquando com números de 3 dígitos.

Em aula, fizemos um programa para calcular o IMC de uma pessoa, ficou algo parecido com:
```c
#include <stdio.h>

int getdig()
{
  int dig;
  dig = getchar() - '0';
  if (dig < 0) {
    // o caractere digitado é menor que '0', ignora e retorna o valor da função que
    //   lê um dígito válido
    return getdig();
  }
  if (dig > 9) {
    return getdig();
  }
  // o caractere digitado era um dígito válido!
  return dig;
}

int get2dig()
{
  return getdig() * 10 + getdig();
}

int getnum()
{
  return get2dig() * 10 + getdig();
}

void putnum(int num)
{
  if (num < 0) {
    putchar('-');
    num = -num;
  }
  if (num >= 10) {
    putnum(num / 10);
  }
  putchar(num % 10 + '0');
}

int quadrado(int x)
{
  return x * x;
}

int calc_imc(int p, int a)
{
  return p * 10000 / quadrado(a);
}

int main()
{
  int peso, altura;
  int imc;

  puts("Cálculo do IMC");
  puts("Digite seu peso em kg");
  peso = getnum();
  puts("Digite sua altura em m");
  altura = getnum();

  imc = calc_imc(peso, altura);

  puts("Seu IMC é");
  putnum(imc);
  putchar('\n');
}
```

<a id="ex6"></a>
### Exercícios

Faça um programa, usando as funções de leitura e escrita de inteiros do programa acima, que:

1. Lê o valor de um litro de gasolina em centavos, o consumo médio de um carro em hm por litro e uma distância a percorrer em km, e calcula e imprime o custo da gasolina para realizar esse percurso, em reais. Lembrete: 1 km tem 10 hm; 1 real tem 100 centavos.
Use uma função para fazer o cálculo.

2. Lê o valor da temperatura em ºC e imprime a temperatura equivalente em ºF. Use uma função para fazer o cálculo.

3. Lê o valor da temperatura e mais um caractere que pode ser 'c' ou 'f'. Se o caractere for 'c', a temperatura lida está em ºC e deve ser convertida para ºF; se for 'f', a temperatura está em ºF e deve ser convertida em ºC. As conversões devem ser realizadas por funções.

4. Faça uma programa que lê um caractere e depois três números que representam a largura, comprimento e profundidade de uma piscina. O programa deve então calcular e imprimir a capacidade da piscina em litros. A piscina tem o formato de um paralelepípedo. O primeiro caractere diz se as dimensões da piscina foram fornecidos em metros (se o caractere for 'm') ou em centímetros (se for 'c').

5. O que será impresso pelo programa abaixo? Simule o funcionamento do computador ao executar o programa, antes de executá-lo em um computador.
Certifique-se de entender eventuais diferenças entre a sua simulação e a execução no computador.
```c
#include <stdio.h>

void g(int x)
{
  int y;
  putchar(x);
  y = x + 1;
  x = y + 1;
  putchar(y + 1);
}

void h(int x)
{
  x = x - 1;
  putchar(x + 1);
  x = x + 2;
}

void f(int x)
{
  putchar(x);
  x = x + 1;
  putchar(x);
}

void ff(int x, int y)
{
  putchar(y);
  putchar(x);
}

int main()
{
  int x;
  x = 'a';
  putchar('\n');
  f(x);
  g(x);
  h(x);
  ff('i', 'x');
  ff('\n', '\n');
}
```

