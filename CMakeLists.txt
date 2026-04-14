cmake_minimum_required(VERSION 3.13)

project(pac-man)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

# create assets symlink in build directory
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources
)