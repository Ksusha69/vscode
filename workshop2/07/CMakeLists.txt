add_executable(07 main.cpp)

target_include_directories(07 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(07 PUBLIC cxx_std_17)
target_compile_definitions(07 PRIVATE SFML_STATIC)

target_link_libraries(07 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})