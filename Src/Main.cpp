#include <GLFW/glfw3.h>


int main(int argc, const char* argv[]) {

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}