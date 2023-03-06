#include "Graphics.h"

struct Window createWindow(){
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwInit();

	window = glfwCreateWindow(500, 500, "Enigma", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	struct Window win = {window, 500, 500};
	return win;
}

struct Frame createTexture(){
	struct Frame frame;
	glGenTextures(1, &frame.texture);
	glBindTexture(GL_TEXTURE_2D, frame.texture);
	glGenFramebuffers(1, &frame.framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frame.framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame.texture, 0);
	return frame;
}
