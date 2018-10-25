#ifndef VECTOR_H
#define VECTOR_H

class Vector{
    protected:
        double X;
        double Y;
        double norm;
    public:
        Vector();
        Vector(double x, double y);
        double crossProduct(Vector v);
        double getNorm();
        double dotProduct(Vector v);
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        Vector normalize();
        bool operator==(Vector v);
        bool operator!=(Vector v);
        Vector operator-(Vector v);
        Vector operator+(Vector v);
        Vector operator*(double mult);
};

#endif