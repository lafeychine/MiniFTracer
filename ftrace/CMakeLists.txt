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
function (generate_syscall _targetName)
  add_custom_command(OUTPUT src/db/${_targetName}.c
                     COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_sys_tables.py --input ${CMAKE_CURRENT_SOURCE_DIR}/scripts/${_targetName}.data --output src/db/${_targetName}.c --table_name ${_targetName})
endfunction()

generate_syscall(sys_interrupt_table)
generate_syscall(sys_syscall_table)

