#include "window/window.hpp"

int main(int argc, char* argv[]) {
    Window mainwindow("Collisions", 0, 800, 800, NULL);
    glDisable(GL_DEPTH_TEST);
    glClearColor((float)midnight.r/255.0, (float)midnight.g/255.0, (float)midnight.b/255.0, 1.0);

    while(!glfwWindowShouldClose(mainwindow.glwindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // check for display errors
		int err = glGetError();
		if (err) {
			fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
		}
		// swap buffers
		glFlush();
		glfwSwapBuffers(mainwindow.glwindow);
		// get key board events
		glfwPollEvents();
    }
}