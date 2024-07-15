// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#ifndef REACTION_GAME_HPP
#define REACTION_GAME_HPP

#include <tuple>
#include <vector>
#include <string>
#include <random>

#include "kitti_dataset.hpp"
#include "player.hpp"
#include "game_mode/game_mode.hpp"
#include "game_mode/mode_1_direct_click.hpp"
#include "game_mode/mode_2_color_change.hpp"
#include "gui.hpp"
#include "image.hpp"
#include "../helpers/member_util.hpp"


class ReactionGame {
public:
    ReactionGame(const StartParams &params);    // Überladener Konstruktor für die Spielinstanz, erhält Startparameter

    bool startGame(GUI &gui);   // Spielablauf durch Funktionsaufrufe in einer Schleife

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_turns, player, dataset, gameMode)

private:
    int m_turns;
    
    Player player;
    KittiDataset dataset;
    GameMode *gameMode;
};

#endif // REACTION_GAME_HPP
