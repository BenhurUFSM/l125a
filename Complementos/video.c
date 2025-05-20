#include "video.h"
#include "teclado.h"
#include <stdio.h>
#include <stdlib.h>   // para ter 'exit'
#include <string.h>   // para ter 'memcpy'
#include <unistd.h>   // para ter 'write'
#include <time.h>     // para ter 'clock_gettime'

// nanosegundos entre desenhos de tela (50M dá 20 telas por segundo)
#define NS_POR_TELA 50000000

void vid_inicia()
{
  printf("\033[?1049h");   // seleciona a tela alternativa
  printf("\033[?25l");     // esconde o cursor
  printf("\033[2J");       // limpa a tela
  printf("\033[H");        // põe o cursor no topo
  printf("\n");            // avança a linha (e força a saída)
}

void vid_fim()
{
  vid_atualiza();
  printf("\033[?25h");     // mostra o cursor
  printf("\033[?1049l");   // seleciona a tela normal
  printf("\n");            // avança a linha (e força a saída)
}

static void erro_brabo(char *msg)
{
  tec_fim();
  vid_fim();
  printf("Erro brabo: %s\n", msg);
  exit(5);
}

// local onde guardar os bytes antes de enviar para o SO em uma tacada.
// declarados static para não serem visíveis fora deste arquivo.
// variáveis globais, mas confinadas às poucas funções abaixo.
#define NCHARS 10000
static char chars[NCHARS];
static int nchars = 0;

// envia todos os caracteres guardados para o SO
static void vid_flush()
{
  if (nchars == 0) return;
  if (nchars > 10000) erro_brabo("excesso de caracteres no buffer");
  write(1, chars, nchars);
  nchars = 0;
}

// envia todos os caracteres guardados para o SO, na frequencia esperada
void vid_atualiza()
{
  // timespec é um registro para o tempo em alta resolução.
  //   tem dois campos, com os segundos e os nanosegundos do horário
  // pega o horário atual e calcula se já passou tempo suficiente
  //   desde a última vez que atualizou a tela
  static struct timespec ultimo = { 0, 0 };
  struct timespec agora;
  clock_gettime(CLOCK_REALTIME, &agora);
  long diff_s = agora.tv_sec - ultimo.tv_sec;
  if (diff_s >= 0 && diff_s < 2) {
    long diff_ns = diff_s * 1000000000
                 + (agora.tv_nsec - ultimo.tv_nsec);
    if (diff_ns < NS_POR_TELA) {
      // faz muito pouco tempo que atualizou a tela, espera um pouco
      struct timespec espera;
      espera.tv_sec = 0;
      espera.tv_nsec = NS_POR_TELA - diff_ns;
      nanosleep(&espera, NULL);
    }
  }
  ultimo = agora;

  vid_flush();
}

// imprime vários caracteres
void vid_impcs(char *s, int tam)
{
  while (tam > 0) {
    int espaco = NCHARS - nchars;
    if (espaco == 0) {
      vid_flush();
      continue;
    }
    int n = tam;
    if (n > espaco) n = espaco;
    memcpy(chars + nchars, s, n);
    nchars += n;
    s += n;
    tam -= n;
  }
}

// imprime um caractere
void vid_impc(char c)
{
  vid_impcs(&c, 1);
}

// imprime uma string
void vid_imps(char *s)
{
  vid_impcs(s, strlen(s));
}

// limpa a tela
void vid_limpa()
{
  vid_impcs("\033[2J\033[H", 7);
}

// posiciona o cursor
void vid_pos(posicao_t pos)
{
  char s[20];
  sprintf(s, "\033[%d;%dH", pos.linha, pos.coluna);
  vid_imps(s);
}

// seleciona a cor das letras do que for escrito a seguir
void vid_cor_texto(cor_t cor)
{
  char s[20];
  sprintf(s, "\033[38;2;%d;%d;%dm", cor.vermelho, cor.verde, cor.azul);
  vid_imps(s);
}

// seleciona a cor do fundo do que for escrito a seguir
void vid_cor_fundo(cor_t cor)
{
  char s[20];
  sprintf(s, "\033[48;2;%d;%d;%dm", cor.vermelho, cor.verde, cor.azul);
  vid_imps(s);
}
