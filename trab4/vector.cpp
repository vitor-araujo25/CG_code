#include "vector.h"
#include <cmath>

Vector::Vector(){}

Vector::Vector (double x, double y){
    this->X = x;
    this->Y = y;
    this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
}

//calcula o produto vetorial this X v
double Vector::crossProduct(Vector v){
    return (this->X)*(v.getY()) - (this->Y)*(v.getX());
}

double Vector::getNorm(){
    return this->norm;
}

double Vector::dotProduct(Vector v){
    return (this->X)*(v.getX()) + (this->Y)*(v.getY());
}

double Vector::getX(){
    return this->X;
}
double Vector::getY(){
    return this->Y;
}
void Vector::setX(double x){
    this->X = x;
}
void Vector::setY(double y){
    this->Y = y;
}

Vector Vector::normalize(){
    if(norm != 0){
        Vector normalized_vector = *this*(1./norm);
        return normalized_vector;
    }
    
    return Vector(0.,0.);
}

 

bool Vector::operator==(Vector v){
    return (this->X == v.getX() && this->Y == v.getY());
}

bool Vector::operator!=(Vector v){
    return !(this->X == v.getX() && this->Y == v.getY());
}

Vector Vector::operator-(Vector v){
    Vector answer(this->getX() - v.getX(), this->getY() - v.getY());
    return answer;
}

Vector Vector::operator+(Vector v){
    Vector answer(this->getX() + v.getX(), this->getY() + v.getY());
    return answer;
}

Vector Vector::operator*(double mult){
    Vector answer(mult*this->getX(), mult*this->getY());
    return answer;
}