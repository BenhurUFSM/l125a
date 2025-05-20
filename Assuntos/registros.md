## Registros (*struct*)

### O tipo de dado composto "registro"

Nos tipos de variáveis que vimos até agora, ou armazenamos um único valor em uma variável simples, ou vários valores do mesmo tipo, em um vetor.
Nesse último caso, cada um dos vários valores é identificado por posição.
Em algumas situações, gostaríamos de agrupar vários valores em uma mesma variável, mas identificá-los por posição pode não ser muito natural.
Por exemplo, se quisermos uma variável que identifique uma data, que contém 3 valores (dia, mês e ano). Colocar esses 3 valores em um vetor não vai levar a um programa especialmente fácil de ser entendido.
Outras vezes, nem todos os dados que se quer reunir são do mesmo tipo -- imagine por exemplo que se queira agrupar vários dados a respeito de um produto (descrição, preço, data de aquisição, etc).

Para esses casos, tem-se uma outra forma de se agrupar dados em uma só variável, o **registro** ou estrutura, como é chamado em C (`struct`).
Em um registro, pode-se colocar quantos dados quiser, cada um deles podendo ser de qualquer dos tipos da linguagem (inclusive vetores e registros).
A forma de se identificar cada um desses dados é através de um nome.
Cada um dos dados componentes de um registro é chamado de **campo**.

Por exemplo, uma variável chamada `nascimento` poderia armazenar uma data, em um registro contendo três campos, `dia`, `mes`, `ano`, todos do tipo `int`. Essa variável poderia ser declarada assim:
```c
  struct {
    int dia;
    int mes;
    int ano;
  } nascimento;
```
A forma de se acessar um campo de uma variável do tipo registro é separando o nome da variável do nome do campo por um ponto (`.`).
Por exemplo, para colocar a data 30/03/2007 na variável declarada acima, e depois imprimir a data, pode-se usar o código abaixo:
```c
  nascimento.dia = 30;
  nascimento.mes = 3;
  nascimento.ano = 2007;
  printf("Fulano nasceu em %02d/%02d/%04d.\n",
         nascimento.dia, nascimento.mes, nascimento.ano);
```

O tipo da variável nascimento declarada acima é `struct { int dia; int mes; int ano; }`.
Para evitar ter que escrever isso tudo ao se declarar outras variáveis do mesmo tipo, ou declarar funções que recebam ou retornem dados desse tipo, geralmente se cria "apelidos" ou nomes alternativos para esses tipos.
Existem duas formas de se dar nomes a estruturas em C.
Uma delas é com "etiquetas" (*tag* em inglês). 
Coloca-se, entre `struct` e o `{` um nome para o registro. 
A partir daí, pode-se usar `struct nome` sempre que precisar se referir a esse tipo.
Por exemplo, a definição do tipo de registro de nascimento poderia receber o nome `data`, e ser usada para declarar uma outra variável, chamada `hoje`, que também é uma dessas estruturas:
```c
  struct data {
    int dia;
    int mes;
    int ano;
  } nascimento;

  struct data hoje;
```

A segunda forma é criando um novo nome para o tipo. 
Isso pode ser feito com qualquer tipo em C, através da palavra chave `typedef`.
Ela funciona como a declaração de uma variável, mas, em vez de criar uma variável, cria um novo tipo.
No exemplo abaixo, se está criando um novo tipo, chamado `inteiro`, que é idêntico ao tipo `int`, e criando uma variável desse novo tipo (a variável `xis` vai ser do tipo `int`).
```c
  typedef int inteiro;
  inteiro xis;
```
Criar novos nomes para os tipos básicos nâo tem muita graça, mas com registros é bastante útil.
O novo tipo pode ser usado em qualquer lugar que o tipo `struct` poderia ser usado.
O exemplo acima ficaria assim:
```c
  // cria o tipo "data"
  typedef struct {
    int dia;
    int mes;
    int ano;
  } data;

  // cria variáveis do tipo "data"
  data nascimento;
  data hoje;
```

De qualquer das formas, um registro pode ser passado como argumento para uma função e pode ser o tipo do valor de retorno de uma função.
Como nos tipos básicos da linguagem (e diferente de vetores), a passagem de registros como argumento de funções é feita por cópia e não por referência.
A função que recebe um registro como argumento, quando altera esse argumento está alterando a sua cópia, e não a variável da função chamadora.

Uma função que recebe uma data e calcula quantos dias se passaram desde o início do ano poderia ser (com o tipo data definido com o typedef acima):
```c
int dias_desde_ano_novo(data dia)
{
                  // J31 F28 M31 A30  M31  J30  J31  A31  S30  O31  N30  D31
  int dias_antes[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 303, 334 };
  int n_dias;
  // calcula quantos dias se passaram até o fim do mês anterior
  n_dias = dias_antes[dia.mes - 1];
  //   sem esquecer que os bissextos têm um dia a mais em fevereiro
  if (bissexto(dia.ano) && dia.mes > 2) n_dias++;
  // soma o dia da data
  n_dias += dia.dia;
  return n_dias;
}
```
Uma função que faz o contrário, retorna a data que corresponde a tantos dias depois do início de um ano:
```c
data data_desde_ano_novo(int ano, int dias)
{
  // se tem mais dias do que cabe no ano, avança para o ano seguinte
  while (dias > dias_no_ano(ano)) {
    dias -= dias_no_ano(ano);
    ano++;
  }
  // chuta a data para o dia primeiro do ano
  data retorno = { 1, 1, ano };
  // se o número de dias é maior que o mês, avança para o mês seguinte
  while (dias > dias_no_mes(retorno.mes, retorno.ano)) {
    dias -= dias_no_mes(retorno.mes, retorno.ano);
    retorno.mes++;
  }
  retorno.dia = dias;
  return retorno;
}
```
Como mostrado no exemplo acima, uma variável do tipo estrutura pode ser inicializada com os valores dos campos separados por vírgula, entre chaves. Os valores devem estar na ordem em que aparecem na definição da estrutura.
 Pode-se atribuir uma estrutura a outra, mas não tem atribuição de valor constante:
```c
   data d1 = {10, 10, 2010};
   data d2;

   d2 = d1; // OK
   d2 = {20, 10, 2020}; // INVÁLIDO
```

Em versões mais recentes do padrão C, isso pode ser feito assim:
```c
   data d1 = { .dia = 10, .mes = 10, .ano = 2010};
   data d2;

   d2 = d1; // OK
   d2 = (data) {20, 10, 2020}; // OK
```

Outros exemplos:

Uma função que calcula a idade de uma pessoa em determinada data recebendo duas datas como argumento:
```c
int idade(data nascimento, data referencia)
{
  int anos = referencia.ano - nascimento.ano;
  if (refencia.mes < nascimento.mes) {
    anos--;
  } else if (referencia.mes == nascimento.mes && referencia.dia < nascimento.dia) {
    anos--;
  }
  return anos;
}
```

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// um tipo de dados "ponto", para representar um ponto no espaço
//   bidimensional.
// Um ponto é formado por dois valores float, as coordenadas "x" e "y".
typedef struct {
  float x;
  float y;
} ponto;

// uma função que lê um par de coordenadas do usuário e retorna um
//   ponto com essas coordenadas. A função não recebe argumentos.
ponto le_ponto(void)
{
  ponto p;
  printf("digite os valores de x e y de um ponto ");
  scanf("%f%f", &p.x, &p.y);
  return p;
}

// uma função que recebe um ponto e imprime suas coordenadas.
void impr_ponto(ponto p)
{
  printf("<%.2f,%.2f>", p.x, p.y);
}

// um programa que usa essas funções.
int main()
{
  ponto a;
  a = le_ponto();
  printf("Você digitou o ponto ");
  impr_ponto(a);
  printf("\n");
  return 0;
}
```
```c
// uma função que recebe dois pontos e retorna a distância entre eles.
float dist_pt(ponto a, ponto b)
{
  // dá para calcular a distância usando o cálculo da hipotenusa
  float c1 = a.x - b.x;
  float c2 = a.y - b.y;
  return sqrt(c1*c1 + c2*c2);
}

// um programa que usa essas funções.
int main()
{
  ponto a, b;
  a = le_ponto();
  b = le_ponto();
  printf("A distância entre ");
  impr_ponto(a);
  printf(" e ");
  impr_ponto(b);
  printf(" é %.2f\n", dist_pt(a, b));
  return 0;
}
```
```c
// um tipo de dados "retangulo", para representar um retângulo no
//   espaço bidimensional.
// Um retângulo alinhado com os eixos pode ser representado por dois pontos,
//   em dois de seus cantos opostos diagonalmente.
typedef struct {
  ponto inf_esq;
  ponto sup_dir;
} retangulo;

// uma função que recebe um retângulo e retorna sua área
float area_retangulo(retangulo r)
{
  float base = r.sup_dir.x - r.inf_esq.x;
  float altura = r.sup_dir.y - r.inf_esq.y;
  return base * altura;
}

// um tipo de dados "circulo", para representar um círculo no
//   espaço bidimensional.
// Um círculo pode ser representado por um ponto (a posição do centro)
//   e o valor do seu raio.
typedef struct {
  ponto centro;
  float raio;
} circulo;

// uma função que recebe dois círculos e retorna a distância entre eles
float dist_circulos(circulo c1, circulo c2)
{
  return dist_pt(c1.centro, c2.centro) - c1.raio - c2.raio;
}

// uma função que recebe dois círculos e retorna um bool que diz se
//   eles colidem
bool colidem_circ(circulo c1, circulo c2)
{
  return dist_circulos(c1, c2) < 0;
}

```

### Exercícios

1. Faça uma função que compara datas; ela recebe duas datas (como a estrutura do exemplo acima) e retorna um bool, que é verdadeiro se a primeira data for anterior à segunda.
2. Faça uma função que recebe um círculo e um ponto e retorna um bool que diz se esse ponto está dentro do círculo ou não.


### Ponteiros para estruturas

Assim como qualquer outro tipo de dados da linguagem, uma estrutura também pode ser apontada por um ponteiro. 
```c
  typedef struct {
    int dia;
    int mes;
    int ano;
  } data;

  data d1;
  data *p;
  p = &d1;
```
Para se acessar os campos de uma estrutura apontada por um ponteiro, temos um probleminha. No código acima, para acessar o campo `dia` da variável `d1`, usamos `d1.dia`.
Para acessar `d1` através do ponteiro, usamos `*p`.
Então, para acessar o campo `dia` da variável `d1` através do ponteiro `p`, deveria ser `*p.dia`.
Infelizmente não é, porque temos dois operadores, o operador `*` e o operador `.`, e o operador `.` tem precedência sobre o operador `*`.
A expressão `*p.dia` significa `*(p.dia)` e nós precisamos de `(*p).dia`.

A notação `*(p.dia)` significa: `p` é uma estrutura, que contém um campo chamado `dia`; esse campo é um ponteiro, e eu quero dereferenciar esse ponteiro.
É um significado perfeitamente válido, e bastante usado.
O outro significado, que é o que queremos (`p` é um ponteiro para uma estrutura que tem um campo chamado `dia` e eu quero acessar esse campo) também é bastante usado, mas necessita dos parênteses.
Para evitar o desgaste dos dedos dos programadores com a digitação excessiva de parênteses, criou-se uma sintaxe alternativa para esse caso, com um novo operador, `->`, que tem à sua esquerda um ponteiro para estrutura e a sua direita o nome de um campo dessa estrutura.
A notação `p->dia` é equivalente a `(*p).dia`, e é bem mais comum.
Como exemplo, a função que vimos anteriormente poderia, em vez de retornar a estrutura `data`, receber um ponteiro para uma estrutura a ser alterada:

```c
void data_desde_ano_novo(int ano, int dias, data *pdata)
{
  // se tem mais dias do que cabe no ano, avança para o ano seguinte
  while (dias > dias_no_ano(ano)) {
    dias -= dias_no_ano(ano);
    ano++;
  }
  pdata->ano = ano;   // poderia ser também   (*pdata).ano = ano;
  // chuta o mês para janeiro
  pdata->mes = 1;
  // se o número de dias é maior que o mês, avança para o mês seguinte
  while (dias > dias_no_mes(pdata->mes, pdata->ano)) {
    dias -= dias_no_mes(pdata->mes, pdata->ano);
    pdata->mes++;
  }
  pdata->dia = dias;
}
```

#### Misturando tipos compostos

Uma estrutura pode conter campos de qualquer tipo, inclusive outras estruturas, vetores ou ponteiros.
Por exemplo, um registro que contém dados a respeito de um aluno poderia ser:
```c
  typedef struct {
    char nome[50];
    int matricula;
    data nascimento;
    data ingresso;
    int notas_trab[10];
    float notas_provas[2];
    float nota_exame;
    float media;
  } aluno;

  void calcula_media(aluno *a)
  {
    float soma_trab = 0;
    for (int i = 0; i < 10; i++) {
      soma_trab += a->notas_trab[i];
    }
    // calcula a media entre trabalhos e provas
    float media_trab = soma_trab / 10;
    float media_provas = (a->notas_provas[0] + a->notas_provas[1]) / 2;
    float media = (media_trab + media_provas) / 2;
    // altera a media de acordo com a avaliacao subjetiva do aluno
    media += (rand() % 2000) / 1000.0 - 1;
    // verifica se tem exame
    if (media < 7) {
       media = (media + a->nota_exame) / 2;
    }
    // atualiza a media final no registro
    a->media = media;
  }

  int main()
  {
    aluno joao, maria;
    joao = le_dados_do_aluno("Joao da Silva");
    maria = le_dados_do_aluno("Maria Andrades");
    calcula_media(&joao);
    calcula_media(&maria);
    imprime_aluno(joao);
    imprime_aluno(maria);
    return 0;
  }
```
Pode-se ter um vetor de registros:
```c
  void calcula_medias(int n, aluno alunos[n])
  {
    for (int i = 0; i < n; i++) {
      calcula_media(&alunos[i]);
    }
  }
```
```c
  // retorna o índice do primeiro círculo do vetor que contém o ponto,
  //   ou -1 se o ponto não estiver em nenhum deles
  int circulo_no_ponto(int n, circulo circulos[n], ponto p)
  {
    for (int i = 0; i < n; i++) {
      if (ponto_no_circulo(p, circulos[i])) {
        return i;
      }
    }
    return -1;
  }
```

## Enumeração (*enum*)

Uma enumeração é um tipo de dados que define (enumera) todos os valores que um dado desse tipo pode ter. Cada valor possível recebe um nome. A forma de definir um tipo desses em C é com a palavra-chave `enum`, com todos os valores possíveis entre chaves.
Por exemplo, o tipo `bool` poderia ser definido assim:
```c
  typedef enum { false, true } bool;
```
Outro exemplo:
```c
  typedef enum { domingo, segunda, terca, quarta, quinta, sexta, sabado } dia_da_semana;

  dia_da_semana hoje;
  hoje = calcula_o_dia_da_semana();
  if (hoje == sexta && hora > 19) happy_hour(); 
```

Em C, um tipo `enum` é um tipo inteiro, e uma variável de tipo enum pode ser usada da mesma forma que outras variáveis de tipo inteiro.
Os valores de um enum são definidos como valores inteiros iniciando em 0. Pode-se alterar isso com, por exemplo:
```c
  typedef enum { janeiro = 1, fevereiro, marco, `...` } mes_t;
```
Um valor com `=` será definido com o valor após o `=`, um valor sem o `=` será definido como um a mais que o valor anterior ou 0 se for o primeiro.
