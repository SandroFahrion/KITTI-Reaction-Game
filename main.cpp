// Programmstart

#include <iostream>

int main(){
    // menü / gui aufrufen

    if (gameMode == "1") {
        // game.setGameMode(std::make_unique<DirectClickReaction>());
    } else if (gameMode == "2") {
        // game.setGameMode(std::make_unique<ColorChangeReaction>());
    } else { // Fehlerausgabe, falls kein valider Spielmodus gewählt wurde
        std::cerr << "Invalid game mode selected!" << std::endl;
        return -1;
    }

    // spielstart -> weitere funktionen des spiels werden über die Spielverwaltung aufgerufen

    game.start();
    return 0;
}