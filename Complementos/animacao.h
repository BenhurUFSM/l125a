// animacao.h
// --------
// tipos e funções para animação simples
// l125a

#ifndef _animacao_h_  // para evitar problemas com inclusão múltipla deste arquivo
#define _animacao_h_

// tipos de animação:
//   linear: anima linearmente conforme o tempo passa
//   entrada: anima mais rapidamente no início e mais lentamente no final
//   saida: anima mais lentamente no início e mais rapidamente no final
//   entrada_saida: anima lentamente no início e no final, e rapidamente no meio
typedef enum {
  linear,
  entrada,
  saida,
  entrada_saida,
} tipo_animacao;

// tipo de dados para definir uma animação
typedef struct {
  double t_inicio;
  float duracao;
  tipo_animacao tipo;
} animacao_t;

// inicializa uma animação, para animar de acordo com o tipo, durante o tempo
// "duracao", à partir do momento que é chamada
void anim_inicia(animacao_t *anim, float duracao, tipo_animacao tipo);

// retorna quanto tempo falta para a animação terminar
// pode retornar um número negativo, se a animação já terminou
float anim_falta(animacao_t *anim);

// retorna o valor da animação (entre 0 e 1) - 0 é o início, 1 é o fim
// esse valor já é alterado pela tipo de animação escolhido
// retorna 1 se a animação já terminou
float anim_valor(animacao_t *anim);

#endif // _animacao_h_
