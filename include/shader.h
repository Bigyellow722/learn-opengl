#ifndef _SHADER_H_
#define _SHADER_H_

#include <stdio.h>
#include <stdlib.h>
    
#define DEFAULT_SIZE_OF_SHADERS 2

enum shaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
};

/* TODO: Hide all details about opengl */
struct shaderInfo {
    unsigned int shader;
    enum shaderType type;
};


struct shaderOps {
    unsigned int (* loadAndCompileShader)(const char *filePath, enum shaderType type);
    
};


struct shaderManagement {
    size_t availableIndex;
    size_t capacity;
    struct shaderOps *ops;
    struct shaderInfo shader[];
};

struct shaderProgram {
    unsigned int shaderProgram;
    struct shaderManagement *sm;
    struct shaderProgramOps *ops;
};

/* for struct shaderManagement */
int registerShaderOps(struct shaderOps *ops);
int registerShaderByFilePath(enum shaderType type, const char *filePath);
int initShaderManagement();



#endif
