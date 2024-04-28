#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat alfa = 0;


void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaSus()
{
    y = y + 10;
}

void CALLBACK MutaJos()
{
    y = y - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK rotate_z_up(AUX_EVENTREC* event)
{
    alfa += 30;
}

void CALLBACK rotate_z_down(AUX_EVENTREC* event)
{
    alfa -= 30;
}


void drawOrigin() {
    glPointSize(5.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
}


void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(x, y, 0.0);
    glRotatef(alfa, 0, 1, 0);


    //dreapta
    glBegin(GL_LINE_LOOP);
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0.0, 100.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(60.0, 0.0, 60.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(60.0, 0.0, -60.0);
    }
    glEnd();


    //stanga
    glBegin(GL_LINE_LOOP);
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0.0, 100.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(-60.0, 0.0, 60.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(-60.0, 0.0, -60.0);
    }
    glEnd();

    //spate
    glBegin(GL_LINE_LOOP);
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0.0, 100.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(-60.0, 0.0, -60.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(60.0, 0.0, -60.0);
    }
    glEnd();

    //fata
    glBegin(GL_LINE_LOOP);
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0.0, 100.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(60.0, 0.0, 60.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(-60.0, 0.0, 60.0);
    }
    glEnd();



    drawOrigin();

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un patrat");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    //auxKeyFunc(AUX_q, rotate_z_down);


    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
