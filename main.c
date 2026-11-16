#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SALAS 20

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
} Player;

typedef struct {
	char sala_nome[50];
	int numero;
    int possui_inimigo;
    int possui_recompensa;
    int possui_armadilha;
    int eh_boss;
} Sala;

typedef struct {
	Player player;
	Sala salas[MAX_SALAS];
	
	int sala_atual;
} Save;

void salvar_jogo(Save *save)
{
    FILE *arquivo = fopen("save.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao salvar o jogo!\n");
        return;
    }

    if (fwrite(save, sizeof(Save), 1, arquivo) != 1)
    {
        printf("Erro ao gravar os dados!\n");
        fclose(arquivo);
        return;
    }

    fclose(arquivo);

    printf("Jogo salvo com sucesso!\n");
}


int carregarJogo(Save *save)
{
    FILE *arquivo = fopen("save.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Nenhum save encontrado!\n");
        return 0;
    }

    if (fread(save, sizeof(Save), 1, arquivo) != 1)
    {
        printf("Erro ao carregar os dados!\n");
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);

    printf("Jogo carregado com sucesso!\n");

    return 1;
}


void escrever_lento(const char *texto, int atraso)
{
    while (*texto)
    {
        printf("%c", *texto);
        fflush(stdout);
        Sleep(atraso);
        texto++;
    }
}

void selecionar_classe(Player *player) {
	
	int opcao, escolhendo_classe;
	
	printf("============================= \n");
	escrever_lento("Selecione sua classe: \n", 20);
	escrever_lento("1 - Cavaleiro \n", 20);
	escrever_lento("2 - Mago\n", 20);
	escrever_lento("3 - Arqueira\n", 20);
	printf("============================= \n");
	scanf("%d", &opcao);
	
	escolhendo_classe = 1;
	while(escolhendo_classe == 1) {
		if (opcao ==  1) {
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
			
			escolhendo_classe = 0;
		} else if (opcao ==  2) {
			strcpy(player->classe, "Mago");
			escrever_lento("Voce sera...\n", 150);
			escrever_lento("um Mago.\n", 50);
			player->vida_max = 5;
			player->vida_atual = player->vida_max;
			player->ATK = 10;
			player->DEF = 0;
			player->PER = 1;
			player->mana_max = 10;
			player->mana_atual = player->mana_max;
			player->quant_chaves = 0;
			player->ouro = 0;
			player->ataca_longa_dist = 1;
			
			escolhendo_classe = 0;
		} else if (opcao ==  3) {
			strcpy(player->classe, "Arqueira");
			escrever_lento("Voce sera...\n", 150);
			escrever_lento("uma Arqueira.\n", 50);;
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
			
			escolhendo_classe = 0;
		} else {
			printf("Opcao invalida, tente novamente \n");
			scanf("%d", &opcao);
		}
	}
}

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
    
    printf("\nVoce atualmente esta na sala %d, chamada de %s", save->sala_atual, save->salas[save->sala_atual].sala_nome);
}

void inicializar_sala(Sala *sala, int numero, char nome[]) {

    strcpy(sala->sala_nome, nome);

    sala->numero = numero;
    sala->possui_inimigo = 0;
    sala->possui_recompensa = 0;
    sala->possui_armadilha = 0;
    sala->eh_boss = 0;
}

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

int main(int argc, char *argv[]) {
    Save save;
    int opcao, rodando;

	Save save = {0}
    rodando = 1;

	menu_principal();
    scanf("%d", &opcao);


	while (rodando == 1) {
		switch(opcao) {
        case 1:
            selecionar_classe(&save.player);

		    // Inicializando a primeira sala
		    strcpy(save.salas[0].sala_nome, "A Primeira Sala");
		    save.salas[0].numero = 0;
		    save.salas[0].possui_inimigo = 0;
		    save.salas[0].possui_recompensa = 1;
		    save.salas[0].possui_armadilha = 0;
		    save.salas[0].eh_boss = 0;

		    // Definindo a sala atual
		    save.sala_atual = 0;
		
		    // Salvando todos os dados
		    salvar_jogo(&save);
		
		    mostrar_status(&save);
		    rodando = 0;
        break;

        case 2:
            if (carregarJogo(&save) == 0) {
                printf("Nao foi possivel carregar o jogo.\n");
                return 0;
            } else {
            	mostrar_status(&save);
            	rodando = 0;
			}
        break;

        case 3:
            printf("Ate a proxima, aventureiro!\n");
            rodando = 0;
            return 0;
        default:
            printf("Opcao invalida! Tente novamente\n");
        break;
    	}	
	}

    return 0;
}
