# Implosion
## Marcus Ng, Adeebur Rahman, Jen Yu
**Systems Period 10**

**Project 2: The Final Frontier**
___
## Exploding Kittens (Terminal Style)
Exploding Kittens is a card game where your goal is to be the last person alive. If you draw an exploding kitten card, you die unless you have a defuse card. Defusing an exploding kitten allows you to place the exploding kitten anywhere in the deck. Players use their action cards to avoid the exploding kittens and cat cards to steal cards from each other. In the beginning of the game, each player receives five cards, including one defuse card. The number of exploding kittens in the deck is one less than the number of players. At the end of each player’s turn, they must draw a card from the deck unless they use an action card that states otherwise.

## Files
```
client.c
DESIGN
DEVLOG
fxn.c
log.sh
makefile
networking.h/.c
README.md 
server.c
```

## Launch Instructions
1. All players need to clone this repo
```
$ git clone https://github.com/jenyu7/implosion.git
```
2. Change directory into the repo
```
$ cd implosion/
```
4. Compile the program
```
$ make
```
5. Only one player needs hosts the server
```
$ ./server <NUMBER OF PLAYERS (2-6)>
```
6. Everyone runs the client to connect to the server
```
$ ./client
```
7. Play the game!

## How to Play

1. Commands: 
  * `print`: prints out your current hand of cards
  * `draw`: draws a card from the deck
  * `<number>`: To use a card, type in its index in the hand (shown using `print`)
2. Each player starts off with five cards, one of them being Defuse, which nullifies any exploding kittens. 
3. Objective of the game is to not draw an exploding kitten without a Defuse handy (if so, you die and lose the game.) 
