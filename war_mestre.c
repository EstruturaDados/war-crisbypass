#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura dos territórios
typedef struct {
    char nome[30];
    char cor[10]; // Ex: "vermelha", "azul"
    int tropas;
} Territorio;

// Prototipação das funções
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirMapa(Territorio* mapa, int tamanho);
void liberarMemoria(char* missao, Territorio* mapa);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // 1. Criar vetor de missões
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar dois territorios com mais de 5 tropas",
        "Ter pelo menos um territorio de cada cor",
        "Reduzir as tropas inimigas a menos de 3 por territorio"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // 2. Atribuir missão ao jogador (armazenar dinamicamente)
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para a missão.\n");
        return 1;
    }
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador); // Exibe só uma vez no início

    // 3. Criar um "mapa" com 4 territórios para teste
    int numTerritorios = 4;
    Territorio* mapa = (Territorio*) malloc(numTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
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

    // Loop de turnos simulados
    int turnos = 5;
    for (int i = 0; i < turnos; i++) {
        printf("\n===== Turno %d =====\n", i+1);
        exibirMapa(mapa, numTerritorios);

        // Simular ataque entre dois territórios
        atacar(&mapa[0], &mapa[1]); // Exemplo fixo: azul ataca vermelho

        // Verificar se missão foi cumprida
        if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
            printf("\n🎉 Missão cumprida! Jogador vence o jogo!\n");
            break;
        }
    }

    liberarMemoria(missaoJogador, mapa);
    return 0;
}

// Atribui missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão ao jogador
void exibirMissao(char* missao) {
    printf("🔍 Sua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo: verificar se todos os territórios vermelhos têm menos de 3 tropas
    if (strcmp(missao, "Reduzir as tropas inimigas a menos de 3 por territorio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas >= 3)
                return 0;
        }
        return 1;
    }

    // Exemplo: controlar dois territórios com mais de 5 tropas
    if (strcmp(missao, "Controlar dois territorios com mais de 5 tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
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
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("🌍 Estado atual do mapa:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s [%s] - Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("⚠️ Não é possível atacar um território aliado!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("⚔️ Ataque de %s (%d) contra %s (%d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("🎲 Rolagem: atacante=%d | defensor=%d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("🏆 Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("🛡️ Defesa bem-sucedida. Atacante perde 1 tropa.\n");
        if (atacante->tropas > 1)
            atacante->tropas -= 1;
    }
}

// Libera toda memória alocada dinamicamente
void liberarMemoria(char* missao, Territorio* mapa) {
    free(missao);
    free(mapa);
}
