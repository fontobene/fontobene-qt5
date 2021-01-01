# Test binary
add_executable(fontobene_qt5_tests
    main.cpp
)

# Compiler defines
add_definitions(-DTESTFILEPATH="${CMAKE_CURRENT_SOURCE_DIR}/fonto.bene")

# Fail on warnings
target_compile_options(fontobene_qt5_tests PRIVATE -Werror -Wall -Wextra)

# Linking
target_link_libraries(fontobene_qt5_tests fontobene_qt5 Qt5::Core)

# Output binary name
set_target_properties(fontobene_qt5_tests PROPERTIES OUTPUT_NAME fontobene-qt5-tests)
