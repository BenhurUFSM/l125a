// Programa de exemplo de uso das funções em janela.h e janela.c
//
// Necessita os arquivos exemplo_janela.c (este), janela.h, janela.c e DejaVuSans.ttf
// Necessita ter instalado a biblioteca allegro5
//
// para compilar este programa manualmente em linux:
//   gcc -Wall -o exemplo_janela exemplo_janela.c janela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
// para executar:
//   ./exemplo_janela
//
// para não digitar isso tudo para compilar, tem um arquivo "compila" com os comandos de compilação. Dá para executar com:
//   source compila

#include "janela.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// cria algumas cores globais
cor_t transparente = { 0.0, 0.0, 0.0, 0.0 };
cor_t branco       = { 1.0, 1.0, 1.0, 1.0 };
cor_t vermelho     = { 1.0, 0.0, 0.0, 1.0 };
cor_t amarelo      = { 0.1, 0.6, 0.6, 1.0 };
cor_t fucsia       = { 1.0, 0.2, 0.8, 1.0 };

// funções auxiliares

static int aleatorio_entre(int minimo, int maximo)
{
  return minimo + rand() % (maximo - minimo); 
}

// retorna a parte fracionária do valor recebido
static float frac(float v)
{
  int v_int = v;
  return v - v_int;
}

static ponto_t posicao_aleatoria()
{
  ponto_t pos;
  pos.x = aleatorio_entre(50, 450);
  pos.y = aleatorio_entre(50, 450);
  return pos;
}

// o estado do jogo
typedef struct {
  // constantes, devem ser inicializadas antes da janela
  tamanho_t tamanho_janela;
  retangulo_t contorno_janela;
  // necessários no início de cada partida
  char tecla;
  int pontos;
  float pontos_do_tiro;
  ponto_t pos_raio;
  double data_inicio;
  bool terminou;
  // não precisam de estado inicial
  ponto_t pos_alvo;
  double tempo_de_jogo;
  enum { sem_raio, rainho, raiao } tipo_de_raio;
  rato_t rato;
  cor_t cor_contorno;
} jogo_t;

// inicializa estado do jogo
void inicializa_jogo(jogo_t *pj)
{
  pj->tecla = 'x';
  pj->pontos = 0;
  pj->pontos_do_tiro = 10;
  pj->pos_alvo = posicao_aleatoria();
  pj->data_inicio = j_relogio();
  pj->terminou = false;
}

// funções que processam entradas
void processa_tempo(jogo_t *pj)
{
  // termina depois de alguns segundos
  pj->tempo_de_jogo = j_relogio() - pj->data_inicio;
  if (pj->tempo_de_jogo >= 30) pj->terminou = true;
}

void processa_teclado(jogo_t *pj)
{
  // altera tecla caso tenha sido digitado algo
  if (j_tem_tecla()) pj->tecla = j_tecla();

  pj->cor_contorno = fucsia;
  if (j_shift()) pj->cor_contorno.verde = 0.8;
  if (j_control()) pj->cor_contorno.azul = 0.4;
}

// vê se a linha a--b passa perto de c
static bool passa_perto(ponto_t a, ponto_t b, ponto_t c)
{
  ponto_t d; // vai conter o ponto na linha a--b mais próximo de c
  // calcula o quadrado da distância a--b em d_ab_2
  float dx_ab = b.x - a.x;
  float dy_ab = b.y - a.y;
  float d_ab_2 = dx_ab * dx_ab + dy_ab * dy_ab;
  if (d_ab_2 < 1) {
    // pontos a e b tão bem pertos, escolhe a para ser o ponto mais perto de c
    d = a;
  } else {
    // calcula o produto escalar entre os vetores ab e ac
    // o produto escalar entre os vetores ab e ac dá
    //   d_ab d_ac cos alfa, d_ab é o comprimento de ab, alfa o âng entre ab e ac 
    // dividindo por d_ab, dá "d_ac cos alfa", que é a projeção de ac sobre ab
    // dividindo por d_ab de novo dá essa projeção entre 0 e 1, um "percentual"
    // da distância entre a e b onde está a projeção de c
    float dx_ac = c.x - a.x;
    float dy_ac = c.y - a.y;
    float esc = dx_ac * dx_ab + dy_ac * dy_ab; // prod. escalar  ab . ac
    float t = esc / d_ab_2; // projeção de ac sobre ab dividido por dist a--b
    // t diz onde está o ponto mais próximo: <0: antes de a; >1: depois de b;
    //   entre 0 e 1: entre a e b
    if (t <= 0) d = a;
    else if (t >= 1) d = b;
    else {
      d.x = a.x + t * dx_ab;
      d.y = a.y + t * dy_ab;
    }
  }
  // calcula o quadrado da distância c--d
  float dx_cd = d.x - c.x;
  float dy_cd = d.y - c.y;
  float d_cd_2 = dx_cd * dx_cd + dy_cd * dy_cd;
  // se a distância for pequena, passa perto
  //   se o quadrado da distância for menor que 2, a distância é menor que 1.5 pixel
  return d_cd_2 < 2;
}

void processa_mouse(jogo_t *pj)
{
  // obtem estado do rato
  pj->rato = j_rato();
  pj->pos_raio.y = pj->contorno_janela.inicio.y;
  pj->pos_raio.x = pj->tamanho_janela.largura - pj->rato.posicao.x;
  if (pj->rato.clicado[0]) {
    pj->tipo_de_raio = raiao;
    if (passa_perto(pj->pos_raio, pj->rato.posicao, pj->pos_alvo)) {
      // acertou! calcula quantidade de pontos e muda alvo de lugar
      pj->pontos += pj->pontos_do_tiro;
      pj->pontos_do_tiro = 10;
      pj->pos_alvo = posicao_aleatoria();
    }
  } else if (pj->rato.apertado[0]) {
    pj->tipo_de_raio = rainho;
    if (pj->pontos_do_tiro > 1.1) pj->pontos_do_tiro -= 0.05;
  } else {
    pj->tipo_de_raio = sem_raio;
  }
}

// desenha 'texto', centrado em 'centro', com um retângulo contornando
void texto_centrado_contornado(ponto_t centro, char *texto, cor_t c_texto, cor_t c_contorno)
{
  // calcula o retângulo que seria ocupado pelo alvo
  retangulo_t dim_txt = j_texto_contorno(texto);
  // ajusta a posição do texto (e o retângulo) para ficar no centro do alvo
  ponto_t pos_txt = centro;
  pos_txt.x = centro.x - dim_txt.tamanho.largura / 2;
  pos_txt.y = centro.y + 5;
  retangulo_t ret_txt;
  ret_txt.inicio.x = centro.x + dim_txt.inicio.x - dim_txt.tamanho.largura / 2;
  ret_txt.inicio.y = centro.y + dim_txt.inicio.y + 5;
  ret_txt.tamanho = dim_txt.tamanho;
  // desenha o texto dentro do retângulo
  j_retangulo(ret_txt, 1, c_contorno, transparente);
  j_texto(pos_txt, c_texto, texto);

}

void desenha_tela(jogo_t *pj)
{
  // desenha um contorno
  j_retangulo(pj->contorno_janela, 5, pj->cor_contorno, transparente);

  // desenha um cursor na posição do mouse
  circulo_t cursor = { pj->rato.posicao, 5 };
  cor_t cor_cursor = {  // uma cor sealterante
    frac(pj->tempo_de_jogo * 5),
    frac(pj->tempo_de_jogo * 3),
    frac(pj->tempo_de_jogo),
    1
  };
  j_circulo(cursor, 3, cor_cursor, branco);

  // desenha um raio se for o caso
  switch (pj->tipo_de_raio) {
    case sem_raio:
      break;
    case rainho:
      j_linha(pj->pos_raio, pj->rato.posicao, 1, branco);
      break;
    case raiao:
      j_linha(pj->pos_raio, pj->rato.posicao, 5, vermelho);
      break;
  }

  // desenha o alvo
  // o alvo é uma string com 3 vezes a última tecla teclada
  char txt[100];
  sprintf(txt, "%c%c%c", pj->tecla, pj->tecla, pj->tecla);
  j_seleciona_fonte(NULL, 20);
  texto_centrado_contornado(pj->pos_alvo, txt, amarelo, vermelho);

  // desenha linhas cruzando o alvo
  ponto_t l1p1 = { 0, pj->pos_alvo.y };
  ponto_t l1p2 = { 499, pj->pos_alvo.y };
  ponto_t l2p1 = { pj->pos_alvo.x, 0 };
  ponto_t l2p2 = { pj->pos_alvo.x, 499 };
  j_linha(l1p1, l1p2, 1, fucsia);
  j_linha(l2p1, l2p2, 1, fucsia);
  // desenha os pontos
  sprintf(txt, "%d  %d  %.0f", pj->pontos, (int)pj->pontos_do_tiro, pj->tempo_de_jogo);
  ponto_t pos_pontos = { 50, 488 };
  j_texto(pos_pontos, branco, txt);

  // faz aparecer na janela o que foi desenhado
  j_mostra();
}

void desenha_tela_final(jogo_t *j)
{
  char txt[100];
  sprintf(txt, "pts: %d", j->pontos);
  ponto_t pos_pontos, pos_enter;
  double tempo_pos = 0;
  do {
    if (j_relogio() - tempo_pos > 1) {
      pos_pontos = posicao_aleatoria();
      pos_enter = posicao_aleatoria();
      tempo_pos = j_relogio();
    }
    j_seleciona_fonte(NULL, 40);
    j_texto(pos_pontos, branco, txt);
    j_seleciona_fonte(NULL, 15);
    j_texto(pos_enter, amarelo, "tecle «enter»");
    j_mostra();
  } while (j_tecla() != T_ENTER);
}

// A função principal
int main(void)
{
  // inicializa gerador de números aleatórios
  srand(time(NULL));

  // cria e inicializa o descritor do jogo
  jogo_t jogo;

  jogo.tamanho_janela = (tamanho_t){ 500, 500 };
  jogo.contorno_janela = (retangulo_t){{ 30, 30 }, { 440, 440 }};

  // inicializa a janela gráfica
  j_inicializa(jogo.tamanho_janela, "exemplo");

  inicializa_jogo(&jogo);

  // laço principal
  while (!jogo.terminou) {
    processa_tempo(&jogo);
    processa_teclado(&jogo);
    processa_mouse(&jogo);
    desenha_tela(&jogo);
  }

  desenha_tela_final(&jogo);

  // encerra a janela gráfica
  j_finaliza();
}
