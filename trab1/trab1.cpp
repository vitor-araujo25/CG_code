//Aluno: Vitor de Oliveira Fernandez Araujo
//DRE: 115162509

#include <vector>
#include <iostream>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <math.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700

class Point{
    float X;
    float Y;
    public:
        Point (float x, float y){
            this->X = x;
            this->Y = y;
        }
        float getX(){
            return this->X;
        }
        float getY(){
            return this->Y;
        }
};

std::vector<Point*> points; //Vetor de pontos que será utilizado pelo loop do openGL.

int click_flag = 0; //Trava a criação de novos pontos. Ativado ao começar a suavização e desativado ao resetar.

//Lógica de suavização das quinas
void smooth(){
    if(!click_flag){
        click_flag = 1;
    }

    std::vector<Point*> new_points;
    Point* prev = points.front();

    for(int i = 0; i < points.size()-1; i++){
        Point* current = points[i+1];

        //Ponto médio entre dois pontos consecutivos calculado por ((x1+x2)/2 , (y1+y2)/2)
        Point* p2 = new Point((prev->getX()+current->getX())/2.,(prev->getY()+current->getY())/2.);

        //Pontos intermediários são calculados da mesma maneira que o ponto médio, agora de forma recursiva
        Point* p1 = new Point((prev->getX()+p2->getX())/2.,(prev->getY()+p2->getY())/2.);
        Point* p3 = new Point((current->getX()+p2->getX())/2.,(current->getY()+p2->getY())/2.);
    
        //Mantém o extremo inicial
        if(i == 0){
            new_points.push_back(prev);
        }
    
        new_points.push_back(p1);
        new_points.push_back(p3);
    
        //Mantém o extremo final
        if(i == points.size() - 2){
            new_points.push_back(current);
        }
    
        prev = current;
    }

    //Exclui o vetor de pontos antigo, atualizando-o com os novos pontos calculados.
    points = new_points;
}

//Limpa os pontos criados e habilita a criação de novos
void reset(){
    points.clear();
    if(click_flag){
        click_flag = 0;
    }
}


void mouse(int button, int state, int X, int Y){
    // Respond to mouse button presses.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !click_flag){
        float x = (2.*X)/SCREEN_WIDTH - 1.;
        float y = -(2.*Y)/SCREEN_HEIGHT + 1.;
        points.push_back(new Point(x,y)); 
        glutPostRedisplay();
    }
}

void keyboard_cb(unsigned char key, int X, int Y){
    switch (key){
        case 27:     //tecla ESC sai do programa
            exit (0);
            break;

        case ' ':   //tecla 'Espaço' suaviza as quinas de uma curva criada
            smooth();
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
    glLineWidth(6.5);


    glBegin(GL_LINE_STRIP);
    
    for(Point* i: points){
        glVertex2f(i->getX(),i->getY());
    }

    glEnd();

    glPointSize(5.);
    glColor3f(1.,0.,0.);
    glBegin(GL_POINTS);
    
    for(Point* i: points){
        glVertex2f(i->getX(),i->getY());
    }

    glEnd();
    
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Smoothie");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS ;

}

