#include "shader.h"

struct shaderManagement *g_shaderManagerment;

int initShaderManagement()
{
    g_shaderManagerment = (struct shaderManagement *)malloc(sizeof(struct shaderManagement) + sizeof(struct shaderInfo) * DEFAULT_SIZE_OF_SHADERS);
    if (!g_shaderManagerment) {
	fprintf(stderr, "%s, failed to alloc memory for g_shaderManagerment\n", __func__);
	return -1;
    }

    return 0;
}

int registerShaderInfo(struct shaderInfo *info)
{
    int ret = 0;


    return 0;
}
