## Vetor

A forma de representar valores em nossos programas é através de variáveis.
Uma variável tem um tipo de dados e pode conter **um** valor desse tipo (a cada instante).
Quando se atribui um valor à variável, o valor antigo é perdido. 
Se necessitamos guardar vários valores em nosso programa ao mesmo tempo, precisamos de várias variáveis, uma para cada valor.
Como cada variável tem que ser declarada no programa e deve ter um nome distinto das demais, temos que saber com antecedência quantos valores o nosso programa vai utilizar, e temos que criar esse tanto de nomes.
Para alguns tipos de programas, isso pode ser muito restritivo.

Suponha um programa que deve ler um certo número de valores e calcular a média entre esses valores.
Para o cálculo da média, necessitamos duas coisas: o somatório dos valores dos quais se quer saber a média e a quantidade desses valores. 
Podemos ter uma variável para cada. Iniciamos elas em 0, e para cada valor lido, somamos o valor no total e incrementamos o contador de valores.
No final, podemos calcular a média sem problemas.
Em forma de programa (digamos que se marque o final dos valores de entrada com um número negativo):
```c
  float soma = 0;
  int n = 0;
  while (true) {
    float valor;
    scanf("%f", &valor);
    if (valor < 0) {
      break;
    }
    soma = soma + valor;
    n = n + 1;
  }
  float media = soma / n;
```
Facinho.
Agora suponha que se deseja saber quantos dos valores estão abaixo da média.
Mais fácil ainda:
```c
  int pequenos = 0;
  while (true) {
    int valor;
    scanf("%d", &valor);
    if (valor < 0) {
      break;
    }
    if (valor < media) {
      pequenos++;
    }
  }
  // a variável "pequenos" tem o número de valores abaixo da média
```
Só tem um porém: tem que ter um valor correto na variável `media`, e para obter esse valor, necessita-se todos os valores da entrada.
Uma forma de resolver o problema seria pedir para o usuário digitar tudo de novo (não seria a melhor forma de contentar o usuário).
Outra forma seria guardar os valores, com uma variável para cada um, para reprocessá-los.
Só que não sabemos quantos valores são, e mesmo que soubéssemos, só seria viável fazer o programa para um número bem pequeno de valores.

Necessitamos de uma forma de poder guardar vários valores, sem precisar de uma variável para cada um.
Um **vetor** é exatamente isso. É uma variável que permite o armazenamento de vários valores independentes entre si.
Tem a restrição de que todos os valores têm que ter o mesmo tipo, mas para o nosso problema, é bem o que necessitamos.

Em C, a forma de se declarar um vetor é semelhante à declaração de uma variável simples, acrescida do número de valores que queremos que o vetor tenha, entre colchetes. 
Por exemplo, para declarar um vetor chamado `a`, capaz de conter 50 valores inteiros, fazemos assim:
```c
  int a[50];
```
Para acessar um dos valores do vetor, dizemos qual deles queremos colocando o seu **índice** entre colchetes.
Índice é a posição no vetor; em um vetor com capacidade para `N` valores, temos índices desde `0` até `N-1`, para identificar a posição de cada valor.
Em qualquer lugar de um programa onde se pode usar uma variável normal de um determinado tipo, pode-se usar um elemento (um dos valores) de um vetor desse mesmo tipo.
Por exemplo:
```c
  a[0] = 30;
  x = a[20];
  a[2] = a[4] - y;
  scanf("%d", &a[6]);
  printf("%d\n", a[3]);
```
O índice pode ser fornecido por uma constante inteira (como nos exemplos acima), ou por qualquer expressão da linguagem que produza um valor inteiro, por exemplo:
```c
  for (int j = 0; j < 10; j++) {  // copia das posicões 10-19 para as posições 0-9
    a[j] = a[j + 10];
  }
```

O exemplo acima, de se calcular quantos dos valores digitados estão abaixo da média desses valores poderia ser escrito assim:
```c
#include <stdio.h>
#include <stdbool.h>

int main()
{
  // primeiro, lê valores para o vetor.
  // n_total vai conter o número de valores válidos no vetor.
  float valores[100];
  int n_total;
  
  n_total = 0; // por enquanto, nenhum valor válido no vetor
  while (n_total < 100) {  // le no máximo 100 valores
    printf("Digite um número (negativo para terminar) ");
    float v;
    scanf("%f", &v);
    if (v < 0) {  // valor negativo indica fim dos dados
      break;
    }
    // valor não negativo interessa -- coloca no vetor
    // se n_total for 10, tem 10 elementos no vetor, nos índices 0 a 9; o novo
    //   vai no índice 10, que é o valor de n_total.
    valores[n_total] = v;
    // tem um elemento a mais, incrementa o número de elementos
    n_total++;
  }

  // segundo, calcula a média dos valores válidos
  if (n_total <= 0) {
    printf("para calcular a média, precisa digitar algum valor!\n");
    return 1;
  }
  // calcula a soma de todos os "n_total" elementos no vetor
  float soma = 0;
  for (int i = 0; i < n_total; i++) {
    soma += valores[i];
  }
  // calcula a média
  float media = soma / n_total;

  // terceiro, conta quantos valores estão abaixo da média
  int n_abaixo; // número de valores abaixo da média
  n_abaixo = 0; // por enquanto nenhum, incrementa conforme encontrar
  // para cada valor válido no vetor, verifica se é menor e incrementa o contador
  for (int i = 0; i < n_total; i++) {
    if (valores[i] < media) {
      n_abaixo++;
    }
  }

  // quarto, imprime os resultados
  printf("media: %f\n", media);
  printf("%d valores estão abaixo da média.\n", n_abaixo);
}
```

A linguagem C não faz verificação dos índices para garantir que sejam válidos.
É responsabilidade do programador garantir que seu programa não faz acesso a um índice inválido (menor que 0 ou maior que N-1).
Essa é uma das principais fontes de erro em programas C.

Em C, não existe atribuição de vetores, somente de elementos de vetor. 
Por exemplo, para copiar o vetor `b` para o vetor `a` abaixo, tem que fazer um laço que copie elemento a elemento.
```c
  int a[30];
  int b[30];
  //... coloca valores em a
  // "b = a;" é um comando inválido, nao existe atribuição de vetores
  for (int i = 0; i < 30; i++) {  // para copiar um vetor, copia-se cada valor
    b[i] = a[i];
  }
```

* * *

### Exercícios

1. Faça um programa que lê dez números e os imprime na ordem inversa à que foram lidos.
1. Faça um programa que lê dois vetores de 5 inteiros cada e depois copia os valores do primeiro vetor para as primeiras 5 posições de um terceiro vetor e os valores do segundo vetor para as posições finais desse terceiro vetor, de 10 posições. O programa deve imprimir os 3 vetores no final.
1. Repita o exercício anterior, mas copiando os elementos alternadamente de cada vetor (se os dois primeiros vetores forem `1 2 3 4 5` e `6 7 8 2 1`, o terceiro vetor deve ser `1 6 2 7 3 8 4 2 5 1`).
1. Repita o exercício anterior, mas copiando os dados do segundo vetor do fim para o início (se forem `1 2 3 4 5` e `6 7 8 9 0`, o terceiro será `1 0 2 9 3 8 4 7 5 6`).
2. Faça um programa que lê 10 valores float do usuário e imprime qual deles está mais próximo da média desses valores. O mais próximo pode ser maior ou menor que a média. Caso mais de um valor esteja na mesma distância da média, o que foi digitado antes deve ser o considerado.
1. A função `rand` (inclua `<stdlib.h>`) produz e retorna um número inteiro aleatório (na verdade, pseudo-aleatório). O número produzido é um número qualquer entre 0 e RAND_MAX (que é um número bem grande).
Cada vez que essa função é chamada, retorna um número diferente.
   Pode-se usar ela para se fazer uma função que funciona como um dado (produz um número entre 1 e 6 cada vez que é chamada):
   ```c
   int dado(void) {
     return rand() % 6 + 1;
     // rand() produz um número qualquer; o resto da divisão desse número por 6 resulta
     //   em um valor entre 0 e 5; somando 1 dá um número entre 1 e 6
   }
   ```
   Faça um programa que testa se essa função faz um bom dado, com probabilidades semelhantes de cair cada um dos valores. Lance o dado um número alto de vezes (alguns milhares) e imprima quantas vezes caiu cada valor possível. Use um vetor de 6 posições para os contadores.
   
   Um valor gerado pela função rand não é verdadeiramente aleatório, ele é gerado à partir do número gerado anteriormente. O primeiro valor é gerado a partir de um número inicial chamado semente, que tem sempre o mesmo valor quando um programa inicia. Por isso, a cada execução, será gerada a mesma série de números "aleatórios". Para se gerar uma série diferente de números, deve-se inicializar a semente (tipicamente no início do programa). Uma forma comum de se inicializar o programa a cada vez com uma semente diferente e ter números mais parecidos com aleatórios é usar a hora de início do programa como semente. Essa hora é obtida com a função time, com argumento 0 (incluir time.h). A chamada para isso é: `srand(time(0));`.
1. Altere o programa anterior para calcular e imprimir um "fator de desonestidade" do dado, definido como a diferença entre o número de vezes que cai o número que cai mais vezes e o número de vezes que cai o número que cai menos vezes dividido pelo número de lançamentos.
1. Faça um programa que preenche um vetor com 100 números aleatórios, cada um entre 0 e 99. Depois, o programa deve dizer qual foi o maior e o menor número gerado.
1. Altere o programa anterior para informar, além do maior e menor números, a posição da primeira ocorrência de cada um deles.
1. Altere o programa anterior para informar quantas vezes ocorreu cada número.
1. Altere o programa anterior para informar qual o número que ocorreu mais vezes.


### Inicialização de vetores

O comando de atribuição não permite que a atribuição seja feita a um vetor.
Para copiar os valores de um vetor para outro deve-se copiar cada elemento.
Há uma exceção, que é na declaração do vetor. Nessa hora, o vetor pode ser inicializado com um valor inicial para cada elemento, colocando-se os valores separados por vírgula, entre chaves:
```c
  int v[5] = {6, 5, 7, 9, 2};
```
Caso tenha menos valores que o tamanho do vetor, os demais valores serão inicializados em 0. Não pode ter mais elementos na lista de inicialização que o número de elementos do vetor.

Pode-se inicializar algum elemento específico assim:
```c
  int v[6] = { 6, [3] = 2, 4 };
```
O vetor v será inicializado com os valores `6, 0, 0, 2, 4, 0`.

No caso de vetores de `char`, eles podem ser inicializados com uma sequência de caracteres entre aspas.
Cada caractere será colocado em uma posição do vetor. O restante do vetor será preenchido com caracteres de código 0:
```c
  char mensagem[20] = "Feliz aniversario";
  // As primeiras 17 posições do vetor serão preenchidas com os caracteres
  // entre aspas, as outras 3 com zeros.
```

Pode-se também omitir o tamanho do vetor, ele será criado como o menor tamanho que contenha todos os valores da inicialização.
```c
  int v[] = { 10, 2, 33, 42 };  // o vetor será declarado com tamanho 4
```

### Vetores como argumentos de funções

Quando se faz uma chamada a uma função que recebe argumentos, tem-se uma atribuição implícita, do valor passado à variável local da função que recebe o argumento.
A linguagem C não tem atribuição de vetores, então não seria possível passar um vetor como argumento para uma função.
O que se fez foi dizer que o nome de um vetor, diferente dos demais tipos de dados, não corresponde ao valor do vetor, mas a uma **referência** ao vetor. A partir dessa referência, pode-se acessar o vetor original passado pela função chamadora.
Na prática, isso quer dizer que quando passamos um vetor para uma função, a função consegue alterar o vetor da função chamadora, a variável que é o argumento na função chamada é uma espécie de "apelido" para a variável original da função chamadora.

O tamanho do vetor (o número de elementos que ele contém) é dado pelo vetor da função chamadora, não pelo declaração do argumento na função chamada.
A forma de se declarar uma função que recebe um vetor como argumento é como a declaração de um vetor, mas geralmente se deixa vazio o interior dos colchetes (esse valor vai ser ignorado pelo compilador):
```c
  int f(double v[])
  {
    //...
  }
```
Declara a função `f` como uma função que recebe um vetor de `double` e retorna um `int`.
Para chamar essa função, poderíamos ter:
```c
  double x[20];
  //...
  a = f(x);
```
Na chamada, o nome do vetor vai dentro dos parênteses da função, **sem colchetes**.
Nesse caso, durante essa execução de `f`, sua variável `v` é um sinônimo para a variável `x` da função chamadora. Toda alteração que `f` fizer em `v` será na verdade uma alteração em `x`.

Quando uma função recebe um vetor, ela não tem como saber o tamanho dele (o número de elementos que ele contém).
Algumas soluções para esse problema:

- a função trabalha com vetores de tamanho predeterminado e conhecido. Cabe a quem chama passar um vetor do tamanho correto.
- dentro do vetor tem alguma informação que permite saber o tamanho dos dados. As formas mais comuns são ter o primeiro elemento usado para armazenar isso ou ter um elemento que marca o final dos dados (um elemento que tem um valor inválido, que é usado para dizer que os dados válidos terminaram logo antes dele).
- a função chamadora passa para a função chamada, além do vetor, o seu tamanho.

O primeiro caso é o mais simples, mas o mais restritivo (tipicamente é usado em programas em que se tem todos os vetores do mesmo tamanho, ou o tamanho é ligado a algo que não varia (o número de dias na semana, por exemplo)).

O segundo caso é bastante usado em C para o armazenamento de cadeias de caracteres, com um caractere especial para representar o final (veremos isso logo).

O terceiro caso é o que vamos usar agora. O recomendado (embora não obrigatoriamente seja o mais comum) é colocar o tamanho logo antes do vetor na lista de argumentos, para se poder usar este estilo:
```c
  int f(int n, double vet[n])
```
para ficar auto-documentado que o parâmetro `n` contém o tamanho do vetor `vet`.

Por exemplo, uma função para ler um vetor de números float poderia ser escrita assim:
```c
  void le_vetor(int n, float v[n])
  {
    printf("Digite %d valores ", n);
    for (int i = 0; i < n; i++) {
      scanf("%f", &v[i]);
    }
  }
```
Essa função poderia ser chamada assim:
```c
  float dados[10];
  float outros_dados[5];
  le_vetor(10, dados);
  le_vetor(5, outros_dados);
```

#### Exercícios

1. Refaça os exercícios anteriores, usando funções para realizar as operações básicas sobre os vetores. Por exemplo, no programa 1 crie uma função para ler o vetor, outra para inverter os valores no vetor e outra para imprimir o vetor. O programa principal poderia ficar assim:
   ```c
   int main()
   {
     int d[10];
     le_vet(10, d);
     inverte_vet(10, d);
     imprime_vet(10, d);
   }
   ```

1. Faça uma função que recebe um vetor de float e dois índices, e troca o valor que está em um dos índices pelo que está no outro.
   Por exemplo, se o vetor `v` tem os valores `1 2 5 4 3 6`, depois de chamar a função `troca(v, 2, 4);`, o vetor passará a conter `1 2 3 4 5 6`.
   Se os índices forem iguais, a função não faz nada.
   Faça um programa para testar essa função.

1. Faça uma função que recebe o tamanho de um vetor e um vetor de float desse tamanho.
   A função deve retornar o índice no vetor onde se encontra o maior valor do vetor.
   Por exemplo, se o vetor `v` contém `1 2 7 6 5 8 3`, a chamada `pos_maior(7, v)` deve retornar 5 (5 é o índice onde está o valor 8, o maior valor no vetor). Se, com o mesmo vetor `v` a chamada for `pos_maior(5, v)`, deve retornar 2.
   Se existir o mesmo maior valor em mais de uma posição, qualquer dessas posições pode ser retornada.

1. Faça uma função que recebe o tamanho de um vetor e o vetor, e ordena os valores no vetor em ordem crescente.
   Para ordenar, faça o seguinte: em cada posição do vetor, começando pela última até a segunda, use a função do exercício anterior para encontrar a posição onde está o maior elemento, desde o início do vetor até essa posição.
   O elemento nessa posição é o que deveria estar na posição considerada.
   Use a função de troca acima para trocar esses dois elementos de posição.

   Por exemplo, suponha que inicialmente o vetor tenha `2 4 1 3`. 
   A primeira posição a considerar é 3 (a última do vetor).
   Chamando a função `pos_maior(4, v)`, retorna 1, que é a posição onde está o maior número. Chamando `troca(v, 1, 3)`, para trocar o maior número com o da posição 3, o vetor fica `2 3 1 4`.

   A próxima posição é 2.
   Chamando agora `pos_maior(3, v)`, retorna 1, que é a posição onde está o maior número entre os 3 primeiros (o número 3).
   Chamando `troca(v, 1, 2)`, o vetor torna-se `2 1 3 4`.

   A próxima posição é 1. Chamando `pos_maior(2, v)` retorna 0. Chamando `troca(v, 0, 1)` o vetor fica `1 2 3 4`.
   Não precisa testar a primeira posição, porque não vai ter com quem trocar, então o único valor que sobrou certamente já está na posição certa.
   
   Para facilitar o teste, inicialize um vetor e o ordene.
   Ou faça uma função que preenche um vetor com valores aleatórios. Chama essa função, chama a que imprime, chama a que ordena e chama a que imprime de novo.
   A função abaixo pode ser usada para gerar valores inteiros aleatórios entre min e max (inclui stdlib.h).
   ```c
    int aleat(int min, int max)
    {
      return rand() % (max - min + 1) + min;
    }
    ```


<a id="string"></a>
## Strings

Uma *string* é uma sequência de caracteres, usada para representar palavras, textos, etc em um programa.
Várias linguagens de programação têm strings como um dos tipos de dados básicos da linguagem, como números inteiros ou em ponto flutuante.

Em um tipo numérico, o quantidade de memória necessária para representar um valor não depende desse valor, mas de seu tipo. Se um inteiro ocupa 4 bytes, esse será o espaço necessário para armazenar o valor 0 ou o valor 200 milhões, ou qualquer outro dos valores representáveis desse tipo.
Com strings, é necessário um espaço para cada caractere que a string contém, fazendo com que o espaço necessário para a string "Oi" seja diferente do necessário para a string "Boa noite".
Foram criadas várias formas de se lidar com esse problema, nas várias linguagens de programação que já foram inventadas.

Na linguagem C, resolveu-se não tratar esse problema diretamente na linguagem. Ela não tem esse tipo de dados, e oferece algumas (poucas) facilidades para sua implementação.
As strings em C são geralmente colocadas em vetores de char.
Como qualquer vetor em C, vetores de char são de tamanho invariável, e esse tamanho não é facilmente acessável (uma função que recebe um vetor não tem como saber seu tamanho por métodos diretos, por exemplo).
Strings são tipicamente mais dinâmicas que vetores de char (em geral se pode alterar seu valor, e alterações no valor de uma string comumente alteram o número de caracteres que ela contém.
O casamento dessas incompatibilidades é tarefa que a linguagem não resolve, seu controle deve ser realizado externamente, diretamente pelo programador e com a ajuda de funções de biblioteca.
Felizmente, a biblioteca padrão da linguagem oferece um conjunto de funções que facilitam o manuseio de strings.

Uma dessas padronizações é a forma de se representar uma string cujo tamanho pode variar, sendo essa string colocada em um vetor que tem tamanho fixo. A forma escolhida foi colocar, logo após o fim da string (e para marcar esse final), um caractere especial que informa que a string terminou. Foi escolhido para isso o caractere com código 0. Como esse caractere serve para informar o final da string, essa representação tem a limitação de que não é possível ter esse caractere no interior de uma string. Essa limitação não é considerada muito importante, porque o caractere de código 0 (que foi criado para indicar uma operação nula a um dispositivo) tem um uso bastante infrequente.
Para chamar a atenção para o fato que se está tratando do caractere que tem o código 0 e não de um zero qualquer, é comum se representar esse caractere como `'\0'`.

Para ser armazenada em um vetor, uma string necessita portanto que o vetor tenha tamanho suficiente para conter todos os caracteres que constituem a string mais um para o caractere que representa o seu final.
Como o estouro de vetor (o acesso além dos limites do vetor) não é controlado pela linguagem, esse controle no caso de strings deve ser uma preocupação constante do programador, que sempre deve certificar-se que seus vetores têm capacidade suficiente para as strings que armazenam.
Essa é uma das principais fontes de erro em programas feitos na linguagem C, e considerado um de seus principais defeitos de projeto.

A linguagem oferece strings constantes, que são representadas entre aspas duplas. Uma sequência de caracteres entre aspas duplas é colocada na memória pelo compilador da forma esperada pelas funções, com um caractere extra de código 0 após o último caractere pertencente à string.
Um vetor de char pode ser inicializado por uma string constante, tomando-se cuidado para que o tamanho do vetor seja suficiente para todos os seus caracteres mais o '\0'.
```c
  char a[8] = "12345"; // ok, o vetor a tem 8 char, a string tem 5 caracteres e ocupa 6 (5+1); os dois char restantes serão preenchidos com 0
  char b[]  = "12345"; // ok, o vetor b será alocado com 6 posicoes
  char c[5] = "12345"; // mais ou menos ok, o vetor de 5 posições será inicializado com os caracteres, mas não será uma string porque nao terá o 0 final
  char d[4] = "12345"; // não ok, e será detectado como um erro pelo compilador, inicialização de mais elementos do que cabe no vetor
```

### Exercícios

1. Faça uma função que recebe dois vetores de char. O segundo vetor contém uma string qualquer. A função deve copiar essa string para o primeiro vetor.
1. Faça uma função que recebe um inteiro e dois vetores de char. O segundo vetor contém uma string qualquer. O inteiro é o tamanho do primeiro vetor. A função deve copiar a string do segundo vetor para o primeiro. Caso não haja espaço suficiente, deve ser copiado só o início da string que cabe no vetor. A string deve ser corretamente terminada com o caractere '\0', que deve obviamente ser colocado em uma posição válida do vetor destino. Posições no vetor destino após esse '\0' (se houver), não devem ser alteradas.
3. Faça uma função que recebe um inteiro e dois vetores de char. Os vetores contêm strings. O inteiro contém o tamanho do primeiro vetor (o tamanho do vetor, não da string). A função deve copiar a string do segundo vetor no final da string do primeiro, sem escrever além do final do vetor, com a correta finalização da string. A cópia deve ser truncada caso o vetor seja muito pequeno. Por exemplo, se o primeiro vetor tem tamanho 10 e contém a string "Oi, ", e o segundo vetor tem a string "povo imundo!", ao final da execução da função o primeiro vetor deverá conter a string "Oi, povo ".
1. Faça uma função que recebe um vetor de char contendo uma string e retorna o número de palavras nessa string. Uma palavra é definida como uma sequência ininterrupta de letras (maiúsculas ou minúsculas). Por exemplo, tem uma palavra em "teste", duas em "outro teste ", três em "9-a.b_c". Teste sua função.
2. Faça uma função que recebe um vetor de char contendo uma string e altera essa string para que as palavras que ela contém fiquem todas com a primeira letra maiúscula e as demais minúsculas. Por exemplo, se a função receber um vetor com "onDE foi PARAR", deve alterar a string para "Onde Foi Parar". Palavras devem ser consideradas como no exercício anterior.
3. Faça uma função que recebe um vetor de char contendo uma string e altera essa string para manter somente as palavras que ela contém, separadas por espaços e alteradas como no exemplo anterior. Por exemplo, se a função receber um vetor com "='onDE,.   foi-PARAR935", deve alterar a string para "Onde Foi Parar".

### Algumas funções padronizadas para tratamento de strings

As funções printf e scanf têm suporte a strings, com o formato `%s`.
No caso do printf, ele imprimirá todos os caracteres encontrados no vetor que recebe como argumento, até encontrar um caractere de código 0 (que não é impresso por não pertencer à string).

No caso do scanf, ele pula caracteres espaço (e fim de linha, tabulação), e coloca na string os caracteres não espaço da entrada, até encontrar um caractere espaço. O scanf não tem como fazer verificação do tamanho do vetor, então pode escrever fora do vetor caso tenha na entrada mais caracteres que a capacidade do vetor. Por causa desse problema, não é recomendado usar scanf para ler strings.
Pode-se limitar o número de caracteres a serem lidos pelo scanf, com um formato como `%29s`; nesse caso, o scanf lerá no máximo 29 caracteres, e não causará estouro ao ler uma string para um vetor com tamanho para 30 char.

O scanf tem também o formato `%[`, que lê uma string composta pelos caracteres da entrada que são iguais aos caracteres dentro dos colchetes, até encontrar um que não pertença a esse conjunto. Por exemplo, `%[abc, ]` vai ler caracteres até encontrar um que não seja abc nem vírgula nem espaço. O conjunto de caracteres pode ser invertido, se começar com `^`, `%[^\n]` é comum, para dizer qualquer caractere exceto `\n`, ou para ler até o fim da linha.

Uma outra função padrão para a leitura de strings é a função `fgets`. Essa função recebe 3 argumentos, o primeiro é o vetor onde colocar a string, o segundo é o tamanho desse vetor (ou quantos caracteres no máximo a função pode escrever), e o terceiro representa de onde se quer ler (a entrada padrão, que é de onde todas as funções de entrada que usamos até agora lêm é representada por `stdin`). Os caracteres da entrada são lidos e armazenados no vetor (sem pular espaços no início), até que tenham sido lidos n-1 caracteres ou até que chegue no final da linha na entrada; a função põe então um caractere de código 0 no final. Se chegar ao final da linha, o caractere de final de linha ('\n') será o último caractere colocado por fgets na string.
Tem uma função mais simples também para imprimir strings, que é `puts`. Abaixo um exemplo de uso das duas.
```c
  char nome[20];
  puts("Qual seu nome? ");
  fgets(nome, 20, stdin);
  printf("Seu nome é %s.\n", nome);
```
Outro cuidado a tomar no caso de usar scanf é que, como se está passando um vetor como argumento, não se deve colocar o `&` antes do nome do vetor, diferente dos demais tipos de dados:
```c
  scanf("%19s", nome);
```

Incluindo `<string.h>`, se tem acesso a um conjunto de funções para o manuseio de strings.
Entre elas:
- `strlen`: recebe uma string (o vetor que contém a string) e retorna o tamanho dessa string (o número de caracteres que ela contém). Para isso, conta todos os caracteres antes do '\0'.
- `strcpy`: recebe dois vetores, e copia para o primeiro a string que está no segundo. Equivale a uma atribuição de strings, já que não existe atribuição de vetores na linguagem. Copia caractere a caractere, até copiar o '\0'. É responsabilidade do programador garantir que o vetor que recebe a string tem o espaço necessário.
- `strcat`: recebe duas strings, e concatena a segunda string à primeira (acrescenta os caracteres da segunda string ao final da primeira. É responsabilidade do programador garantir que tem espaço no vetor.

### Exercícios

1. Implemente as funções acima, mudando o nome para não dar conflito com as funções originais. Abaixo está um programa, para ajudar a testar a implementação dessas funções. Altere para incluir `string.h` e para usar as funções oficiais, para ver se o resultado é o mesmo.
```c
#include <stdio.h>

int mstrlen(char v[]) { // retorna o número de caracteres da string em v
}

void mstrcpy(char d[], char o[]) { // copia a str em o para d
}

void mstrcat(char d[], char o[]) { // copia a str em o para o final da string em d
}

void imprime_str(char s[])
{
  for (int i = 0; s[i] != '\0'; i++) {
    putchar(s[i]);
  }
}

int main()
{
  char s[30] = "Abacaxi";
  char s2[10] = "bom";
  char s3[10];
  printf("%s tem %d caracteres\n", s, mstrlen(s));
  printf("%s tem %d caracteres\n", s2, mstrlen(s2));
  mstrcpy(s3, s2);
  printf("%s tem %d caracteres\n", s3, mstrlen(s3));
  mstrcat(s, " ");
  mstrcat(s, s2);
  printf("%s tem %d caracteres\n", s, mstrlen(s));
  imprime_str(s);
}
```
1. Faça uma função que recebe um vetor de char contendo uma string e retorna um int que diz quantas letras a string possui. Considere só as 52 letras, sem acentos.
1. Implemente uma função que recebe um vetor de char que contém uma string, e retorna um bool que diz se essa string é ou não um palíndromo (se a sequência de caracteres é a mesma, lida da esquerda para a direita ou da direita pra esquerda). ```"AS SATAS SA"``` é um palíndromo, ```"OS SOTOS SA"``` não é. Faça um programa para testar sua função.
2. Faça uma função que copia uma string para um vetor, copiando somente as letras, e transformando minúsculas em maiúsculas. Usando essa função, o resultado da cópia de "Socorram-me, subi no onibus em Marrocos" deve ser um palíndromo.
1. Faça uma função que compara duas strings. A função deve receber duas strings e retornar um int, que deve ser 0 se as strings são iguais, um número negativo se a primeira string vem antes da segunda em um dicionário e positivo caso contrário. Uma forma simples de calcular é subtraindo o primeiro caractere diferente das duas strings (sem esquecer de parar no primeiro `'\0'`). A biblioteca padrão tem uma função para fazer isso, chamada `strcmp`, e é a forma de se comparar strings.
1. Faça uma função recebe um vetor de char, imprime a string que está nesse vetor, pede para o usuário digitar uma string com "sim" ou "não", e retorna `true` se for digitado "sim" ou `false` se for digitado "nao" ou "não". Se for digitado outro texto, volta a pedir ao usuário para digitar "sim" ou "não", até que o usuário faça o que é pedido. Use a função acima para verificar a string digitada.

### Mais exercícios

1. Faça uma função que recebe um vetor com uma string e inverte os caracteres dessa string. Por exemplo, se receber "teste", deve alterar para "etset".
   Com essa função, dá para implementar a função de detecção de palíndromo assim:
   ```c
   bool palindromo(char s[])
   {
     char cp[strlen(s)+1];
     strcpy(cp, s);
     inverte(cp);
     return strcmp(cp, s) == 0;
   }
   ```
2. Faça uma função que recebe um vetor com uma string e um char, e retorna um int que diz em que posição da string está a primeira ocorrência do char, ou -1, caso a string não contenha o char. 
   Com essa função, seria possível implementar a função que diz se um char é uma vogal assim:
   ```c
   bool vogal(char c)
   {
     return achachar("aeiou", minusculiza1(c)) != -1;
   }
   ```
3. Faça uma função que recebe dois vetores com strings, e retorna um int que diz a posição no primeiro vetor onde está a primeira ocorrência de algum dos caracteres da segunda string, ou -1 caso a primeira string não contenha nenhum caractere da segunda.
   Por exemplo, chamando essa função com "teste 82.5" e "0123456789", retorna 6, a posição do primeiro dígito da primeira string.
4. Faça uma função que recebe um vetor com uma string e retorna um bool que diz se a string pode ser uma senha. Uma senha deve ter no mínimo 8 caracteres, pelo menos uma minúscula, uma maiúscula, um dígito e um caractere que não é nem letra nem dígito.
5. Faça uma função que recebe um inteiro e um vetor de char. O inteiro diz o tamanho do vetor. A função deve ler uma linha da entrada (ler caracteres com getchar até o `\n`) e colocar esses caracteres no vetor como uma string. A string deve ser corretamente terminada com '\0', não deve conter o '\n', não deve estrapolar a capacidade do vetor, deve descartar os caracteres que não cabem, caso a linha seja muito grande. Deve suportar uma linha vazia (se o primeiro caractere for '\n', deve retornar uma string vazia válida, com '\0' no início do vetor).
6. Faça uma função para ler uma nova senha do usuário. A função recebe o tamanho de um vetor e um vetor de char, que deve preencher com a senha digitada. A função deve ler a senha 2 vezes, e só aceitar se as duas forem iguais e se a primeira for uma senha válida. Se a primeira for vazia, deve retornar com o vetor contendo uma string vazia. Caso a primeira não seja válida, deve pedir novamente até que seja. Caso a segunda não seja igual à primeira, deve pedir novamente a primeira.
