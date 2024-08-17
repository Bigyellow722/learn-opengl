#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


const char *vertexShaderSource = "#version 460 core\n"
				 "layout (location = 0) in vec3 aPos;\n"
				 "void main()\n"
				 "{\n"
				 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				 "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
				   "out vec4 FragColor;\n"
				   "uniform vec4 ourColor;\n"
				   "void main()\n"
				   "{\n"
				   "  FragColor = ourColor;\n"
				   "}\n\0";

void APIENTRY glDebugOutput(GLenum source,
			    GLenum type,
			    unsigned int id,
			    GLenum severity,
			    GLsizei length,
			    const char *message,
			    const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    fprintf(stderr, "---------------\n");
    fprintf(stderr, "Debug message %d: %s\n)", id, message);
    switch (source) {
    case GL_DEBUG_SOURCE_API:
	fprintf(stderr, "Source: API"); break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
	fprintf(stderr, "Source: Window System"); break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
	fprintf(stderr, "Source: Shader Compiler"); break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
	fprintf(stderr, "Source: Third Party"); break;
    case GL_DEBUG_SOURCE_APPLICATION:
	fprintf(stderr, "Source: Application"); break;
    case GL_DEBUG_SOURCE_OTHER:
	fprintf(stderr, "Source: Other"); break;
    }
    fprintf(stderr, "\n");
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
	fprintf(stderr, "Type: Error"); break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
	fprintf(stderr, "Type: Deprecated Behaviour"); break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
	fprintf(stderr, "Type: Undefined Behaviour"); break;
    case GL_DEBUG_TYPE_PORTABILITY:
	fprintf(stderr, "Type: Portability"); break;
    case GL_DEBUG_TYPE_PERFORMANCE:
	fprintf(stderr, "Type: Performance"); break;
    case GL_DEBUG_TYPE_MARKER:
	fprintf(stderr, "Type: Marker"); break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
	fprintf(stderr, "Type: Push Group"); break;
    case GL_DEBUG_TYPE_POP_GROUP:
	fprintf(stderr, "Type: Pop Group"); break;
    case GL_DEBUG_TYPE_OTHER:
	fprintf(stderr, "Type: Other"); break;
    }
    fprintf(stderr, "\n");
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
	fprintf(stderr, "Severity: high"); break;
    case GL_DEBUG_SEVERITY_MEDIUM:
	fprintf(stderr, "Severity: medium"); break;
    case GL_DEBUG_SEVERITY_LOW:
	fprintf(stderr, "Severity: low"); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
	fprintf(stderr, "Severity: notification"); break;
    }
    fprintf(stderr, "\n");
}
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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 400, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    /* GLFW will call frambuffer_size_callback on every window resize */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* load the address of the opengl function pointers which is OS-specific */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }

    float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
    };

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

    /* specify vertex attribute */
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
	fprintf(stderr, "failed to compile vertex shader, err:%s\n", infoLog);
    }

    /* create a fragment shader */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	fprintf(stderr, "failed to compile fragment shader, err:%s\n", infoLog);
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
	fprintf(stderr, "failed to compile shader program, err:%s\n", infoLog);
    }

    /* free shaders */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* render loop */
    while (!glfwWindowShouldClose(window)) {
	/* input handler defined by user */
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	/* whenever glClear is called, the entire color buffer will be filled with the color as configured by glClearColor. */
        glClear(GL_COLOR_BUFFER_BIT);

	/* activate shader program */
	glUseProgram(shaderProgram);
	
	/* draw */
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* swap buffer */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
