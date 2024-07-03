// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#ifndef REACTION_GAME_HPP
#define REACTION_GAME_HPP

#include "include/kitti_dataset.hpp"
#include "include/player.hpp"
#include "include/game_mode/game_mode.hpp"
#include "include/gui.hpp"

class ReactionGame{
    public:
        //ReactionGame(); // Standardkonstruktor
        //~ReactionGame(); // Destruktor

        ReactionGame(const StartParams &params); // Überladener Konstruktor für die Spielinstanz, erhält Startparameter von GUI

        void startGame(); // Spielablauf durch Aufruf der benötigten Funktionen
        
    private:        
        Player player;            // Instanziierung der Player-Klasse mit der Instanz / dem Objekt "player" zur Kapselung der Spielerdaten
        KittiDataset dataset;     // Instanziierung der KittiDataset-Klasse mit "dataset" zur Kapselung der Datensatz-Dateizugriffe
        GameMode *gameMode;       // Instanziierung mit Zeiger "*gamemode" als Instanz auf die GameMode-Basisklasse zur Kapselung der Spielmodi
        StartParams params;       // Instanz für Startparameter
};

#endif // REACTION_GAME_HPP