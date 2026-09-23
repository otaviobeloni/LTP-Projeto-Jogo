# Overtale

## 1. Descrição do Sistema
O projeto consiste em um video game, do gênero RPG (Role Playing Game) e *Dungeon crawler*. No game, o jogador escolherá entre três classes jogáveis, O Guerreiro, O Mago e A Arqueira; cada um com acesso a
ataques, habilidades e itens diferentes, além de favorecerem um estilo de jogo único. A gameplay se baseia no jogador controlar seu personagem através de salas, contendo inimigos e possívelmente recompensas para o
personagem, até chegar na sala final contento o Chefão (Boss), o inimigo final do jogo. O game utilizará arquivos de save em binário, para restaurar o estado do jogo e permitir que o jogador salve seu progresso em pontos específicos, e estruturas de dados para guardar informações sobre o personagem do Jogador e NPCs (Non Playable Characters).


---

## 2. Fluxo de Utilização Esperado para o Sistema

  1. **Menu inicial**

      *Ao iniciar o programa (Overtale) o usuário irá se deparar com um simples menu onde poderá escolher entre:*
     
      - `1. Iniciar Jogo`
      - `2. Sair` (Encerra a execução do programa).
      
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
             3- Fugir     
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

```c
