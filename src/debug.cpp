#include "debug.hpp"

void Debugger::log(const std::string &message) {
    std::cout << "\n[DEBUG]: " << message << "\n" << std::endl;
}

void Debugger::logPlayer(const Player &player) {
    std::cout << "[DEBUG Player]: Name = " << player.getName() << std::endl;
    std::cout << "[DEBUG Player]: Reaction Times = ";
    for (double time : player.getReactionTimes()) {
        std::cout << time << " ";
    }
    std::cout << std::endl;
}

void Debugger::logStartParams(const StartParams &params) {
    std::cout << "[DEBUG StartParams]: Player Name = " << params.m_playerName << std::endl;
    std::cout << "[DEBUG StartParams]: Number of Images = " << params.m_numImages << std::endl;
    std::cout << "[DEBUG StartParams]: Sequence = " << params.m_sequence << std::endl;
    std::cout << "[DEBUG StartParams]: Game Mode = " << params.m_gameMode << std::endl;
}

void Debugger::logReactionGame(const ReactionGame &game) {
    std::cout << "\n";
    logPlayer(game.getPlayer());
    logStartParams(game.getStartParams());
}
