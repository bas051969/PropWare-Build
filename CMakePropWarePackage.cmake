set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
set(CPACK_INSTALL_CMAKE_PROJECTS "${PROPWARE_PATH}/bin;PropWare;ALL;/")
set(CPACK_PACKAGE_VENDOR "David Zemon")
set(CPACK_PACKAGE_VERSION "releasee-2.0-nightly")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_SOURCE_STRIP_FILES false)

set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_RESOURCE_FILE_README ${PROPWARE_PATH}/README.md)

include(CPack)
