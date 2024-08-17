#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#define VERTEX_SHADER_PATH "../res/shader/vertexShader.glsl"
#define FRAGMENT_SHADER_PATH "../res/shader/fragmentShader.glsl"

static char *loadShader(const char *filePath)
{
    
    FILE *file = fopen(filePath, "r");
    if (!file) {
	fprintf(stderr, "%s, failed to open file\n", __func__);
	goto err_open_file;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
	fprintf(stderr, "%s, failed to allocate memory\n", __func__);
	goto err_alloc_buf;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
	fprintf(stderr, "%s, there is something wrong with reading file\n", __func__);
	goto err_read_file;

    }
    buffer[fileSize] = '\0';

    fprintf(stdout, "file content:\n %s\n", buffer);
    return buffer;

err_read_file:
    free(buffer);
err_alloc_buf:
    fclose(file);
err_open_file:
    return NULL;
}

static unsigned int compileShader(const char *shaderSource, enum shaderType type)
{
    unsigned int shader = 0;

    int shaderTypeGL;
    switch (type) {
    case VERTEX_SHADER:
	shaderTypeGL = GL_VERTEX_SHADER;
	break;
    case FRAGMENT_SHADER:
	shaderTypeGL = GL_FRAGMENT_SHADER;
	break;
    default:
	fprintf(stderr, "%s, unsupport type: %d\n", __func__, type);
	return 0;
    };

    shader = glCreateShader(shaderTypeGL);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(shader, 512, NULL, infoLog);
	fprintf(stderr, "failed to compile vertex shader, err:%s\n", infoLog);
    }

    return shader;
}

static unsigned int loadAndCompileShader(const char *filePath, enum shaderType type)
{
    unsigned int shader = 0;

    char *shaderSource = loadShader(filePath);
    if (!shaderSource) {
	fprintf(stderr, "%s, failed to load %s\n", __func__, filePath);
	return 0;
    }

    shader = compileShader((const char *)shaderSource, type);
    if (!shader) {
	fprintf(stderr, "%s, failed to compile shader\n", __func__);
    }

    return shader;
}

struct shaderOps gl_shaderOps = {
    .loadAndCompileShader = loadAndCompileShader,
};
