add_executable(06 main.cpp)

target_include_directories(06 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(06 PUBLIC cxx_std_17)
target_compile_definitions(06 PRIVATE SFML_STATIC)

target_link_libraries(06 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})