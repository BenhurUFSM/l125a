// Exemplo de uso de video.c (e teclado.c)
//
// Compile com
//   gcc -o exemplo_video exemplo_video.c teclado.c video.c
//
// Fuja do monstro usando as setas.
// Não encoste na cerca.
// Pode desistir com a tecla "End".

#include "video.h"
#include "teclado.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// linha e coluna onde começa a cerca
#define COL0 10
#define LIN0 5
// tamanho do cercadinho
#define LARGURA 20
#define ALTURA 10

int aleat_entre(int a, int b)
{
  return rand() % (b - a) + a;
}

// altera o valor de *pos de acordo com a tecla
void trata_tecla(tecla_t tec, posicao_t *pos)
{
  if (tec == T_CIMA) pos->linha--;
  if (tec == T_BAIXO) pos->linha++;
  if (tec == T_DIREITA) pos->coluna++;
  if (tec == T_ESQUERDA) pos->coluna--;
}

// move monstro em direção ao fujão
void move_monstro(posicao_t *pmonstro, posicao_t fujao)
{
  if (fujao.coluna > pmonstro->coluna) pmonstro->coluna++;
  if (fujao.coluna < pmonstro->coluna) pmonstro->coluna--;
  if (fujao.linha > pmonstro->linha) pmonstro->linha++;
  if (fujao.linha < pmonstro->linha) pmonstro->linha--;
}

void desenha_cerca()
{
  cor_t c_cerca = {aleat_entre(100, 255), 50, 0};

  vid_cor_texto(c_cerca);
  // linha de cima
  posicao_t pos = { LIN0, COL0 };
  vid_pos(pos);
  for (int i = 0; i < LARGURA + 2; i++) vid_impc('+');
  // linhas verticais
  for (int i = 0; i < ALTURA; i++) {
    pos.linha++;
    pos.coluna = COL0;
    vid_pos(pos);
    vid_impc('+');
    pos.coluna += LARGURA + 1;
    vid_pos(pos);
    vid_impc('+');
  }
  // linha de baixo
  pos.linha++;
  pos.coluna = COL0;
  vid_pos(pos);
  for (int i = 0; i < LARGURA + 2; i++) vid_impc('+');
}

// desenha a tela do jogo, com o fugitivo e o monstro
void desenha(posicao_t fujao, posicao_t monstro, int tempo)
{
  cor_t c_fundo = {0, 0, 0};
  cor_t c_jogador = {55, 86, 138};
  cor_t c_monstro = {30, 182, 110};

  // a cerca
  vid_cor_fundo(c_fundo);
  vid_limpa();
  desenha_cerca();
  // o jogador
  vid_pos(fujao);
  vid_cor_texto(c_jogador);
  vid_impc('#');
  // o monstro
  vid_pos(monstro);
  vid_cor_texto(c_monstro);
  vid_impc('@');
  // o tempo
  vid_pos((posicao_t){LIN0+ALTURA+2, COL0+1});
  char s[10];
  sprintf(s, "%d", tempo);
  vid_cor_texto((cor_t){100, 100, 100});
  vid_imps(s);
  // faz aparecer
  vid_atualiza();
}

bool perdeu(posicao_t j, posicao_t m)
{
  // perde se bater no monstro
  if (j.linha == m.linha && j.coluna == m.coluna) return true;
  // perde se encostar na cerca
  if (j.linha <= LIN0 || j.linha > LIN0 + ALTURA) return true;
  if (j.coluna <= COL0 || j.coluna > COL0 + LARGURA) return true;
  // ainda não \o/
  return false;
}

int main()
{
  // posição do fugitivo
  posicao_t jogador = { LIN0 + ALTURA/2, COL0 + LARGURA / 2 };
  // posição do perseguidor
  posicao_t monstro = { LIN0, COL0 };
  // temporizador para o movimento do perseguidor
  int t = 5;
  // contador de tempo de fuga
  int sobrevivencia = 0;
  // inicializa o teclado e o vídeo
  tec_inicia();
  vid_inicia();

  // laço principal
  for (;;) {
    // processa uma tecla
    tecla_t tec = tec_tecla();
    if (tec == T_END) break;
    trata_tecla(tec, &jogador);

    // processa movimentos automáticos (passagem do tempo)
    if (t-- == 0) {
      t = 5;
      move_monstro(&monstro, jogador);
    }

    // desenha a tela
    desenha(jogador, monstro, sobrevivencia);

    // verifica se o jogador perdeu
    if (perdeu(jogador, monstro)) break;

    // ainda não
    sobrevivencia++;
  }
  // volta o terminal para o modo normal
  tec_fim();
  vid_fim();
}
