#include <cglm/cglm.h>
#include "core/log.h"
int main() {
    // 1. Vector Operations
    vec3 v1 = {1.0f, 2.0f, 3.0f};
    vec3 v2 = {4.0f, 5.0f, 6.0f};
    vec3 result_vec;

    // Adding two vectors
    glm_vec3_add(v1, v2, result_vec);
    info("v1 + v2 = {%.2f, %.2f, %.2f}\n", result_vec[0], result_vec[1], result_vec[2]);

    // Normalizing a vector
    glm_vec3_normalize(result_vec);
    info("Normalized result_vec = {%.2f, %.2f, %.2f}\n", result_vec[0], result_vec[1], result_vec[2]);

    // 2. Matrix Operations
    mat4 identity_matrix, translation_matrix, result_matrix;

    // Creating an identity matrix
    glm_mat4_identity(identity_matrix);
    info("Identity matrix:\n");
    for (int i = 0; i < 4; i++) {
        info("{%.2f, %.2f, %.2f, %.2f}\n", identity_matrix[i][0], identity_matrix[i][1], identity_matrix[i][2], identity_matrix[i][3]);
    }

    // Creating a translation matrix
    glm_translate_make(translation_matrix, (vec3){1.0f, 2.0f, 3.0f});
    info("Translation matrix:\n");
    for (int i = 0; i < 4; i++) {
        info("{%.2f, %.2f, %.2f, %.2f}\n", translation_matrix[i][0], translation_matrix[i][1], translation_matrix[i][2], translation_matrix[i][3]);
    }

    // Multiplying the identity matrix with the translation matrix
    glm_mat4_mul(identity_matrix, translation_matrix, result_matrix);
    info("Result matrix (Identity * Translation):\n");
    for (int i = 0; i < 4; i++) {
        info("{%.2f, %.2f, %.2f, %.2f}\n", result_matrix[i][0], result_matrix[i][1], result_matrix[i][2], result_matrix[i][3]);
    }

    // 3. Creating a Perspective Projection Matrix
    mat4 projection_matrix;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection_matrix);
    info("Perspective projection matrix:\n");
    for (int i = 0; i < 4; i++) {
        info("{%.2f, %.2f, %.2f, %.2f}\n", projection_matrix[i][0], projection_matrix[i][1], projection_matrix[i][2], projection_matrix[i][3]);
    }

    return 0;
}

