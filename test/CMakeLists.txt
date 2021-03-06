find_package(GTest)
find_package(rapidassist)

add_executable(shellanything_unittest
  ${SHELLANYTHING_EXPORT_HEADER}
  ${SHELLANYTHING_VERSION_HEADER}
  ${SHELLANYTHING_CONFIG_HEADER}
  main.cpp
  TestConfigManager.cpp
  TestConfigManager.h
  TestConfiguration.cpp
  TestConfiguration.h
  TestContext.cpp
  TestContext.h
  TestItem.cpp
  TestItem.h
  TestNode.cpp
  TestNode.h
  TestPlatform.cpp
  TestPlatform.h
  TestPropertyManager.cpp
  TestPropertyManager.h
  TestValidator.cpp
  TestValidator.h
)

# Unit test projects requires to link with pthread if also linking with gtest
if(NOT WIN32)
  set(PTHREAD_LIBRARIES -pthread)
endif()

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(shellanything_unittest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(shellanything_unittest PRIVATE ${GTEST_INCLUDE_DIR} rapidassist)
add_dependencies(shellanything_unittest shellanything)
target_link_libraries(shellanything_unittest PUBLIC shellanything PRIVATE ${PTHREAD_LIBRARIES} ${GTEST_LIBRARIES} rapidassist )

# Copy test files database to target dir
add_custom_command( TARGET shellanything_unittest POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/test_files $<TARGET_FILE_DIR:shellanything_unittest>/test_files
                    COMMENT "Copying test_files database.")

# Copy test files to build dir for local execution (from within the IDE)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS shellanything_unittest
        EXPORT shellanything-targets
        ARCHIVE DESTINATION ${SHELLANYTHING_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${SHELLANYTHING_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${SHELLANYTHING_INSTALL_BIN_DIR}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
        DESTINATION ${SHELLANYTHING_INSTALL_BIN_DIR}
)
