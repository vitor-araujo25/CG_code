//Aluno: Vitor de Oliveira Fernandez Araujo
//DRE: 115162509

#include <vector>
#include <iostream>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <cmath>
#include <map>
#include <string>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700

using namespace std;

class Point{
    protected:
        float X;
        float Y;
    public:
        Point(){}

        Point (float x, float y){
            this->X = (2.*x)/SCREEN_WIDTH - 1.;
            this->Y = -(2.*y)/SCREEN_HEIGHT + 1.;
        }

        float getX(){
            return this->X;
        }
        float getY(){
            return this->Y;
        }
        void setX(float x){
            this->X = x;
        }
        void setY(float y){
            this->Y = y;
        }
};

class Vector: public Point{
    float norm;
    public:
        Vector(float x, float y): Point(x,y){
            this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
        }

        Vector(Point* p1, Point* p2){
            this->X = p2->getX() - p1->getX();
            this->Y = p2->getY() - p1->getY();
            this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
        }

        //calcula o produto vetorial this X v
        float crossProduct(Vector* v){
            return (this->X)*(v->getY()) - (this->Y)*(v->getX());
        }

        float getNorm(){
            return this->norm;
        }
};

vector<Point*> points; //Vetor de pontos que será utilizado pelo loop do openGL.

Point* pointIn = NULL;  //ponto que será criado pelo clique
Point* pointOut = new Point((SCREEN_WIDTH/2)+100,0);  //ponto fixo, fora da tela

int polygonEnd = 0;  //flag que indica o fim do desenho do poligono
int pointStatus = 0; //flag que indica se o ponto está dentro ou fora do poligono e definirá sua cor

//Limpa os pontos criados e habilita a criação de novos
void reset(){
    for(Point* i: points){
        delete i;
    }
    points.clear();
    if(polygonEnd){
        polygonEnd = 0;
    }
}

void polygonLock(){
    if(!polygonEnd){
        polygonEnd = 1;
        if(points.size() > 0){
            Point initial = *points[0];
            points.push_back(new Point(initial));
        }
    }
}


void mouse(int button, int state, int X, int Y){
    // Respond to mouse button presses.
    if(!polygonEnd){
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            points.push_back(new Point(X,Y)); 
        }
    }else{
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            pointIn = new Point(X,Y); 
            int crossCount = 0;
            map<string, Vector*> lines;

            lines["AB"] = new Vector(pointIn, pointOut); //reta fixa
            for(long unsigned int i = 0; i < points.size() - 1; i++){
                lines["CD"] = new Vector(points[i], points[i+1]); //reta atual do polígono

                //vetores diagonais
                lines["AD"] = new Vector(pointIn,points[i+1]);
                lines["AC"] = new Vector(pointIn,points[i]);
                lines["CA"] = new Vector(points[i],pointIn);
                lines["CB"] = new Vector(points[i],pointOut);


                if(lines["AB"]->crossProduct(lines["AD"]) * lines["AB"]->crossProduct(lines["AC"]) < 0 \
                 && lines["CD"]->crossProduct(lines["CA"]) * lines["CD"]->crossProduct(lines["CB"]) < 0){
                    crossCount++;
                }                
            }

            if(crossCount % 2 == 0){
                cout << "Ponto fora do polígono!\n";
                pointStatus = 0;
            }else{
                cout << "Ponto dentro do polígono!\n";
                pointStatus = 1;
            }

            //desalocando memória dos ponteiros
            for(map<string, Vector*>::iterator it = lines.begin(); it != lines.end(); it++){
                delete it->second;
            }
        }
    }
    
    glutPostRedisplay();
}

void keyboard_cb(unsigned char key, int X, int Y){
    switch (key){
        case 27:     //tecla ESC sai do programa
            glutLeaveMainLoop();
            break;

        case ' ':   //tecla 'Espaço' trava a criação de linhas e fecha o polígono
            polygonLock();
            glutPostRedisplay();
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
    glColor3f(1.0,1.0,1.0);
    glLineWidth(5.);

    glBegin(GL_LINE_STRIP);
        
    for(Point* i: points){
        glVertex2f(i->getX(),i->getY());
    }

    glEnd();

    if(polygonEnd){
        glPointSize(7.);
        if(pointStatus){
            glColor3f(0.,0.,1.);
        }else{
            glColor3f(1.,0.,0.);
        }
        glBegin(GL_POINTS);
        
        if(pointIn){
            glVertex2f(pointIn->getX(),pointIn->getY());
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

    delete pointOut;
    delete pointIn;
    return EXIT_SUCCESS;
}

