#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SALAS 6
#define PRECO_CHAVE 5

typedef struct {
    char classe[20];
    int vida_max;
    int vida_atual;
    int ATK;
    int DEF;
    int PER;
    int mana_max;
    int mana_atual;
    int ouro;
    int quant_chaves;
    int ataca_longa_dist;
    int dacio_sword;
} Player;

typedef struct {
    char sala_nome[50];
    int numero;
    int possui_inimigo;
    int quantidade_inimigos;
    int possui_recompensa;
    int possui_armadilha;
    int possui_bau;
    int bau_aberto;
    int eh_boss;
    int visitada;
} Sala;

typedef struct {
    Player player;
    Sala salas[MAX_SALAS];
    int sala_atual;
} Save;


// Limpar resto de entradas

void limpar_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


// Sistema de save

void salvar_jogo(Save *save) {
    FILE *arquivo = fopen("save.dat", "wb");

    if (arquivo == NULL) {
        printf("\nErro ao salvar o jogo!\n");
        return;
    }

    if (fwrite(save, sizeof(Save), 1, arquivo) != 1) {
        printf("\nErro ao gravar os dados!\n");
        fclose(arquivo);
        return;
    }

    fclose(arquivo);
}


int carregarJogo(Save *save) {
    FILE *arquivo = fopen("save.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhum save encontrado!\n");
        return 0;
    }

    if (fread(save, sizeof(Save), 1, arquivo) != 1) {
        printf("\nErro ao carregar os dados!\n");
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);

    if (save->sala_atual < 0 || save->sala_atual >= MAX_SALAS) {
        printf("\nSave invalido!\n");
        return 0;
    }

    printf("\nJogo carregado com sucesso!\n");

    return 1;
}


void escrever_lento(const char *texto, int atraso) {
    while (*texto) {
        printf("%c", *texto);
        fflush(stdout);
        Sleep(atraso);
        texto++;
    }
}


// Easter egg

void easter_egg(Player *player) {
    char codigo[20];

    printf("\nExiste algo estranho escrito na parede...\n");
    printf("Digite uma palavra: ");

    scanf("%19s", codigo);
    limpar_buffer();

    if (strcmp(codigo, "DACIO") == 0 && player->dacio_sword == 0) {
        player->dacio_sword = 1;

        printf("\n====================================\n");
        printf("       EASTER EGG DESCOBERTO!\n");
        printf("====================================\n");

        printf("Voce encontrou a DACIO SWORD!\n");
        printf("Sua arma recebeu +999 de dano!\n");

        player->ATK += 999;
    }
    else if (strcmp(codigo, "DACIO") == 0 && player->dacio_sword == 1) {
        printf("\nVoce ja possui a DACIO SWORD!\n");
    }
    else {
        printf("\nNada aconteceu...\n");
    }
}


// Primeira sala: introducao da masmorra

void primeira_sala(Save *save) {
    printf("\n========================================\n");
    printf("          A ENTRADA DA MASMORRA\n");
    printf("========================================\n\n");

    escrever_lento("Voce atravessa os enormes portoes de uma antiga masmorra...\n", 35);
    escrever_lento("O ar e pesado, e o silencio parece esconder algo.\n\n", 35);
    escrever_lento("Ao observar as paredes, voce percebe uma inscricao estranha.\n", 35);
    escrever_lento("Parece que alguem deixou uma mensagem escondida...\n\n", 35);

    easter_egg(&save->player);

    printf("\n----------------------------------------\n");

    escrever_lento("Depois de explorar a entrada, voce percebe uma passagem adiante.\n", 35);
    escrever_lento("O verdadeiro desafio comeca agora...\n", 35);

    printf("----------------------------------------\n");
}


// Selecao de classe

void selecionar_classe(Player *player) {
    int opcao;
    int escolhendo_classe = 1;

    while (escolhendo_classe == 1) {
        printf("\n=============================\n");

        escrever_lento("Selecione sua classe:\n", 20);
        escrever_lento("1 - Cavaleiro\n", 20);
        escrever_lento("2 - Mago\n", 20);
        escrever_lento("3 - Arqueira\n", 20);

        printf("=============================\n");
        printf("> ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");
            limpar_buffer();
            continue;
        }

        limpar_buffer();

        if (opcao == 1) {
            escrever_lento("Voce sera...\n", 150);
            escrever_lento("um Cavaleiro.\n", 50);

            strcpy(player->classe, "Cavaleiro");

            player->vida_max = 10;
            player->vida_atual = player->vida_max;
            player->ATK = 5;
            player->DEF = 3;
            player->PER = 0;
            player->mana_max = 0;
            player->mana_atual = player->mana_max;
            player->ouro = 0;
            player->quant_chaves = 0;
            player->ataca_longa_dist = 0;
            player->dacio_sword = 0;

            escolhendo_classe = 0;
        }
        else if (opcao == 2) {
            escrever_lento("Voce sera...\n", 150);
            escrever_lento("um Mago.\n", 50);

            strcpy(player->classe, "Mago");

            player->vida_max = 5;
            player->vida_atual = player->vida_max;
            player->ATK = 10;
            player->DEF = 0;
            player->PER = 1;
            player->mana_max = 10;
            player->mana_atual = player->mana_max;
            player->ouro = 0;
            player->quant_chaves = 0;
            player->ataca_longa_dist = 1;
            player->dacio_sword = 0;

            escolhendo_classe = 0;
        }
        else if (opcao == 3) {
            escrever_lento("Voce sera...\n", 150);
            escrever_lento("uma Arqueira.\n", 50);

            strcpy(player->classe, "Arqueira");

            player->vida_max = 8;
            player->vida_atual = player->vida_max;
            player->ATK = 3;
            player->DEF = 1;
            player->PER = 3;
            player->mana_max = 5;
            player->mana_atual = player->mana_max;
            player->ouro = 5;
            player->quant_chaves = 1;
            player->ataca_longa_dist = 1;
            player->dacio_sword = 0;

            escolhendo_classe = 0;
        }
        else {
            printf("\nOpcao invalida, tente novamente!\n");
        }
    }
}


// Atributor do jogador

void mostrar_status(Save *save) {
    escrever_lento("\n=============================\n", 10);
    escrever_lento("       STATUS DO JOGADOR\n", 50);
    escrever_lento("=============================\n", 10);

    printf("Classe: %s\n", save->player.classe);
    printf("Vida: %d/%d\n", save->player.vida_atual, save->player.vida_max);
    printf("ATK: %d\n", save->player.ATK);
    printf("DEF: %d\n", save->player.DEF);
    printf("PER: %d\n", save->player.PER);
    printf("Mana: %d/%d\n", save->player.mana_atual, save->player.mana_max);
    printf("Ouro: %d\n", save->player.ouro);
    printf("Chaves: %d\n", save->player.quant_chaves);

    printf("\nVoce atualmente esta na sala %d, chamada de %s\n",
        save->salas[save->sala_atual].numero,
        save->salas[save->sala_atual].sala_nome);
}


// Inicializar sala

void inicializar_sala(Sala *sala, int numero, char nome[]) {
    strcpy(sala->sala_nome, nome);

    sala->numero = numero;
    sala->possui_inimigo = 0;
    sala->quantidade_inimigos = 0;
    sala->possui_recompensa = 0;
    sala->possui_armadilha = 0;
    sala->possui_bau = 0;
    sala->bau_aberto = 0;
    sala->eh_boss = 0;
    sala->visitada = 0;
}


// Configuracao de Sala

void configurar_salas(Save *save) {
    inicializar_sala(&save->salas[0], 1, "Introducao");

    inicializar_sala(&save->salas[1], 2, "Primeiro Combate");
    save->salas[1].possui_inimigo = 1;
    save->salas[1].quantidade_inimigos = 1;
}


// Descricao das salas

void mostrar_sala(Save *save) {
    system("cls");

    switch (save->sala_atual) {
        case 0:
            primeira_sala(save);
            break;

        case 1:
            printf("\n========================================\n");
            printf("              PRIMEIRA SALA\n");
            printf("========================================\n\n");

            escrever_lento("Voce atravessa a passagem e chega a uma sala escura.\n", 35);
            escrever_lento("O chao esta coberto de poeira e restos de antigas batalhas.\n", 35);
            escrever_lento("Algo parece estar se movimentando nas sombras...\n\n", 35);
            escrever_lento("Prepare-se. Voce nao esta sozinho aqui.\n", 35);
            break;
    }

    save->salas[save->sala_atual].visitada = 1;
    salvar_jogo(save);
}


// Passagem de Sala

void executar_jogo(Save *save) {
    int continuar = 1;

    while (continuar == 1) {
        mostrar_sala(save);

        printf("\n----------------------------------------\n");

        if (save->sala_atual == MAX_SALAS - 1) {
            printf("\nVoce chegou ao final desta parte da masmorra!\n");
            printf("O primeiro combate espera por voce...\n");

            printf("\nPressione ENTER para encerrar...");
            getchar();

            continuar = 0;
        }
        else {
            printf("\nPressione ENTER para avancar para a proxima sala...");
            getchar();

            save->sala_atual++;

            salvar_jogo(save);
        }
    }
}


// Menu

void menu_principal() {
    escrever_lento("Bem vindo, aventureiro...\n", 100);

    escrever_lento("\n=============================\n", 10);
    escrever_lento("       MENU PRINCIPAL\n", 50);
    escrever_lento("=============================\n", 10);

    escrever_lento("1 - Novo jogo\n", 50);
    escrever_lento("2 - Carregar jogo\n", 50);
    escrever_lento("3 - Sair\n", 50);

    printf("\n> ");
}


// Main

int main() {
    Save save = {0};

    int opcao;
    int rodando = 1;

    while (rodando == 1) {
        menu_principal();

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");
            limpar_buffer();
            continue;
        }

        limpar_buffer();

        switch (opcao) {
            case 1:
                configurar_salas(&save);

                selecionar_classe(&save.player);

                save.sala_atual = 0;

                system("cls");

                mostrar_status(&save);

                printf("\n\nPressione ENTER para iniciar a masmorra...");
                getchar();

                executar_jogo(&save);

                rodando = 0;
                break;

            case 2:
                if (carregarJogo(&save) == 0) {
                    printf("\nNao foi possivel carregar o jogo.\n");
                    printf("Pressione ENTER para voltar ao menu...");
                    getchar();
                }
                else {
                    system("cls");

                    mostrar_status(&save);

                    printf("\n\nPressione ENTER para continuar...");
                    getchar();

                    executar_jogo(&save);

                    rodando = 0;
                }
                break;

            case 3:
                printf("\nAte a proxima, aventureiro!\n");
                return 0;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
