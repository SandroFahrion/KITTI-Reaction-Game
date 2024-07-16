// Informationen zu den Bounding Boxen

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <string>

class BoundingBox {
public:
    BoundingBox(); // Standardkonstruktor
    BoundingBox(std::string &type, int frame, int x, int y, int width, int height);   // Überladener Konstruktor zur Erzeugung eines BoundingBox-Objektes

    bool contains(int px, int py) const; // Methode zur Prüfung, ob Mauskoordinaten innerhalb der Box liegen

    // getter-Methoden
    int getCoordX() const{ return m_x; } 
    int getWidthX() const{ return m_width; }
    int getCoordY() const{ return m_y; }
    int getHeightY() const{ return m_height; }
    const std::string &getType() const { return m_type; }
    int getFrame() const { return m_frame; }

    // setter-Methoden
    void setCoordX(int x) { m_x = x; }
    void setWidthX(int width) { m_width = width; }
    void setCoordY(int y) { m_y = y; }
    void setHeightY(int height) { m_height = height; }
    void setType(const std::string &type) { m_type = type; }
    void setFrame(int frame) { m_frame = frame; }

private:
    // Member Variablen
    std::string m_type;
    int m_frame;
    int m_x, m_y, m_width, m_height;
};

#endif // BOUNDING_BOX_HPP
