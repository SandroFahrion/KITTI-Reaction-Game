// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#ifndef REACTION_GAME_HPP
#define REACTION_GAME_HPP

#include "kitti_dataset.hpp"
#include "player.hpp"
#include "game_mode/game_mode.hpp"
#include "gui.hpp"

class ReactionGame{
    public:
        ReactionGame(const StartParams &params); // Standardkonstruktor
        ~ReactionGame(); // Destruktor

        void startGame(); // selbsterklärend
        
    private:        
        Player player;          // Instanziierung der Player-Klasse mit der Instanz "player" zur Kapselung der Spielerdaten
        KittiDataset dataset;   // Instanziierung der KittiDataset-Klasse mit der Instanz "dataset" zur Kapselung des KITTI Datensatzes
        GameMode *gameMode;     // Instanziierung mit Zeiger "*gamemode" als Instanz auf die GameMode-Basisklasse zur Kapselung der Spielmodi
};

#endif // REACTION_GAME_HPP