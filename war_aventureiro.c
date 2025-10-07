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
/// @param numTerritorios Número de territórios para alocar em memória.
/// @return Ponteiro para o vetor de territórios, em caso de sucesso. Ou NULL, em caso de falha.
Territorio *alocarMapa(int numTerritorios)
{
    // calloc converte implicitamente para qualquer outro tipo de ponteiro. Portanto, o cast aqui é opcional.
    // Mas não foi estabelecida nenhuma convenção para o uso. Por isso, foi mantido.

    Territorio *vetor = (Territorio *)calloc(numTerritorios, sizeof(Territorio));

    if (vetor == NULL)
    {
        printf(" ❌  Erro ao alocar memória para o mapa.\n");
        return NULL;
    }

    return vetor;
}

/// @brief Libera a memória previamente alocada para o mapa usando free.
/// @param mapa Ponteiro para o vetor de territorios.
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
    printf("\nA memória alocada foi liberada com sucesso.\n");
}

// **** Funções de interface com o usuário: ****

/// @brief Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
/// Esta função modifica o mapa passado por referência (ponteiro).
/// @param mapa Ponteiro para o vetor de territorios.
/// @param numTerritorios Número de territórios alocados.
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

/// @brief Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
/// @param mapa Ponteiro para o vetor de territórios. Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
/// @param tamanho Número representando o tamanho do vetor.
void exibirMapa(Territorio *mapa, int tamanho)
{
    printf("\n=== 🌍  MAPA DO MUNDO - ESTADO ATUAL ===\n\n");
    // Evitar mostrar o número do exército baseado no índice zero.
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] %s | Exército Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
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
        printf("\n ⚠️  Aviso: Você não pode atacar um território da mesma cor.\n");
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
    printf("\n ⚔️  Ataque de %s (%d) contra %s (%d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("\n 🎲  Rolagem da dados: atacante => %d | defensor => %d\n", dadoAtacante, dadoDefensor);

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

            printf("O território %s agora pertence a %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
        }
    }
    else
    {
        // Caso contrário, a defesa é favorecida.
        printf("\n 🛡️  Defesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
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
        printf("\n ❌  Erro ao alocar memória.\n");
        return EXIT_FAILURE;
    }

    cadastrarTerritorios(mapa, numTerritorios);

    char continuar;

    do
    {
        int idAtacante, idDefensor;

        printf("\n=== FASE DE ATAQUE ===\n");

        printf("\n ⚔️  Escolha o território atacante [ID] de %d a %d, ou 0 para sair: ", 1, numTerritorios);
        scanf("%d", &idAtacante);
        limparBufferEntrada();

        printf("\n 🛡️  Escolha o território defensor [ID] de %d a %d, ou 0 para sair: ", 1, numTerritorios);
        scanf("%d", &idDefensor);
        limparBufferEntrada();

        if (idAtacante > numTerritorios || idDefensor > numTerritorios)
        {
            printf(" ⚠️  IDs inválidos. Tente novamente.\n");
            continuar = 'S';
            continue;
        }
        else if (idAtacante < 1 || idDefensor < 1)
        {
            printf(" ❌  A ação foi cancelada.\n");
            break;
        }

        // Como o vetor é baseado em índice zero, precisamos informar a posição atual adequada.
        atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);

        exibirMapa(mapa, numTerritorios);

        printf("\n 🔁  Deseja realizar outro ataque? (s/n): ");
        continuar = getchar();
        limparBufferEntrada();

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);

    printf("\n====  Fim de jogo! ====\n");

    return EXIT_SUCCESS;
}

#pragma region Implementacao_das_Funcoes

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

#pragma endregion