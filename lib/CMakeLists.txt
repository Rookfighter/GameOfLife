get_filename_component(DEP_INSTALL_DIR "./" ABSOLUTE)

# Information for installing SFML
set(SFML_ARCH_NAME "SFML-2.2.tar.gz")
set(SFML_ARCH_PATH "${DEP_INSTALL_DIR}/${SFML_ARCH_NAME}")
set(SFML_RESULT_NAME "SFML-2.2")
set(SFML_RESULT_DIR "${DEP_INSTALL_DIR}/${SFML_RESULT_NAME}")
set(SFML_DONWLOAD_URL "www.sfml-dev.org/files/SFML-2.2-linux-gcc-64-bit.tar.gz")

# Information for installing Catch
set(CATCH_ARCH_NAME "Catch.zip")
set(CATCH_ARCH_PATH "${DEP_INSTALL_DIR}/${CATCH_ARCH_NAME}")
set(CATCH_EXTRACT_NAME "Catch-master")
set(CATCH_RESULT_NAME "Catch")
set(CATCH_RESULT_DIR "${DEP_INSTALL_DIR}/${CATCH_RESULT_NAME}")
set(CATCH_DONWLOAD_URL "https://github.com/philsquared/Catch/archive/master.zip")

message(STATUS "Installing dependencies")

# install SFML
if(NOT EXISTS "${SFML_RESULT_DIR}")
    message(STATUS "  Installing ${SFML_RESULT_NAME}")

    file(DOWNLOAD ${SFML_DONWLOAD_URL} ${SFML_ARCH_PATH})
    execute_process(COMMAND tar xzf ${SFML_ARCH_NAME} WORKING_DIRECTORY
    ${DEP_INSTALL_DIR})
    file(REMOVE ${SFML_ARCH_NAME})
else(NOT EXISTS "${SFML_RESULT_DIR}")
    message(STATUS "  ${SFML_RESULT_NAME} is already installed")
endif(NOT EXISTS "${SFML_RESULT_DIR}")

# install Catch
if(NOT EXISTS "${CATCH_RESULT_DIR}")
    message(STATUS "  Installing ${CATCH_RESULT_NAME}")

    file(DOWNLOAD ${CATCH_DONWLOAD_URL} ${CATCH_ARCH_PATH})
    execute_process(COMMAND unzip -qq ${CATCH_ARCH_NAME} WORKING_DIRECTORY
    ${DEP_INSTALL_DIR})
    file(REMOVE ${CATCH_ARCH_NAME})
    file(RENAME ${CATCH_EXTRACT_NAME} ${CATCH_RESULT_NAME})
else(NOT EXISTS "${CATCH_RESULT_DIR}")
    message(STATUS "  ${CATCH_RESULT_NAME} is already installed")
endif(NOT EXISTS "${CATCH_RESULT_DIR}")