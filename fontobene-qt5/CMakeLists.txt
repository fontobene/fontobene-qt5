# Add header-only library
add_library(fontobene_qt5 INTERFACE)
target_include_directories(fontobene_qt5
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

# Install target
include(GNUInstallDirs)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fontobene-qt5
    FILES_MATCHING PATTERN "*.h"
)

# Alias to namespaced variant
add_library(FontoBene::FontoBeneQt5 ALIAS fontobene_qt5)
