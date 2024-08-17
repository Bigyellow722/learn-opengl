add_library(core OBJECT
		 init.c
		 log.c
		 memory.c)

target_include_directories(core PUBLIC
				${CMAKE_CURRENT_SOURCE_DIR}/)
