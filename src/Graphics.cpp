#include "Graphics.h"

Window createWindow(unsigned int dx, unsigned int dy){
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwInit();

	window = glfwCreateWindow(dx, dy, "Enigma", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	Window win = {window, dx, dy};
	return win;
}

GLuint createShader(int type, const char* source){
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	checkShaderCompilation(shader, type);
	return shader;
}

void checkShaderCompilation(unsigned int shader, int type){
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		const char* ctype;
		switch(type){
			case GL_VERTEX_SHADER:
				ctype = "VERTEX";
				break;
			case GL_FRAGMENT_SHADER:
				ctype = "FRAGMENT";
				break;
			case GL_COMPUTE_SHADER:
				ctype = "COMPUTE";
				break;
		}
		std::cerr << "ERROR::SHADER::"<<ctype<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}