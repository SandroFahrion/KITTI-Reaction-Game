// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#ifndef REACTION_GAME_HPP
#define REACTION_GAME_HPP

#include "kitti_dataset.hpp"
#include "player.hpp"
#include "game_mode/game_mode.hpp"
#include "gui.hpp"
#include "image.hpp"

#include <tuple>
#include <vector>
#include <string>

class ReactionGame {
public:
    ReactionGame(const StartParams &params);    // Überladener Konstruktor für die Spielinstanz, erhält Startparameter von GUI

    bool startGame(GUI &gui);   // Spielablauf durch Aufruf der benötigten Funktionen

     // Debugging tools
    auto getMembers() const {
        return std::make_tuple(m_turns, player, dataset, gameMode, params, image);
    }

    std::vector<std::string> getMemberNames() const {
        return {"m_turns", "player", "dataset", "gameMode", "params", "image"};
    }

private:
    int m_turns;
    Player player;
    KittiDataset dataset;
    GameMode *gameMode;
    StartParams params;
    Image image;
};

#endif // REACTION_GAME_HPP
