#ifndef window
#define window

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// different headers depending on what machine you're on
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

extern double dim; // size of the world
extern double asp; // aspect ratio
extern bool wasResized; // called resize function

// colors for drawing
struct color {
	int r;
	int g;
	int b;
};

const struct color asphalt = { 52, 73, 94 };
const struct color concrete = { 127, 140, 141 };
const struct color nephritis = { 39, 174, 96 };
const struct color midnight = { 44, 62, 80 };
const struct color emerald = { 46, 204, 113 };
const struct color sunflower = { 241, 196, 15 };
const struct color alizarin = { 231, 76, 60 };

class Window {
	//GLFWwindow* window;
public:
	Window(const char* title, int sync, int width, int height,
		void(*key)(GLFWwindow*, int, int, int, int));
	~Window();
	//void startDisplayLoop(void (*display)(Window*)); // this program isn't going to use this
	GLFWwindow* glwindow;
};

#endif
