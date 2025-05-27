#ifndef _janela_h_  // para evitar problemas com inclusão múltipla deste arquivo
#define _janela_h_

// janela.h
// ------
// funções de acesso à janela gráfica, mouse, relógio
// l125a

#include <stdbool.h>

// frequência de atualização
#define QUADROS_POR_SEGUNDO 30.0
#define SEGUNDOS_POR_QUADRO (1/QUADROS_POR_SEGUNDO)

// TIPOS DE DADOS

// um tamanho na janela, em pixels
typedef struct {
  float largura;
  float altura;
} tamanho_t;

// uma coordenada na janela, em pixels
typedef struct {
  float x;
  float y;
} ponto_t;

// um círculo, com ponto central e raio em pixels
typedef struct {
  ponto_t centro;
  float raio;
} circulo_t;

// um retângulo, com o ponto superior esquerdo e o tamanho, em pixels
typedef struct {
  ponto_t inicio;
  tamanho_t tamanho;
} retangulo_t;

// uma cor, com os componentes entre 0 e 1
typedef struct {
  float vermelho;
  float verde;
  float azul;
  float opacidade;
} cor_t;

// o estado do mouse
typedef struct {
  ponto_t posicao;  // onde está o mouse
  bool apertado[3]; // o estado de cada um dos 3 botões
  bool clicado[3];  // se cada botão foi solto desde a última leitura do estado
  int giro;         // quanto a rodela de rolagem girou desda a última leitura
} rato_t;

// constantes para representar as teclas de controle.
// usa uma enumeração para gerar os valores de teclas que estão sendo traduzidas.
// usa typedef para definir um tipo (tecla_t) que será usado para declarar variáveis que
//   recebem esses valores.
typedef enum {
  // nenhuma tecla foi pressionada
  T_NADA = 0,
  // a tecla esc
  T_ESC = 27,
  // as setas
  T_CIMA = -256,
  T_BAIXO,
  T_DIREITA,
  T_ESQUERDA,
  // outras teclas
  T_ENTER,
  T_PGUP,
  T_PGDN,
  T_HOME,
  T_END,
  T_BS,
  T_BACKSPACE = T_BS,
  T_DEL,
} tecla_t;

// CRIAÇÃO E DESTRUIÇÃO

// inicialização da janela
// cria uma janela com o tamanho dado em pixels
// deve ser executada antes do uso de qualquer outra função da janela
void j_inicializa(tamanho_t tamanho, char nome[]);


// finalização da janela
// deve ser chamada no final da utilização da janela, nenhuma outra função da
// janela deve ser chamada depois desta.
void j_finaliza(void);


// DESENHO

// desenha um círculo
void j_circulo(circulo_t circulo, float largura_linha, cor_t cor_linha, cor_t cor_interna);

// desenha uma linha reta
void j_linha(ponto_t inicio, ponto_t fim, float largura_linha, cor_t cor_linha);

// desenha um retângulo
void j_retangulo(retangulo_t retangulo, float largura_linha,
                 cor_t cor_linha, cor_t cor_interna);


// seleciona a fonte a usar nas próximas funções de texto
// caso o nome seja NULL, usa o fonte padrão (DejaVuSans)
// tamanho é a altura aproximada de uma letra minúscula, em pixels
void j_seleciona_fonte(char *nome, int tamanho);

// desenha texto
// o texto é desenhado na cor escolhida, usando a última fonte selecionada
// posição é o ponto de início do texto, na base do primeiro caractere
void j_texto(ponto_t posicao, cor_t cor, char texto[]);

// retorna o retângulo que contorna o texto
// o tamanho do retângulo corresponde ao tamanho necessário para desenhar o texto,
//   usando a fonte selecionada; a posição do retângulo corresponde ao quanto o texto
//   se desloca em relação ao ponto na base do primeiro caractere (valores negativos).
retangulo_t j_texto_contorno(char texto[]);


// atualiza a janela
// faz com o que foi desenhado na janela desde a última atualização apareça.
// deve ser chamada ao final das funções de desenho
void j_mostra();


// ACESSO AO RATO

// retorna o estado do rato
rato_t j_rato();


// ACESSO AO TECLADO

// retorna true se algo foi digitado e não lido
bool j_tem_tecla();

// retorna uma tecla digitada ou T_NADA se nenhuma tecla for digitada
tecla_t j_tecla();

// retorna o estado das teclas shift e control da última tecla (true se apertadas)
bool j_shift();
bool j_control();

// TEMPO

// retorna quantos segundos transcorreram desde algum momento no passado
double j_relogio();

// fica um tempo sem fazer nada
void j_cochila(double segundos);

#endif // _janela_h_
