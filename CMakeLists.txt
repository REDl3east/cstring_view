cmake_minimum_required(VERSION 3.14.0)
project(piping-hot-images VERSION 0.1.0)

function(add_example SRC)
  get_filename_component(TARGET_NAME ${SRC} NAME_WE)
  add_executable(${TARGET_NAME} ${SRC})
  target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
  set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
endfunction(add_example)

function(add_test_me SRC)
  get_filename_component(TARGET_NAME ${SRC} NAME_WE)
  add_executable(${TARGET_NAME} ${SRC})
  target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
  add_test(
    NAME    ${TARGET_NAME} 
    COMMAND ${TARGET_NAME}
  )
  set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
endfunction(add_test_me)


file(GLOB EXAMPLE_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.c)
foreach(file ${EXAMPLE_SRCS})
  add_example(${file})
endforeach(file ${EXAMPLE_SRCS})

enable_testing()
file(GLOB EXAMPLE_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c)
foreach(file ${EXAMPLE_SRCS})
  add_test_me(${file})
endforeach(file ${EXAMPLE_SRCS})
