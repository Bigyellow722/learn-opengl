#include "shader.h"
#include <stdio.h>

extern struct shaderOps gl_shaderOps;

int main()
{
    int ret = 0;
    printf("init shader management\n");
    ret = initShaderManagement();
    printf("create shader program");
    
    printf("register vertex shader\n");
    
}
