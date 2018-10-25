#include <vector>
#include "jarvis.h"
#include "vector.h"
#include "globals.h"


Vector nextHullPoint(Vector current, Vector baseline){
    double highestDotProduct = -2.0;
    int nextPointIndex;
    for(unsigned i = 0; i < points.size(); i++){
        if(current == points[i]) continue;

        Vector direction = (points[i] - current).normalize();
        
        if(baseline.dotProduct(direction) > highestDotProduct){
            highestDotProduct = baseline.dotProduct(direction);
            nextPointIndex = i;
        }
    }

    return points[nextPointIndex];
}


void jarvis(int p0){
    Vector baseline = Vector(1,0);
    Vector currentPoint = points[p0];
    hullVertices.push_back(currentPoint);  

    do{
        Vector nextPoint = nextHullPoint(currentPoint,baseline);
        hullVertices.push_back(nextPoint);     
        
        baseline = (nextPoint - currentPoint).normalize();
        currentPoint = nextPoint;

    }while(currentPoint != points[p0]);

}

//encontra o ponto de menor Y e chama a função jarvis passando sua posição como argumento
void closeConvexHull(){
    if(!hullClose){
        hullClose = 1;
        int lowestYindex = 0;
        double lowestY = 2.;
        for(unsigned i = 0; i < points.size(); i++){
            if(points[i].getY() < lowestY){
                lowestYindex = i;
                lowestY = points[i].getY();
            }
        }
        jarvis(lowestYindex);
    }else{
        hullClose = 0;
        hullVertices.clear();
    }

}

