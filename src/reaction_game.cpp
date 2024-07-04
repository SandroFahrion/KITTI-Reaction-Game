// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params):  //siehe header-file für doku
player(params.m_playerName), dataset(params.m_sequence), gameMode(nullptr), params(params) {
}

// Spielablauf durch Aufruf der Funktionen in einer Schleife
bool ReactionGame::startGame(){
    bool end = false;
    GUI gui;
    
    while (end == false){
        for (int i = 0; i < params.m_numImages; ++i) {
        Image image = dataset.getImage(i);
        image.setBoundingBoxes(dataset.getBoundingBoxes(i));
        gui.displayImage(image);
        // gameMode->processClick();
        // reaction times
        // stats ausgeben
        }
    }

end = true;
return end;
}

// Debugging tools
const Player &ReactionGame::getPlayer() const {
    return player;
}

const StartParams &ReactionGame::getStartParams() const {
    return params;
}
