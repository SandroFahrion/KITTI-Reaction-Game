// spielerinformationen

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {
    public:
        Player(const std::string &name);
        void addReactionTime(double time);
        void printStatistics();
    
    private:
        std::string name;
        std::vector<double> reactionTimes;
};

#endif PLAYER_HPP
