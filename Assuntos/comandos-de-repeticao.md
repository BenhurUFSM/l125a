## Comandos de repetição

Muitas vezes, precisamos que nosso programa execute repetidamente certo número de comandos.
As linguagens de programação oferecem várias formas de se expressar repetição.
A linguagem C possui 3 desses comandos: `while`, `do .. while` e `for`.
Qualquer deles pode ser usado para implementar repetições, mas em algumas situações um deles pode expressar melhor a intenção do programador.
Um grupo de comandos que se repetem é também chamado de laço de repetição ou simplesmente **laço**.

O comando de repetição `while` é semelhante ao comando `if`, tanto sintática quanto semanticamente:
```c
while (condição) {
    comandos
}
```
Da mesma forma que o `if`, ele inicialmente calcula o valor lógico da condição.
Caso seja falso, o comando `while` termina e a execução continua no comando que segue o `while` (após o `}`).
Caso seja verdadeiro, os comandos dentro das chaves são executados.
A diferença em relação ao `if` é que, no caso do `while`, após a execução dos comandos, ele volta ao início, e repete o cálculo da condição.
Ele se chama *while* ("enquanto", em inglês) porque, enquanto o valor calculado para a condição for verdadeiro, ele fica repetindo os comandos.

Por exemplo, o código abaixo fica pedindo um dado para o usuário até que ele digite um valor considerado válido:
```c
  int val;
  printf("digite um número positivo ");
  scanf("%d", &val);
  while (val <= 0) {
    printf("o valor deve ser positivo. Tente novamente ");
    scanf("%d", &val);
  }
```

O teste da condição só é calculado no início de cada repetição. O código abaixo vai imprimir "123" e não "12".
```c
  int x = 0;
  while (x < 3) {
    x = x + 1;
    printf("%d", x);
  }
```

O comando
```c
while (condição) {
    comandos
}
```
é equivalente a:
```c
   ①
   if (condição) {
     comandos
     ②
     desvie para ①
   }
   ③
```
Em qualquer comando de repetição em C, pode-se usar, entre os comandos que ele controla, os comandos `break`, que causa o encerramento do comando de repetição, e `continue`, que causa o encerramento da repetição atual. No esquema acima, `break` corresponde a desviar a execução para o ponto `③` e `continue` corresponde a desviar para o ponto `②`.

Podemos usar o comando `while` para implementar a leitura de números inteiros do teclado caractere à caractere de forma bem melhor do que fizemos antes, sem ter comando de repetição.

A função de leitura de um número pode ser esquematizada assim:
```
   repete
     lê um caractere
     se não for dígito, para de repetir
     usa o dígito para compor o número
   retorna o número
```
Transformando em C, pode ficar assim:
```c
int getnum()
{
  char c;           // para conter cada caractere lido
  int valor = 0;    // contém o número constituído pelos caracteres já processados

  while (true) {    // vai sair do laço no meio, com 'break'
    c = getchar();
    if (!digito(c)) {
      break;        // interrompe o laço
    }
    valor = valor * 10 + (c - '0');
  }
  return valor
}
```
Nesse código foi usada uma função auxiliar que classifica um caractere, dizendo se ele é dígito ou não. Essa função pode ser:
```c
bool digito(char c)
{
  if (c < '0') return false;
  if (c > '9') return false;
  return true;
}
```
Usando o operador lógico "ou" (`||`), essa função poderia ser escrita assim:
```c
bool digito(char c)
{
  if (c < '0' || c > '9') return false;
  return true;
}
```
Usando o operador lógico "e" (`&&`), essa função poderia ser escrita assim:
```c
bool digito(char c)
{
  return c >= '0' && c <= '9';
}
```


### O comando `do .. while`

O comando `do .. while` é semelhante ao `while`, com a diferença que o primeiro teste é realizado após a primeira execução do corpo, garantindo que ele será executado ao menos uma vez.
A forma dele está abaixo:
```c
   do {
      comandos
   } while (condição);
```
Esse comando é equivalente a:
```c
   ①
     comandos
     ②
     if (condição) {
       desvie para ①
     }
   ③
```
Caso entre os comandos tenha `break`, a execução é desviada para o ponto `③`, e `continue` desvia para o ponto `②`.

Por exemplo, o programa abaixo pede para o usuário adivinhar o número secreto, dando dicas sobre os chutes do usuário:
```c
   #include <stdio.h>
   
   int main()
   {
     int segredo = 15;
     int chute;
     do {
       printf("Digite um número entre 1 e 100 ");
       scanf("%d", &chute);
       if (chute < segredo) {
         printf("Muito pequeno\n");
       }
       if (chute > segredo) {
         printf("Muito grande\n");
       }
     } while(chute != segredo);
     printf("Muito bem, você adivinhou o número secreto!\n");
   }
```
Ou, usando `continue` e `break`:
```c
   #include <stdio.h>
   
   int main()
   {
     int segredo = 15;
     int chute;
     while (true) {
       printf("Digite um número entre 1 e 100 ");
       scanf("%d", &chute);
       if (chute == segredo) {
         break;
       }
       if (chute < segredo) {
         printf("Muito pequeno\n");
         continue;
       }
       printf("Muito grande\n");
     }
     printf("Muito bem, você adivinhou o número secreto!\n");
   }
```
Ou ainda, sem usar `continue` mas usando `else` no segundo `if`:
```c
   #include <stdio.h>
   
   int main()
   {
     int segredo = 15;
     int chute;
     while (true) {
       printf("Digite um número entre 1 e 100 ");
       scanf("%d", &chute);
       if (chute == segredo) {
         break;
       }
       if (chute < segredo) {
         printf("Muito pequeno\n");
       } else {
         printf("Muito grande\n");
       }
     }
     printf("Muito bem, você adivinhou o número secreto!\n");
   }
```

Esse programa fica um pouco mais interessante se o número secreto for aleatório. 
Incluindo `stdlib.h`, tem-se acesso à função `rand()`, que calcula e retorna um número pseudo-aleatório cada vez que é chamada.
Essa função retorna um número entre e RAND_MAX (tipicamente entre 0 e 2 bilhões); pegando o resto da divisão desse número por 100 consegue-se um valor entre 0 e 99; somando-se 1 tem-se o valor entre 1 e 100.
Os valores de `rand()` são chamados de pseudo-aleatórios porque são calculados a partir do último valor gerado. Um problema é que o primeiro valor é gerado a partir de 0 sempre, o que faz que a cada execução do programa os valores gerados sejam repetidos.
Para se poder gerar sequências diferentes, existe a função `srand()`, que permite alterar o valor inicial (a semente de geração). 
Um modo usual de se obter uma semente diferente a cada execução é com o uso da função `time(NULL)` (tem que incluir `time.h`), que dá o número de segundos desde o início de 1970 (um número que é diferente a cada segundo):
```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <time.h>
   
   int main()
   {
     srand(time(NULL));
     int segredo = rand() % 100 + 1;
     int chute;
     do {
       printf("Digite um número entre 1 e 100 ");
       scanf("%d", &chute);
       if (chute < segredo) {
         printf("Muito pequeno\n");
       } else if (chute > segredo) {
         printf("Muito grande\n");
       }
     } while(chute != segredo);
     printf("Muito bem, você adivinhou o número secreto!\n");
   }
```
Dá para esconder um pouco os detalhes dos números aleatórios usando funções auxiliares:
```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <time.h>
   
   void inicializa_aleatorios()
   {
     srand(time(NULL));
   }

   int aleatorio_entre(int menor, int maior)
   {
     return menor + rand() % (maior - menor + 1);
   }

   int main()
   {
     inicializa_aleatorios();
     int segredo = aleatorio_entre(1, 100);
     int chute;
     while (true) {
       printf("Digite um número entre 1 e 100 ");
       scanf("%d", &chute);
       if (chute == segredo) {
         printf("Muito bem, você adivinhou o número secreto!\n");
         break;
       }
       if (chute < segredo) {
         printf("Muito pequeno\n");
       } else {
         printf("Muito grande\n");
       }
     }
   }
```


Outro exemplo. Suponha que se deseja fazer um programa para calcular a média de dois números.
Simples, declara duas variáveis para conter os dois números e uma para a média, lê os dois valores, e calcula a média como `(a+b)/2`.
Se o problema foi calcular a média de 3 números, é só adicionar mais uma variável, ler mais um valor, adicionar o terceiro valor para o cálculo, e dividir por 3.

Conforme vai aumentando o número de valores, porém, o programa começa a ficar desagradável de ser escrito ou até inviável.
Pior ainda se não se sabe de antemão o número de valores (o usuário fornecerá o número no início da execução, por exemplo).

A forma de se resolver problemas como esse é usando repetição.
Inicialmente, precisamos reescrever a solução de forma a encontrar um trecho de código que possa ser repetido.
No exemplo, para o cálculo da média de um número qualquer de valores, necessitamos de dois valores: a soma dos valores dos quais se quer a média e o número de valores que foram somados. Vamos supor por enquanto que o número de valores é conhecido, precisamos somente calcular o somatório.

Para se calcular o somatório com repetição, precisamos de um código que use um número de cada vez, e esse código será repetido para cada número. No final da última repetição, usaremos o último número para obter a soma final, para isso precisamos ter antes a soma dos demais números: `soma_final = soma_dos_demais_numeros + ultimo_numero`.
Na penúltima repetição, devemos produzir a soma_dos_demais_numeros, usando o penúltimo número. Precisamos para isso da soma dos primeiros números menos os dois últimos: `soma_dos_demais_numeros = soma_dos_primeiros + penultimo_numero`.
Esses dois comandos são bem parecidos, se pudermos unificar as variáveis podemos ter um comando que pode ser repetido.
Cada número é usado uma única vez, então podemos usar uma única variável para conter o último número digitado, se pedirmos para o usuário digitar essa variável logo antes do uso:
```c
   //... 
   scanf(... &numero_digitado);
   soma_dos_demais_numeros = soma_dos_primeiros + numero_digitado;
   scanf(... &numero_digitado);
   soma_final = soma_dos_demais_numeros + numero_digitado;
```
O valor que é somado a cada número digitado é a soma de todos os números anteriores a ele.
O valor que é produzido é a soma de todos os números incluindo ele.
Esse valor é o que é necessário para a soma seguinte:
```c
   //... 
   scanf(... &numero_digitado);
   soma_com_este_numero = soma_dos_anteriores + numero_digitado;
   soma_dos_anteriores = soma_com_este_numero;
   scanf(... &numero_digitado);
   soma_com_este_numero = soma_dos_anteriores + numero_digitado;
   soma_final = soma_com_este_numero;
```
Todas as variáveis soma_ são usadas uma só vez, dá pra unificá-las:
```c
   //... 
   scanf(... &numero_digitado);
   soma = soma + numero_digitado;
   scanf(... &numero_digitado);
   soma = soma + numero_digitado;
```
Agora o código para a soma dos últimos dois números ficou igual, e dá para usar em uma repetição.
Na verdade, é o mesmo código para qualquer número de valores, só tem que tomar o cuidado de para o primeiro número o valor de soma ser 0:
```c
   soma = 0;
   repete tantas vezes quantos forem os números a somar
     scanf(... &numero_digitado);
     soma = soma + numero_digitado;
   media = soma / quantos_numeros;
```
Essa é a forma genérica de se fazer um somatório com um laço de repetição.
Dá para usar o mesmo esquema para contar o número de valores (que é um somatório de 1s):
```c
   soma = 0;
   quantos_numeros = 0;
   repete tantas vezes quantos forem os números a somar
     scanf(... &numero_digitado);
     soma = soma + numero_digitado;
     quantos_numeros = quantos_numeros + 1;
   media = soma / quantos_numeros;
```
Se se sabe quantos número se quer, pode-se usar a variável que está contando quantos números foram digitados para controlar o número de vezes a repetir:
```c
   soma = 0;
   quantos_numeros = 0;
   while (quantos_numeros < quantos_numeros_eu_quero_somar) {
     scanf(... &numero_digitado);
     soma = soma + numero_digitado;
     quantos_numeros = quantos_numeros + 1;
   }
   media = soma / quantos_numeros;
```
Nem sempre se sabe de antemão quantos números se tem. Uma forma de se tratar esse problema é aceitando os números digitados até que seja digitado um valor especial que representa o final dos dados.
Por exemplo, se todos os valores válidos são positivos, pode-se usar qualquer valor não positivo para representar o final dos dados:
```c
#include <stdio.h>

int main()
{
  int digitado;
  int num_valores = 0;
  int soma_valores = 0;

  do {
    printf("Digite um número ");
    scanf("%d", &digitado);
    if (digitado > 0) {
      num_valores = num_valores + 1;
      soma_valores = soma_valores + digitado;
    }
  } while (digitado > 0);
  printf("soma: %d, nval: %d\n", soma_valores, num_valores);
  float media = (float)soma_valores / num_valores;
  printf("A media dos valores digitados é %.2f\n", media);
  return 0;
}
```

Outro exemplo, um programa para realizar alguma operação com valores sequenciais.
Por exemplo, imprimir os números entre 1 e 10 (ou entre 1 e 100).
Primeiro, temos que pensar nos comandos que serão repetidos.
Certamente terá um comando para imprimir um valor.
Como o valor é diferente a cada impressão, deve ser impresso o valor de uma variável.
Algo como
```c
  printf("%d ", valor);
```
Se só isso for repetido, teremos o mesmo valor impresso.
O valor da variável deve ser alterado entre uma impressão e outra.
Como queremos imprimir valores sucessivos, o valor a imprimir deve ser incrementado de 1 após cada impressão:
```c
  printf("%d ", valor);
  valor = valor + 1;
```
[!NOTE] Pode-se incrementar o valor também usando o operador de atribuição com soma (`valor += 1;`) ou com o operador de incremento (`valor++;`).

O primeiro valor a ser impresso é 1, então devemos colocar esse valor na variável antes da primeira impressão (devemos inicializar a variável com 1).
Nosso programa fica, então:
```c
  int valor;
  valor = 1;
  repete
    printf("%d ", valor);
    valor = valor + 1;
```
Falta controlarmos nossa repetição.
Para isso, precisamos de uma expressão que resulte em 'verdadeiro' se os comandos devem ser executados (e o valor impresso) e 'falso' caso contrário.
Essa expressão deve testar algo que muda a cada repetição, e no caso só tem a variável `valor`.
Temos que ter um teste com o valor da variável `valor` que permita decidir se a impressão deve ser feita (e a repetição continuar) ou não.
O primeiro comando repetido imprime `valor`, e devemos imprimir os valores até 10. Como `valor` está aumentando, se ele passar de 10 não precisamos mais repetir.
```c
  int valor;
  valor = 1;
  while (valor <= 10) {
    printf("%d ", valor);
    valor++;
  }
```

Essa forma geral de se controlar um laço é bastante comum. Ela usa uma variável, que é:
- inicializada logo antes do laço;
- testada para controlar a repetição;
- alterada no final do laço.
É tão comum que a linguagem tem um comando específico para esse caso, o comando `for`.
Usando esse comando, o programa acima pode ser:
```c
  for (int valor = 1; valor <= 10; valor++) {
    printf("%d ", valor);
  }
```

O comando `for` tem a seguinte forma:
```c
  for (inicialização; expressão; incremento) {
    comandos
  }
```
Esse comando é equivalente a:
```c
   inicialização
   ①
   if (condição) {
     comandos
     ②
     incremento
     desvie para ①
   }
   ③
```
Um comando `break` desvia para ③ e um comando `continue` desvia para ②.
O uso mais comum do comando `for` é para repetir comandos um número conhecido de vezes.
Se a variável `vezes` contém o número de repetições que se quer, usa-se geralmente essa forma:
```c
   for (int i = 0; i < vezes; i++) {
     comandos
   }
```


* * *

### Exercícios

1. Altere o programa das médias, para que calcule duas médias, a dos valores pares e a dos ímpares.
2. Faça um programa que imprime os números de 20 a 29, separados por espaços, usando um comando de repetição.
3. Altere o programa anterior para imprimir um valor por linha.
4. Altere novamente para imprimir o valor em decimal e binário, com 2 e 5 casas:
   ```
   20 10100
   21 10101
   ...
   ```
5. Altere novamente, para imprimir os números entre 32 e 126 (correspondem aos caracteres imprimíveis da tabela ASCII), em decimal (3 casas, preenchido com espaços), hexadecimal (2 casas), binário (7 casas preenchido com zeros) e o caractere que tem esse código:
   ```
    32 0100000 20  
    33 0100001 21 !
   ...
    99 1100011 63 c
   100 1100100 64 d
   ...
   126 1111110 7e ~
   ```
   Faça uma função para formatar um número. Por exemplo, se for chamada com `99` como argumento, deve imprimir ` 99 1100011 63 c`.
4. Um laboratório tem duas colônias de bactérias. A primeira tem 5000 indivíduos, e a população dobra a cada hora. A segunda tem 100000 indivíduos, que têm sua população multiplicada por 1,8 a cada hora. Faça um programa, usando repetição, para calcular quantas horas serão necessárias para que a população da primeira colônia seja maior que da segunda.
8. Um dos programas acima pede para o usuário adivinhar um número secreto. Faça um programa que faz o contrário: pede para o usuário pensar em um número e depois chuta valores até acertar. Para cada chute do programa, ele imprime o chute e pede para o usuário responder se acertou ou se está acima ou abaixo do valor secreto (digitando 0, 1 ou 2). O chute do programa deve ser um valor aleatório entre os valores que ainda são possíveis a cada chute. A função abaixo pode ser de ajuda, ela retorna um valor aleatório que está entre os limites fornecidos:
```c
int aleatorio_entre(int menor, int maior)
{
  return menor + rand() % (maior - menor + 1);
}
```
5. Faça uma função que imprime a tabuada do número recebido em argumento, no seguinte formato (caso receba 2 como argumento):
   ```
   2x1 =  2
   2x2 =  4
   2x3 =  6
   2x4 =  8
   2x5 = 10
   2x6 = 12
   2x7 = 14
   2x8 = 16
   2x9 = 18
   ```
6. Faça um programa que imprime toda a tabuada (de 1 a 9), usando a função do exercício anterior. Separe-as com uma linha contendo 8 caracteres `-`. Use uma função para desenhar esses 8 caracteres - essa função deve receber como argumento o caractere e o número de vezes que se quer imprimí-lo.
7. Use a função de selecionar a cor de fundo para desenhar um quadrado degradê cinza vertical na tela. Desenhe 16 linhas, com 32 espaços cada. No início de cada linha, escolha a cor com os componentes R, G e B iguais ao número da linha (0 a 15) multiplicado por 16. No final de cada linha, escolha a cor normal antes do enter.
8. Inverta o degradê (claro em cima, escuro em baixo).
9. Consegue fazer o degradê horizontal?
9. Colorido?

* * *
