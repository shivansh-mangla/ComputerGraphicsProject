#include <GL/glut.h>
#include <iostream>
//#include "stb_image.h"
#include <cstring>


int currentScene = 0;
float timer = 0.0f;    // To track time


void drawText(float x, float y, const char* text) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glRasterPos2f(x, y); // Position of text

    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void introSlideScene(const char* text, float x=-0.5f, float y=0.0f) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawText(x, y, text);
}

void stickman(float x = 0.0f, float y = 0.0f, float scale = 1.0f, float angle = 0.0f, bool isMale = true) {
    glPushMatrix(); // Save current transformation
    glTranslatef(x, y, 0.0f); // Move stickman to (x, y)
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f); // Scale stickman size

    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // Head (circle)
    float theta;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        theta = 2.0f * 3.1415926f * float(i) / float(100);
        float dx = 0.05f * cosf(theta);
        float dy = 0.05f * sinf(theta);
        glVertex2f(dx, dy + 0.5f);
    }
    glEnd();


    if (!isMale) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            theta = 1.0f * 3.1415926f * float(i) / float(100);
            float dx = 0.075f * cosf(theta);
            float dy = 0.075f * sinf(theta);
            glVertex2f(dx, dy + 0.5f);
        }
        glEnd();
    }
    

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    // Body
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.1f);


    // Left Arm
    glVertex2f(0.0f, 0.4f);
    glVertex2f(-0.1f, 0.3f);

    // Right Arm
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.1f, 0.3f);

    // Left Leg
    glVertex2f(0.0f, 0.1f);
    glVertex2f(-0.1f, -0.1f);

    // Right Leg
    glVertex2f(0.0f, 0.1f);
    glVertex2f(0.1f, -0.1f);
    glEnd();

    glPopMatrix(); // Restore transformation
}



void scene1() {
    glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawText(-0.5f, 0.8f, "5th Jan 1981");
    stickman();
    stickman(0.5f, 0, 0.9f, 0, false);
    stickman(0.55f, 0.25f, 0.35f, 52.0f);
}

void scene2() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawText(-0.5f, 0.0f, "Scene 2: Mid-Air Flight");
}

void scene3() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawText(-0.5f, 0.0f, "Scene 3: Landing");
}


void display() {
    switch (currentScene) {
        case 0: introSlideScene("Scene 1: Born in Hospital"); break;
        case 1: scene1(); break;
    }
    glutSwapBuffers();
}

void update(int value) {
    timer += 0.1f;

    if (timer > 1.0f && currentScene == 0) {
        currentScene = 1;
    }
    if (timer > 6.0f && currentScene == 1) {
        currentScene = 2;
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);  // Update every 100ms
}


void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Life Cycle of Human");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Start timer
    glutMainLoop();

    return 0;
}