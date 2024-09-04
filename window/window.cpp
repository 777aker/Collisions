/*
* Window class
* Handles making a window
*/
#include "window.hpp"

double dim = 100; // size of the world
double asp = 1; // aspect ratio
bool wasResized = false; // called resize function

// Fatal error occured
static void Fatal(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}

// different type of error occured 
static void error(int error, const char* text) {
	fprintf(stderr, "GLFW error %d: %s\n", error, text);
}

// resize the window
void reshape(GLFWwindow* windowobj, int width, int height) {
	glfwGetFramebufferSize(windowobj, &width, &height);
	asp = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-asp * dim, asp * dim, -dim, +dim, -dim, +dim);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	wasResized = true;
}

// initialize a lot of window stuff
Window::Window(const char* title, int sync, int width, int height,
	void(*key)(GLFWwindow*, int, int, int, int)) {
	// initialize GLFW
	if (!glfwInit()) Fatal("Cannot initialize glfw\n");

	// Error callback
	glfwSetErrorCallback(error);

	// set window properties
	glfwWindowHint(GLFW_RESIZABLE, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);

	// create window
	glwindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!glwindow) Fatal("Cannot create GLFW window\n");
	glfwMakeContextCurrent(glwindow);

	// enable vsync 
	glfwSwapInterval(sync);

	glfwSetWindowSizeCallback(glwindow, &reshape);
	// set window size and call reshape
	glfwGetWindowSize(glwindow, &width, &height);
	reshape(glwindow, width, height);

	// set callback for keyboard input
	glfwSetKeyCallback(glwindow, key);
}

// clean up window
Window::~Window() {
	glfwDestroyWindow(glwindow);
	glfwTerminate();
}