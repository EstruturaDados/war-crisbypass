#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// **** Protótipos das Funções ****


void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void exibirMissao(char *missao);

//**** Funções de setup e gerenciamento de memória ****

/// @brief Aloca dinamicamente a memória para o vetor de territórios usando malloc.
/// @param numTerritorios Número de territórios para alocar em memória.
/// @return Ponteiro para o vetor de territórios, em caso de sucesso. Ou NULL, em caso de falha.
Territorio *alocarMapa(int numTerritorios);
/// @brief Libera a memória previamente alocada para o mapa usando free.
/// @param missao Ponteiro para o vetor de caracteres(string) que representa a missão. 
/// @param mapa Ponteiro para o vetor de territorios.
void liberarMemoria(char *missao, Territorio *mapa);

// **** Funções de interface com o usuário: ****

/// @brief Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
/// Esta função modifica o mapa passado por referência (ponteiro).
/// @param mapa Ponteiro para o vetor de territorios.
/// @param numTerritorios Número de territórios alocados.
void cadastrarTerritorios(Territorio *mapa, int numTerritorios);
/// @brief Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
/// @param mapa Ponteiro para o vetor de territórios. Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
/// @param tamanho Número representando o tamanho do vetor.
void exibirMapa(const Territorio *mapa, int tamanho);

// **** Funções de lógica principal do jogo: ****

/// @brief Função de ataque entre territórios.
/// @param atacante Ponteiro representando o território atacante.
/// @param defensor Ponteiro representando o território defensor.
void atacar(Territorio *atacante, Territorio *defensor);

// **** Funções utilitárias: ****

/// @brief Limpa o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada();
/// @brief Função para limpar '\n' deixado pelo fgets.
/// @param str Conteúdo do texto a ser analisado e limpo.
void limparEnter(char *str);

/// @brief Função Principal (main). Ponto de entrada do programa.
/// Orquestra o fluxo do jogo, chamando as outras funções em ordem.
/// @return Número inteiro. Zero em caso de sucesso, Exemplo: EXIT_SUCCESS. Ou diferente de zero, em caso de falha, Exemplo: EXIT_FAILURE.
int main()
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios.

    // 1. Criar vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Eliminar todas as tropas da cor azul",
        "Eliminar todas as tropas da cor amarela",
        "Eliminar todas as tropas da cor verde",
        "Controlar dois territorios com mais de 5 tropas",
        "Ter pelo menos um territorio de cada cor",
        "Reduzir as tropas inimigas a menos de 3 por territorio"};

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // 2. Atribuir missão ao jogador (armazenar dinamicamente)
    char *missaoJogador = (char *)malloc(100 * sizeof(char));
    
    if (missaoJogador == NULL)
    {
        printf("Erro ao alocar memória para a missão.\n");
        return EXIT_FAILURE;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    exibirMissao(missaoJogador); // Exibe só uma vez no início

    // 3. Criar um "mapa" com 4 territórios para teste
    int numTerritorios = 4;
    Territorio *mapa = (Territorio *)malloc(numTerritorios * sizeof(Territorio));
    if (mapa == NULL)
    {
        printf("Erro ao alocar memória para o mapa.\n");
        free(missaoJogador);
        return 1;
    }

    // Inicialização dos territórios
    strcpy(mapa[0].nome, "Territorio A");
    strcpy(mapa[0].cor, "azul");
    mapa[0].tropas = 6;

    strcpy(mapa[1].nome, "Territorio B");
    strcpy(mapa[1].cor, "vermelha");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Territorio C");
    strcpy(mapa[2].cor, "azul");
    mapa[2].tropas = 4;

    strcpy(mapa[3].nome, "Territorio D");
    strcpy(mapa[3].cor, "vermelha");
    mapa[3].tropas = 2;

    
    
    printf("====================================\n");
    printf("      💣 WAR ESTRUTURADO 💣 \n");
    printf("====================================\n");





    // Loop de turnos simulados
    int turnos = 5;
    for (int i = 0; i < turnos; i++)
    {
        printf("\n===== Turno %d =====\n", i + 1);
        exibirMapa(mapa, numTerritorios);

        // Simular ataque entre dois territórios
        atacar(&mapa[0], &mapa[1]); // Exemplo fixo: azul ataca vermelho

        // Verificar se missão foi cumprida
        if (verificarMissao(missaoJogador, mapa, numTerritorios))
        {
            printf("\n🎉 Missão cumprida! Jogador vence o jogo!\n");
            break;
        }
    }

    liberarMemoria(missaoJogador, mapa);

    return EXIT_SUCCESS;
}








// ***** Implementação das Funções *****




// Atribui missão aleatória ao jogador



void atribuirMissao(char *destino, char *missoes[], int totalMissoes)
{
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão ao jogador
void exibirMissao(char *missao)
{
    printf(" 🔍  Sua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho)
{
    // Exemplo: verificar se todos os territórios vermelhos têm menos de 3 tropas
    if (strcmp(missao, "Reduzir as tropas inimigas a menos de 3 por territorio") == 0)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas >= 3)
                return 0;
        }
        return 1;
    }

    // Exemplo: controlar dois territórios com mais de 5 tropas
    if (strcmp(missao, "Controlar dois territorios com mais de 5 tropas") == 0)
    {
        int cont = 0;
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 5)
                cont++;
        }
        if (cont >= 2)
            return 1;
    }

    // Outras missões podem ser implementadas aqui com lógicas específicas

    return 0; // Missão não cumprida ainda
}

// Exibe o estado atual do mapa
// void exibirMapa(Territorio *mapa, int tamanho)
// {
//     printf(" 🌍  Estado atual do mapa:\n");
//     for (int i = 0; i < tamanho; i++)
//     {
//         printf("%s [%s] - Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
//     }
// }


Territorio *alocarMapa(int numTerritorios)
{
    // malloc converte implicitamente para qualquer outro tipo de ponteiro. Portanto, o cast aqui é opcional.
    
    Territorio *vetor = malloc(numTerritorios * sizeof(Territorio));

    if (vetor == NULL)
    {
        printf(" ❌  Erro ao alocar memória!\n");
        return NULL;
    }

    return vetor;
}

void exibirMapa(const Territorio *mapa, int tamanho)
{
    printf("\n=== 🌍  MAPA DO MUNDO - ESTADO ATUAL ===\n\n");
    // Evitar mostrar o número do exército baseado no índice zero.
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] %s | Exército Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


void cadastrarTerritorios(Territorio *mapa, int numTerritorios)
{
    printf("\n=== Cadastro dos Territórios ===\n");

    for (int i = 0; i < numTerritorios; i++)
    {
        printf("Território %d\n", i + 1);

        printf("Nome: \n");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        limparEnter(mapa[i].nome);

        printf("Cor do exército: \n");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        limparEnter(mapa[i].cor);

        printf("Número de tropas: \n");
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

    printf("\n=== RESULTADO DO ATAQUE ===\n");    
    printf("\n ⚔️  Ataque de %s (%d) contra 🛡️ defesa de %s (%d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("\n 🎲  Rolagem da dados: atacante => %d | defensor => %d\n", dadoAtacante, dadoDefensor);

    // Não foi especificado nas regras se o atacante precisa de mais de uma investida para vencer.
    // Mas ainda assim, pelo comportamento apresentado na vídeo aula, podemos implementar uma lógica semelhante à do defensor.
    if (dadoAtacante > dadoDefensor)
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

            printf("O território %s agora pertence a %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
        }
    }
    else
    {
        printf("\n 🛡️  Defesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

void liberarMemoria(char *missao, Territorio *mapa)
{
    free(missao);
    free(mapa);
    printf("\nA memória alocada foi liberada com sucesso.\n");
}



// **** Funções utilitárias: ****

/// @brief Limpa o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/// @brief Função para limpar '\n' deixado pelo fgets.
/// @param str Conteúdo do texto a ser analisado e limpo.
void limparEnter(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}





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
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Implementado.
