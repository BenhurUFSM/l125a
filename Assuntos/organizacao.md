## Introdução - organização de um computador

O objetivo da disciplina é conseguir programar um computador. Para isso devemos produzir um conjunto de comandos que o computador deve realizar. Para entendermos melhor que comandos podemos esperar que um computador consiga realizar, vamos antes ver, de forma bem resumida, como um computador é constituído.

A arquitetura de um computador atual é descendente direta dos primeiros computadores, o que ficou conhecido como arquitetura de von Neumann. Ela é composta de 3 componentes principais:
- unidades de entrada e saída,
- memória, e
- unidade central de processamento.

Essas unidades são interligadas, de forma que dados possam ser passados entre elas.
Um "dado" é um número, e é a única coisa que um computador é capaz de processar.
Para que algo possa ser processado por um computador, devemos encontrar uma forma de representar esse algo como um número ou um conjunto de números.

As unidades de **entrada e saída** convertem informações externas ao computador em dados internos ou vice-versa. Uma unidade de entrada é responsável por converter alguma informação que se deseja que o computador manipule, da forma de representação que ela tem externamente ao computador para uma forma de representação numérica interna (por exemplo, um teclado ou um microfone). Uma unidade de saída converte algum dado interno ao computador em uma representação externa (por exemplo, uma tela ou um fone de ouvido). Algumas unidades, como dispositivos de armazenamento de dados podem ser de entrada e de saída. Uma operação de uma unidade de E/S consiste na realização de uma dessas conversões.

A **memória** do computador é capaz de reter uma grande quantidade de dados. Cada dado é um número, que pode ser alterado ou acessado.
Uma operação da memória corresponde ou a alterar um desses dados (operação de escrita) ou a encontrar um desses dados (operação de leitura).
Cada um dos dados é identificado por um número que representa a posição desse dado na memória, chamado de *endereço*.
Em uma memória com capacidade para N valores existem N endereços diferentes, geralmente com valores entre 0 e N-1.

A **unidade central de processamento**, também chamada de processador ou CPU, da sigla em inglês, é quem controla o funcionamento da máquina. Ela tem dois componentes principais: *unidade lógica e aritmética*, que consegue realizar operações sobre números (soma, multiplicação, comparação, etc), e a *unidade de controle*, que decide quando cada uma das demais unidades deve operar, que operação deve realizar, e que valores devem ser usados nessa operação.

O funcionamento do computador é realizado através da execução de **instruções**. Uma instrução é uma ação básica que é realizada pela execução de uma sequência de operações pelas unidades do computador, controladas pela unidade de controle.
Os principais tipos de instrução envolvem a transferência de dados entre as unidades.
Por exemplo, uma instrução pode movimentar um dado que está na memória para um dispositivo de saída, outra pode transferir um dado de um dispositivo de entrada para uma posição da memória; outra pode realizar duas operações de leitura à memória para pegar dois números, enviá-los à ULA para somá-los e o resultado ser escrito em uma terceira posição de memória, e assim por diante.

A unidade de controle tem pré-programadas as sequências de operações que devem ser realizadas pelas unidades para a execução de cada uma das instruções que um computador pode executar.
O conjunto dessas instruções, que representa tudo que um computador é capaz de realizar, é definido pelo fabricante do processador.
Cada uma dessas instruções recebe um código, um número que a identifica.
A unidade de controle executa a sequência de operações que correspondem a uma instrução assim que recebe um desses códigos. 

Os códigos de instruções para serem executados pela unidade de controle são colocados na memória do computador, assim como os dados que essas instruções manipularão.
Para identificar a instrução a executar, a unidade de controle contém um número (chamado "contador de programa" ou PC), que corresponde ao endereço da memória onde está o código da instrução a ser executada.

A unidade de controle realiza um ciclo de execução durante todo o tempo em que está em funcionamento:
- primeiro ela faz a **busca**, que é uma operação de leitura na memória, no endereço contido no PC, para obter o código da instrução a executar;
- ela então faz a **decodificação**, que corresponde a obter (em seus circuitos internos) a sequência de passos necessários para a execução dessa instrução;
- a seguir, ela realiza a **execução** dessa instrução, seguindo esses passos.

Um desses passos é a alteração do PC, para que ele passe a ter o endereço da instrução seguinte.
Depois de terminar a execução dos passos correspondentes à instrução buscada, a unidade de controle volta à primeira etapa, realizando a busca da próxima instrução.
Esse ciclo se repete enquanto o processador estiver ativo.

Cada instrução realiza pouca coisa; o poder do computador está em realizar essas instruções muito rapidamente, alguns bilhões delas a cada segundo em um computador pessoal atual (alguns quintilhões por segundo no [supercomputador mais rápido do mundo](https://www.top500.org)).

Algumas instruções necessitam mais informação para sua execução, por exemplo, em que endereços de memória estão os valores a somar, ou onde colocar o resultado de uma operação.
Essas informações fazem parte da instrução e são colocadas em memória, logo após o código da instrução.

Por exemplo, suponha que o nosso processador saiba realizar as instruções abaixo. Nessa tabela, a notação `[E]` representa o dado que está no endereço `E` da memória; `[[E]]` é o dado que está no endereço correspondente ao dado que está no endereço `E` da memória; `PC` é o valor do contador de programa; `PC+1` é um a mais que o valor do contador de programa.

código | o que faz                           | ações a executar
-----: | :---------------------------------- | :-----------------------------------------------
1      | escreve em um dispositivo de saída  | envie o dado em `[[PC+1]]` para o dispositivo identificado por `[PC+2]`; some 3 em `PC`
2      | lê de um dispositivo de entrada     | leia um dado do dispositivo identificado por `[PC+1]`; coloque esse dado em `[[PC+2]]`; some 3 em `PC`
3      | soma dois valores                   | some os valores `[[PC+1]]` e `[[PC+2]]`; coloque o resultado em `[[PC+3]]`; some 4 em `PC`
5      | divide dois valores                 | divida o valor `[[PC+1]]` pelo valor `[[PC+2]]`; coloque o resultado em `[[PC+3]]`; some 4 em `PC`
9      | interrompe a execução               | para o funcionamento da unidade de controle

Suponha ainda que em nosso computador a unidade de E/S `2` corresponde ao teclado e a unidade `3` ao vídeo. 
A memória do computador, a partir do endereço 0 contém os valores abaixo, e a unidade de controle inicia com o valor do `PC` em zero.

.            | .   | .   | .   | .   | .   | .   | .   | .   | .   | .
-----------: | --: | --: | --: | --: | --: | --: | --: | --: | --: | --: 
**endereço** |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9
**valor**    |  2  |  2  | 20  |  2  |  2  | 21  |  3  | 20  | 21  | 22
||||||||||
**endereço** | 10  | 11  | 12  | 13  | 14  | 15  | 16  | 17  | 18  | 19
**valor**    |  5  | 22  | 18  | 23  |  1  | 23  |  3  |  9  |  2  | ?

O funcionamento da unidade de controle nesse caso seria o seguinte:
- (busca) inicialmente, pede para a memória o valor armazenado no endereço em PC. O valor em PC é zero, a memória vai fornecer o valor que está no endereço 0, que é 2.
- (decodificação) a unidade de controle decodifica essa instrução, para descobrir a sequência de passos a executar. O código 2 corresponde à instrução de leitura. A UC passa a executar esses passos.
- (execução)
  - inicialmente, a UC deve conseguir a identificação do dispositivo, que está em PC+1 -- PC vale 0, PC+1 é 1, e a UC pede para a memória o valor contido nesse endereço (obtém 2);
  - então, faz uma operação de leitura de entrada e saída, na unidade 2;
  - a unidade correspondente (o teclado), vai transferir o dado lido do teclado para a UC;
  - a UC deve então obter o valor em PC+2 -- PC vale 0, PC+2 vale 2, a memória entrega o conteúdo no endereço 2, que é 20.
  - a unidade de controle então faz uma operação de escrita na memória, escrevendo o valor lido do teclado na posição 20 da memória;
  - UC atualiza o PC, somando 3: PC vale 0 e é atualizado para 3.

Fim da execução da primeira instrução.

A UC volta a repetir o ciclo, iniciando com a busca no endereço que está no PC.
O código obtido do endereço 3 é novamente 2, a UC vai repetir o que fez antes, com a diferença de que desta vez o valor lido será armazenado no endereço 21 e não 20 como antes. O PC é atualizado para 6.

No endereço 6, a UC encontra a instrução 3, e realiza a soma dos valores que estão nos endereços 20 e 21, e armazena o resultado no endereço 22. E assim por diante, até executar a instrução com código 9, contida no endereço 17, que faz o computador parar.

Fica mais fácil entender essa sequência de números quando eles são separados por instrução:

 endereço | instrução
--------: | ----------
0         | 2 2 20
3         | 2 2 21
6         | 3 20 21 22
10        | 5 22 18 23
14        | 1 23 3
17        | 9
18        | 2

Na posição 18, o valor não é uma instrução, mas um dado, utilizado pela instrução no endereço 10. Essa instrução é uma divisão do valor no endereço 22 pelo valor em 18, colocando o resultado em 23. O programa quer dividir por 2, mas a instrução de divisão só sabe dividir por valores que estão na memória, então quem faz o programa tem que preparar a memória de acordo. 

A colocação de instruções e dados na mesma memória é uma ideia chave da arquitetura de von Neumann, que permite que os programas sejam tão facilmente alterados quanto os dados, e torna essa máquina facilmente configurável para realizar operações diferentes.

Nós humanos temos mais facilidade para lidar com nomes que com números. A sequência acima fica mais fácil de ler trocando os códigos das instruções por palavras simples que nos ajudam a lembrar o que fazem. Essas palavras são chamadas de **mnemônicos**:

 endereço | instrução
--------: | ----------
0         | LE 2 20
3         | LE 2 21
6         | SOMA 20 21 22
10        | DIV 22 18 23
14        | ESCR 23 3
17        | PARA
18        | 2

O endereço onde fica cada instrução em geral não é uma informação importante para se entender o programa. A posição onde cada dado é colocado também não, é muito mais fácil referir-se a esses dados por um nome. O endereço onde fica o valor 2 também não é muito importante para se entender as instruções. Fazendo essas substituições, pode-se escrever essa mesma sequência de uma forma mais fácil de ser lida (para um humano):
```
    LE TECL, N1
    LE TECL, N2
    SOMA N1, N2, S
    DIV S, #2, R
    ESCR R, VIDEO
    PARA
```

Essa última versão é sem dúvida mais fácil de ser escrita e entendida, mais difícil de se cometer erros ao escrevê-la, e não é muito complicado de se fazer a tradução entre esse texto e a sequência de números que representa as mesmas instruções.
Não é muito difícil de se fazer um programa para fazer essa tradução: lê o texto de uma unidade de entrada e coloca a sequência de números equivalentes em algum lugar da memória para depois ser executado, ou escreve essa sequência em um dispositivo de saída, de onde poderá ser lido mais tarde (e executado).

Uma sequência de instruções para um computador executar, como essa, é chamada de **programa**. Quando esse programa é escrito com números, pronto para ser executado pela máquina, diz-se que ele está escrito em **linguagem de máquina**. Quando ele está escrito com mnemônicos e nomes para as posições de memória, diz-se que ele está escrito em **linguagem de montagem** (*assembly language* em inglês). 
Para poder ser executado, um programa escrito em linguagem de montagem deve ser traduzido para o programa equivalente em linguagem de máquina. Esse processo é realizado por um programa, chamado **montador** (*assembler* em inglês).

Apesar de ser bem mais fácil de se programar em linguagem de montagem do que em linguagem de máquina, é um processo bastante tedioso. Outras linguagens foram inventadas, permitindo se expressar os comandos que se quer que um computador execute de uma maneira menos detalhada. Por vezes se chama essas linguagens de 'linguagens de alto nível' ou mais comumente 'linguagens de programação'.
O mesmo programa acima poderia ser escrito assim, por exemplo:
```
  le(n1, n2)
  r = (n1+n2)÷2
  escreve(r)
```

Um programa escrito em uma dessas linguagens, para poder ser executado, deve ser traduzido para um programa equivalente em linguagem de máquina. Esse processo de tradução, mais complicado que a montagem, é chamado de compilação, e é realizado por um programa chamado **compilador**.
Para que a tradução possa ser feita, a linguagem tem que ser suficientemente simples e não ambígua, o que elimina as linguagens naturais. [Uma enorme quantidade](https://en.wikipedia.org/wiki/Timeline_of_programming_languages) de linguagens de programação já foram inventadas.
Nesta disciplina, será utilizada uma dessas linguagens, chamada "[C](https://en.wikipedia.org/wiki/C_(programming_language))".

### Exercício

O programa que vimos acima calcula e imprime a média entre dois números lidos do teclado.
Faça um programa que lê 3 valores do teclado e imprime a média deles.
O programa deve ser escrito em linguagem de montagem e traduzido para linguagem de máquina, usando as definições acima:
- tem que usar as instruções fornecidas, e só elas (de código 1, 2, 3, 5, 9).
- as instruções devem manter o mesmo comportamento definido acima (em especial, a instrução de soma não soma 3 valores, soma 2).

* * *

Esse assunto pode ser visto no capítulo 4 do [livro de algoritmos da UFPR](https://www.inf.ufpr.br/marcos/livro_alg1/livro_alg1.pdf).
Recomendo ler também os capítulos anteriores...

