// janela.c
// ------
// implementação das funções de acesso à janela gráfica, mouse, relógio
//   usando allegro
// l125a

// inclui as definicoes
#include "janela.h"

// includes normais
#include <stdio.h>
#include <assert.h>

// includes do allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// variáveis globais

static struct {
  // estado do teclado
  bool shift;
  bool control;
  tecla_t tecla_guardada;
  // fila para receber os eventos do teclado
  ALLEGRO_EVENT_QUEUE *eventos_teclado;
  // quando a tela foi atualizada
  double tempo_ultima_atualizacao;
  // uma cache para as fontes
#define N_FONTES 20  // número de fontes a guardar
#define MAX_NOME_FONTE 30 // tamanho máximo que o nome de uma fonte pode ter
  struct {
    int tamanho;
    char nome[MAX_NOME_FONTE+1];
    ALLEGRO_FONT *fonte;
  } fontes[N_FONTES];
  int prox_indice_fonte;
  int indice_fonte_atual;
  // dados para o mouse
  int ultimo_giro;
  bool ultimo_apertado[3];
} glob;

// funções auxiliares

// abandona o programa com erro
static void cai_fora(char *msg)
{
  int cai = 42;
  int fora = 42;
  fprintf(stderr, "\n\nERRO FATAL\n%s\n\n", msg);
  assert(cai-fora);
}

static void j_inicializa_janela(tamanho_t tamanho, char nome[])
{
  // pede para tentar linhas mais suaves (multisampling)
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  // cria uma janela
  ALLEGRO_DISPLAY *janela = al_create_display(tamanho.largura, tamanho.altura);
  if (janela == NULL) {
    cai_fora("problema na criação de janela do allegro");
  }
  // esconde o cursor do mouse
  al_hide_mouse_cursor(janela);
  al_set_window_title(janela, nome);
}

static ALLEGRO_COLOR conv_cor(cor_t cor)
{
  return al_premul_rgba_f(cor.vermelho, cor.verde, cor.azul, cor.opacidade);
}

static void j_inicializa_teclado(void)
{
  if (!al_install_keyboard()) {
    cai_fora("problema na inicialização do teclado do allegro");
  }
  // cria e inicializa a fila de eventos do teclado
  glob.eventos_teclado = al_create_event_queue();
  if (glob.eventos_teclado == NULL) {
    cai_fora("problema na criação da fila de eventos do teclado do allegro");
  }
  al_register_event_source(glob.eventos_teclado,
                           al_get_keyboard_event_source());
}

void j_inicializa(tamanho_t tamanho, char nome[])
{
  // inicializa os subsistemas do allegro
  if (!al_init()) cai_fora("problema na inicialização do allegro");
  if (!al_install_mouse()) cai_fora("problema na inicialização do mouse do allegro");
  if (!al_init_primitives_addon()) cai_fora("problema na inicialização de addons do allegro");
  al_init_font_addon();
  if (!al_init_ttf_addon()) cai_fora("problema na inicialização do addon de fontes ttf");
  j_seleciona_fonte(NULL, 15);

  // inicializa a janela
  j_inicializa_janela(tamanho, nome);
  j_inicializa_teclado();
}


void j_finaliza(void)
{
  // badabum!
  al_uninstall_system();
}

void j_mostra(void)
{
  double agora = j_relogio();
  double quando_mostrar = glob.tempo_ultima_atualizacao + SEGUNDOS_POR_QUADRO;
  double tempo_ate_mostrar = quando_mostrar - agora;
  if (tempo_ate_mostrar > 0) {
    // é muito cedo, dá uma cochilada
    j_cochila(tempo_ate_mostrar);
  }
  // troca a janela mostrada pela que foi desenhada em memória
  al_flip_display();
  glob.tempo_ultima_atualizacao = j_relogio();

  // limpa todo o canvas em memória, para desenhar a próxima janela
  cor_t preto = { 0, 0, 0, 1 };
  al_clear_to_color(conv_cor(preto));
}


void j_circulo(circulo_t circulo, float largura, cor_t cor_linha, cor_t cor_interna)
{
  // preenche
  al_draw_filled_circle(circulo.centro.x, circulo.centro.y, circulo.raio,
                        conv_cor(cor_interna));
  // faz o contorno
  if (largura > 0) {
    al_draw_circle(circulo.centro.x, circulo.centro.y, circulo.raio,
                   conv_cor(cor_linha), largura);
  }
}

void j_linha(ponto_t inicio, ponto_t fim, float largura, cor_t cor_linha)
{
  al_draw_line(inicio.x, inicio.y, fim.x, fim.y, conv_cor(cor_linha), largura);
}

void j_retangulo(retangulo_t retangulo, float largura,
                    cor_t cor_linha, cor_t cor_interna)
{
  int x1 = retangulo.inicio.x;
  int y1 = retangulo.inicio.y;
  int x2 = retangulo.inicio.x + retangulo.tamanho.largura;
  int y2 = retangulo.inicio.y + retangulo.tamanho.altura;
  al_draw_filled_rectangle(x1, y1, x2, y2, conv_cor(cor_interna));
  if (largura > 0) {
    al_draw_rectangle(x1, y1, x2, y2, conv_cor(cor_linha), largura);
  }
}


static ALLEGRO_FONT *fonte_atual()
{
  if (glob.indice_fonte_atual < 0 || glob.indice_fonte_atual >= N_FONTES) {
    cai_fora("sem fonte selecionada.\nfoi chamada j_inicializa?\n");
  }
  return glob.fontes[glob.indice_fonte_atual].fonte;
}

void j_seleciona_fonte(char *nome, int tamanho)
{
  // usa nome default se não informado
  if (nome == NULL) nome = "DejaVuSans.ttf";

  if (strlen(nome) > MAX_NOME_FONTE) {
    cai_fora("nome de fonte muito grande");
  }

  // procura fonte na cache
  for (int i = 0; i < N_FONTES; i++) {
    if (glob.fontes[i].tamanho == tamanho && strcmp(glob.fontes[i].nome, nome) == 0) {
      glob.indice_fonte_atual = i;
      return;
    }
  } 

  // se o vetor de fontes está cheio, livra-se du uma fonte antes de carregar outra
  if (glob.fontes[glob.prox_indice_fonte].fonte != NULL) {
    al_destroy_font(glob.fontes[glob.prox_indice_fonte].fonte);
  }

  // carrega a fonte pedida
  ALLEGRO_FONT *fonte = al_load_font(nome, tamanho, 0);
  if (fonte == NULL) {
    al_uninstall_system();
    fprintf(stderr, "Erro na carga de '%s'\n", nome);
    cai_fora("A carga do arquivo de caracteres não deu certo na função.\n"
             "A função j_inicializa foi chamada?\n"
             "O arquivo existe?\n");
  }
  // coloca a nova fonte no vetor
  glob.fontes[glob.prox_indice_fonte].fonte = fonte;
  strcpy(glob.fontes[glob.prox_indice_fonte].nome, nome);
  glob.fontes[glob.prox_indice_fonte].tamanho = tamanho;
  glob.indice_fonte_atual = glob.prox_indice_fonte;

  glob.prox_indice_fonte++;
  if (glob.prox_indice_fonte >= N_FONTES) {
    glob.prox_indice_fonte = 0;
  }
}

void j_texto(ponto_t posicao, cor_t cor, char texto[])
{
  ALLEGRO_FONT *fonte = fonte_atual();
  posicao.y -= al_get_font_ascent(fonte);
  al_draw_text(fonte, conv_cor(cor), posicao.x, posicao.y, ALLEGRO_ALIGN_LEFT, texto);
}

retangulo_t j_texto_contorno(char texto[])
{
  ALLEGRO_FONT *fonte = fonte_atual();
  retangulo_t ret;
  int rx, ry, rw, rh;
  al_get_text_dimensions(fonte, texto, &rx, &ry, &rw, &rh);
  ret.inicio.x = rx;
  ret.inicio.y = ry - al_get_font_ascent(fonte);
  ret.tamanho.largura = rw;
  ret.tamanho.altura = rh;
  return ret;
}


rato_t j_rato()
{
  ALLEGRO_MOUSE_STATE mouse;
  rato_t rato;
  al_get_mouse_state(&mouse);
  rato.posicao.x = al_get_mouse_state_axis(&mouse, 0);
  rato.posicao.y = al_get_mouse_state_axis(&mouse, 1);

  int giro = al_get_mouse_state_axis(&mouse, 2);
  rato.giro = glob.ultimo_giro - giro;
  glob.ultimo_giro = giro;
  
  for (int b = 0; b < 3; b++) {
    rato.apertado[b] = al_mouse_button_down(&mouse, b + 1);
    rato.clicado[b] = glob.ultimo_apertado[b] && !rato.apertado[b];
    glob.ultimo_apertado[b] = rato.apertado[b];
  }

  return rato;
}

static void ve_se_tem_tecla()
{
  ALLEGRO_EVENT ev;

  while (glob.tecla_guardada == T_NADA && al_get_next_event(glob.eventos_teclado, &ev)) {
    glob.shift = ev.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
    glob.control = ev.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      int k = ev.keyboard.keycode;
      switch (k) {
        case ALLEGRO_KEY_UP:        glob.tecla_guardada = T_CIMA;     break;
        case ALLEGRO_KEY_DOWN:      glob.tecla_guardada = T_BAIXO;    break;
        case ALLEGRO_KEY_RIGHT:     glob.tecla_guardada = T_DIREITA;  break;
        case ALLEGRO_KEY_LEFT:      glob.tecla_guardada = T_ESQUERDA; break;
        case ALLEGRO_KEY_ENTER:     glob.tecla_guardada = T_ENTER;    break;
        case ALLEGRO_KEY_PGUP:      glob.tecla_guardada = T_PGUP;     break;
        case ALLEGRO_KEY_PGDN:      glob.tecla_guardada = T_PGDN;     break;
        case ALLEGRO_KEY_HOME:      glob.tecla_guardada = T_HOME;     break;
        case ALLEGRO_KEY_END:       glob.tecla_guardada = T_END;      break;
        case ALLEGRO_KEY_BACKSPACE: glob.tecla_guardada = T_BS;       break;
        case ALLEGRO_KEY_ESCAPE:    glob.tecla_guardada = T_ESC;      break;
        case ALLEGRO_KEY_DELETE:    glob.tecla_guardada = T_DEL;      break;
        default:
          glob.tecla_guardada = ev.keyboard.unichar;
          break;
      }
    }
  }
}

bool j_shift()
{
  return glob.shift;
}

bool j_control()
{
  return glob.control;
}

bool j_tem_tecla()
{
  ve_se_tem_tecla();
  return glob.tecla_guardada != '\0';
}

tecla_t j_tecla()
{
  int tec = '\0';
  if (j_tem_tecla()) {
    tec = glob.tecla_guardada;
    glob.tecla_guardada = '\0';
  }
  return tec;
}


double j_relogio(void)
{
  return al_get_time();
}

void j_cochila(double segundos)
{
  al_rest(segundos);
}
