// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#include "game_mode/mode_1_direct_click.hpp"

void processClick(int x, int y){
    int m_x(x), m_y(y);
    // Startzeit für die Reaktionszeitmessung setzen
    // das sollte im gleichen moment passieren, in dem das bild angezeigt wird
    // m_startTime = std::chrono::system_clock::now();
}

void calculateReactionTime(){
    // Endzeit der Reaktionszeitmessung
    auto endTime = std::chrono::system_clock::now();
    //std::chrono::duration<double> reactionTime = endTime - m_startTime;
    
    // Reaktionszeit dem Spieler hinzufügen
    //m_player->addReactionTime(reactionTime.count());
}