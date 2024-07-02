// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params):  //siehe header-file für doku
player(params.m_playerName), dataset(), gameMode(nullptr), params(params) {

}

void ReactionGame::startGame(){
    GUI gui;
    // Spielablauf durch Aufruf der Funktionen in einer Schleife
}