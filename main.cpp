#include "window/window.hpp"

int main(int argc, char* argv[]) {
    Window mainwindow("Collisions", 0, 800, 800, NULL);

    while(!glfwWindowShouldClose(mainwindow.glwindow)) {
        continue;
    }
}