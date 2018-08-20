/*
 When creating your project, uncheck OWL,
 uncheck Class Library, select Static
 instead of Dynamic and change the target
 model to Console from GUI.
 Also link glut.lib to your project once its done.
 */

#include <cstdlib>

// change OpenGL to GL
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header

#include <math.h>

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 700

float rot=0;

float center_x=0.2;
float center_y=0.2;


void rotacao(float &x, float &y, float theta)
{
    float x_rot = x*cos(theta)+y*sin(theta);
    float y_rot =-x*sin(theta)+y*cos(theta);
    
    x=x_rot;
    y=y_rot;
}


void mouse (int button, int state, int X, int Y)
{
    // Respond to mouse button presses.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        center_x =  (2.*X)/SCREEN_WIDTH - 1.;
        center_y = -(2.*Y)/SCREEN_HEIGHT + 1.;
        glutPostRedisplay();
    }
}

void keyboard_cb(unsigned char key, int X, int Y)
{
    switch (key)
    {
        case 27:             // ESCAPE key
            exit (0);
            break;
            
        case 'r':
            rot+=0.13;
            glutPostRedisplay();
            break;
    }
}


void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPointSize(8.0);
    
    glLineWidth(6);
    
    glBegin(GL_LINE_STRIP);
    for (int i=0; i<100; ++i)
    {
        glColor3f(1.0,(i/100.),1-(i/100.));
        
        float x = (i/100.)*cos(i/3.14);
        float y = (i/100.)*sin(i/3.14);
        
        rotacao(x,y, rot);
        
        glVertex2f(center_x + x,center_y + y);
    }
    glEnd();
    
   // glBegin(GL_TRIANGLES);
    
    //glEnd();
    
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Ponto");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS ;

}

