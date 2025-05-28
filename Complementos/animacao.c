// animacao.c
// --------
// implementação das funções de animação simples
// l125a

// inclui as definicoes
#include "animacao.h"
#include "janela.h"

// funções de "easing", recebem um número entre 0 e 1 com uma posição linear,
//   retornam um número entre 0 e 1 com um valor alterado para realizar uma
//   transição mais suave (ou menos suave) geralmente entre 0 e 1, mas podendo
//   passar momentaneamente se houver "overshooting"
// usei uma função quadrática; tem várias outras, busque "easing functions"
float anim_linear(float x)
{
  return x;
}
float anim_entrada(float x)
{
  return x * x;
}
float anim_saida(float x)
{
  return 1 - anim_entrada(1 - x);
}
float anim_entrada_saida(float x)
{
  if (x < 0.5) {
    return 2 * x * x;
  } else {
    float y = -2 * x + 2;
    return 1 - y * y / 2;
  }
}

void anim_inicia(animacao_t *anim, float duracao, tipo_animacao tipo)
{
  anim->t_inicio = j_relogio();
  anim->duracao = duracao;
  anim->tipo = tipo;
}
float anim_falta(animacao_t *anim)
{
  float tempo_decorrido = j_relogio() - anim->t_inicio;
  return anim->duracao - tempo_decorrido;
}
float anim_valor(animacao_t *anim)
{
  float tempo_decorrido = j_relogio() - anim->t_inicio;
  float valor_linear = tempo_decorrido / anim->duracao;
  if (valor_linear < 0) valor_linear = 0;
  if (valor_linear > 1) valor_linear = 1;
  float valor_alterado;
  switch (anim->tipo) {
    case linear:        valor_alterado = anim_linear(valor_linear);        break;
    case entrada:       valor_alterado = anim_entrada(valor_linear);       break;
    case saida:         valor_alterado = anim_saida(valor_linear);         break;
    case entrada_saida: valor_alterado = anim_entrada_saida(valor_linear); break;
    default:            valor_alterado = valor_linear;                     break;
  }
  return valor_alterado;
}

