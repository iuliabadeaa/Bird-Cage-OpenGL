#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include "glut.h"

GLfloat ctrlpoints[4][3] = {
	{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, {2.0, 4.0, 0.0}, {4.0, -4.0, 0.0} };

GLUquadricObj* quadric = gluNewQuadric();
GLUquadricObj* circle = gluNewQuadric();
static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat alfa = 0;
static GLfloat angle = 0;

GLuint textureId1;
GLuint textureId2;

GLuint incarcaTextura(const char* s)
{
	GLuint textureId = 0;
	AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(s);

	if (pImagineTextura != NULL)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
	}
	if (pImagineTextura)
	{
		if (pImagineTextura->data) {
			free(pImagineTextura->data);
		}
		free(pImagineTextura);
	}
	return textureId;
}

void CALLBACK MutaStanga(void)
{
	x -= 1;
}

void CALLBACK MutaDreapta(void)
{
	x += 1;
}

void CALLBACK MutaSus(void)
{
	y += 1;
}

void CALLBACK MutaJos(void)
{
	y -= 1;
}
void CALLBACK rot_z_up(AUX_EVENTREC* event)
{
	alfa += 2;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event)
{
	alfa -= 2;
}

void CALLBACK rot_y_left()
{
	angle += 2;
}

void CALLBACK rot_y_right()
{
	angle -= 2;
}




void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_MAP1_VERTEX_3);
	textureId1 = incarcaTextura("covor.bmp");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}


void drawString(const char* str, int x, int y) {
	glRasterPos2i(x, y);

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}


void CALLBACK display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(x, y, 0.0f);
	glRotatef(alfa, 1, 0, 0);
	glRotatef(angle, 0, 1, 0);

	glLineWidth(3.0f);

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);


	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, 4.0);
	glColor3f(1, 1, 0.2);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(quadric, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, textureId1);
	gluCylinder(quadric, 4.0f, 4.0f, 0.75f, 60, 6);
	glColor3f(0.9, 0.8, 0.3);
	gluQuadricTexture(circle, GL_TRUE);
	gluDisk(circle, 0, 4.0f, 60, 6);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 4, 0);

	for (int i = 10; i < 120; i += 10)
	{
		glRotatef(i, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, i / 120.0f, 0.0f);

		glBegin(GL_LINE_STRIP);
		{
			glEnable(GL_AUTO_NORMAL);
			for (int j = 0; j <= 50; j++) {
				glEvalCoord1f((GLfloat)j / 50.0f);
			}
		}
		glEnd();
	}

	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	drawString("Badea Maria-Iulia", 0, 7);

	glPopMatrix();


	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0f, w/h, -5, 20);
	gluLookAt(0, 4, 24, 0, 4, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow("Colivie RIP");
	myInit();
	auxReshapeFunc(myReshape);
	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_UP, MutaSus);
	auxKeyFunc(AUX_DOWN, MutaJos);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEUP, rot_z_down);
	auxKeyFunc(AUX_w, rot_y_left);
	auxKeyFunc(AUX_s, rot_y_right);
	auxMainLoop(display);
	return 0;
}