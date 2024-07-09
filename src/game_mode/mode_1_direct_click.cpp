// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#include "game_mode/mode_1_direct_click.hpp"

Mode1DirectClick::Mode1DirectClick() {
}

void Mode1DirectClick::processClick(int x, int y) {
    int m_x(x), m_y(y);
    // Überprüfen, ob der Klick innerhalb der Bounding Box liegt
    if (boundingBox.contains(m_x, m_y)) {
        reactionTime = calculateReactionTime();
    } else {
        // Strafzeit hinzufügen
        reactionTime += penaltyTime;
    }
    // Startzeit für die Reaktionszeitmessung setzen
    // das sollte im gleichen moment passieren, in dem das bild angezeigt wird
    // m_startTime = std::chrono::system_clock::now();
}

double Mode1DirectClick::calculateReactionTime() {

    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = endTime - startTime;

    return elapsed.count();
}