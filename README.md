# Overtale

## 1. Descrição do Sistema

O projeto consiste no desenvolvimento de um jogo eletrônico do gênero RPG (*Role-Playing Game*) e *Dungeon Crawler*, utilizando a linguagem de programação C.

No jogo, o jogador poderá escolher entre três classes jogáveis: **Cavaleiro, Mago e Arqueira**. Cada classe possui atributos próprios, como pontos de vida, ataque, defesa, percepção e mana, proporcionando características diferentes durante a aventura.

A jogabilidade é baseada na exploração de uma masmorra dividida em salas. Durante o percurso, o jogador encontrará inimigos com diferentes atributos e enfrentará combates por turnos até chegar à sala final, onde estará o chefe (*Boss*).

O sistema também conta com uma loja, um baú que pode ser aberto utilizando chaves, equipamentos específicos para cada classe e um sistema de salvamento em arquivos binários, permitindo registrar e recuperar o progresso do jogador em pontos específicos da aventura.

Além disso, o projeto possui um sistema de inventário com poções de vida e mana, permitindo que o jogador recupere esses recursos durante sua jornada.

---

## 2. Fluxo de Utilização Esperado para o Sistema

### 2.1 Menu principal

Ao iniciar o programa, o usuário encontrará um menu principal com as seguintes opções:

- `1.` **Novo jogo** — inicia uma nova aventura.
- `2.` **Carregar jogo** — recupera um progresso salvo anteriormente.
- `3.` **Sair** — encerra a execução do programa.

### 2.2 Escolha de classe

Ao iniciar um novo jogo, o sistema apresentará um menu para a escolha da classe do personagem:

- `1.` **Cavaleiro**
- `2.` **Mago**
- `3.` **Arqueira**

A classe escolhida determinará os atributos iniciais do jogador, como vida, ataque, defesa, percepção e mana.

### 2.3 Jogabilidade

Após a escolha da classe, o jogador será apresentado à introdução da masmorra e poderá iniciar sua exploração.

O jogo é dividido em seis salas, cada uma com características e eventos específicos:

1. **Introdução:** apresenta a entrada da masmorra.
2. **Primeiro Combate:** sala onde o jogador enfrenta um Esqueleto.
3. **Sala da Armadilha:** apresenta um ambiente com possíveis perigos e um confronto contra um Goblin.
4. **Loja e Baú:** permite comprar chaves utilizando ouro e abrir um baú para obter um equipamento específico da classe escolhida.
5. **Combate Duplo:** sala que contém dois confrontos contra inimigos.
6. **Chefe da Masmorra:** sala final, onde acontece o confronto contra o Boss.

### 2.4 Sistema de combate

Os combates acontecem por turnos. Durante o confronto, o jogador poderá escolher uma ação disponível no sistema.

O ataque utiliza um cálculo de dano com variação aleatória, podendo ocorrer também um acerto crítico, que dobra o dano causado.

O inimigo realiza seu ataque após a ação ofensiva do jogador, desde que ainda esteja vivo.

Caso os pontos de vida do jogador cheguem a zero, será apresentada uma tela de **GAME OVER**, oferecendo a possibilidade de carregar o último salvamento ou sair do jogo.

### 2.5 Inventário e poções

O sistema de inventário permite que o jogador acompanhe e utilize os itens disponíveis durante a aventura.

Entre os itens estão:

- **Poção de vida:** recupera pontos de vida do personagem.
- **Poção de mana:** recupera pontos de mana do personagem.

A utilização das poções respeita a quantidade disponível no inventário e os limites máximos de vida e mana da classe escolhida.

### 2.6 Sistema de salvamento

O jogo utiliza arquivos binários para armazenar o estado atual da partida.

O salvamento registra informações do jogador, das salas e da sala atual. O sistema cria checkpoints antes da execução dos eventos de cada sala, permitindo que o jogador recupere seu progresso caso seja derrotado.

---

## 3. Fluxograma da Lógica do Sistema

**[Fluxograma reservado para atualização pelo integrante responsável.]**

<img width="890" height="935" alt="Fluxograma (Overtale RPG)" src="https://github.com/user-attachments/assets/a13ad353-8c79-40c8-a6bd-99de773fe683" />

---

## 4. Estrutura de Dados

O sistema utiliza estruturas de dados heterogêneas (`struct`) para organizar as informações dos principais elementos do jogo, como o personagem do jogador, os inimigos, as salas e os dados de salvamento.

### 4.1 Estrutura do Jogador

A estrutura `Player` é responsável por armazenar as informações referentes ao personagem controlado pelo usuário.

```c
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
    int pocoes_vida;
    int pocoes_mana;
} Player;
```

Os principais dados armazenados são:

- `classe`: classe escolhida pelo jogador, podendo ser Cavaleiro, Mago ou Arqueira;
- `vida_max` e `vida_atual`: quantidade máxima e atual de pontos de vida;
- `ATK`: poder de ataque do personagem;
- `DEF`: capacidade de defesa contra ataques dos inimigos;
- `PER`: atributo de percepção do personagem;
- `mana_max` e `mana_atual`: quantidade máxima e atual de mana;
- `ouro`: quantidade de ouro obtida durante o jogo;
- `quant_chaves`: quantidade de chaves carregadas pelo jogador;
- `ataca_longa_dist`: indica se a classe possui capacidade de realizar ataques à longa distância;
- `pocoes_vida`: quantidade de poções de vida disponíveis;
- `pocoes_mana`: quantidade de poções de mana disponíveis.

### 4.2 Estrutura dos Inimigos

A estrutura `Inimigo` armazena as informações dos inimigos encontrados durante a exploração das salas.

```c
typedef struct {
    char inmg[20];
    int vida_max_inmg;
    int vida_atual_inmg;
    int ATK_inmg;
} Inimigo;
```

Os principais dados armazenados são:

- `inmg`: nome ou identificação do inimigo, como Esqueleto, Goblin, Zumbi ou Boss;
- `vida_max_inmg`: quantidade máxima de pontos de vida do inimigo;
- `vida_atual_inmg`: quantidade atual de pontos de vida;
- `ATK_inmg`: poder de ataque do inimigo.

Cada tipo de inimigo possui atributos próprios, definidos durante sua inicialização.

### 4.3 Estrutura das Salas

A estrutura `Sala` representa as salas presentes na masmorra e suas respectivas características.

```c
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
```

Os principais dados armazenados são:

- `sala_nome`: nome da sala;
- `numero`: identificação numérica da sala;
- `possui_inimigo`: indica se existe algum inimigo na sala;
- `quantidade_inimigos`: quantidade de inimigos presentes;
- `possui_recompensa`: indica se a sala possui uma recompensa;
- `possui_armadilha`: indica se a sala possui uma armadilha;
- `possui_bau`: indica se a sala possui um baú;
- `bau_aberto`: indica se o baú já foi aberto;
- `eh_boss`: identifica se a sala corresponde à batalha contra o chefe;
- `visitada`: indica se o jogador já visitou a sala.

### 4.4 Estrutura de Salvamento

A estrutura `Save` reúne as informações necessárias para armazenar o progresso da partida.

```c
typedef struct {
    Player player;
    Sala salas[MAX_SALAS];
    int sala_atual;
} Save;
```

Os dados armazenados são:

- `player`: estrutura que contém os atributos e o inventário do jogador;
- `salas`: vetor que armazena as informações das seis salas da masmorra;
- `sala_atual`: identifica a sala em que o jogador se encontra.

Dessa forma, as estruturas de dados permitem organizar as informações necessárias para o funcionamento do jogo, facilitando a implementação dos sistemas de combate, inventário, exploração, loja e salvamento do progresso.
