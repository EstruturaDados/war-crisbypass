// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

//**** Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria. ****

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

//**** Funções de setup e gerenciamento de memória ****

/// @brief Aloca dinamicamente a memória para o vetor de territórios usando calloc.
/// @param num_territorios Número de territórios para alocar em memória.
/// @return Ponteiro para o vetor de territórios em caso de sucesso, ou NULL em caso de falha.
Territorio *alocarMapa(int num_territorios)
{
    Territorio *vetor = calloc(num_territorios, sizeof(Territorio));

    if (vetor == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    return vetor;
}

/// @brief Libera a memória previamente alocada para o mapa usando free.
/// @param territorios Ponteiro para o vetor de territorios.
void liberarMemoria(Territorio *territorios)
{
    free(territorios);
}

// **** Funções de interface com o usuário: ****

/// @brief Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
/// Esta função modifica o mapa passado por referência (ponteiro).
/// @param mapa Ponteiro para o vetor de territorios.
/// @param n Número de territórios para alocar.
void cadastrarTerritorios(Territorio *mapa, int n)
{
    printf("\n=== Cadastro dos Territórios ===\n");    

    for (int i = 0; i < n; i++)
    {
        // printf("\nTerritório %d:\n", i + 1);
        // printf("Nome: ");
        // scanf(" %[^\n]", mapa[i].nome);
        // printf("Cor do exército: ");
        // scanf(" %[^\n]", mapa[i].cor);
        // printf("Número de tropas: ");
        // scanf("%d", &mapa[i].tropas);

        printf("Território %d\n", i + 1);        

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

/// @brief Função para exibir os territórios.
/// @param mapa Ponteiro para o vetor de territorios.
/// @param n Número de territórios a serem alocados.
void exibirTerritorios(Territorio *mapa, int n)
{
    printf("\n=== Estado Atual dos Territórios ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// **** Funções de lógica principal do jogo: ****

/// @brief Função de ataque entre territórios.
/// @param atacante Ponteiro representando o território atacante.
/// @param defensor Ponteiro representando o território defensor.
void atacar(Territorio *atacante, Territorio *defensor)
{

    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\nErro: Você não pode atacar um território da mesma cor.\n");
        return;
    }

    if (atacante->tropas < 2)
    {
        printf("\nErro: O território atacante precisa de pelo menos 2 tropas para atacar.\n");
        return;
    }

    // Simula a rolagem dos dados (1 a 6). Vamos evitar o retorno do valor zero.
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDados rolados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        printf("\nVitória do atacante!\n");
        // Metade das tropas do atacante se movem para o território conquistado
        int tropasTransferidas = atacante->tropas / 2;

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        printf("O território %s agora pertence a %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
    }
    else
    {
        printf("\nDefesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}


// **** Função Principal (main). Ponto de entrada do programa. ****
// Orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main()
{
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

    // Territorio* territorios = allocarMapa();
    // int totalTerritorios = 0;
    // bool finalizar = false;

    srand(time(NULL)); // Garante aleatoriedade nos dados

    int num_territorios;
    printf("Digite o número de territórios a cadastrar: ");
    scanf("%d", &num_territorios);
    limparBufferEntrada();

    // Alocação dinâmica de memória para os territórios
    Territorio *mapa = alocarMapa(num_territorios); // (Territorio*) malloc(num_territorios * sizeof(Territorio));

    if (mapa == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return EXIT_FAILURE;
    }

    cadastrarTerritorios(mapa, num_territorios);

    char continuar;
    do
    {
        exibirTerritorios(mapa, num_territorios);

        int idAtacante, idDefensor;

        printf("\nEscolha o território atacante (ID): ");
        scanf("%d", &idAtacante);
        printf("Escolha o território defensor (ID): ");
        scanf("%d", &idDefensor);
        getchar(); // Limpa o \n após scanf

        if (idAtacante + 1 < 1 || idAtacante >= num_territorios || idDefensor + 1 < 1 || idDefensor >= num_territorios)
        {
            printf("IDs inválidos. Tente novamente.\n");
            continue;
        }

        atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);

        exibirTerritorios(mapa, num_territorios);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        continuar = getchar();
        limparBufferEntrada();
        //getchar(); // Consumir o \n

    } while (continuar == 's' || continuar == 'S');

    return EXIT_SUCCESS;
}

// --- Implementação das Funções ---

// alocarMapa():
// Implementado.

// Função para cadastrar territórios
// cadastrarTerritorios()
// Implementado.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

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
