add_executable(test_print test_print.cpp ../src/print.c)
target_link_libraries(test_print fffmock)