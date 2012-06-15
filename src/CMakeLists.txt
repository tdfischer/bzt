set(bzt_SRCS
  main.cpp
  client.cpp
  bug.cpp
  formatting.cpp
  configuration.cpp
  command.cpp
)

macro(add_bzt_command NAME SOURCE)
  add_library(command-${NAME} SHARED ${SOURCE})
  install(TARGETS command-${NAME} DESTINATION libexec/bzt/)
  set_target_properties(command-${NAME} PROPERTIES
    LIBRARY_OUTPUT_NAME ${NAME}
    PREFIX ""
  )
endmacro(add_bzt_command)

add_bzt_command(list commands/list.cpp)
add_bzt_command(show commands/show.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
include_directories(${GLIB_INCLUDE_DIRS} ${XMLRPC_INCLUDE_DIRS} ${YAML_INCLUDE_DIRS})

add_executable(bzt ${bzt_SRCS})

target_link_libraries(bzt ${XMLRPC_LIBRARIES} ${GLIB_LIBRARIES} ${YAML_LIBRARIES} dl)

install(TARGETS bzt DESTINATION bin)
