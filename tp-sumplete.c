// nome: Davi Samuel Machado Soares
// matricula: 25.2.4160

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_GRAY       "\x1b[90m"
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
#define GRAY(string)       ANSI_COLOR_GRAY       string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" 
#define TAB_VER "\u2503" 
#define TAB_TL  "\u250F" 
#define TAB_ML  "\u2523" 
#define TAB_BL  "\u2517" 
#define TAB_TJ  "\u2533" 
#define TAB_MJ  "\u254B" 
#define TAB_BJ  "\u253B" 
#define TAB_TR  "\u2513" 
#define TAB_MR  "\u252B" 
#define TAB_BR  "\u251B" 
   
typedef struct{
    int numero;
    int numero_mask;
    int cor;
} Tabela;

typedef struct {
    char nome[30];
    int tempo;
} Jogador;

// prototipos das funcoes
Tabela ** criaMatriz(int d);
void liberaMatriz(Tabela ** matriz, int d);
void mostrarTabuleiro(int d, Tabela ** matriz);
void novoJogo(char nome[30], int *dimensao, Tabela ***matriz);
void sair();
void mostrarRanking();
int adicionarRanking(char *nomeJogador, int tempoGasto);
void adicionarPosicao(int d, Tabela ** matriz);
void removerPosicao(int d, Tabela ** matriz);
void mostrarDica(Tabela **matriz, int dimensao);
void mostrarComandos(int temJogoAtivo);
void rodarJogo(char nome[30], int * dimensao, Tabela *** matriz);
int gerarNumeroAleatorio(int min, int max);
int calcularSomaLinhaAlvo(int d, Tabela **matriz, int linha);
int calcularSomaColunaAlvo(int d, Tabela **matriz, int coluna);
int calcularSomaLinhaAtual(int d, Tabela **matriz, int linha);
int calcularSomaColunaAtual(int d, Tabela **matriz, int coluna);
int verificarVitoria(int d, Tabela **matriz);

// Prototipos atualizados para as novas funcoes com nomeBase
void carregarJogo(Tabela ***matriz, int *dimensao, char *nome, struct timeval *inicio, int *temJogoAtivo, char *nomeBase);
void salvarJogo(Tabela **matriz, int dimensao, char *nome, struct timeval inicio, char *nomeBase);
void resolverJogo(int dimensao, Tabela **matriz);

int main(){
    srand(time(NULL));
    Tabela **matriz = NULL;
    int dimensao = 0;
    char nome[30] = "";

    printf(BG_WHITE("\nBem vindo ao Jogo SUMPLETE!\n"));
    
    // passamos o endereco da matriz
    rodarJogo(nome, &dimensao, &matriz);
    
    liberaMatriz(matriz, dimensao);
    return 0;
}

int gerarNumeroAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

Tabela ** criaMatriz(int d){
    // aloca a matriz de structs
    Tabela **matriz = (Tabela **)malloc(d * sizeof(Tabela *));
    for (int i = 0; i < d; i++){
        matriz[i] = (Tabela *)malloc(d * sizeof(Tabela));
    }

    // preenche todas as propriedades de uma vez
    for (int i = 0; i < d; i++){        
        for (int j = 0; j < d; j++){    
            matriz[i][j].numero = gerarNumeroAleatorio(1, 9);
            matriz[i][j].numero_mask = gerarNumeroAleatorio(0, 1);
            matriz[i][j].cor = 0; // 0 padrao 1 adicionado 2 removido
        }
    }
    return matriz;
}

void liberaMatriz(Tabela ** matriz, int d){
    if (matriz != NULL) {
        for (int i = 0; i < d; i++){
            free(matriz[i]);
        }
        free(matriz);
    }
}

void novoJogo(char nome[30], int *dimensao, Tabela ***matriz){
    char dificuldade;
    printf("\nDigite o nome do jogador: ");
    scanf("%s", nome);
    printf("\nDigite a dificuldade desejada: (F: 3x3, M: 5x5, D: 7x7) ");
    scanf(" %c", &dificuldade);
    
    // libera a matriz anterior se o usuario pedir novo no meio do jogo
    if (*matriz != NULL) {
        liberaMatriz(*matriz, *dimensao);
    }

    if(dificuldade == 'f'|| dificuldade == 'F'){
        *dimensao = 3;
        *matriz = criaMatriz(3);
    }
    else if(dificuldade == 'm'|| dificuldade == 'M'){
        *dimensao = 5;
        *matriz = criaMatriz(5);
    }
    else if(dificuldade == 'd'|| dificuldade == 'D'){
        *dimensao = 7;
        *matriz = criaMatriz(7);
    }
    else{
        printf("\n\nErro: entrada inválida\nTente novamente\n");
    }
}

void mostrarComandos(int temJogoAtivo){
    printf(BOLD("\nComandos do jogo\n"));
    printf(BOLD("\najuda: ") "Exibe os comandos do jogo");
    printf(BOLD("\nsair: ") "Sair do Jogo");
    printf(BOLD("\nnovo: ") "Começar um novo jogo");
    printf(BOLD("\ncarregar: ") "<nome>: carrega um save (ex: carregar jogo)");
    printf(BOLD("\nranking: ") "Exibir o ranking");
    if(temJogoAtivo){
        printf(BOLD("\nsalvar: ") "<nome>: salva o jogo atual (ex: salvar jogo)");
        printf(BOLD("\ndica: ") "Marca uma posição no jogo");
        printf(BOLD("\nresolver: ") "Resolve o jogo atual");
        printf(BOLD("\nadicionar: ") "<lin> <col>: marca a posição <lin> <col> para entrar na soma");
        printf(BOLD("\nremover: ") "<lin> <col>: remove a posição da soma");
    }
    printf("\n");
}

void rodarJogo(char nome[30], int * dimensao, Tabela *** matriz){
    int continuarJogando = 1; 
    int temJogoAtivo = 0;
    
    // variaveis para calcular o tempo
    struct timeval inicio, fim;

    do{
        char comandoDigitado[20];
        if(strcmp("", nome)){
            printf(BOLD("\n\n %s, digite um comando: (digite \"ajuda\" para listar os comandos) "), nome);
        }
        else{
            printf(BOLD("\n\nDigite um comando: (digite \"ajuda\" para listar os comandos) "));
        }
        
        // Pega a primeira palavra digitada
        scanf("%s", comandoDigitado);
    
        if(!strcmp(comandoDigitado, "ajuda")){
            mostrarComandos(temJogoAtivo);
        }
        else if (!strcmp(comandoDigitado, "sair")){
            sair();
            continuarJogando = 0; 
        }
        else if (!strcmp(comandoDigitado, "novo")){
            novoJogo(nome, dimensao, matriz);
            if (*dimensao > 0) {
                temJogoAtivo = 1; 
                gettimeofday(&inicio, 0); // dispara o cronometro
            }
        }
        else if (!strcmp(comandoDigitado, "carregar")){
            char nomeSave[50];
            scanf("%s", nomeSave); // Pega a segunda palavra digitada
            carregarJogo(matriz, dimensao, nome, &inicio, &temJogoAtivo, nomeSave);
        }
        else if(!strcmp(comandoDigitado, "ranking"))
            mostrarRanking();
        else if(temJogoAtivo){
            if (!strcmp(comandoDigitado, "salvar")){
                char nomeSave[50];
                scanf("%s", nomeSave); // Pega a segunda palavra digitada
                salvarJogo(*matriz, *dimensao, nome, inicio, nomeSave);
            }
            else if(!strcmp(comandoDigitado, "dica"))
               mostrarDica(*matriz, *dimensao);
            else if(!strcmp(comandoDigitado, "resolver"))
               resolverJogo(*dimensao, *matriz);
            else if(!strcmp(comandoDigitado, "adicionar") || !strcmp(comandoDigitado, "remover")){
                
                // executa a acao baseada no comando
                if (!strcmp(comandoDigitado, "adicionar")) adicionarPosicao(*dimensao, *matriz);
                else removerPosicao(*dimensao, *matriz);

                // mostra o tabuleiro atualizado apos a jogada
                mostrarTabuleiro(*dimensao, *matriz);

                // verifica a vitoria
                if(verificarVitoria(*dimensao, *matriz)){
                    // para o cronometro
                    gettimeofday(&fim, 0);
                    long sec = fim.tv_sec - inicio.tv_sec;
                    long microsec = fim.tv_usec - inicio.tv_usec;
                    double passado = sec + microsec * 1e-6;
                    int tempoInteiro = (int)passado; // converte para o ranking

                    printf("\n\n"BG_GREEN(BOLD("Parabéns %s, você ganhou!"))"\n\n", nome);
                    
                    // adiciona no ranking e mostra
                    int posicao = adicionarRanking(nome, tempoInteiro);
                    printf(GREEN("Tempo de jogo: %.3f segundos (Registrado como %ds).\n"), passado, tempoInteiro);
                    if (posicao != -1) printf(GREEN("Você entrou para o Top 10 na %dº posição!\n"), posicao);
                    else printf(YELLOW("\nSeu tempo não foi suficiente para entrar no Top 10.\n"));

                    temJogoAtivo = 0; // desativa o jogo atual
                    
                    // laço para validar a resposta de jogar novamente
                    int respostaValida = 0;
                    do {
                        char resposta[30];
                        printf("\nDeseja jogar novamente? (sim/nao) ");
                        scanf("%s", resposta);
                        
                        if(!strcmp(resposta, "sim") || !strcmp(resposta, "Sim") || !strcmp(resposta, "SIM")){
                            novoJogo(nome, dimensao, matriz); 
                            if (*dimensao > 0) {
                                temJogoAtivo = 1;
                                gettimeofday(&inicio, 0); // reinicia o cronometro para o novo jogo
                            }
                            if (temJogoAtivo) mostrarTabuleiro(*dimensao, *matriz); 
                            respostaValida = 1;
                        }
                        else if (!strcmp(resposta, "nao") || !strcmp(resposta, "Nao") || !strcmp(resposta, "NAO")) {
                            sair();
                            continuarJogando = 0; 
                            respostaValida = 1;
                        }
                        else {
                            printf(RED("\nEntrada inválida! digite sim ou nao\n"));
                        }
                    } while(!respostaValida);
                }
            }
            else{
                printf("\nComando inválido! digite novamente");
            }
        } else{
            printf("\nComando inválido ou jogo não iniciado! digite novamente");
        }
        
        // mostra o tabuleiro se tiver um jogo ativo e se nao acabou de interagir
        if (temJogoAtivo && continuarJogando && strcmp(comandoDigitado, "adicionar") && strcmp(comandoDigitado, "remover")) {
            mostrarTabuleiro(*dimensao, *matriz);
        }

    } while (continuarJogando);
}

// calculo de somas acessando as structs
int calcularSomaLinhaAlvo(int d, Tabela **matriz, int linha) {
    int soma = 0;
    for (int i = 0; i < d; i++) {
        soma += matriz[linha][i].numero * matriz[linha][i].numero_mask;
    }
    return soma;
}

int calcularSomaColunaAlvo(int d, Tabela **matriz, int coluna) {
    int soma = 0;
    for (int i = 0; i < d; i++) {
        soma += matriz[i][coluna].numero * matriz[i][coluna].numero_mask;
    }
    return soma;
}

// calcula a soma atual baseada nas escolhas do jogador
int calcularSomaLinhaAtual(int d, Tabela **matriz, int linha) {
    int soma = 0;
    for (int j = 0; j < d; j++) {
        if (matriz[linha][j].cor == 0 || matriz[linha][j].cor == 1) { // 0 padrao 1 adicionado
            soma += matriz[linha][j].numero;
        }
    }
    return soma;
}

int calcularSomaColunaAtual(int d, Tabela **matriz, int coluna) {
    int soma = 0;
    for (int i = 0; i < d; i++) {
        if (matriz[i][coluna].cor == 0 || matriz[i][coluna].cor == 1) { // 0 padrao 1 adicionado
            soma += matriz[i][coluna].numero;
        }
    }
    return soma;
}

// verifica se todas as linhas e colunas bateram com o alvo
int verificarVitoria(int d, Tabela **matriz) {
    for (int i = 0; i < d; i++) {
        if (calcularSomaLinhaAtual(d, matriz, i) != calcularSomaLinhaAlvo(d, matriz, i)) {
            return 0; 
        }
    }
    for (int j = 0; j < d; j++) {
        if (calcularSomaColunaAtual(d, matriz, j) != calcularSomaColunaAlvo(d, matriz, j)) {
            return 0; 
        }
    }
    return 1; 
}

void mostrarTabuleiro(int d, Tabela **matriz){
    printf("\n\n");

    // imprime os indices das colunas no topo
    printf("    ");
    for (int j = 0; j < d; j++) {
        printf(YELLOW(BOLD(" %d  ")), j + 1);
    }
    printf("\n");

    // imprime a borda superior
    printf("   ");
    printf("%s", TAB_TL);
    for (int j = 0; j < d; j++) {
        printf("%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR);
        if (j < d - 1) printf("%s", TAB_TJ);
        else printf("%s\n", TAB_TR);
    }

    // imprime as linhas da matriz e os separadores
    for (int i = 0; i < d; i++) {
        
        printf(YELLOW(BOLD(" %d ")), i + 1); 
        printf("%s", TAB_VER);
        
        // imprime os numeros do jogo mudando a cor conforme o estado da struct
        for (int j = 0; j < d; j++) {
            if (matriz[i][j].cor == 1) { 
                printf(GREEN(BOLD(" %d ")), matriz[i][j].numero);
            } else if (matriz[i][j].cor == 2) { 
                printf(RED(" %d "), matriz[i][j].numero);
            } else { 
                printf(" %d ", matriz[i][j].numero);
            }
            printf("%s", TAB_VER);
        }
        
        // calcula as somas da linha
        int somaLinhaAlvo = calcularSomaLinhaAlvo(d, matriz, i);
        int somaLinhaAtual = calcularSomaLinhaAtual(d, matriz, i);
        
        // se bateu com o esperado, fica branco forte, senao fica cinza/escuro
        if (somaLinhaAlvo == somaLinhaAtual) {
            printf(WHITE(BOLD(" %2d\n")), somaLinhaAlvo);
        } else {
            printf(GRAY(" %2d\n"), somaLinhaAlvo);
        }

        // imprime o separador do meio ou a borda inferior
        printf("   ");
        if (i < d - 1) {
            // se nao for a ultima linha
            printf("%s", TAB_ML);
            for (int j = 0; j < d; j++) {
                printf("%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR);
                if (j < d - 1) printf("%s", TAB_MJ);
                else printf("%s\n", TAB_MR);
            }
        } else {
            // se for a ultima linha
            printf("%s", TAB_BL);
            for (int j = 0; j < d; j++) {
                printf("%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR);
                if (j < d - 1) printf("%s", TAB_BJ);
                else printf("%s\n", TAB_BR);
            }
        }
    }

    // calcula e imprime as somas alvo das colunas no rodape
    printf("    ");
    for (int j = 0; j < d; j++) {
        int somaColAlvo = calcularSomaColunaAlvo(d, matriz, j);
        int somaColAtual = calcularSomaColunaAtual(d, matriz, j);
        
        // se bateu com o esperado, fica branco forte, senao fica cinza/escuro
        if (somaColAlvo == somaColAtual) {
            printf(WHITE(BOLD(" %2d ")), somaColAlvo);
        } else {
            printf(GRAY(" %2d "), somaColAlvo);
        }
    }
    printf("\n\n");
}

void adicionarPosicao(int d, Tabela ** matriz) {
    int linha, coluna;
    printf("\nDigite a linha e a coluna para ADICIONAR (ex: 1 2): ");
    scanf("%d %d", &linha, &coluna);
    
    // verifica se as coordenadas estao dentro do tabuleiro
    if (linha > 0 && linha <= d && coluna > 0 && coluna <= d) {
        matriz[linha - 1][coluna - 1].cor = 1; 
        printf(GREEN("\n\nPosição %d %d adicionada à soma!\n"), linha, coluna);
    } else {
        printf(RED("\n\nErro: Coordenadas fora do tabuleiro!\n"));
    }
}

void removerPosicao(int d, Tabela ** matriz) {
    int linha, coluna;
    printf("\n\nDigite a linha e a coluna para REMOVER (ex: 1 2): ");
    scanf("%d %d", &linha, &coluna);
    
    // verifica se as coordenadas estao dentro do tabuleiro
    if (linha > 0 && linha <= d && coluna > 0 && coluna <= d) {
        matriz[linha - 1][coluna - 1].cor = 2; 
        printf(RED("\n\nPosição %d %d removida da soma!\n"), linha, coluna);
    } else {
        printf(RED("\n\nErro: Coordenadas fora do tabuleiro!\n"));
    }
}

void mostrarRanking() {
    FILE *arquivo = fopen("sumplete.rnk", "r");
    if (arquivo == NULL) {
        printf(RED("\nNenhum ranking encontrado ainda. Jogue uma partida para criar!\n"));
        return;
    }

    printf(BOLD("\n"BG_BLUE("--- RANKING DOS JOGADORES (TOP 10) ---")"\n"));
    printf(BOLD(" Posição  | Tempo (s) | Nome\n"));
    printf(" ━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━━━━\n");
    
    Jogador j;
    int posicao = 1;
    
    while (fscanf(arquivo, "%s %d", j.nome, &j.tempo) == 2 && posicao <= 10) {
        printf(" %2dº      | %4d      | %s\n", posicao, j.tempo, j.nome);
        posicao++;
    }
    
    fclose(arquivo);
    printf("\n");
}

int adicionarRanking(char *nomeJogador, int tempoGasto) {
    Jogador ranking[11]; 
    int qtd = 0;

    FILE *arquivo = fopen("sumplete.rnk", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %d", ranking[qtd].nome, &ranking[qtd].tempo) == 2) {
            qtd++;
            if (qtd == 10) break; 
        }
        fclose(arquivo);
    }

    strcpy(ranking[qtd].nome, nomeJogador);
    ranking[qtd].tempo = tempoGasto;
    qtd++;

    // ordena do menor para o maior
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (ranking[j].tempo > ranking[j + 1].tempo) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    if (qtd > 10) qtd = 10;

    int posicaoFinal = -1;
    for(int i = 0; i < qtd; i++) {
        if(strcmp(ranking[i].nome, nomeJogador) == 0 && ranking[i].tempo == tempoGasto) {
            posicaoFinal = i + 1;
            break;
        }
    }

    arquivo = fopen("sumplete.rnk", "w");
    if (arquivo != NULL) {
        for (int i = 0; i < qtd; i++) {
            fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].tempo);
        }
        fclose(arquivo);
    } else {
        printf(RED("\nErro ao salvar o arquivo sumplete.rnk!\n"));
    }

    return posicaoFinal;
}

void sair(){
    printf("\nSaindo do jogo...\n");
}

void mostrarDica(Tabela **matriz, int dimensao) {
    int dicas = 0;

    // varre a matriz contando quantas posicoes corretas ainda nao foram pintadas
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].numero_mask == 1 && matriz[i][j].cor != 1) {
                dicas++;
            }
        }
    }

    // se o contador continuou zerado, é pq nao tem mais o que revelar
    if (dicas == 0) {
        printf(YELLOW("\nTodos os números necessários já foram adicionados\n"));
        return;
    }

    // se tem celula escondida, sorteia ate acertar uma
    while (1) {
        int linAleatoria = rand() % dimensao;
        int colAleatoria = rand() % dimensao;
        
        if (matriz[linAleatoria][colAleatoria].numero_mask == 1 && matriz[linAleatoria][colAleatoria].cor != 1) {
            matriz[linAleatoria][colAleatoria].cor = 1;
            printf(GREEN("\nDica: Posição %d %d revelada!\n"), linAleatoria + 1, colAleatoria + 1);
            break; // sai do laco
        }
    }
}

void resolverJogo(int dimensao, Tabela **matriz) {
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].numero_mask == 1) {
                matriz[i][j].cor = 1; // Deve ser adicionado
            } else {
                matriz[i][j].cor = 2; // Deve ser removido
            }
        }
    }
    printf(GREEN("\nO jogo foi resolvido automaticamente!\n"));
}

void salvarJogo(Tabela **matriz, int dimensao, char *nome, struct timeval inicio, char *nomeBase) {
    char nomeArquivo[100];
    
    // Adiciona o .sum ao nome que o usuario digitou
    strcpy(nomeArquivo, nomeBase);
    strcat(nomeArquivo, ".sum");

    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf(RED("\nErro ao criar arquivo!\n"));
        return;
    }

    // calcula o tempo decorrido no momento do save
    struct timeval fim;
    gettimeofday(&fim, 0);
    int tempoDecorrido = (int)(fim.tv_sec - inicio.tv_sec);

    // escreve a dimensão (d)
    fprintf(f, "%d\n", dimensao);

    // escreve a matriz com os números
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            fprintf(f, "%d", matriz[i][j].numero);
            if (j < dimensao - 1) fprintf(f, " ");
        }
        fprintf(f, "\n");
    }

    // escreve a soma das linhas
    for (int i = 0; i < dimensao; i++) {
        fprintf(f, "%d", calcularSomaLinhaAlvo(dimensao, matriz, i));
        if (i < dimensao - 1) fprintf(f, " ");
    }
    fprintf(f, "\n");

    // escreve a soma das colunas
    for (int j = 0; j < dimensao; j++) {
        fprintf(f, "%d", calcularSomaColunaAlvo(dimensao, matriz, j));
        if (j < dimensao - 1) fprintf(f, " ");
    }
    fprintf(f, "\n");

    // conta e escreve a quantidade de células a remover para formar a máscara (v)
    int v = 0;
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].numero_mask == 0) v++;
        }
    }
    fprintf(f, "%d\n", v);

    // escreve as posições (linha e coluna) das células removidas da máscara (1-based index)
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].numero_mask == 0) {
                fprintf(f, "%d %d\n", i + 1, j + 1);
            }
        }
    }

    // conta e escreve as jogadas do jogador (m)
    int m = 0;
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].cor == 1 || matriz[i][j].cor == 2) m++;
        }
    }
    fprintf(f, "%d\n", m);

    // escreve os detalhes das jogadas ('a' = adicionado/1, 'r' = removido/2)
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (matriz[i][j].cor == 1) {
                fprintf(f, "a %d %d\n", i + 1, j + 1);
            } else if (matriz[i][j].cor == 2) {
                fprintf(f, "r %d %d\n", i + 1, j + 1);
            }
        }
    }

    // escreve nome e tempo
    fprintf(f, "%s\n", nome);
    fprintf(f, "%d\n", tempoDecorrido);

    fclose(f);
    printf(GREEN("\nJogo salvo com sucesso em '%s'!\n"), nomeArquivo);
}

void carregarJogo(Tabela ***matriz, int *dimensao, char *nome, struct timeval *inicio, int *temJogoAtivo, char *nomeBase) {
    char nomeArquivo[100];
    
    // Adiciona o .sum ao nome que o usuario digitou
    strcpy(nomeArquivo, nomeBase);
    strcat(nomeArquivo, ".sum");

    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        printf(RED("\nErro ao abrir o arquivo '%s'. Verifique se ele existe!\n"), nomeArquivo);
        return;
    }

    int d;
    if (fscanf(f, "%d", &d) != 1) {
        printf(RED("\nErro na leitura do arquivo!\n"));
        fclose(f);
        return;
    }

    // limpa jogo atual para recarregar o novo
    if (*matriz != NULL) liberaMatriz(*matriz, *dimensao);
    
    *dimensao = d;
    *matriz = criaMatriz(d); 
    *temJogoAtivo = 1;

    // lendo a matriz de números e resetando o estado base da struct
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            fscanf(f, "%d", &(*matriz)[i][j].numero);
            (*matriz)[i][j].numero_mask = 1; // Tudo começa fazendo parte da máscara...
            (*matriz)[i][j].cor = 0;         // ...sem marcações do usuário
        }
    }

    // pula a linha das somas 
    int temp;
    for (int i = 0; i < d; i++) fscanf(f, "%d", &temp); 
    for (int j = 0; j < d; j++) fscanf(f, "%d", &temp); 

    // lendo a máscara de remoções (v)
    int v;
    fscanf(f, "%d", &v);
    for (int k = 0; k < v; k++) {
        int l, c;
        fscanf(f, "%d %d", &l, &c);
        (*matriz)[l - 1][c - 1].numero_mask = 0; // Configura as máscaras corretamente
    }

    // lendo jogadas feitas (m)
    int m;
    fscanf(f, "%d", &m);
    for (int k = 0; k < m; k++) {
        char tipo;
        int l, c;
        fscanf(f, " %c %d %d", &tipo, &l, &c); 
        if (tipo == 'a') (*matriz)[l - 1][c - 1].cor = 1;
        else if (tipo == 'r') (*matriz)[l - 1][c - 1].cor = 2;
    }

    // recuperando nome e manipulando o relógio
    int tempoGasto;
    fscanf(f, "%s", nome);
    fscanf(f, "%d", &tempoGasto);

    fclose(f);

    // ajusta o relógio interno
    gettimeofday(inicio, 0);
    inicio->tv_sec -= tempoGasto;

    printf(GREEN("\nJogo de %s carregado com sucesso!\n"), nome);
}