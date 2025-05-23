## Arquivos

Nos programas que desenvolvemos até agora, os dados que foram manipulados estavam na memória principal, acessados na forma de variáveis.
Essa memória é de uso temporário, ela é toda liberada para reuso quando o programa termina sua execução.
Existem situações, porém, em que os dados devem sobreviver aos programas.
Na verdade, esse é o caso mais comum, e os dados tipicamente têm mais valor que os programas que os manipulam.

Para garantir a sobrevida dos dados, eles são armazenados em unidades de memória externa aos programas, em dispositivos de armazenamento, na forma de **arquivos**.
Um arquivo é uma região de um dispositivo de armazenamento, que é identificado por um nome, e contém uma quantidade qualquer de bytes (limitado, claro, à capacidade do dispositivo).
É responsabilidade do sistema operacional gerenciar os blocos dos dispositivos de armazenamento para implementar a abstração de arquivos.

Para que o conteúdo de um arquivo possa ser manipulado por um programa, ele deve ser copiado para a memória principal do computador, em uma operação de **leitura**.
Para que dados da memória principal sejam colocados em arquivos, eles devem ser transferidos para esses arquivos, em uma operação de **escrita**.

Para se poder realizar uma operação de leitura ou de escrita sobre um arquivo, ele inicialmente deve ser "**aberto**" -- o programa deve indicar o nome do arquivo que quer acessar e o tipo de operação que pretende realizar.
Após a realização das operações de leitura ou escrita sobre o arquivo, ele deve ser **fechado**, para que o sistema atualize corretamente as informações sobre o dispositivo de armazenamento.

Resumindo, são 4 as operações básicas sobre arquivos: abertura, leitura, escrita e fechamento. As operações de leitura, escrita e fechamento só podem ser realizadas sobre um arquivo que tenha sido previamente aberto e ainda não fechado.

Em C, o acesso a arquivos é feito através de funções. 
Vamos ver um conjunto básico de funções que permite o manuseio de arquivos.
Para ter acesso a essas funções, o programa deve incluir `stdio.h`.
Em um programa, um arquivo é representado por uma variável, do tipo `FILE *`.
Essa variável deve ser inicializada na abertura do arquivo e deve ser fornecida para as demais funções de manipulação do arquivo, para identificar sobre qual arquivo se quer realizar tal operação.
As funções são:

- `fopen` - serve para abrir um arquivo. Recebe dois argumentos: o *nome do arquivo* (uma string) e o *modo de abertura* (outra string). Dois dos modos de abertura possíveis nos interessam por enquanto: `"r"`, para abrir o arquivo para leitura e `"w"`, para abri-lo para gravação.

   Só se pode abrir para leitura um arquivo que já exista e sobre o qual o programa tenha direito de leitura.

   Só se pode abrir para gravação um arquivo que já existe sobre o qual o programa tenha direito de gravação ou um arquivo que não exista, que será criado pela operação de abertura, se o programa tiver o direito de criar arquivos no local pedido.
Quando o arquivo é aberto para gravação, qualquer conteúdo que o mesmo tenha é descartado.

   A função `fopen` returna um `FILE *` que identifica o arquivo aberto.
Caso a operação de abertura não tenha sido possível, o valor `NULL` é retornado, e não se pode realizar nenhuma outra operação sobre o arquivo.
- `fclose` - serve para informar o sistema que não vamos mais realizar operações sobre esse arquivo. Recebe como argumento um `FILE *`, que deve corresponder a um arquivo aberto.
- `fscanf` - serve para realizar leitura de dados sobre um arquivo aberto para leitura.
Tem funcionamento similar à função `scanf`, exceto que em vez de ler os dados do teclado, lê do arquivo.
Os argumentos da função são os mesmos de `scanf`, acrescidos de um primeiro argumento, um `FILE *` que identifica um arquivo que foi previamente aberto para leitura, do qual serão pegos os dados necessários para o scanf.

   Da mesma forma que `scanf`, `fscanf` retorna o número de conversões bem sucedidas que conseguiu realizar, ou um número negativo em caso de erro.
- `feof` - serve para saber se já foi realizada uma operação de leitura que tenha tentado ler além do final dos dados do arquivo.
Recebe como argumento um `FILE *` que corresponde a um arquivo aberto para leitura e retorna um valor que pode ser testado como verdadeiro ou falso. Ele retorna verdadeiro somente após se realizar uma operação mal sucedida (por ir além do final do arquivo) de leitura -- retorna falso mesmo que se tenha lido o último byte do arquivo, se não se tentou ler além dele.
- `fprintf` - serve para gravar dados em um arquivo.
Funciona como o `printf`, e tem os mesmos argumentos, acrescidos de um argumento inicial, um `FILE *` que corresponde a um arquivo que tenha sido aberto para escrita, no qual serão escritos os dados formatados por `fprintf`.

Exemplo de um programa que lê números de um arquivo e informa a soma dos números lidos:

```c
#include <stdio.h>

int main()
{
  FILE *arq;
  char nome[] = "dados";

  // abre o arquivo para leitura
  arq = fopen(nome, "r");
  // verifica se a abertura do arquivo foi bem sucedida
  if (arq == NULL) {
    printf("Não foi possível abrir o arquivo '%s' para leitura\n", nome);
    return 1;
  }

  long soma = 0;
  int nnum = 0;
  for (;;) {
    int val;
    // lê um inteiro do arquivo e verifica se a leitura foi bem sucedida
    if (fscanf(arq, "%d", &val) != 1) {
      break;
    }
    // acumula o valor lido à soma e incrementa o contador de números lidos
    soma += val;
    nnum++;
  }
  // fecha o arquivo
  fclose(arq);

  printf("Foram lidos %d números do arquivo, que somam %ld\n", nnum, soma);
  return 0;
}
```

Outro exemplo, um programa que cria um arquivo com dados interessantes para o programa anterior:
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *arq;

  // abre o arquivo para escrita
  arq = fopen("dados", "w");
  // verifica se a abertura foi bem sucedida
  if (arq == NULL) {
    printf("Não foi possível abrir o arquivo 'dados' para escrita.\n");
    return 1;
  }

  for (int i=0; i<100; i++) {
    // escreve uma linha no arquivo com um valor inteiro aleatório
    fprintf(arq, "%d\n", rand());
  }

  // fecha o arquivo
  fclose(arq);
  return 0;
}
```

Outro exemplo, um programa que copia um arquivo para outro, retirando espaços duplicados:
```c
#include <stdio.h>
#include <stdbool.h>

int main()
{
  char nome_entrada[30], nome_saida[30];
  FILE *entrada;
  FILE *saida;

  printf("Programa de copia de arquivos.\n");
  printf("Digite o nome do arquivo de entrada: ");
  scanf("%s", nome_entrada);
  entrada = fopen(nome_entrada, "r");
  if (entrada == NULL) {
    printf("Não foi possível abrir o arquivo '%s'.\n", nome_entrada);
    return 1;
  }

  printf("Digite o nome do arquivo de saída: ");
  scanf("%s", nome_saida);
  saida = fopen(nome_saida, "w");
  if (saida == NULL) {
    printf("Nao foi possível abrir o arquivo '%s'.\n", nome_saida);
    return 2;
  }

  int bytes_lidos = 0, bytes_escritos = 0;
  bool anterior_foi_espaco = false; // true se o caractere anterior foi um espaço
  for (;;) {
    char c;
    fscanf(entrada, "%c", &c);
    if (feof(entrada)) { // poderia também testar o retorno do fscanf
      break;
    }
    bytes_lidos++;
    if (c != ' ' || !anterior_foi_espaco) {
      fprintf(saida, "%c", c);
      bytes_escritos++;
    }
    anterior_foi_espaco = (c == ' ');
  }

  fclose(entrada);
  fclose(saida);
  printf("Foram lidos %d bytes e gravados %d.\n", bytes_lidos, bytes_escritos);
  return 0;
}
```
Mais um exemplo, que mostra na tela o conteúdo de um arquivo
```c
#include <stdio.h>

int main(int argc, char *argv[argc])
{
  if (argc != 2) {
    fprintf(stderr, "Uso: %d nome_do_arquido", argc[0]);
    return -1;
  }
  FILE *descritor = fopen(argv[1], "r");
  if (descritor != NULL) {
    fprintf(stderr, "Erro no acesso ao arquivo '%s'\n", argv[1]);
    return -2;
  }
  // lê o arquivo byte a byte -- seria melhor ler mais por vez (linha, por ex.)
  for (;;) {
    int c = fgetc(descritor);
    if (feof(descritor)) break;
    putchar(c);
  }
  fclose(c);
}
```

* * *

### Exercícios

1. Faça uma função que recebe o nome de um arquivo e retorna quantos números inteiros existem nesse arquivo.
A função deve abrir o arquivo, ler os diversos números, contando quantos são, até que o arquivo acabe, e fechar o arquivo.
1. Altere a função anterior, para que retorne -1 caso o arquivo contenha algo que não é interpretado como um número.
Para reconhecer essa situação, use o retorno de fscanf e de feof (o fscanf diz que não consegue realizar a conversão mas o feof diz que o arquivo não terminou).
1. Faça uma função que recebe um nome de arquivo, um tamanho de vetor e um vetor de inteiros desse tamanho, e lê os inteiros que estão nesse arquivo para dentro do vetor. A função não deve ler mais inteiros que cabem no vetor, e deve retornar o número de inteiros que foram colocados no vetor. Não esqueça de fechar o arquivo.
1. Faça uma função que recebe um nome de arquivo, um tamanho de vetor e um vetor de inteiros desse tamanho, e escreve esses valores no arquivo, um por linha.
A função deve retornar um *bool* informando se a gravação deu certo.
1. Um arquivo contém dados correspondentes a um vetor de inteiros, no seguinte formato: o primeiro inteiro é o tamanho do vetor (o número de valores que ele contém) e os valores seguintes são os valores em cada posição do vetor, em ordem de índice. O tamanho do vetor em um arquivo desses está sempre entre 1 e 100, inclusive. Faça uma função que recebe o nome de um arquivo que está nesse formato e um vetor onde cabem 100 inteiros, lê os valores do arquivo para o vetor e retorna o tamanho do vetor lido (o número de valores que foram colocados no vetor). A função deve retornar um número negativo em caso de erro (se não conseguiu acessar o arquivo ou se o conteúdo do arquivo não está de acordo com o esperado).
2. Faça uma função que recebe o tamanho de um vetor e um vetor de inteiros desse tamanho e imprime o conteúdo do vetor na tela.
3. Faça uma função como a anterior, que recebe também uma string com o nome de um arquivo, e grava o conteúdo desse vetor no arquivo, no formato descrito no exercício 5.
4. Faça uma função que recebe dois vetores preenchidos com inteiros (cada um tem também um argumento com seu tamanho) e um terceiro vetor. A função deve preencher o terceiro vetor com os valores comuns aos outros dois vetores, e retornar o número de valores que colocou nesse terceiro vetor.
5. Faça um programa que lê dois vetores de dois arquivos, produz um terceiro com os valores comuns, escreve na tela o conteúdo dos 3 vetores e grava em um terceiro arquivo o vetor calculado. O programa deve usar as funções dos exercícios 5, 6, 7, 8.
1. Faça um programa para corrigir provas do vestibular. Ele deve ler um arquivo chamado "gabarito", que contém o gabarito da prova, em duas linhas: na primeira linha tem um inteiro com o número "n" de questões da prova, e a segunda tem "n" letras, correspondentes a resposta certa de cada questão. A resposta pode ser uma letra entre A e E, ou X, para indicar que a questão foi anulada.

   O segundo arquivo, chamado "provas" contém uma linha para cada candidato, com "n" letras, seguidas de um espaço, seguido de até 40 caracteres com o nome do candidato. Cada um dos "n" caracteres pode ser A a E ou X, para uma resposta inválida.

   O programa deve gravar um terceiro arquivo, "resultados", contendo uma linha por candidato, cada linha contendo o número de acertos, seguido de um espaço, seguido do nome do candidato.

   Uma questão que tenha X no gabarito não deve ser considerada correta para nenhum candidato; uma questão que tenha X na resposta deve ser considerada errada.

* * *
