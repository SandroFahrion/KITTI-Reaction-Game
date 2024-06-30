// Attribute: Größe der Bounding Box

// Funktionen: Bounding Box "zeichnen"

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

class BoundingBox {
    public:
        BoundingBox(int x, int y, int width, int height);
        void draw();
    
    private:
        int x, y, width, height;
};

#endif BOUNDING_BOX_HPP
