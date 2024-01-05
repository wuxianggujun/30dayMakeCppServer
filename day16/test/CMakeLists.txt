file(GLOB_RECURSE DAY_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

foreach (day_test_source ${DAY_TEST_SOURCES})
    get_filename_component(day_test_filename ${day_test_source} NAME)
    string(REPLACE ".cpp" "" day_test_name ${day_test_filename})

    add_executable(${day_test_filename} EXCLUDE_FROM_ALL ${day_test_source})
    add_dependencies(build-tests ${day_test_filename})
    add_dependencies(check-tests ${day_test_filename})

    target_link_libraries(${day_test_filename} day_shared)

    set_target_properties(${day_test_filename}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            COMMAND ${day_test_filename}
    )
endforeach (day_test_source ${DAY_TEST_SOURCES})