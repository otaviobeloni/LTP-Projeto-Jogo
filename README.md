# Overtale

## 1. Descrição do Sistema
O projeto consiste em um video game, do gênero RPG (Role Playing Game) e *Dungeon crawler*. No game, o jogador escolherá entre três classes jogáveis, O Guerreiro, O Mago e A Arqueira; cada um com acesso a
ataques, habilidades e itens diferentes, além de favorecerem um estilo de jogo único. A gameplay se baseia no jogador controlar seu personagem através de salas, contendo inimigos e possívelmente recompensas para o
personagem, até chegar na sala final contento o Chefão (Boss), o inimigo final do jogo. O game utilizará arquivos de save em binário, para restaurar o estado do jogo e permitir que o jogador salve seu progresso em pontos específicos, e estruturas de dados para guardar informações sobre o personagem do Jogador e NPCs (Non Playable Characters).


---

## 2. Fluxo de Utilização Esperado para o Sistema

  1. **Menu inicial**

      *Ao iniciar o programa (Overtale) o usuário irá se deparar com um simples menu onde poderá escolher entre:*
     
      - `1.` **Iniciar Jogo**
      - `2.` **Sair** *(Encerra a execução do programa).*
      
  3. **Escolha de classes**

      *Caso o usuário escolha iniciar o jogo o sistema apresentará um menu de classes, contendo:*
     
      - `1.` **Guerreiro**
      - `2.` **Mago**    
      - `3.` **Arqueiro**
        
     *(A escolha de classes determinará os status do jogador, como a Vida, Mana, Ataque e Defesa).*

  4. **Jogabilidade**
     
     *Depois da escolha de classes o jogo será introduzido ao usuário*
      ```Markdonw
      IDEIA PRINCIPAL:
      o jogo que iremos desenvolver em C, será um RPG de turnos, dividido em salas,
      onde o jogador (usuário) enfrentará inimigos, cada um com status diferentes, por exemplo:
      (Vida, Defesa e Ataque) esses status serão atribuídos de acordo com o tipo de inimigo (Zumbi, Esqueleto, etc...)
      e de acordo com o nível atribuído a eles. Para cada inimigo derrotado o usuário tem uma chance de dropar algum item,
      sendo eles: (Poções, Buff de ataque, etc...), itens esses que poderão ajudar na jornada ao longo do jogo, até o chefão final.
      ```
      ```Markdonw
      COMO IRÁ FUNCIONAR:
      Ao entrar no jogo o usuário irá se deparar com a sala inicial, representada com um mapa ASCII, e com o seu primeiro inimigo,
      Nessa sala, o jogador terá 3 opções, sendo elas:
             1- Atacar
             2- Usar item (essa opção irá abrir um menu, contendo todos os itens e seus respectivos números e uma opção de voltar.)
             3- Recuar (essa opção faz o jogador recuperar bastante vida e esquivar de um golpe inimigo,
                porém é uma opção com baixa taxa de êxito e só deve ser utilizada em ultimos casos).  
           
      Como o jogo será um RPG de turnos, após a escolha do jogador, o inimigo irá atacar o mesmo, porém, caso o jogador derrote o oponente,
      o usuário avançará de sala. Esse processo vai se repetir ao longo de todo o jogo até a fase do boss (fase final), ao menos que a vida do
      jogador chegue em zero, que caso aconteça uma tela de GAME OVER será apresentada, porém caso o usuário chegue até o final e consiga derrotar
      o boss uma tela vitória irá aparecer, parabenizando o jogador e assim encerrando o jogo
      ```

---

## 3. Fluxograma da Lógica do Sistema
<img width="890" height="935" alt="Fluxograma (Overtale RPG) " src="https://github.com/user-attachments/assets/a13ad353-8c79-40c8-a6bd-99de773fe683" />



---

## 4. Estrutura de Dados

O sistema utilizará estruturas de dados heterogêneas (`struct`) para organizar as informações dos principais elementos do jogo. As estruturas serão utilizadas para representar o personagem do jogador, os inimigos, os itens e as salas presentes na dungeon.

### 4.1 Estrutura do Jogador

A estrutura `Jogador` será responsável por armazenar as informações referentes ao personagem controlado pelo usuário.

```c
typedef struct {
    char nome[50];
    char classe[20];
    int vida;
    int mana;
    int ataque;
    int defesa;
    int nivel;
    int experiencia;
    int ouro;
} Jogador;
```

Os principais dados armazenados serão:

* `nome`: nome escolhido para o personagem;
* `classe`: classe escolhida pelo jogador, podendo ser Guerreiro, Mago ou Arqueiro;
* `vida`: quantidade de pontos de vida do personagem;
* `mana`: quantidade de mana disponível para utilizar habilidades;
* `ataque`: poder de ataque do personagem;
* `defesa`: capacidade de defesa contra ataques dos inimigos;
* `nivel`: nível atual do personagem;
* `experiencia`: quantidade de experiência acumulada;
* `ouro`: quantidade de ouro obtida durante o jogo.

### 4.2 Estrutura dos Inimigos

A estrutura `Inimigo` será utilizada para armazenar as informações dos inimigos encontrados durante a exploração das salas.

```c
typedef struct {
    char nome[50];
    int nivel;
    int vida;
    int ataque;
    int defesa;
    int experiencia;
} Inimigo;
```

Os principais dados armazenados serão:

* `nome`: nome ou tipo do inimigo, como Zumbi ou Esqueleto;
* `nivel`: nível do inimigo;
* `vida`: quantidade de pontos de vida;
* `ataque`: poder de ataque do inimigo;
* `defesa`: capacidade de defesa;
* `experiencia`: quantidade de experiência recebida pelo jogador ao derrotá-lo.

O Boss utilizará a mesma estrutura `Inimigo`, porém possuirá atributos maiores, como maior quantidade de vida, ataque e defesa.

### 4.3 Estrutura dos Itens

A estrutura `Item` será utilizada para armazenar as informações dos itens encontrados ou obtidos durante o jogo.

```c
typedef struct {
    char nome[50];
    char tipo[30];
    int efeito;
    int quantidade;
} Item;
```

Os principais dados armazenados serão:

* `nome`: nome do item;
* `tipo`: função ou categoria do item, como recuperação de vida ou aumento de ataque;
* `efeito`: valor do efeito causado pelo item;
* `quantidade`: quantidade disponível daquele item.

Entre os possíveis itens estarão poções e itens capazes de aumentar o ataque do jogador.

### 4.4 Estrutura das Salas

A estrutura `Sala` será utilizada para representar as salas presentes na dungeon e suas características.

```c
typedef struct {
    int numero;
    int possui_inimigo;
    int possui_recompensa;
    int eh_boss;
} Sala;
```

Os principais dados armazenados serão:

* `numero`: número ou identificação da sala;
* `possui_inimigo`: indica se existe um inimigo na sala;
* `possui_recompensa`: indica se a sala possui alguma recompensa;
* `eh_boss`: indica se a sala é a sala final onde ocorrerá a batalha contra o Boss.

Dessa forma, as estruturas de dados permitirão organizar as informações necessárias para o funcionamento do jogo, incluindo o personagem do jogador, os inimigos, os itens, as salas, os combates e a progressão dentro da dungeon.


```c
