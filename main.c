#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
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

// Struct Inimigos

typedef struct {
    char inmg[20];
    int vida_max_inmg;
    int vida_atual_inmg;
    int ATK_inmg;
} Inimigo;

// Qual inimigo

void tipoinimigo (Inimigo *inimigo, char nome_inmg[]){

    if (strcmp(nome_inmg, "Esqueleto") == 0){
        strcpy(inimigo->inmg, "Esqueleto");
        inimigo->vida_max_inmg = 20;
        inimigo->vida_atual_inmg = 20;
        inimigo->ATK_inmg = 5;
    }

    else if (strcmp(nome_inmg, "Goblin") == 0){
        strcpy(inimigo->inmg, "Goblin");
        inimigo->vida_max_inmg = 30;
        inimigo->vida_atual_inmg = 30;
        inimigo->ATK_inmg = 3;
    }

    else if (strcmp(nome_inmg, "Zumbi") == 0){
        strcpy(inimigo->inmg, "Zumbi");
        inimigo->vida_max_inmg = 50;
        inimigo->vida_atual_inmg = 50;
        inimigo->ATK_inmg = 7;
    }

    else if (strcmp(nome_inmg, "Boss") == 0){
        strcpy(inimigo->inmg, "Boss");
        inimigo->vida_max_inmg = 100;
        inimigo->vida_atual_inmg = 100;
        inimigo->ATK_inmg = 12;
    }
}

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

// Escrever lento

void escrever_lento(const char *formato, int atraso, ...) {

    char texto[500];
    int i;

    va_list args;

    va_start(args, atraso);

    vsnprintf(texto, sizeof(texto), formato, args);

    va_end(args);

    i = 0;

    while (texto[i] != '\0') {

        printf("%c", texto[i]);
        fflush(stdout);
        Sleep(atraso);

        i++;
    }
}

// Limpar resto de entradas

void limpar_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// Ataque player

void ataque_plyr (Player *player, Inimigo *inimigo){

	int dano = player->ATK;

	inimigo -> vida_atual_inmg -=dano;

	if(inimigo->vida_atual_inmg < 0){
		inimigo->vida_atual_inmg = 0;
	}

	printf("\n=============================\n");

    escrever_lento("Voce atacou o %s!\n",20 ,inimigo->inmg);
    escrever_lento("O dano causou %d pontos de ataque\n",20 ,dano);
    escrever_lento("Vida do inimigo: %d/%d\n",20
	,inimigo->vida_atual_inmg,
	inimigo->vida_max_inmg);

    printf("=============================\n");

}

// Ataque Inimigo

void ataque_inmg (Player *player, Inimigo *inimigo){

	int dano = inimigo->ATK_inmg - player->DEF;

	if (dano<0) dano = 0;

	player -> vida_atual -= dano;

	if(player->vida_atual < 0){
		player->vida_atual = 0;
	}

	printf("\n=============================\n");

    escrever_lento("O %s te atacou!\n",20 ,inimigo->inmg);
    escrever_lento("O dano causou %d pontos de ataque\n",20 ,dano);
    escrever_lento("Sua vida: %d/%d\n",20 
	,player->vida_atual,
	player->vida_max);
	escrever_lento("Sua defesa: %d",20 ,player->DEF);

    printf("=============================\n");

}

// Combate

void combate (Player *player, Inimigo *inimigo){

	int opcao;

	while(player->vida_atual > 0 && inimigo->vida_atual_inmg > 0){

		printf("\n========== COMBATE ==========\n");
        printf("1 - Atacar\n");
        printf("2 - Usar pocao\n");
        printf("=============================\n");
		printf("> ");
		if(scanf("%d", &opcao) != 1){

    		limpar_buffer();

    		printf("Digite uma opcao valida!\n");

    		continue;
		}

		limpar_buffer();

		switch(opcao){

			case 1:
				ataque_plyr(player, inimigo);

				if(inimigo->vida_atual_inmg > 0){
					ataque_inmg(player, inimigo);
				}
				break;

			case 2:
				// Função poção
				break;

			default:
				printf("Opcao Invalida!");
				break;
		}	
	}

	if(player->vida_atual <= 0){
		printf("\nVoce foi Derrotado!\n");
	}

	if(inimigo->vida_atual_inmg <= 0){
		printf("\nVoce derrotou o inimigo\n");
		printf("Voce ganhou 3 de ouro!");
		player->ouro+=3;
	}
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

        printf("\nVoce encontrou a DACIO SWORD!\n\n");

        printf(
            "             /\\\n"
            "            /  \\\n"
            "            |  |\n"
            "            |  |\n"
            "            |  |\n"
            "         ___|  |___\n"
            "            |  |\n"
            "            |  |\n"
            "            |__|\n\n"
        );

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


// Atributo do jogador

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

    inicializar_sala(&save->salas[2], 3, "Sala da Armadilha");
    save->salas[2].possui_inimigo = 1;
    save->salas[2].quantidade_inimigos = 1;
    save->salas[2].possui_armadilha = 1;

    inicializar_sala(&save->salas[3], 4, "Loja e Bau");
    save->salas[3].possui_bau = 1;

    inicializar_sala(&save->salas[4], 5, "Combate Duplo");
    save->salas[4].possui_inimigo = 1;
    save->salas[4].quantidade_inimigos = 2;

    inicializar_sala(&save->salas[5], 6, "Chefe da Masmorra");
    save->salas[5].possui_inimigo = 1;
    save->salas[5].quantidade_inimigos = 1;
    save->salas[5].eh_boss = 1;
}


// Loja e Bau

void loja_bau(Save *save) {
    int opcao;

    while (1) {
        printf("\n========================================\n");
        printf("                LOJA E BAU\n");
        printf("========================================\n");

        printf("\nOuro: %d", save->player.ouro);
        printf("\nChaves: %d\n", save->player.quant_chaves);

        printf("\n1 - Comprar uma chave (%d ouros)\n", PRECO_CHAVE);
        printf("2 - Abrir o bau\n");
        printf("3 - Sair da loja\n");

        printf("\n> ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");
            limpar_buffer();
            continue;
        }

        limpar_buffer();

        if (opcao == 1) {
            if (save->player.ouro >= PRECO_CHAVE) {
                save->player.ouro -= PRECO_CHAVE;
                save->player.quant_chaves++;

                printf("\nVoce comprou uma chave!\n");
            }
            else {
                printf("\nVoce nao possui ouro suficiente!\n");
            }
        }
        else if (opcao == 2) {
            if (save->salas[3].bau_aberto == 1) {
                printf("\nO bau ja foi aberto!\n");
            }
            else if (save->player.quant_chaves > 0) {
                save->player.quant_chaves--;
                save->salas[3].bau_aberto = 1;

                printf("\nVoce utilizou uma chave e abriu o bau!\n");
                printf("\nDentro do bau, voce encontrou um equipamento especial!\n");

                if (strcmp(save->player.classe, "Cavaleiro") == 0) {
                    printf("\nVoce encontrou uma ESPADA DE GUERRA!\n\n");

                    printf(
                        "             /\\\n"
                        "            /  \\\n"
                        "            |  |\n"
                        "            |  |\n"
                        "            |  |\n"
                        "         ___|  |___\n"
                        "            |  |\n"
                        "            |  |\n"
                        "            |__|\n\n"
                    );

                    printf("ATK +5\n");
                    save->player.ATK += 5;
                }
                else if (strcmp(save->player.classe, "Mago") == 0) {
                    printf("\nVoce encontrou um CAJADO DE DESTRUICAO!\n\n");

                    printf(
                        "              *\n"
                        "             /|\\\n"
                        "              |\n"
                        "              |\n"
                        "              |\n"
                        "              |\n"
                        "              |\n"
                        "             / \\\n\n"
                    );

                    printf("ATK +5\n");
                    save->player.ATK += 5;
                }
                else if (strcmp(save->player.classe, "Arqueira") == 0) {
                    printf("\nVoce encontrou um ARCO DE CACADA!\n\n");

                    printf(
                        "             ) | \n"
                        "            )  | \n"
                        "           )   | \n"
                        "            )  | \n"
                        "             ) | \n\n"
                    );

                    printf("ATK +5\n");
                    save->player.ATK += 5;
                }
            }
            else {
                printf("\nVoce precisa de uma chave para abrir o bau!\n");
            }
        }
        else if (opcao == 3) {
            printf("\nVoce deixou a loja para tras.\n");
            break;
        }
        else {
            printf("\nOpcao invalida!\n");
        }
    }
}


// Descricao das salas

void mostrar_sala(Save *save) {
    system("cls");

    switch (save->sala_atual) {
        case 0:
            primeira_sala(save);
            break;

        case 1:{

        	Inimigo inimigo;

            printf("\n========================================\n");
            printf("              PRIMEIRA SALA\n");
            printf("========================================\n\n");

            escrever_lento("Voce atravessa a passagem e chega a uma sala escura.\n", 35);
            escrever_lento("O chao esta coberto de poeira e restos de antigas batalhas.\n", 35);
            escrever_lento("Algo parece estar se movimentando nas sombras...\n\n", 35);
            escrever_lento("Prepare-se. Voce nao esta sozinho aqui.\n", 35);

            escrever_lento("\nUm goblin surge das sombras!\n", 35);

            tipoinimigo(&inimigo, "Goblin");
    		combate(&save->player, &inimigo);

            break;
		}	

        case 2:{
        	Inimigo inimigo;

            printf("\n========================================\n");
            printf("          SEGUNDA SALA\n");
            printf("========================================\n\n");

            escrever_lento("Apos deixar a primeira batalha para tras, voce encontra uma nova passagem.\n", 35);
            escrever_lento("Esta sala parece tranquila, mas ha algo estranho no ambiente.\n", 35);
            escrever_lento("O chao apresenta marcas e algumas partes parecem instaveis.\n\n", 35);
            escrever_lento("Tenha cuidado ao avancar...\n", 35);

            escrever_lento("\nUm esqueleto aparece diante de voce!\n", 35);

    		tipoinimigo(&inimigo, "Esqueleto");
    		combate(&save->player, &inimigo);

            break;
		}

        case 3:

            system("cls");

            printf("\n========================================\n");
            printf("                LOJA\n");
            printf("========================================\n\n");

            escrever_lento("Voce encontra uma sala diferente das anteriores.\n", 35);
            escrever_lento("Um comerciante misterioso parece estar esperando por voce.\n", 35);
            escrever_lento("Ao lado da loja, existe um bau antigo protegido por uma fechadura.\n\n", 35);
            escrever_lento("Talvez exista algo valioso guardado la dentro...\n", 35);

            loja_bau(save);

            break;

        case 4:{
        	Inimigo inimigo;

            printf("\n========================================\n");
            printf("             TERCEIRA SALA\n");
            printf("========================================\n\n");

            escrever_lento("Voce deixa a loja para tras e atravessa uma enorme porta de pedra.\n", 35);
            escrever_lento("Ao entrar, percebe que a sala e muito maior que as anteriores.\n", 35);
            escrever_lento("De repente, dois inimigos surgem diante de voce!\n\n", 35);
            escrever_lento("Prepare-se...\n", 35);

			tipoinimigo(&inimigo, "Zumbi");
			combate(&save->player, &inimigo);

			if (save->player.vida_atual > 0) {

    			escrever_lento("\n\nO zumbi cai ao chao, mas voce nao tem tempo para descansar...\n", 35);
    			escrever_lento("Um goblin surge das sombras, pronto para atacar!\n\n", 35);

    			tipoinimigo(&inimigo, "Goblin");
    			combate(&save->player, &inimigo);
			}

            break;
		}

        case 5:{
        	Inimigo inimigo;

            printf("\n========================================\n");
            printf("               ??? SALA ???\n");
            printf("========================================\n\n");

            escrever_lento("Apos derrotar os inimigos, voce encontra uma enorme porta.\n", 35);
            escrever_lento("Ao atravessa-la, chega a uma sala sombria e silenciosa.\n", 35);
            escrever_lento("No centro da sala, uma criatura gigantesca aguarda sua chegada.\n\n", 35);
            escrever_lento("O CHEFE DA MASMORRA despertou!\n", 50);
            escrever_lento("Prepare-se para a batalha final...\n", 50);

            tipoinimigo(&inimigo, "Boss");
    		combate(&save->player, &inimigo);

            if (save->player.vida_atual > 0 &&
                inimigo.vida_atual_inmg <= 0) {

                printf("\n");
                printf("========================================\n");

                escrever_lento(
                    "\nO silencio finalmente retorna a masmorra...\n", 45);

                escrever_lento(
                    "A criatura que aterrorizava aquele lugar foi derrotada.\n", 45);

                escrever_lento(
                    "Com suas ultimas forcas, voce observa os portoes se abrindo.\n", 45);

                escrever_lento(
                    "\nA luz do mundo exterior finalmente alcanca seus olhos.\n", 45);

                escrever_lento(
                    "\nVoce entrou naquela masmorra como um aventureiro...\n", 45);

                escrever_lento(
                    "E saiu como uma verdadeira lenda.\n", 70);

                printf("\n========================================\n");
                printf("          FIM DA AVENTURA\n");
                printf("========================================\n");
            }

            break;
    	}
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

            printf("\nSua jornada pela masmorra chegou ao fim.\n");

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
