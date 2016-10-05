#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "ConwayGame.h"
#include "main.h"
#ifdef USE_GRAPHICS_VERSION
#include "graphicsMain.h"
#endif

using namespace std;


ConwayGame *game = NULL;

static int staticMain(int argc, char** argv) {
	const char* filename;
	filename = (argc > 1 ? argv[1] : "input.txt");
	ConwayGame *game = new ConwayGame(filename);
	game->printState();
	printf("\n");

	game->runIteration();
	game->printState();
	printf("\n");

	game->runIteration();
	game->printState();
	printf("\n");

	game->runIteration();
	game->printState();
	printf("\n");

	game->runIteration();
	game->printState();
	printf("\n");

	char c;
	scanf("%c", &c);
	return 0;
}

int main(int argc, char** argv) {
#ifdef USE_GRAPHICS_VERSION
	return graphicsMain(argc, argv);
#else
	return staticMain(argc, argv);
#endif
}

