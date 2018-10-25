//Aluno: Vitor de Oliveira Fernandez Araujo
//DRE: 115162509

#include "vector.h"
#include "globals.h"
#include "jarvis.h"

using namespace std;

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