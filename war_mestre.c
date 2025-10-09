#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

// **** Constantes Globais ****
// **** Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção. ****

#define TAM_NOME 30
#define TAM_COR 10

// **** Estrutura de Dados ****

/// @brief Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
/// Criação da struct: definir uma struct chamada Territorio com os campos char nome[30], char cor[10] e int tropas.
typedef struct
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

typedef struct
{
    char *corRemanescente;
    int razaoTropas;
} MissaoInfo;

// **** Protótipos das Funções ****

//**** Funções de setup e gerenciamento de memória ****

/// @brief Aloca dinamicamente a memória para o vetor de territórios usando malloc.
/// @param numTerritorios Número de territórios para alocar em memória.
/// @return Ponteiro para o vetor de territórios, em caso de sucesso. Ou NULL, em caso de falha.
Territorio *alocarMapa(int numTerritorios);

/// @brief Libera a memória previamente alocada para o mapa usando free.
/// @param mapa Ponteiro para o vetor de territorios.
/// @param missaoJogador Ponteiro para o vetor de caracteres(string) que representa a missão.
/// @param missoes
/// @param numMissoes
void liberarMemoria(Territorio *mapa, char *missaoJogador, char **missoes, int numMissoes);

// **** Funções de interface com o usuário: ****

/// @brief Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
/// Esta função modifica o mapa passado por referência (ponteiro).
/// @param mapa Ponteiro para o vetor de territorios.
/// @param numTerritorios Número de territórios alocados.
void cadastrarTerritorios(Territorio *mapa, int numTerritorios);

/// @brief Imprime na tela o menu de ações disponíveis para o jogador.
/// @param opcao Ponteiro para um inteiro, para conter o valor representado a escolha do jogador.
void exibirMenuPrincipal(int *opcao);

/// @brief Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
/// Chama a função de simular o ataque para executar a lógica da batalha.
/// @param mapa Ponteiro para o mapa(vetor de territórios) em questão.
/// @param codigoRetorno Número inteiro. 1 representa um identificador inválido e 2, uma ação cancelada.
/// @param numTerritorios Número inteiro. Representa os territórios(elementos) alocados no vetor em questão.
void faseDeAtaque(Territorio *mapa, int *codigoRetorno, int numTerritorios);

/// @brief Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
/// @param mapa Ponteiro para o vetor de territórios. Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
/// @param tamanho Número representando o tamanho do vetor.
void exibirMapa(const Territorio *mapa, int tamanho);

// **** Funções de lógica principal do jogo: ****

/// @brief Sorteia e atribui uma missão aleatória para o jogador.
/// @param destino Ponteiro referenciando o buffer a ser inicializado e populado, com o conteúdo da missão do jogador.
/// @param missoes Vetor contendo textos(strings), representando as missões.
/// @param totalMissoes Número de missões(elementos do vetor), para definição do intervalo de geração de números randômicos.
void atribuirMissao(char **destino, char *missoes[], int totalMissoes);

/// @brief // Verifica se o jogador cumpriu os requisitos de sua missão atual.
/// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
/// @param missao Missão atual com conteúdo alocado.
/// @param mapa Vetor de territórios, atualmente representando o mapa.
/// @param tamanho Tamanho do vetor em questão.
/// @return Retorna 1 (verdadeiro) se a missão foi cumprida. E 0 (falso), caso contrário.
int verificarMissao(char *missao, const Territorio *mapa, int tamanho);

/// @brief Exibe o conteúdo alocado, representando a missão atual do jogador.
/// @param missao Ponteiro com o conteúdo(string).
void exibirMissao(char *missao);

/// @brief Executa a lógica de uma batalha entre dois territórios.
/// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
/// Se um território for conquistado, atualiza seu dono e move uma tropa.
/// @param atacante Ponteiro representando o território atacante.
/// @param defensor Ponteiro representando o território defensor.
void atacar(Territorio *atacante, Territorio *defensor);

// **** Funções utilitárias: ****

/// @brief Limpa o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada();
/// @brief Função para limpar '\n' deixado pelo fgets.
/// @param str Conteúdo do texto a ser analisado e limpo.
void limparEnter(char *str);

int maiorQue(int a, int b);
int maiorOuIgualQue(int a, int b);
int menorQue(int a, int b);
int menorOuIgualQue(int a, int b);
int igualA(int a, int b);

int verificarTropaPelaCor(const char *cor, const Territorio *mapa, int tamanho);

int verificarCondicaoMissao(
    const Territorio *mapa,
    int tamanho,
    const char *corJogador,
    int (*condicao)(int, int),
    int valorComparacao,
    int valorEsperado);

MissaoInfo *missaoInfo = NULL;

// Territorio *remanescente = NULL;

char *format(const char *fmt, ...);

/// @brief Função Principal (main). Ponto de entrada do programa.
/// Orquestra o fluxo do jogo, chamando as outras funções em ordem.
/// @return Número inteiro. Zero em caso de sucesso, Exemplo: EXIT_SUCCESS. Ou diferente de zero, em caso de falha, Exemplo: EXIT_FAILURE.
int main()
{
#pragma region Instrucoes
// 1. Configuração Inicial (Setup):
// - Define o locale para português.
// - Inicializa a semente para geração de números aleatórios com base no tempo atual.
// - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
// - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
// - Define a cor do jogador e sorteia sua missão secreta.

// 2. Laço Principal do Jogo (Game Loop):
// - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
// - A cada iteração, exibe o mapa, a missão e o menu de ações.
// - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
//   - Opção 1: Inicia a fase de ataque.
//   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
//   - Opção 0: Encerra o jogo.
// - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

// 3. Limpeza:
// - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
#pragma endregion

    srand(time(NULL)); // Inicializa o gerador de números aleatórios.

    printf("====================================\n");
    printf("      💣 WAR ESTRUTURADO 💣 \n");
    printf("====================================\n");

    int numTerritorios;
    printf("Digite o número de territórios a cadastrar: ");
    scanf("%d", &numTerritorios); // Em caso de letra, corresponderá a um código numérico. Não foi solicitada a validação de todas as entradas do jogador.
    limparBufferEntrada();

    // Alocação dinâmica de memória para os territórios
    Territorio *mapa = alocarMapa(numTerritorios);

    if (mapa == NULL)
    {
        printf("\n ❌  Erro ao alocar memória para o mapa.\n");
        return EXIT_FAILURE;
    }

    // Cadastrando os territórios.
    cadastrarTerritorios(mapa, numTerritorios);

    // Atribuir missão ao jogador e armazenar as missões dinamicamente. Dessa forma, podemos evitar
    // sortear missões desalinhadas com o contexto do cadastro de territórios, como cores de jogadores,
    // ou números de tropas inconsistentes, sorteio de missões para jogadores não cadastrados, entre outros.

    char *missaoJogador = NULL;

    char *missoes[numTerritorios + 4];

    int maxTropas = 0;

    for (int i = 0; i < numTerritorios; i++)
    {
        missoes[i] = format("Eliminar todas as tropas da cor %s", mapa[i].cor);
        if (maxTropas < mapa[i].tropas)
            maxTropas = mapa[i].tropas;
    }
    int razaoTropas = maxTropas / numTerritorios; // Cálculo rudimentar para tentar evitar incoerências entre as informações da missão e dos exércitos.
    missoes[numTerritorios] = format("Conquistar %d territorios", numTerritorios);
    missoes[numTerritorios + 1] = format("Controlar %d territorios com mais de %d tropas", numTerritorios, razaoTropas);
    missoes[numTerritorios + 2] = format("Controlar %d territorios com menos de %d tropas", numTerritorios, razaoTropas);
    missoes[numTerritorios + 3] = format("Controlar %d territorios com exatamente %d tropas", numTerritorios, razaoTropas);

    missaoInfo = (MissaoInfo *)malloc(sizeof(MissaoInfo));
    missaoInfo->corRemanescente = NULL;
    missaoInfo->razaoTropas = razaoTropas;

    int totalMissoes = numTerritorios + 4;

    atribuirMissao(&missaoJogador, missoes, totalMissoes); // Não podemos apontar para o char em si, mas sim para um vetor de char(para um buffer de texto).

    if (missaoJogador == NULL)
    {
        printf(" ❌  Erro ao alocar memória para a missão.\n");
        return EXIT_FAILURE;
    }

    exibirMissao(missaoJogador);

    char continuar;

    do
    {
        int opcao;

        exibirMenuPrincipal(&opcao);

        switch (opcao)
        {
        case 1:
            // Escolha de Ataque.
            // Antes, vamos exibir as informações do mapa atual ao jogador.
            exibirMapa(mapa, numTerritorios);

            int codigoRetorno;

            faseDeAtaque(mapa, &codigoRetorno, numTerritorios);
            // Alguns tratamentos básicos.
            if (codigoRetorno == 1) // Id's inválidos.
            {
                continuar = 'S';
                continue;
            }
            else if (codigoRetorno == 2) // Ação cancelada pelo jogador.
            {
                continuar = 'N';
                continue;
            }

            break;
        case 2:
            // Escolha para exibir a missão.
            exibirMissao(missaoJogador);
            break;
        case 0:
            // Sair.
            continuar = 'N';
            continue;
        default:
            // Continua.
            printf("\n==== Opção inválida. ==== \n");
            break;
        }

        // Verificando se missão foi cumprida.
        if (verificarMissao(missaoJogador, mapa, numTerritorios))
        {
            printf("\n 🎉  Missão cumprida! Jogador vence o jogo!\n");
            continuar = 'N'; // Não foi definido nas regras se após o termino de uma partida, o jogo pode reiniciar.
            continue;
        }

        printf("\n 🔁  Deseja continuar? (s/n): ");
        continuar = getchar();
        limparBufferEntrada();

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador, missoes, totalMissoes);

    printf("\n====  Fim de jogo! ====\n");

    return EXIT_SUCCESS;
}

// ***** Implementação das Funções *****

void atribuirMissao(char **destino, char *missoes[], int totalMissoes)
{
    // Sorteando o valor da missão.
    int indice = rand() % totalMissoes;
    // Alocando conforme a opção recuperada.
    *destino = malloc(strlen(missoes[indice]) + 1);
    // Verificando se a alocação foi efetuada ou não.
    if (*destino == NULL)
    {
        return;
    }
    // Atribuição de valor com strcpy.
    strcpy(*destino, missoes[indice]);
}

void exibirMissao(char *missao)
{
    printf("\n ================================================== \n");
    printf("\n 🔍  Sua missão: %s\n", missao);
    printf("\n ================================================== \n");
}

int maiorQue(int a, int b) { return a > b; }
int maiorOuIgualQue(int a, int b) { return a >= b; }
int menorQue(int a, int b) { return a < b; }
int menorOuIgualQue(int a, int b) { return a <= b; }
int igualA(int a, int b) { return a == b; }

int verificarMissao(char *missao, const Territorio *mapa, int tamanho)
{
    const char *corJogador = missaoInfo->corRemanescente; // Cor do jogador que prevaleceu na batalha atual.
    if (corJogador == NULL)
    {
        //printf("⚠️ A cor do jogador ainda não foi definida. Realize ao menos um ataque primeiro.\n");
        return 0;
    }

    int razaoTropas = missaoInfo->razaoTropas; // Cálculo rudimentar para tentar evitar incoerências nos números da missão.

    int sucesso = 0;

    if (strstr(missao, "Eliminar todas as tropas da cor ") != NULL)
    {
        const char *prefixo = "Eliminar todas as tropas da cor ";
        const char *corAlvo = missao + strlen(prefixo); // Vamos efetuar um deslocamento suficiente para recuperar o sufixo.

        sucesso = verificarTropaPelaCor(corAlvo, mapa, tamanho);
        if (sucesso)
            printf("\n🎉 O exército %s eliminou todas as tropas da cor %s!\n", corJogador, corAlvo);
    }
    // Aqui, 1 indica ao menos uma tropa por território, sendo que é necessário conquistar todos.
    if (strstr(missao, "Conquistar ") != NULL && verificarCondicaoMissao(mapa, tamanho, corJogador, igualA, 1, tamanho))
    {
        printf("\n🎉  O exército %s conquistou %d territórios!\n", corJogador, tamanho);
        sucesso = 1;
    }
    // Mais da média X de tropas.
    if (strstr(missao, "territorios com mais de ") && verificarCondicaoMissao(mapa, tamanho, corJogador, maiorQue, razaoTropas, tamanho))
    {
        printf("\n 🎉  O exército %s controla %d territórios com mais de %d tropas!\n", corJogador, tamanho, razaoTropas);
        sucesso = 1;
    }
    // Menos da média X de tropas.
    if (strstr(missao, "territorios com menos de ") && verificarCondicaoMissao(mapa, tamanho, corJogador, menorQue, razaoTropas, tamanho))
    {
        printf("\n 🎉  O exército %s controla %d territórios com menos de %d tropas!\n", corJogador, tamanho, razaoTropas);
        sucesso = 1;
    }
    // Exatamente a média X de tropas.
    if (strstr(missao, "territorios com exatamente ") && verificarCondicaoMissao(mapa, tamanho, corJogador, igualA, razaoTropas, tamanho))
    {
        printf("\n 🎉  O exército %s controla %d territórios com exatamente %d tropas!\n", corJogador, tamanho, razaoTropas);
        sucesso = 1;
    }

    return sucesso;
}

int verificarTropaPelaCor(const char *cor, const Territorio *mapa, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        if (strcmp(mapa[i].cor, cor) == 0 && mapa[i].tropas > 0)
            return 0;
    return 1;
}

int verificarCondicaoMissao(
    const Territorio *mapa,
    int tamanho,
    const char *corJogador,
    int (*condicao)(int, int),
    int valorComparacao,
    int valorEsperado)
{
    int count = 0;

    for (int i = 0; i < tamanho; i++)
    {
        printf("\n===== MapaCor[i] => %s | CorJogador => %s Mapa[i].tropas => %d ValorComparacao => %d =====", mapa[i].cor, corJogador, mapa[i].tropas, valorComparacao);

        if (strcmp(mapa[i].cor, corJogador) == 0 && condicao(mapa[i].tropas, valorComparacao))
        {
            count++;
        }
    }

    return count == valorEsperado;
}

Territorio *alocarMapa(int numTerritorios)
{
    // malloc converte implicitamente para qualquer outro tipo de ponteiro. Portanto, o cast aqui é opcional.
    // Mas nenhuma convenção foi estabelecida para o uso. Por isso, foi mantido.

    Territorio *vetor = (Territorio *)malloc(numTerritorios * sizeof(Territorio));

    if (vetor == NULL)
    {
        printf(" ❌  Erro ao alocar memória para os territórios!\n");
        return NULL;
    }

    return vetor;
}

void exibirMenuPrincipal(int *opcao)
{
    printf("\n ==== Menu de Ações ==== \n");
    printf("\n1 - Atacar. \n");
    printf("2 - Verificar missão. \n");
    printf("0 - Sair. \n");
    printf("Escolha uma opção: ");

    scanf("%d", opcao); // Já temos um ponteiro aqui. Não precisamos aplicar o &.
    limparBufferEntrada();
}

void faseDeAtaque(Territorio *mapa, int *codigoRetorno, int numTerritorios)
{
    int idAtacante, idDefensor;

    printf("\n==== FASE DE ATAQUE ====\n");

    printf("\n ⚔️  Escolha o território atacante [ID] de %d a %d, ou 0 para sair: ", 1, numTerritorios);
    scanf("%d", &idAtacante);
    limparBufferEntrada();

    printf("\n 🛡️  Escolha o território defensor [ID] de %d a %d, ou 0 para sair: ", 1, numTerritorios);
    scanf("%d", &idDefensor);
    limparBufferEntrada();

    if (idAtacante > numTerritorios || idDefensor > numTerritorios)
    {
        printf(" ⚠️  IDs inválidos. Tente novamente.\n");
        *codigoRetorno = 1;
        return;
    }
    else if (idAtacante == idDefensor)
    {
        printf(" ⚠️  Um território não pode atacar a si mesmo.\n");
        *codigoRetorno = 1;
        return;
    }
    else if (idAtacante < 1 || idDefensor < 1)
    {
        printf(" ❌  A ação foi cancelada.\n");
        *codigoRetorno = 2;
        return;
    }

    // Como o vetor é baseado em índice zero, precisamos informar a posição atual de forma adequada.
    atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
}

void exibirMapa(const Territorio *mapa, int tamanho)
{
    printf("\n==== 🌍  MAPA DO MUNDO - ESTADO ATUAL ====\n\n");
    // Evitar mostrar o número do exército baseado no índice zero.
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] %s | Exército Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void cadastrarTerritorios(Territorio *mapa, int numTerritorios)
{
    printf("\n==== Cadastro dos Territórios ====\n");

    for (int i = 0; i < numTerritorios; i++)
    {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        limparEnter(mapa[i].nome);

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        limparEnter(mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

void atacar(Territorio *atacante, Territorio *defensor)
{
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\n ⚠️  Aviso: Você não pode atacar um território aliado!.\n");
        return;
    }

    if (atacante->tropas < 2)
    {
        printf("\n ⚠️  Aviso: O território atacante precisa de pelo menos 2 tropas para atacar.\n");
        return;
    }

    // Simula a rolagem dos dados (1 a 6). Vamos evitar o retorno do valor zero.
    int dadoAtacante = rand() % 6 + 1, dadoDefensor = rand() % 6 + 1;

    printf("\n==== RESULTADO DO ATAQUE ====\n");
    printf("\n ⚔️  Ataque de %s (%d tropas) contra 🛡️  defesa de %s (%d tropas)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("\n 🎲  Rolagem da dados: atacante => %d | defensor => %d\n", dadoAtacante, dadoDefensor);

    if (missaoInfo->corRemanescente != NULL)
    {
        free(missaoInfo->corRemanescente);
        missaoInfo->corRemanescente = NULL;
    }

    // Pelo comportamento apresentado na vídeo aula, nos conteúdos e de acordo com o arquivo README.md, vamos implementar a lógica.
    if (dadoAtacante >= dadoDefensor)
    {
        printf("\n ⚔️  Ataque bem-sucedido! O defensor perde 1 tropa.\n");
        defensor->tropas -= 1;
        // Se as tropas defensoras se esgotarem, a conquista do atacante é decretada.
        if (defensor->tropas < 1)
        {
            printf("\n 🏆  Vitória do atacante!\n");
            // Metade das tropas do atacante se movem para o território conquistado.
            int tropasTransferidas = atacante->tropas / 2;

            strcpy(defensor->cor, atacante->cor);
            defensor->tropas += tropasTransferidas;
            atacante->tropas -= tropasTransferidas;

            printf("\nO território %s agora pertence a %s com %d tropas.\n", defensor->nome, atacante->nome, defensor->tropas);
        }

        missaoInfo->corRemanescente = malloc(strlen(atacante->cor) + 1);
        strcpy(missaoInfo->corRemanescente, atacante->cor);
    }
    else
    {
        // Caso contrário, a defesa é favorecida.
        printf("\n 🛡️  Defesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;

        missaoInfo->corRemanescente = malloc(strlen(defensor->cor) + 1);
        strcpy(missaoInfo->corRemanescente, defensor->cor);
    }
}

void liberarMemoria(Territorio *mapa, char *missaoJogador, char **missoes, int numMissoes)
{
    free(mapa);
    free(missaoJogador);
    for (int i = 0; i < numMissoes; i++)
    {
        free(missoes[i]);
    }
    if (missaoInfo != NULL)
        free(missaoInfo);
    printf("\nA memória alocada foi liberada com sucesso.\n");
}

// **** Funções utilitárias: ****

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void limparEnter(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

char *format(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char *buffer = malloc(len + 1);
    if (!buffer)
        return NULL;

    va_start(args, fmt);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    return buffer;
}

#pragma region Info_Implementacao_das_Funcoes

// alocarMapa():
// Implementado.

// Função para cadastrar territórios
// cadastrarTerritorios()
// Implementado.

// cadastrarTerritorios():
// Implementado.

// liberarMemoria():
// Implementado.

// exibirMenuPrincipal():
// Implementado.

// exibirMapa():
// Implementado.

// exibirMissao():
// Implementado.

// faseDeAtaque():
// Implementado.

// simularAtaque():
// Implementado.

// sortearMissao():
// Implementado.

// verificarVitoria():
// Implementado.

// limparBufferEntrada():
// Implementado.

#pragma endregion