

# for core

add_executable(test_log test_log.c)
target_link_libraries(test_log PRIVATE template)

add_executable(test_memory test_memory.c)
target_link_libraries(test_memory PRIVATE template)

# for cglm
add_executable(test_cglm test_cglm.c)
target_link_libraries(test_cglm PRIVATE template)
target_link_options(test_cglm PRIVATE -Wl,--whole-archive $<TARGET_FILE:template> -Wl,--no-whole-archive)
# for rendering

add_executable(test_triangles test_triangles.c)
target_link_libraries(test_triangles template)
add_executable(test_rectangles test_rectangles.c)
target_link_libraries(test_rectangles template)
add_executable(test_rectangles_with_template test_rectangles_with_template.c)
target_link_libraries(test_rectangles_with_template template)
target_link_options(test_rectangles_with_template PRIVATE -Wl,--whole-archive $<TARGET_FILE:template> -Wl,--no-whole-archive)
add_executable(test_uniform_triangle test_uniform_triangle.c)
target_link_libraries(test_uniform_triangle template)
#add_executable(test_shader test_shader.c)
#target_link_libraries(test_shader template)




# Add a test to CTest
## core
add_test(NAME LogTest COMMAND test_log)

## rendering
add_test(NAME TrianglesTest COMMAND test_triangles)
add_test(NAME RectanglesTest COMMAND test_rectangles)
add_test(NAME UniformTriangleTest COMMAND test_uniform_triangle)
#add_test(NAME ShaderTest COMMAND test_shader)
