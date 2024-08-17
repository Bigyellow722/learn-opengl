#ifndef _SHADER_H_
#define _SHADER_H_

#include <stdio.h>
#include <stdlib.h>
    
#define DEFAULT_SIZE_OF_SHADERS 2

enum shaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    MAX_TYPE_SHADER,
};

/* TODO: Hide all details about opengl */
struct shaderInfo {
    unsigned int shader;
    
};


struct shaderProgramOps {
    unsigned int (* loadAndCompile)(void);
    unsigned int (* loadAndCompileShader)(const char *filePath);
};


struct shaderManagement {
    struct shaderInfo shader[MAX_TYPE_SHADER];
};

struct shaderProgram {
    unsigned int shaderProgram;
    struct shaderManagement *sm;
    struct shaderProgramOps *ops;
};


int registerShaderByFilePath(enum shaderType type, const char *filePath);
/* different shaders are store at ShaderManagement */
int initShaderManagement();
/* init a shader program in a render flow */
int initShaderProgram(struct shaderProgram* prog);


#endif
