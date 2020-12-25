add_library(trace
  src/fork.c
  src/ftrace.c
  src/loop.c)

target_include_directories(trace PUBLIC export PRIVATE include)
