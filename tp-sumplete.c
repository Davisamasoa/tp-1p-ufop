// Nome: Davi Samuel Machado Soares
// Matrícula: 25.2.4160

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
int ** criaMatriz(int d, int mask);
void liberaMatriz(int ** matrizJogo, int ** matrizMask, int d);
void mostrarTabuleiro(int d);
void novoJogo(char nome[30], int *dimensao, int ***matrizJogo, int ***matrizMask);
void sair();
void carregarJogo();
void salvarJogo();
void mostrarRanking();
void adicionarPosicao();
void removerPosicao();
void mostrarDica();
void resolverJogo();
void mostrarComandos(int temJogoAtivo);
void rodarJogo(char nome[30], int * dimensao, int *** matrizJogo, int *** matrizMask, int temJogoAtivo);
int gerarNumeroAleatorio(int min, int max);

int main(){
    srand(time(NULL));
    int **matrizJogo = NULL;
    int **matrizMask = NULL;
    int dimensao = 0;
    char nome[30];

    printf(BG_WHITE("\nBem vindo ao Jogo SUMPLETE!\n"));
    

    rodarJogo(nome, &dimensao, &matrizJogo, &matrizMask, 0);
    liberaMatriz(matrizJogo, matrizMask, dimensao);
    return 0;
}

void novoJogo(char nome[30], int *dimensao, int ***matrizJogo, int ***matrizMask){
    // Inicializa o gerador com o tempo atual
    char dificuldade;
    printf("\nDigite o nome do jogador: ");
    scanf("%s", nome);
    printf("\nDigite a dificuldade desejada: (F: 3x3, M: 5x5, D: 7x7) ");
    scanf(" %c", &dificuldade);
    if(dificuldade == 'f'|| dificuldade == 'F'){
        *dimensao = 3;
        *matrizJogo = criaMatriz(3, 0);
        *matrizMask = criaMatriz(3, 1);
    }
    else if(dificuldade == 'm'|| dificuldade == 'M'){
        *dimensao = 5;
        *matrizJogo = criaMatriz(5, 0);
        *matrizMask = criaMatriz(5, 1);
    }
    else if(dificuldade == 'd'|| dificuldade == 'D'){
        *dimensao = 7;
        *matrizJogo = criaMatriz(7, 0);
        *matrizMask = criaMatriz(7, 1);
    }
    else{
        printf("\nErro: entrada inválida\nTente novamente");
    }

}
int gerarNumeroAleatorio(int min, int max){
    // Gera um número entre 1 e 9
    int numAleatorio = (rand() % (max - min + 1)) + min;

    return numAleatorio;
}

int ** criaMatriz(int d, int mask){
    // função que cria e aloca a matriz dinamicamente
    int **matriz;
    matriz = (int **)malloc(d * sizeof(int *));
    for (int i = 0; i < d; i++){
        matriz[i] = (int *)malloc(d * sizeof(int));
    }

    if(mask){
        for (int i = 1; i < d - 1; i++){
            for (int j = 1; j < d - 1; j++){
                matriz[i][j] = gerarNumeroAleatorio(0, 1);
            }
        }
    }
    else{
        for (int i = 1; i < d - 1; i++){
            for (int j = 1; j < d - 1; j++){
                matriz[i][j] = gerarNumeroAleatorio(1, 9);
            }
        }
    }


        return matriz;
}

void liberaMatriz(int ** matrizJogo, int ** matrizMask, int d){
    if (matrizJogo != NULL) {
        for (int i = 0; i < d; i++){
            free(matrizJogo[i]);
        }
        free(matrizJogo);
    }

    if (matrizMask != NULL) {
        for (int i = 0; i < d; i++){
            free(matrizMask[i]);
        }
        free(matrizMask);
    }
}

void mostrarComandos(int temJogoAtivo){
    // comandos do jogo
    printf(BOLD()"\nComandos do jogo\n");
    printf(BOLD("\najuda: ")"Exibe os comandos do jogo");
    printf(BOLD("\nsair: ")"Sair do Jogo");
    printf(BOLD("\nnovo: ")"Começar um novo jogo");
    printf(BOLD("\ncarregar: ")" Carregar um jogo salvo em arquivo");
    printf(BOLD("\nranking: ")"Exibir o ranking");
    if(temJogoAtivo){
        printf(BOLD("\nsalvar: ")"Salva o jogo atual");
        printf(BOLD("\ndica: ")"Marca uma posição no jogo");
        printf(BOLD("\nresolver: ")"Resolve o jogo atual");
        printf(BOLD("\nadicionar: ")" <lin> <col>: marca a posição <lin> <col> para entrar na soma");
        printf(BOLD("\nremover: ")"<lin> <col>: remove a posição da soma");
    }
}

void rodarJogo(char nome[30], int * dimensao, int *** matrizJogo, int *** matrizMask, int temJogoAtivo){
    int continuarJogando = 0;
    do{
        // recebe e armazena o comando digitado
        char comandoDigitado[20];
        printf(BOLD("\n\nDigite um comando: (digite \"ajuda\" para listar os comandos) "));
        scanf("%s", comandoDigitado);
    
        // verifica qual comando foi digitado e executa a função correspondente
        if(!strcmp(comandoDigitado, "ajuda")){
            mostrarComandos(temJogoAtivo);
            continuarJogando = 1;
        }
        else if (!strcmp(comandoDigitado, "sair")){
            sair();
            break;
        }
        else if (!strcmp(comandoDigitado, "novo")){
            novoJogo(nome, dimensao, matrizJogo, matrizMask);
            continuarJogando = 1;
            temJogoAtivo = 1;
        }
        else if (!strcmp(comandoDigitado, "carregar"))
            carregarJogo();
        else if(!strcmp(comandoDigitado, "ranking"))
            mostrarRanking();
        else if(temJogoAtivo){
            if (!strcmp(comandoDigitado, "salvar"))
                salvarJogo();
            else if(!strcmp(comandoDigitado, "dica"))
               mostrarDica();
            else if(!strcmp(comandoDigitado, "resolver"))
               resolverJogo();
            else if(!strcmp(comandoDigitado, "adicionar"))
               adicionarPosicao();
            else if(!strcmp(comandoDigitado, "remover"))
               removerPosicao();
            else{
            printf("\nComando inválido! digite novamente");
            continuarJogando = 1;
            }
        } else{
            printf("\nComando inválido! digite novamente");
            continuarJogando = 1;
        }
        printf("%d", *dimensao);
        mostrarTabuleiro(*dimensao);

    } while (continuarJogando);
}

void mostrarTabuleiro(int d){
    printf("\n\n");
    for (int i = 0; i < d + 2; i++)
    {
        for (int j = 0; j < d + 2; j++){
            // se a linha for par
            if (i % 2 == 0){
                // se for a primeira coluna
                if(j == 0 && i <= d && i > 0){
                    printf(BG_YELLOW(BOLD(" %d")), i);;
                }
                // se não for a primeira coluna
                else{
                    //se a coluna for par
                    if(j % 2 == 0){
                        // se for a primeira linha
                        if(i == 0 && j <= d && j > 0){
                            printf(BG_YELLOW(BOLD(" %d")), j);
                        }
                        // se não for a primeira linha - numero do jogo aqui
                        else
                            printf(BG_YELLOW("  "));
                    }
                    // se a coluna for ímpar
                    else{
                        if(i == 0 && j <= d && j > 0){
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
                if (j == 0 && i <= d && i > 0)
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

void sair(){}
void carregarJogo(){}
void salvarJogo(){}
void mostrarRanking(){}
void adicionarPosicao(){}
void removerPosicao(){}
void mostrarDica(){}
void resolverJogo(){}