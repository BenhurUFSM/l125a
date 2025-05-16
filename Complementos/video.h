#ifndef VIDEO_H
#define VIDEO_H

typedef struct {
  unsigned char vermelho;
  unsigned char verde;
  unsigned char azul;
} cor_t;

typedef struct {
  int linha;
  int coluna;
} posicao_t;

// função que inicializa o vídeo
// deve ser chamada no início do programa
void vid_inicia();

// função que devolve o vídeo para o modo normal
// deve ser chamada no final do programa
void vid_fim();

// envia todos os caracteres guardados para o SO
// deve ser chamada quando tiver terminado de desenhar a tela
void vid_atualiza();

// imprime vários caracteres
void vid_impcs(char *s, int tam);

// imprime um caractere
void vid_impc(char c);

// imprime uma string
void vid_imps(char *s);

// limpa a tela
void vid_limpa();

// posiciona o cursor
void vid_pos(posicao_t pos);

// seleciona a cor das letras do que for escrito a seguir
void vid_cor_texto(cor_t cor);

// seleciona a cor do fundo do que for escrito a seguir
void vid_cor_fundo(cor_t cor);

#endif  // VIDEO_H
