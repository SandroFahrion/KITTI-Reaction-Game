// Attribute: Größe der Bounding Box
// Funktionen: Bounding Box "zeichnen"

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

class BoundingBox {
public:
    BoundingBox(); // Standardkonstruktor
    BoundingBox(int x, int y, int width, int height);   // Überladener Konstruktor zur Erzeugung eines BoundingBox-Objektes
        
    void draw();    // Verarbeitung der Daten zu einer BoundingBox

    bool contains(int px, int py) const;

    // getter-Methoden
    int getCoordX() const{ return m_x; } 
    int getWidthX() const{ return m_width; }
    int getCoordY() const{ return m_y; }
    int getHeightY() const{ return m_height; }

    // setter-Methoden
    void setCoordX(int x) { m_x = x; }
    void setWidthX(int width) { m_width = width; }
    void setCoordY(int y) { m_y = y; }
    void setHeightY(int height) { m_height = height; }

private:
    int m_x, m_y, m_width, m_height;
};

#endif // BOUNDING_BOX_HPP
