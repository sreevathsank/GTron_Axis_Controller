# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(NGen_GTron_AxC_M_default_library_list )

# Handle files with suffix s, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assemble)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_assemble OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assemble})
    NGen_GTron_AxC_M_default_default_ARM_GCC_assemble_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_assemble)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_assemble>")

endif()

# Handle files with suffix S, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assembleWithPreprocess)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_assembleWithPreprocess OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assembleWithPreprocess})
    NGen_GTron_AxC_M_default_default_ARM_GCC_assembleWithPreprocess_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_assembleWithPreprocess)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_compile OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile})
    NGen_GTron_AxC_M_default_default_ARM_GCC_compile_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_compile)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_compile>")

endif()

# Handle files with suffix cpp, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile_cpp)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_compile_cpp OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile_cpp})
    NGen_GTron_AxC_M_default_default_ARM_GCC_compile_cpp_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_compile_cpp)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_compile_cpp>")

endif()

# Handle files with suffix elf, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_ihex)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_ihex OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_ihex})
    NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_ihex_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_ihex)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_ihex>")

endif()

# Handle files with suffix elf, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_eep)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_eep OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_eep})
    NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_eep_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_eep)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_eep>")

endif()

# Handle files with suffix elf, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_lss)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_lss OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_lss})
    NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_lss_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_lss)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_lss>")

endif()

# Handle files with suffix elf, for group default-ARM-GCC
if(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_srec)
add_library(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_srec OBJECT ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_srec})
    NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_srec_rule(NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_srec)
    list(APPEND NGen_GTron_AxC_M_default_library_list "$<TARGET_OBJECTS:NGen_GTron_AxC_M_default_default_ARM_GCC_objcopy_srec>")

endif()


# Main target for this project
add_executable(NGen_GTron_AxC_M_default_image_RBHAEjJz ${NGen_GTron_AxC_M_default_library_list})

set_target_properties(NGen_GTron_AxC_M_default_image_RBHAEjJz PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${NGen_GTron_AxC_M_default_output_dir})
set_target_properties(NGen_GTron_AxC_M_default_image_RBHAEjJz PROPERTIES OUTPUT_NAME "default")
set_target_properties(NGen_GTron_AxC_M_default_image_RBHAEjJz PROPERTIES SUFFIX ".elf")

target_link_libraries(NGen_GTron_AxC_M_default_image_RBHAEjJz PRIVATE ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_link})

#Add objcopy steps
NGen_GTron_AxC_M_default_objcopy_ihex_rule(NGen_GTron_AxC_M_default_image_RBHAEjJz)
NGen_GTron_AxC_M_default_objcopy_eep_rule(NGen_GTron_AxC_M_default_image_RBHAEjJz)
NGen_GTron_AxC_M_default_objcopy_lss_rule(NGen_GTron_AxC_M_default_image_RBHAEjJz)
NGen_GTron_AxC_M_default_objcopy_srec_rule(NGen_GTron_AxC_M_default_image_RBHAEjJz)

# Add the link options from the rule file.
NGen_GTron_AxC_M_default_link_rule(NGen_GTron_AxC_M_default_image_RBHAEjJz)



