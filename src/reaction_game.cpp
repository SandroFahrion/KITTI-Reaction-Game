// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params):
player(params.m_playerName), dataset(), gameMode(nullptr), params(params) {

}

void startGame(){
    GUI gui;
    // Spielablauf durch Aufruf der Funktionen in einer Schleife
}