WRAP_GGO(rtkosem_GGO_C rtkosem.ggo ../rtkinputprojections_section.ggo ../rtk3Doutputimage_section.ggo ../rtkprojectors_section.ggo ../rtkiterations_section.ggo ${RTK_BINARY_DIR}/rtkVersion.ggo)
add_executable(rtkosem rtkosem.cxx ${rtkosem_GGO_C})
target_link_libraries(rtkosem RTK)

# Installation code
if(NOT RTK_INSTALL_NO_EXECUTABLES)
  foreach(EXE_NAME rtkosem)
    install(TARGETS ${EXE_NAME}
      RUNTIME DESTINATION ${RTK_INSTALL_RUNTIME_DIR} COMPONENT Runtime
      LIBRARY DESTINATION ${RTK_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
      ARCHIVE DESTINATION ${RTK_INSTALL_ARCHIVE_DIR} COMPONENT Development)
  endforeach()
endif()

