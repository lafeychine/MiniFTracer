add_executable(ftrace
  src/main.c
  src/crawler.c
  src/signal.c
  src/syscall.c
  src/db/sys_interrupt_table.c
  src/db/sys_syscall_table.c)

target_include_directories(ftrace PRIVATE include trace)

target_link_libraries(ftrace elf trace)


# Syscall generators
function (generate_syscall _targetName _outputFile)
  add_custom_command(OUTPUT src/db/${_outputFile}.c
                     COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_sys_tables.py --file ${_targetName} --output src/db/${_outputFile}.c --table_name ${_outputFile})
endfunction()

generate_syscall("i386~syscallent" "sys_interrupt_table")
generate_syscall("x86_64~syscallent" "sys_syscall_table")
