// teclado.h
// 
// declaração de constantes e funções para acesso ao teclado em modo cru
// para l125a

// proteção contra inclusão dupla (se TECLADO_H já estiver definido, ignora tudo)
#ifndef TECLADO_H
#define TECLADO_H

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
  T_CIMA = 256,
  T_BAIXO,
  T_DIREITA,
  T_ESQUERDA,
  // outrar teclas
  T_ENTER,
  T_PGUP,
  T_PGDN,
  T_HOME,
  T_END,
  T_BS,
  T_BACKSPACE = T_BS,
  T_DEL,
} tecla_t;

// funções

// função que coloca o teclado em modo cru
// deve ser chamada no início do programa
void tec_inicia();

// função que devolve o teclado para o modo normal
// deve ser chamada no final do programa
void tec_fim();

// função que lê a próxima tecla digitada
// retorna T_NADA se não houver tecla digitada
tecla_t tec_tecla();

#endif // TECLADO_H
