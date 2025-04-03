## *float*

Até agora, os dados que usamos eram todos inteiros. Eles são suficientes para muitos programas, mas às vezes necessitamos tratar com valores que não são inteiros. A linguagem C tem o tipo de dados `float` para essas situações.
Em computação, é comum chamar valores com vírgula de "ponto flutuante" ou "vírgula flutuante", para ressaltar suas limitações em relação ao conjunto de números reais da matemática. (Talvez devessem fazer a mesma coisa com os inteiros).

Considere o programa abaixo:
```c
#include <stdio.h>

int main()
{
  float a, b, m;
  printf("Digite dois números: ");
  scanf("%f%f", &a, &b);
  m = (a + b) / 2.0;
  printf("A média entre %f e %f é %f.\n", a, b, m);
}
```
Nesse programa:
- variáveis são declaradas como do tipo `float`;
- a leitura de variáveis do tipo `float` com scanf é feita com o formato `%f`;
- a escrita de valores do tipo `float` com printf é feita com o formato `%f`;
- constantes de ponto flutuante são escritas com um `.` (não pode usar `,`).

Algumas considerações:
- os números `float` são implementados internamente como dois inteiros, chamados de mantissa e expoente.
A mantissa contém os dígitos que compõem o número e o expoente contém a posição da vírgula (por isso o nome de "flutuante").
Por exemplo, o número `1,23` poderia ser representado em decimal como `(123, -2)`, com o significado de `123×10⁻²`
- em geral o tipo `float` é implementado com 4 bytes, 3 para a mantissa e um para o expoente. Isso corresponde em decimal a entre 6 e 7 dígitos para a mantissa, com a vírgula podendo ser deslocada aproximadamente 38 casas decimais para a esquerda ou para a direita.
- essas limitações fazem com que se possa armazenar números bastante grandes (até 10³⁸) e bastante pequenos (até 10⁻³⁸), mas não se consegue distinguir entre 98765435 e 98765429, por exemplo.
- quando imprime números `float` com `%f` no `printf`, ele imprime sempre com 6 dígitos depois da vírgula.
Para mudar, pode-se usar `%.2f`, por exemplo, para pedir para ele imprimir com 2 dígitos depois da vírgula.

### Mais tipos de dados

Outros tipos de dados em C:
- tipos inteiros: `char`, `short`, `int`, `long`, `long long`
- tipos de ponto flutuante: `float`, `double`, `long double`

Quanto mais para a esquerda nessas listas de tipos, menor o espaço ocupado e menor a gama de valores representados.
A linguagem C não especifica o espaço ocupado por cada tipo, só diz que esse tamanho de um tipo não pode ser menor que o tipo à sua esquerda na lista.

No computador que estou usando agora, e com o compilador gcc, esses tamanhos são, em bytes:
| tipo        | tamanho | valores representáveis |
| ---:        |    ---: | :--- |
| `char`        |       1 | -128 a 127 ou 0 a 255 |
| `short`       |       2 | -32768 a 32767 |
| `int`         |       4 | -2 a +2 bilhões |
| `long`        |       8 | -4 a +4 quintilhões |
| `long long`   |       8 | idem |
| `float`       |       4 | ±7 dígitos, ±10³⁸ |
| `double`      |       8 | ±16 dígitos, ±10³⁰⁸ |
| `long double` |      16 | sei lá |

Para ler ou escrever valores desses tipos, devemos usar formatos específicos com `printf` e `scanf` (nem sempre são iguais):
| tipo        | `printf` | `scanf` |
| ---:        |    :--- | :--- |
| `char`        | `%c` ou `%d` | `%c` ou `%hhd` |
| `short`       | `%c` ou `%d` | `%hd` |
| `int`         | `%c` ou `%d` | `%d` |
| `long`        | `%ld`      | `%ld` |
| `long long`   | `%lld`     | `%lld` |
| `float`       | `%f`       | `%f` |
| `double`      | `%f` ou `%lf`| `%lf` |
| `long double` | `%Lf`      | `%Lf` |


### Mais detalhes

Nos tipos inteiros, pode-se colocar `signed` ou `unsigned` antes do tipo, para dizer se se quer possibilitar a representação de valores negativos ou não. Um tipo "unsigned" pode representar o dobro dos valores positivos que um tipo "signed" (mas não pode representar valores negativos). Por exemplo, um "signed int" de 4 bytes pode representar valores entre -2 e +2 bilhões, e um "unsigned int" de 4 bytes pode representar valores entre 0 e 4 bilhões.

Quando não se especifica nem "signed" nem "unsigned", é considerado como "signed", exceto para o tipo "char", que não foram capazes de decidir na norma, e depende do compilador.

Para ler um valor unsigned com scanf ou escrever com printf, tem que substituir o formato `d` por `u` (`%lu` para um unsigned long, por exemplo).

Dá para ler ou escrever valores unsigned em outras bases além de decimal, trocando o formato `d` por `o` para octal, `x` para hexadecimal ou `b` para binário.

Valores inteiros constantes no corpo de um programa também podem ser escritos nessas outras bases: se iniciar com `0` e for seguido de dígitos entre `0` e `7`, está em base octal, se iniciar com `0x` está em base hexadecimal e `0b` em binário.
```c
  // todas as atribuições abaixo colocam o valor dez em x
  int x;
  x = 10;
  x = 012;
  x = 0xa;
  x = 0b1010;
  x = '\n';
```

Quando se imprime um número com `%d`, a função printf vai usar o número mínimo de caracteres necessários para imprimir o valor pedido. Se for impresso o valor 52, usará 2 caracteres, se for impresso -128, usará 4.
Caso se queira que o printf use um número mínimo de caracteres, pode-se colocar esse valor entre o `%` e o `d`. Por exemplo, `%3d` irá imprimir o valor 52 com 3 caracteres, colocando um espaço antes do `5`. Dá para escolher `0` em vez de espaço com `%03d`.

Isso funciona também para valores em ponto flutuante. `%10f` vai imprimir pelo menos 10 caracteres: 3 antes do ponto, o ponto e 6 dígitos depois do ponto. `%7.2f` vai imprimir pelo menos 4 antes do ponto, o ponto e dois dígitos depois.
Caso o número seja muito grande ou muito pequeno, o printf usará notação científica, com o caractere `e` sendo usado para significar "vezes 10 elevado na potência". Por exemplo, 123456 pode ser impresso como 1.234560e+05, e 0.0001 pode ser escrito como 1.000000e-04. Essa mesma forma pode ser usada para representar constantes em ponto flutuante no interior de um programa C ou para a entrada de dados, em resposta a um scanf.

### Mais detalhes sobre expressões aritméticas

Em uma expressão aritmética, podemos usar os operadores aritméticos da linguagem para codificar a realização de operações aritméticas entre os valores gerenciados por nosso programa.
A linguagem tem 5 operadores aritméticos, `+-*/%`, que codificam as operações de soma, subtração, multiplicação, divisão e resto da divisão.

Em uma CPU, tem-se várias implementações dessas operações, para os vários tipos e tamanhos de dados que a CPU é capaz de operar. Para cada uma dessas operações, a CPU tem uma instrução distinta. Em geral, uma instrução que opera sobre valores de um tipo produz resultado desse mesmo tipo (a instrução que divide um inteiro de 32 bits por outro inteiro de 32 bits produz como resultado um inteiro de 32 bits).

Em C, usa-se os mesmos símbolos para codificar todas elas. O compilador deve então ter uma maneira de escolher a instrução adequada cada vez que tem que compilar uma expressão aritmética.
A regra da linguagem é a seguinte:
- a expressão é analisada, e a ordem de execução dos operadores é decidida;
- para cada operador, o compilador verifica os tipos de seus operandos;
- se os dois operandos forem do mesmo tipo, a operação será realizada com esse tipo, e o resultado da operação será do mesmo tipo;
- se os dois operandos forem de tipos diferentes, um dos operandos tem seu valor convertido para o tipo do outro - agora os dois têm o mesmo tipo, e a escolha é como acima;
- o tipo escolhido é o que está mais abaixo entre os dois, na tabela de tipos vista acima (entre dois inteiros ou dois de ponto flutuante, é escolhido o de maior tamanho; entre um inteiro e um ponto flutuante, é escolhido o de ponto flutuante).

Por exemplo, considere o código abaixo:
```c
  float r;
  int a = 9;
  r = 3.5 + a / 2 - 2;
```
A ordem das operações será divisão, soma, subtração. Para a divisão, `a` e `2` são inteiros, a divisão será inteira, o resultado é 4. Para a soma, 3.5 é float, 4 é int, a operação e o resultado serão float; 4 inteiro é convertido em 4.0 float, o resultado é 7.5. Para a subtração, 7.5 é float, 2 é int, o resultado será 7.5. Por último vem a atribuição, o valor à direita é float e a variável também, a atribuição é direta. Se `r` fosse int, o valor 7.5 teria que ser convertido para int e seria atribuído o valor 7.

### Exercício

1. O que será impresso pelo programa abaixo? Responda só analisando o código, confira sua resposta executando ele. Se programa não imprimir igual a sua resposta, entenda por que; pode colocar outros printf para conferir os valores intermediários, se ajudar.
```c
#include <stdio.h>

int f(int a)
{
  int x;
  x = 2.5 * a;
  printf("%d ", x);
  return x + 2;
}

int main()
{
  int a, b, x;
  a = 3;
  x = a - 1.5;
  b = x * a;
  printf("%d\n", a);
  a = f(b);
  printf("%d %d\n", a, x);
}
```
2. Faça um programa que lê os coeficientes `a`, `b` e `c` de uma equação de segundo grau (`y = a x² + b x + c`). O programa deve imprimir o número de raízes reais distintas que a equação tem. Os coeficientes são `float`.
3. Altere o programa acima para, após ler o valor dos coeficientes, ler o valor de `x`. O programa deve então chamar uma função para calcular o valor de `y` e imprimir esse valor.
