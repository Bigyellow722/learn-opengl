#include "shader.h"

struct shaderManagement *g_shaderManagerment;
struct shaderOps *g_shaderOps;

int registerShaderOps(struct shaderOps *ops)
{
    if (!ops) {
	fprintf(stderr, "%s, ops is null\n", __func__);
	return -1;
    }
    g_shaderOps = ops;
    return 0;
}

int initShaderManagement()
{
    g_shaderManagerment = (struct shaderManagement *)malloc(sizeof(struct shaderManagement) + sizeof(struct shaderInfo) * DEFAULT_SIZE_OF_SHADERS);
    if (!g_shaderManagerment) {
	fprintf(stderr, "%s, failed to alloc memory for g_shaderManagerment\n", __func__);
	return -1;
    }
    g_shaderManagerment->availableIndex = 0;
    g_shaderManagerment->capacity = DEFAULT_SIZE_OF_SHADERS;
    g_shaderManagerment->ops = g_shaderOps;
    return 0;
}

int initShaderInfo(enum shaderType type, const char *filePath)
{
    int ret = 0;

    g_shaderManagerment->shader[g_shaderManagerment->availableIndex].type = type;
    g_shaderManagerment->shader[g_shaderManagerment->availableIndex].shader = g_shaderManagerment->ops->loadAndCompileShader(filePath, type);

    return 0;
}

int registerShaderByFilePath(enum shaderType type, const char *filePath)
{
    if (g_shaderManagerment->capacity <= g_shaderManagerment->availableIndex) {
	/* increase capacity to 2 times */
	g_shaderManagerment = (struct shaderManagement *)realloc(g_shaderManagerment, sizeof(struct shaderManagement) + sizeof(struct shaderInfo) * 2 * g_shaderManagerment->capacity);
	if (!g_shaderManagerment) {
	    fprintf(stderr, "%s, no more enough memory for shaderManagement\n", __func__);
	    return -1;
	}
    }
    /* initShader Info */
    int ret = initShaderInfo(type, filePath);
    if (ret) {
	fprintf(stderr, "%s, failed to init shaderInfo\n", __func__);
	return -1;
    }
    g_shaderManagerment->availableIndex++;
    return 0;
}

int unregisterShaderByFilePath(unsigned int shader)
{
    int ret = 0;

    return ret;
}
