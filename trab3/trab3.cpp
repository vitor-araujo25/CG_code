//Aluno: Vitor de Oliveira Fernandez Araujo
//DRE: 115162509

#include <vector>
#include <iostream>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <cmath>
#include <list>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700

using namespace std;

class Vector{
    protected:
        double X;
        double Y;
        double norm;
    public:
        Vector(){}

        Vector (double x, double y){
            this->X = x;
            this->Y = y;
            this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
        }

        //calcula o produto vetorial this X v
        double crossProduct(Vector v){
            return (this->X)*(v.getY()) - (this->Y)*(v.getX());
        }

        double getNorm(){
            return this->norm;
        }

        double dotProduct(Vector v){
            return (this->X)*(v.getX()) + (this->Y)*(v.getY());
        }

        double getX(){
            return this->X;
        }
        double getY(){
            return this->Y;
        }
        void setX(double x){
            this->X = x;
        }
        void setY(double y){
            this->Y = y;
        }

        Vector normalize(){
            if(norm != 0){
                Vector normalized_vector = *this*(1./norm);
                return normalized_vector;
            }
            
            return Vector(0.,0.);
        }

        bool operator==(Vector v){
            return (this->X == v.getX() && this->Y == v.getY());
        }

        bool operator!=(Vector v){
            return !(this->X == v.getX() && this->Y == v.getY());
        }

        Vector operator-(Vector v){
            Vector answer(this->getX() - v.getX(), this->getY() - v.getY());
            return answer;
        }

        Vector operator+(Vector v){
            Vector answer(this->getX() + v.getX(), this->getY() + v.getY());
            return answer;
        }

        Vector operator*(double mult){
            Vector answer(mult*this->getX(), mult*this->getY());
            return answer;
        }

};


int hullClose = 0;

vector<Vector> points;
vector<Vector> hullVertices;

void reset(){
    hullVertices.clear();
    points.clear();
    if(hullClose){
        hullClose = 0;
    }
}

void mouse(int button, int state, int X, int Y){
    // Respond to mouse button presses.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !hullClose){
        float x = (2.*X)/SCREEN_WIDTH - 1.;
        float y = -(2.*Y)/SCREEN_HEIGHT + 1.;
        points.push_back(Vector(x,y)); 

        glutPostRedisplay();
    }
}


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


void keyboard_cb(unsigned char key, int X, int Y){
    switch (key){
        case 27:     //tecla ESC sai do programa
            glutLeaveMainLoop();
            break;

        case ' ':   
        //tecla 'Espaço' trava a criação de pontos e forma o fecho convexo. 
        //Ao pressioná-la de novo, a criação é liberada para que um novo fecho seja calculado.
            if(points.size() > 3){
                closeConvexHull();
                glutPostRedisplay();
            }
            break;
        case 'r':   //tecla 'r' limpa tudo o que foi feito
            reset();
            glutPostRedisplay();
            break;
    }
}

void display() {
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(7.);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
        
    for(Vector i: points){
        glVertex2f(i.getX(),i.getY());
    }

    glEnd();

    if(hullClose){
        glLineWidth(5.);
        glBegin(GL_LINE_STRIP);

        for(unsigned i = 0; i < hullVertices.size(); i++){
            glColor3f(0.0,(i/hullVertices.size())*1.0,0.0);
            glVertex2f(hullVertices[i].getX(),hullVertices[i].getY());
        }

        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutCreateWindow("Polygon Test");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();    

    return EXIT_SUCCESS;
}