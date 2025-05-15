// Exemplo de uso de teclado.c
//
// Compile com
//   gcc -o exemplo_teclado exemplo_teclado.c teclado.c
//
// Fuja do monstro usando as setas.
// Não encoste na cerca.
// Pode desistir com a tecla "End".

#include "teclado.h"
#include <stdio.h>

// altera o valor de [*px, *py] de acordo com a tecla
void trata_tecla(tecla_t tec, int *px, int *py)
{
  if (tec == T_CIMA) (*py)--;
  if (tec == T_BAIXO) (*py)++;
  if (tec == T_DIREITA) (*px)++;
  if (tec == T_ESQUERDA) (*px)--;
}

// move [*px, *py] em direção à [x, y]
void move_monstro(int *px, int *py, int x, int y)
{
  if (x > *px) (*px)++;
  if (x < *px) (*px)--;
  if (y > *py) (*py)++;
  if (y < *py) (*py)--;
}

// desenha a tela do jogo, com o fugitivo em [x,y] e o monstro em [xm,ym]
void desenha(int x, int y, int xm, int ym)
{
  for (int i = -3; i < 13; i++) {
    for (int j = -6; j < 28; j++) {
      if (i == ym && j == xm) putchar('@');
      else if (i == y && j == x) putchar('#');
      else if (i == 0 || i == 11) putchar ('+');
      else if (j == 0 || j == 21) putchar ('+');
      else putchar(' ');
    }
    putchar('\n');
    putchar('\r'); // em modo cru, tem que imprimir \n\r para o fim de linha
  }
}

int main()
{
  // posição do fugitivo
  int x = 10;
  int y = 5;
  // posição do perseguidor
  int xm = 1;
  int ym = 1;
  // temporizador para o movimento do perseguidor
  int t = 5;
  // contador de tempo de fuga
  int sobrevivencia = 0;
  // coloca o terminal em modo cru, para poder ler o teclado sem esperar <enter>
  tec_inicia();

  for (;;) {
    // processa uma tecla
    tecla_t tec = tec_tecla();
    if (tec == T_END) break;
    trata_tecla(tec, &x, &y);

    // processa movimentos automáticos (passagem do tempo)
    if (t-- == 0) {
      t = 5;
      move_monstro(&xm, &ym, x, y);
    }

    // desenha a tela
    desenha(x, y, xm, ym);
    printf(" %d\r\n", sobrevivencia);

    // verifica se o jogador perdeu
    if (x == xm && y == ym) break;
    if (x < 1 || x > 20 || y < 1 || y > 10) break;

    sobrevivencia++;
  }
  // volta o terminal para o modo normal
  tec_fim();
}
