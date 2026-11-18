# Overtale

## 1. Descrição do Sistema

O Overtale é um jogo eletrônico do gênero RPG (*Role-Playing Game*) e *Dungeon Crawler*, desenvolvido utilizando a linguagem de programação C.

O jogador poderá escolher entre três classes jogáveis: **Cavaleiro, Mago e Arqueira**. Cada classe possui atributos próprios, como pontos de vida, ataque, defesa, percepção e mana, proporcionando diferentes características durante a aventura.

A jogabilidade é baseada na exploração de uma masmorra dividida em seis salas. Durante o percurso, o jogador encontrará armadilhas, inimigos, uma loja e um baú com equipamentos específicos para cada classe. O objetivo é sobreviver aos desafios e derrotar o chefe final da masmorra.

O sistema também conta com um inventário de poções de vida e mana, gerenciamento de ouro e chaves, habilidades especiais e salvamento do progresso por meio de arquivos binários.

Ao derrotar o chefe final, o jogador recebe uma mensagem de vitória que representa o encerramento da jornada.

---

## 2. Fluxo de Utilização do Sistema

### 2.1 Menu Principal

Ao iniciar o programa, o usuário encontrará um menu principal com as seguintes opções:

- `1.` **Novo jogo** — inicia uma nova aventura.
- `2.` **Carregar jogo** — recupera um progresso salvo anteriormente.
- `3.` **Sair** — encerra a execução do programa.

### 2.2 Escolha de Classe

Ao iniciar um novo jogo, o sistema apresentará um menu para a escolha da classe do personagem:

- `1.` **Cavaleiro**
- `2.` **Mago**
- `3.` **Arqueira**

A classe escolhida determinará os atributos iniciais do jogador.

| Atributo | Cavaleiro | Mago | Arqueira |
|---|---:|---:|---:|
| Vida | 30 | 20 | 25 |
| Ataque | 5 | 20 | 3 |
| Defesa | 3 | 0 | 1 |
| Percepção | 0 | 1 | 3 |
| Mana | 10 | 10 | 5 |

Cada classe também possui recursos iniciais diferentes:

- **Cavaleiro:** 1 poção de vida e nenhuma poção de mana.
- **Mago:** 1 poção de vida e 1 poção de mana.
- **Arqueira:** 1 poção de vida, 1 poção de mana, 5 moedas de ouro e 1 chave.

### 2.3 Exploração da Masmorra

Após a escolha da classe, o jogador será apresentado à introdução da masmorra e poderá iniciar sua exploração.

O jogo é dividido em seis salas:

1. **Introdução:** apresenta a entrada da masmorra e permite descobrir um segredo escondido por meio de um Easter Egg.
2. **Primeiro Combate:** sala onde o jogador enfrenta um Esqueleto.
3. **Sala da Armadilha:** apresenta uma armadilha que pode ser evitada dependendo do atributo de percepção do personagem, além de um confronto contra um Goblin.
4. **Loja e Baú:** permite comprar itens utilizando ouro e abrir um baú com uma chave para obter um equipamento específico da classe escolhida.
5. **Combate Duplo:** sala onde o jogador enfrenta dois Goblins consecutivamente.
6. **Chefe da Masmorra:** sala final, onde acontece o confronto contra o Boss.

Durante a exploração, o jogador poderá utilizar os recursos adquiridos para aumentar suas chances de sobreviver aos desafios.

### 2.4 Sistema de Combate

Os combates acontecem por turnos. Durante os confrontos, o jogador poderá selecionar as ações disponíveis no menu de combate:

- Atacar o inimigo.
- Utilizar uma poção de vida.
- Utilizar uma poção de mana, quando disponível para a classe.
- Consultar o inventário.

O dano dos ataques normais é determinado pelo atributo de ataque (`ATK`) do personagem. A defesa (`DEF`) reduz o dano recebido dos inimigos, sem ser consumida após os ataques.

Cada classe possui uma habilidade especial:

- **Cavaleiro — Golpe Digno:** causa 10 pontos de dano, consome 5 pontos de mana e aumenta temporariamente a defesa em 1 ponto até o próximo ataque inimigo.
- **Mago — Raio Místico:** causa 20 pontos de dano e consome 5 pontos de mana.
- **Arqueira — Manto dos Caçadores:** aumenta temporariamente o ataque e a defesa em 3 pontos para o próximo ataque, consumindo 5 pontos de mana.

Caso o jogador não possua mana suficiente, a habilidade especial não será executada e o turno não será consumido.

O inimigo realiza seu ataque após uma ação ofensiva do jogador, desde que ainda esteja vivo. A utilização de poções e a consulta ao inventário não provocam um contra-ataque.

Caso os pontos de vida do jogador cheguem a zero, será apresentada uma tela de encerramento da jornada, seguida pela tela de **GAME OVER**, que oferece a possibilidade de carregar o último salvamento ou sair do jogo.

### 2.5 Inventário e Poções

O sistema de inventário permite que o jogador acompanhe os itens disponíveis durante a aventura.

Entre os itens estão:

- **Poção de vida:** recupera até 5 pontos de vida.
- **Poção de mana:** recupera até 5 pontos de mana.

A utilização das poções respeita a quantidade disponível no inventário e os limites máximos de vida e mana do personagem.

Caso o jogador já esteja com o recurso no limite máximo, a poção não será consumida.

### 2.6 Loja, Ouro e Baú

Durante a aventura, o jogador poderá obter ouro ao derrotar determinados inimigos:

- Esqueleto: 4 moedas de ouro.
- Goblin: 4 moedas de ouro.

O ouro pode ser utilizado na loja para adquirir os seguintes itens:

| Item | Preço |
|---|---:|
| Chave | 5 moedas de ouro |
| Poção de vida | 3 moedas de ouro |
| Poção de mana | 3 moedas de ouro |

O baú exige uma chave para ser aberto. Ao utilizá-la, o jogador recebe um equipamento específico para sua classe, que aumenta o atributo de ataque em 5 pontos:

- **Cavaleiro:** Espada de Guerra.
- **Mago:** Cajado de Destruição.
- **Arqueira:** Arco de Caçada.

### 2.7 Easter Egg

Na primeira sala, o jogador poderá encontrar uma inscrição misteriosa na parede.

Ao digitar a palavra `DACIO`, o sistema libera a **Dacio Sword**, uma arma secreta que aumenta o ataque do personagem em 999 pontos.

O segredo pode ser descoberto apenas uma vez por partida.

### 2.8 Sistema de Salvamento

O jogo utiliza arquivos binários para armazenar o estado atual da partida.

O salvamento registra as informações do jogador, das salas e da sala atual. O sistema cria checkpoints automaticamente antes da execução dos eventos de cada sala.

Caso o jogador seja derrotado, poderá selecionar a opção de carregar o último salvamento disponível ou encerrar o jogo.

### 2.9 Encerramento da Jornada

O jogo possui dois possíveis encerramentos:

- **Derrota:** quando os pontos de vida do jogador chegam a zero, é apresentada uma narrativa de derrota e a tela de Game Over, permitindo carregar o último salvamento ou sair.
- **Vitória:** após derrotar o Boss na sexta sala, é apresentada uma narrativa de conclusão e a mensagem **VOCÊ VENCEU!**, encerrando a jornada.

---

## 3. Fluxograma da Lógica do Sistema

**[Seção reservada para inclusão do novo fluxograma.]**

---

## 4. Estrutura de Dados

O sistema utiliza estruturas de dados heterogêneas (`struct`) para organizar as informações dos principais elementos do jogo, como o personagem do jogador, os inimigos, as salas e os dados de salvamento.

### 4.1 Estrutura do Jogador

A estrutura `Player` armazena as informações referentes ao personagem controlado pelo usuário.

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
    int pocoes_vida;
    int pocoes_mana;
    int dacio_sword;
    char ataque_esp[20];
} Player;
```

Os principais dados armazenados são:

- `classe`: classe escolhida pelo jogador;
- `vida_max` e `vida_atual`: quantidade máxima e atual de pontos de vida;
- `ATK`: poder de ataque do personagem;
- `DEF`: capacidade de defesa contra ataques dos inimigos;
- `PER`: atributo de percepção do personagem;
- `mana_max` e `mana_atual`: quantidade máxima e atual de mana;
- `ouro`: quantidade de ouro obtida durante o jogo;
- `quant_chaves`: quantidade de chaves carregadas pelo jogador;
- `pocoes_vida`: quantidade de poções de vida disponíveis;
- `pocoes_mana`: quantidade de poções de mana disponíveis;
- `dacio_sword`: indica se o jogador já descobriu o Easter Egg e obteve a arma secreta;
- `ataque_esp`: armazena o nome da habilidade especial da classe.

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

- `inmg`: nome ou identificação do inimigo;
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

---

## 5. Considerações Finais

O Overtale foi desenvolvido como um projeto acadêmico com o objetivo de aplicar conceitos fundamentais da linguagem C, como estruturas de dados, funções, vetores, manipulação de arquivos, condições, laços de repetição e organização do código.

Por meio do desenvolvimento do jogo, foi possível integrar diferentes funcionalidades em um único sistema, proporcionando uma experiência de RPG com exploração de salas, combates por turnos, gerenciamento de recursos, habilidades especiais e dois possíveis encerramentos: vitória ou derrota.
