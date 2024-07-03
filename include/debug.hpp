#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include "player.hpp"
#include "reaction_game.hpp"
#include "gui.hpp"

class Debugger {
public:
    bool debug = false;
    static void log(const std::string &message);    
    // Anwendungsbeispiel
    // Debugger::log("Message string");

    static void logPlayer(const Player &player);

    static void logStartParams(const StartParams &params);

    static void logReactionGame(const ReactionGame &game);

};

#endif // DEBUG_HPP
