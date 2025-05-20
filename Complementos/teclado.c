// teclado.c
// 
// implementação de funções para acesso ao teclado em modo cru
// para l125a

#include "teclado.h"
#include <stdlib.h>     // para ter 'system'
#include <unistd.h>     // para ter 'read'

// função que coloca o teclado em modo cru
// deve ser chamada no início do programa
void tec_inicia()
{
  // executa o programa stty para configurar o terminal
  //   raw - não processa os caracteres de entrada (nem de saída); o programa recebe todos
  //   -echo - não imprime os caracteres digitados
  //   min 0 - permite que a leitura possa ler 0 caracteres (não bloqueia o programa)
  //   time 1 - espera até 1 décimo de segundo antes de desbloquear o programa caso nada
  //            seja digitado. colocando 0 o programa não bloqueia.
  system("stty raw -echo min 0 time 0");
}

// função que devolve o teclado para o modo normal
// deve ser chamada no final do programa
void tec_fim()
{
  // chama o programa stty para configurar o terminal para um estado saudável
  system("stty sane");
}

// função que lê a próxima tecla digitada
// retorna T_NADA se não houver tecla digitada

// funções auxiliares
// (internas, declaradas `static` para não serem visíveis fora deste arquivo)

// retorna o próximo char do teclado ou '\0'
// usa a função de baixo nível "read" para ler até 1 caractere da entrada 0 (entrada padrão)
// a função read retorna o número de caracteres lidos (pode ser 0) ou um número negativo
//   para indicar algum erro.
static char le_1()
{
  char c;
  if (read(0, &c, 1) != 1) return '\0';
  return c;
}

// a primeira tecla foi esc, traduz a sequência
static tecla_t tec_esc()
{
  char t2 = le_1();
  // só estão sendo tratadas algumas das sequências esc-[
  // as teclas F1-F4, por exemplo, usam outro prefixo
  // quando tem modificadores como shift ou control, é mais complicado e não está
  //   sendo tratado.
  if (t2 != '[') return T_ESC;
  char t3 = le_1();
  if (t3 == 'A') return T_CIMA;
  if (t3 == 'B') return T_BAIXO;
  if (t3 == 'C') return T_DIREITA;
  if (t3 == 'D') return T_ESQUERDA;
  if (t3 == 'F') return T_END;
  if (t3 == 'H') return T_HOME;

  // pgup e pgdn enviam 4 códigos!  (<esc><[><5><~> para pgup, por exemplo)
  char t4 = le_1();
  if (t4 != '~') return T_ESC;
  if (t3 == '5') return T_PGUP;
  if (t3 == '6') return T_PGDN;

  // tem várias outras possibilidades, mas essas são suf, pelo menos por enquanto
  return T_ESC;
}

// a forma como as teclas são enviadas para um programa é arcaica e horrível.
// as teclas simples (ASCII) enviam o código ASCII
// as teclas de controle mais comuns como enter ou backspace enviam um código de 1 byte,
//   em geral um código de controle padronizado ASCII
// as demais teclas enviam uma sequência de códigos, iniciada pelo caractere ESC (código 27)
//   esta função traduz alguns (bem poucos) desses códigos para valores T_* definidos
//   em teclado.h
tecla_t tec_tecla()
{
  tecla_t tec = le_1();
  if (tec == 127) tec = T_BS;
  else if (tec == '\r') tec = T_ENTER;
  else if (tec == T_ESC) {
    tec = tec_esc();
  }
  return tec;
}
