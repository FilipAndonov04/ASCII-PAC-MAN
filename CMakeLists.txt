cmake_minimum_required(VERSION 3.13)

project(pac-man)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

# create resources symlink in build directory
set(RESOURCES_DIR resources/)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/${RESOURCES_DIR}
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/${RESOURCES_DIR}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    RESOURCES_PATH=\"./${RESOURCES_DIR}\"
)