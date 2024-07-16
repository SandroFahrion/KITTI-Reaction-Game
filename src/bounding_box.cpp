// Attribute: Größe der Bounding Box

// Funktionen: Bounding Box "zeichnen"

#include "bounding_box.hpp"

BoundingBox::BoundingBox(){}

BoundingBox::BoundingBox(std::string &type, int frame, int x, int y, int width, int height)   // Überladener Konstruktor
    : m_frame(frame), m_type(type), m_x(x), m_y(y), m_width(width), m_height(height) {}       // Initialzier list

bool BoundingBox::contains(int px, int py) const {
    return (px >= m_x && px <= m_x + m_width && py >= m_y && py <= m_y + m_height);
}

