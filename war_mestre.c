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

/// @brief Sorteia e atribui uma missão aleatória para o jogador.
/// @param destino Ponteiro referenciando o buffer a ser inicializado e populado, com o conteúdo da missão do jogador.
/// @param missoes Vetor contendo textos(strings), representando as missões.
/// @param totalMissoes Número de missões(elementos do vetor), para definição do intervalo de geração de números randômicos.
void atribuirMissao(char **destino, char *missoes[], int totalMissoes);

/// @brief Verifica se o jogador cumpriu os requisitos de sua missão atual.
/// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
/// @param missao Missão atual com conteúdo alocado.
/// @param mapa Vetor de territórios, atualmente representando o mapa.
/// @param tamanho Tamanho do vetor em questão.
/// @return Retorna 1 (verdadeiro) se a missão foi cumprida. E 0 (falso), caso contrário.
int verificarMissao(char *missao, Territorio *mapa, int tamanho);

/// @brief Exibe o conteúdo alocado, representando a missão atual do jogador.
/// @param missao Ponteiro com o conteúdo(string).
void exibirMissao(char *missao);

//**** Funções de setup e gerenciamento de memória ****

/// @brief Aloca dinamicamente a memória para o vetor de territórios usando malloc.
/// @param numTerritorios Número de territórios para alocar em memória.
/// @return Ponteiro para o vetor de territórios, em caso de sucesso. Ou NULL, em caso de falha.
Territorio *alocarMapa(int numTerritorios);

/// @brief Libera a memória previamente alocada para o mapa usando free.
/// @param mapa Ponteiro para o vetor de territorios.
/// @param missao Ponteiro para o vetor de caracteres(string) que representa a missão.
/// @param missoes Ponteiro para um vetor de ponteiros de caracteres, usado no sorteio da missão.
void liberarMemoria(Territorio *mapa, char *missao, char **missoes);

// **** Funções de interface com o usuário: ****

/// @brief Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
/// Esta função modifica o mapa passado por referência (ponteiro).
/// @param mapa Ponteiro para o vetor de territorios.
/// @param numTerritorios Número de territórios alocados.
void cadastrarTerritorios(Territorio *mapa, int numTerritorios);

/// @brief Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal();

/// @brief Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
/// @param mapa Ponteiro para o vetor de territórios. Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
/// @param tamanho Número representando o tamanho do vetor.
void exibirMapa(const Territorio *mapa, int tamanho);

// **** Funções de lógica principal do jogo: ****

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

/// @brief Função Principal (main). Ponto de entrada do programa.
/// Orquestra o fluxo do jogo, chamando as outras funções em ordem.
/// @return Número inteiro. Zero em caso de sucesso, Exemplo: EXIT_SUCCESS. Ou diferente de zero, em caso de falha, Exemplo: EXIT_FAILURE.
int main()
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios.

    // Criar vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Eliminar todas as tropas da cor azul",
        "Eliminar todas as tropas da cor amarela",
        "Eliminar todas as tropas da cor verde",
        "Controlar dois territorios com mais de 5 tropas",
        "Ter pelo menos um territorio de cada cor",
        "Reduzir as tropas inimigas a menos de 3 por territorio"};

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]); // Vamos usar um denominador com o mesmo tipo usado para o vetor.

    // Atribuir missão ao jogador e armazenar dinamicamente.

    char *missaoJogador = NULL; // Não podemos apontar para o char em si, mas sim para um vetor de char.

    atribuirMissao(&missaoJogador, missoes, totalMissoes);

    if (missaoJogador == NULL)
    {
        printf(" ❌  Erro ao alocar memória para a missão.\n");
        return EXIT_FAILURE;
    }

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

    char continuar;

    do
    {
        int opcao;

        exibirMenuPrincipal(&opcao);

        switch (opcao)
        {
        case 1:
            // Escolha de Ataque.
            int codigoRetorno;

            faseDeAtaque(&mapa, &codigoRetorno, numTerritorios);
            // Alguns tratamentos básicos.
            if (codigoRetorno = 1)
            {
                continuar = 'S';
                continue;
            }
            else if (codigoRetorno = 2)
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
            break;
        default:
            // Continua.
            printf("\n=== Opção inválida. === \n");
            break;
        }

        // Verificando se missão foi cumprida.
        if (verificarMissao(missaoJogador, mapa, numTerritorios))
        {
            printf("\n 🎉  Missão cumprida! Jogador vence o jogo!\n");
            break;
        }

        printf("\n 🔁  Deseja continuar? (s/n): ");
        continuar = getchar();
        limparBufferEntrada();

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador, missoes);

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
    printf(" 🔍  Sua missão: %s\n", missao);
}

int maiorQue(Territorio *t, int valor) { return t->tropas > (valor); }
int menorQue(Territorio *t, int valor) { return t->tropas < (valor); }

int verificarMissao(char *missao, Territorio *mapa, int tamanho)
{
    // Verificar cores específicas
    if (strstr(missao, "Eliminar todas as tropas da cor") != NULL)
    {
        const char *prefixo = "Eliminar todas as tropas da cor ";

        size_t tamanho_prefixo = strlen(prefixo);

        // Pega o que vem depois do prefixo. Vamos deslocar no tamanho do prefixo para extraírmos o sufixo.
        const char *cor = missao + tamanho_prefixo;
        // Aloca memória para a string da cor
        char *cor_extraida = malloc(strlen(cor) + 1);
        if (cor_extraida == NULL)
        {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        strcpy(cor_extraida, cor);

        int resultado;

        if (verificarTropaPorCor(cor_extraida, mapa, tamanho))
        {
            resultado = 1;
        }

        // Libera memória
        free(cor_extraida);

        return resultado;
    }

    // Verificações adicionais, relativas ao número de tropas.
    if (verificarPorCorExato(mapa, tamanho, menorQue, 3) ||
        verificarPorCorExato(mapa, tamanho, maiorQue, 5) ||
        verificarPorCorExato(mapa, tamanho, maiorQue, 2))
    {
        return 1;
    }

    return 0; // Missão não cumprida ainda.
}

int verificarTropaPorCor(const char *cor, Territorio *mapa, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        if (strcmp(mapa[i].cor, cor) == 0 && mapa[i].tropas > 0)
            return 0;
    return 1;
}

int verificarPorCorExato(Territorio *mapa, int tamanho, int (*criterio)(Territorio *, int valor), int valor)
{
    char **cores = NULL;
    int *validos = NULL;
    int *total = NULL;
    int numCores = 0;
    int resultado = 0;
    char *corResultado = NULL;

    for (int i = 0; i < tamanho; i++)
    {
        int j, encontrada = 0;
        for (j = 0; j < numCores; j++)
        {
            if (strcmp(mapa[i].cor, cores[j]) == 0)
            {
                total[j]++;
                if (criterio(&mapa[i], valor))
                    validos[j]++;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada)
        {
            cores = realloc(cores, (numCores + 1) * sizeof(char *));
            validos = realloc(validos, (numCores + 1) * sizeof(int));
            total = realloc(total, (numCores + 1) * sizeof(int));

            cores[numCores] = malloc(strlen(mapa[i].cor) + 1);
            strcpy(cores[numCores], mapa[i].cor);

            validos[numCores] = criterio(&mapa[i], valor) ? 1 : 0;
            total[numCores] = 1;
            j = numCores;
            numCores++;
        }
    }

    // Verifica se alguma cor tem todos seus territórios cumprindo o critério
    for (int i = 0; i < numCores; i++)
    {
        if (validos[i] == total[i])
        {
            resultado = 1;
            corResultado = cores[i];
            break;
        }
    }

    // Liberação única da memória
    for (int i = 0; i < numCores; i++)
    {
        free(cores[i]);
    }
    free(cores);
    free(validos);
    free(total);

    if (resultado)
    {
        printf("\nO exército da cor %s cumpriu o objetivo com sucesso!\n", corResultado);
    }

    return resultado;
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

void exibirMenuPrincipal()
{
    int opcao;
    // menu de acoes, 1 - atacar, 2 - verificar missao, 0 - sair
    printf("\n ==== Menu de Ações ==== \n");
    printf("\n1 - Atacar. \n");
    printf("2 - Verificar missão. \n");
    printf("0 - Sair. \n");
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    limparBufferEntrada();
}

void faseDeAtaque(Territorio *mapa, int *codigoRetorno, const int numTerritorios)
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
        *codigoRetorno = 1;
        return;
    }
    else if (idAtacante < 1 || idDefensor < 1)
    {
        printf(" ❌  A ação foi cancelada.\n");
        *codigoRetorno = 2;
        return;
    }

    // Como o vetor é baseado em índice zero, precisamos informar a posição atual adequada.
    atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);

    // Exibir mapa atual.
    exibirMapa(mapa, numTerritorios);
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

void liberarMemoria(Territorio *mapa, char *missao, char **missoes)
{
    free(mapa);
    free(missao);
    free(missoes);
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
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Implementado.

// sortearMissao():
// Implementado.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Implementado.