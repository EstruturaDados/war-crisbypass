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

#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// **** Estrutura de Dados ****

/// @brief Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
/// Criação da struct: definir uma struct chamada Territorio com os campos char nome[30], char cor[10] e int tropas.
struct Territorio
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// **** Protótipos das Funções ****

//**** Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria. ****

//**** Funções de setup e gerenciamento de memória ****

// Não implementado nesse desafio.

// **** Funções de interface com o usuário: ****

// Não implementado nesse desafio.

// **** Funções de lógica principal do jogo: ****

// Não implementado nesse desafio.

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

    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    printf("==============================\n");
    printf(" ==========💣 WAR 💣=========\n");
    printf("==============================\n");

    do
    {
        opcao = -1; // Vamos evitar reter o cache anterior do valor, para recuperar a alteração da opção pelo usuário.
        
        printf("\n1 - Cadastrar novos territorios. \n");
        printf("2 - Listar todos os territorios. \n");
        printf("0 - Sair. \n");
        printf("Escolha uma opção: ");

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
                limparEnter(territorios[totalTerritorios].nome);

                printf("Digite a Cor do Territorio: \n");
                fgets(territorios[totalTerritorios].cor, TAM_COR, stdin);
                limparEnter(territorios[totalTerritorios].cor);

                printf("Digite o Número de Tropas do Territorio: \n");
                scanf("%d", &territorios[totalTerritorios].tropas);
                limparBufferEntrada();

                totalTerritorios++;

                printf("\n=== Território cadastrado com sucesso. === \n");
            }
            else
            {
                printf("\n=== O número limite de Territórios foi atingido. === \n");
            }

            break;

        case 2:
            // Listagem de territorios
            printf("\n=== Listagem de Territórios cadastrados. === \n");

            if (totalTerritorios == 0)
            {
                printf("\n=== Nenhum Território foi cadastrado ainda. === \n");
            }
            else
            {
                for (int i = 0; i < totalTerritorios; i++)
                {
                    printf("======================================== \n");
                    printf("TERRITORIO %d\n", i + 1); // Vamos evitar exibir o item baseado no índice zero.
                    printf("Nome: %s\n", territorios[i].nome);
                    printf("Dominado por: Exercito %s\n", territorios[i].cor);
                    printf("Número de Tropas: %d\n", territorios[i].tropas);
                }
                printf("======================================== \n");
            }

            break;

        case 0:
            // Sair.
            printf("\n=== Saindo do sistema. Operação encerrada. === \n");
            break;

        default:
            // Continua.
            printf("\n=== Opção inválida. === \n");
            printf("\n=== Pressione Enter para continuar. === \n");
            limparBufferEntrada();
            break;
        }

    } while (opcao != 0);

    return EXIT_SUCCESS;
}

#pragma region Implementacao_das_Funcoes

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
// Implementado neste desafio.

#pragma endregion