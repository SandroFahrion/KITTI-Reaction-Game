// Attribute: Größe der Bounding Box
// Funktionen: Bounding Box "zeichnen"

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

class BoundingBox {
    public:
        BoundingBox(int x, int y, int width, int height); // Überladener Konstruktor zur Erzeugung eines BoundingBox-Objektes
        
        void draw();    // Verarbeitung der Daten zu einer BoundingBox        
    private:
        int m_x, m_y, m_width, m_height;
};

#endif // BOUNDING_BOX_HPP
