file(GLOB GOL_SRC "logic/*.cpp")
set(GOL_MAIN "main.cpp"

add_library(${GOL_LIB} ${GOL_SRC})

add_executable(${GOL_EXEC} ${GOL_MAIN})
target_link_libraries(${GOL_EXEC} ${GOL_LIB})