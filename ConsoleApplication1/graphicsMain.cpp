#include <GL/glut.h>
#include "graphicsMain.h"
#include "ConwayGame.h"


#ifndef REFRESH_RATE
#define REFRESH_RATE 1.0f
#endif

static ConwayGame *conwayGame;

static void init(int argc, char** argv) {
	conwayGame = new ConwayGame(argc > 1 ? argv[1] : "input.txt");
}

static void render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	conwayGame->draw(30, 40);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

static void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

static void update() {
	static int lastUpdate = 0;
	int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	if (elapsedTime - lastUpdate > (int)(1000.0f / REFRESH_RATE)) {
		conwayGame->runIteration();
		render();
		lastUpdate = elapsedTime;
	}
}

int graphicsMain(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("Conway");

	init(argc, argv);

	glutDisplayFunc(&render);
	glutIdleFunc(&update);

	glutMainLoop();
	return 0;
}