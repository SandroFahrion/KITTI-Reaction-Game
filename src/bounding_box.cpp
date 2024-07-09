// Attribute: Größe der Bounding Box

// Funktionen: Bounding Box "zeichnen"

#include "bounding_box.hpp"

BoundingBox::BoundingBox() : m_x(0), m_y(0), m_width(0), m_height(0) {} // Standardkonstruktor

BoundingBox::BoundingBox(int x, int y, int width, int height)   // Überladener Konstruktor
    : m_x(x), m_y(y), m_width(width), m_height(height) {}       // Initialzier list

bool BoundingBox::contains(int px, int py) const {
    return (px >= m_x && px <= m_x + m_width && py >= m_y && py <= m_y + m_height);
}

void BoundingBox::draw() {

}
