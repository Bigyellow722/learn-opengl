include_directories(../include)
add_executable(test_triangles test_triangles.c)
target_link_libraries(test_triangles template)

# Add a test to CTest
add_test(NAME TrianglesTest COMMAND test_triangles)
