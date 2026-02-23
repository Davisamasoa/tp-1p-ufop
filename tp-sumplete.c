// Nome: Davi Samuel Machado Soares
// Matrícula: 25.2.4160

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)
   
typedef struct{
    int numero;
    int numero_mask;
    int cor;
} Tabela;
int ** criaMatriz(int m, int n);
void liberaMatriz(int ** matriz, int l);
void mostrarTabuleiro(int l, int c);
void processarComandoDigitado();
void novoJogo(char nome[30], char * dificuldade, int ** matrizJogo, int ** matrizMask);
void sair();
void carregarJogo();
void salvarJogo();
void mostrarRanking();
void adicionarPosicao();
void removerPosicao();
void mostrarDica();
void resolverJogo();
void mostrarComandos();
void processarComando();

int main(){
    int **matrizJogo;
    int **matrizMask;
    char dificuldade;
    char nome[30];

    // printf("\nBem vindo ao Jogo SUMPLETE!\n\n");
    // mostrarTabuleiro(3, 3);

    novoJogo(nome, &dificuldade, matrizJogo, matrizMask);
    printf("%s, %c\n", nome, dificuldade);
    return 0;
}

void novoJogo(char nome[30], char * dificuldade, int ** matrizJogo, int ** matrizMask){
    printf("\nDigite o nome do jogador: ");
    scanf("%s", nome);
    printf("\nDigite a dificuldade desejada: (F: 3x3, M: 5x5, D: 7x7) ");
    scanf(" %c", dificuldade);
}

int ** criaMatriz(int l, int c){
    // função que cria e aloca a matriz dinamicamente
    int **matriz;
    matriz = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++){
        matriz[i] = (int *)malloc(c * sizeof(int));
    }
    return matriz;
}

void liberaMatriz(int ** matriz, int l){
    for (int i = 0; i < l; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void mostrarComandos(){
    // comandos do jogo
    printf("\nComandos do jogo");
    printf(BOLD("\najuda:"));
    printf(BOLD("\nsair:"));
    printf(BOLD("\nnovo:"));
    printf(BOLD("\ncarregar:"));
    printf(BOLD("\nranking:"));
    printf(BOLD("\nsalvar:"));
    printf(BOLD("\ndica:"));
    printf(BOLD("\nresolver:"));
    printf(BOLD("\nadicionar:"));
    printf(BOLD("\nremover:\n"));
}

void processarComando(){
    // recebe e armazena o comando digitado
    char comandoDigitado[20];
    printf("\nDigite um dos comandos mostrados acima: (digite tudo em minúsculo)");
    scanf("%s", comandoDigitado);

    // verifica qual comando foi digitado e executa a função correspondente
    if(!strcmp(comandoDigitado, "ajuda"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "sair"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "novo"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "carregar"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "ranking"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "salvar"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "dica"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "resolver"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "adicionar"))
       mostrarComandos();
    else if(!strcmp(comandoDigitado, "remover"))
       mostrarComandos();
}

void processarComandoDigitado(){
    char comandoDigitado[20];
    printf("\nDigite um comando: ");
    scanf("%s", comandoDigitado);
}

void mostrarTabuleiro(int l, int c){
    for (int i = 0; i < l + 2; i++){
        for (int j = 0; j < c + 2; j++){
            // se a linha for par
            if (i % 2 == 0){
                // se for a primeira coluna
                if(j == 0 && i <= l && i > 0){
                    printf(BG_YELLOW(BOLD(" %d")), i);;
                }
                // se não for a primeira coluna
                else{
                    //se a coluna for par
                    if(j % 2 == 0){
                        // se for a primeira linha
                        if(i == 0 && j <= c && j > 0){
                            printf(BG_YELLOW(BOLD(" %d")), j);
                        }
                        // se não for a primeira linha - numero do jogo aqui
                        else
                            printf(BG_YELLOW("  "));
                    }
                    // se a coluna for ímpar
                    else{
                        if(i == 0 && j <= c && j > 0){
                            printf(YELLOW(" %d"), j);
                        }
                        else
                         printf("  ");
                    }
                }
            } 
            // se a linha for ímpar
            else{
                // se for a primeira coluna
                if (j == 0 && i <= l && i > 0)
                {
                    printf(YELLOW(BOLD(" %d")), i);
                }
                // se não for a primeira coluna
                else{
                    // se a coluna for ímpar
                    if(j % 2 != 0){
                            printf(BG_YELLOW("  "));
                    }
                    // se a coluna for par
                    else{
                        printf("  ");
                    }    
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}