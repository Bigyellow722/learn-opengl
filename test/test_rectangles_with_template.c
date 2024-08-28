#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

#include "core/window.h"
#include "core/log.h"
const char *vertexShaderSource = "#version 330 core\n"
				 "layout (location = 0) in vec3 aPos;\n"
				 "void main()\n"
				 "{\n"
				 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
				 "out vec4 FragColor;\n"
				 "void main()\n"
				 "{\n"
				 "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				 "}\n\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    /* the first two parameters set the location of the lower left corner of the window */
    /* the third and fourth parameter set the width and height of the rendering window in pixels */
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    struct window *win = createWindow("Learn OpenGL", 800, 600);
    if (!win) {
	err("Failed to create Window\n");
	return -1;
    }
    glfwMakeContextCurrent(win->m_window);
    /* GLFW will call frambuffer_size_callback on every window resize */
    glfwSetFramebufferSizeCallback(win->m_window, framebuffer_size_callback);

    /* load the address of the opengl function pointers which is OS-specific */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        err("Failed to initialize GLAD\n");
        return -1;
    }

#if 0
    float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
    };
#endif
    float vertices[] = {
	0.5f,  0.5f, 0.0f, /* top right */
	0.5f, -0.5f, 0.0f, /* bottom right */
	-0.5f, -0.5f, 0.0f, /* bottom left */
	-0.5f, 0.5f, 0.0f  /* top left */
    };

    unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
    };
    
    /* create a element buffer array */
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    /* create a Vertex attribute array */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    /* create a vertex buffer object */
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /* load vertices into gpu memory */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* load element array after vertices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /* create a vertex shader */
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	err( "failed to compile vertex shader, err:%s\n", infoLog);
    }

    /* create a fragment shader */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	err( "failed to compile fragment shader, err:%s\n", infoLog);
    }

    /* create a share program */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	err( "failed to compile shader program, err:%s\n", infoLog);
    }

    /* free shaders */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* render loop */
    while (!glfwWindowShouldClose(win->m_window)) {
	/* input handler defined by user */
        processInput(win->m_window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	/* whenever glClear is called, the entire color buffer will be filled with the color as configured by glClearColor. */
        glClear(GL_COLOR_BUFFER_BIT);

	/* activate shader program */
	glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	/* draw */
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	/* swap buffer */
        updateWindow(win);
    }

    //glfwTerminate();
    closeWindow(win);
    return 0;
}
