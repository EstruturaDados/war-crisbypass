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
#include <stdbool.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
// Criação da struct: definir uma struct chamada Territorio com os campos char nome[30], char cor[10] e int tropas
struct Territorio
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// Funções de lógica principal do jogo:
// Funções utilitárias:
// Limpa o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);    
}

// --- Função Principal (main). Ponto de entrada do programa. ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
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

    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    bool finalizar = false;

    do
    {
        int opcao;

        printf("==============================\n");
        printf("============= WAR ============\n");
        printf("1 - Cadastrar novos territorios. \n");
        printf("2 - Listar todos os territorios. \n");
        printf("0 - Sair. \n");
        printf("Escolha uma opção: \n");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
            // Cadastro de novo territorio
            printf("=== Cadastro de novo territorio === \n");

            if (totalTerritorios < MAX_TERRITORIOS)
            {
                printf("Digite o Nome do Territorio: \n");
                fgets(territorios[totalTerritorios].nome, TAM_NOME, stdin);

                printf("Digite a Cor do Territorio: \n");
                fgets(territorios[totalTerritorios].cor, TAM_COR, stdin);

                territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';
                territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

                printf("Digite o Número de Tropas do Territorio: \n");
                scanf("%d", &territorios[totalTerritorios].tropas);
                limparBufferEntrada();

                totalTerritorios++;

                printf("=== Território cadastrado com sucesso. === \n");
            }
            else
            {
                printf("=== O número limite de Territórios foi atingido. === \n");
            }

            break;
        case 2:
            // Listagem de territorios
            printf("=== Listagem de Territórios cadastrados. === \n");

            if (totalTerritorios == 0)
            {                
                printf("=== Nenhum Território foi cadastrado ainda. === \n");
            }
            else
            {
                for (int i = 0; i < totalTerritorios; i++)
                {
                    printf("======================================== \n");
                    printf("Nome: %s\n", territorios[i].nome);
                    printf("Cor: %s\n", territorios[i].cor);
                    printf("Número de Tropas: %d\n", territorios[i].tropas);
                }
                printf("======================================== \n");
            }

            break;

        case 0:
            finalizar = true;
            printf("=== Saindo do sistema. Operação encerrada. === \n");
            break;

        default:            
            printf("=== Opção inválida. === \n");
            printf("=== Pressione Enter para continuar. === \n");
            getchar();
            break;
        }

    } while (!finalizar);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

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
