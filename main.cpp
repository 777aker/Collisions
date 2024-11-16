#include "window/window.hpp"

void key(GLFWwindow *windowobj, int key, int scancode, int action, int mods) {
	if (action == GLFW_RELEASE)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(windowobj, 1);
		break;
	}
}

void display_loop(Window *windowobj) {
	while (!glfwWindowShouldClose(windowobj->glwindow)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// want to see fps
		glColor3ub(nephritis.r, nephritis.g, nephritis.b);
		glRasterPos2i(-windowobj->dim * windowobj->asp + 5, windowobj->dim - 5);
		Print("FPS=%d", windowobj->FramesPerSecond());

		// check for display errors
		int err = glGetError();
		if (err)
		{
			fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
		}
		// swap buffers
		glFlush();
		glfwSwapBuffers(windowobj->glwindow);
		// get key board events
		glfwPollEvents();
	}
}

int main(int argc, char *argv[]) {
	Window mainwindow("Collisions", 0, 800, 800, key);
	glDisable(GL_DEPTH_TEST);
	glClearColor((float)midnight.r / 255.0, (float)midnight.g / 255.0, (float)midnight.b / 255.0, 1.0);

	display_loop(&mainwindow);
}