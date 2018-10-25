#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <list>
#include <vector>

#include "vector.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700

int hullClose = 0;

std::vector<Vector> points;
std::vector<Vector> hullVertices;

#endif
