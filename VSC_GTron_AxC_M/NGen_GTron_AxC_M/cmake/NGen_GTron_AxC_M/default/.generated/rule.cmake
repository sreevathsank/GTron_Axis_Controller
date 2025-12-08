# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/sreevathsank/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(NGen_GTron_AxC_M_default_default_ARM_GCC_assemble_rule target)
    set(options
        "-g"
        "${ASSEMBLER_PRE}"
        "-gdwarf-2"
        "-mcpu=cortex-m0plus"
        "-mthumb"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--gdwarf-2")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=1"
        PRIVATE "__SAMC21N18A__")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/SAMC21_DFP/3.9.248/samc21n/include")
endfunction()
function(NGen_GTron_AxC_M_default_default_ARM_GCC_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "-g"
        "-gdwarf-2"
        "-mcpu=cortex-m0plus"
        "-mthumb"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--gdwarf-2,-g,--defsym=__DEBUG=1")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=1"
        PRIVATE "__SAMC21N18A__"
        PRIVATE "default=default")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/SAMC21_DFP/3.9.248/samc21n/include")
endfunction()
function(NGen_GTron_AxC_M_default_default_ARM_GCC_compile_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "-mcpu=cortex-m0plus"
        "-x"
        "c"
        "-mthumb"
        "-O1"
        "-ffunction-sections"
        "-mlong-calls"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "__SAMC21N18A__"
        PRIVATE "default=default")
    target_include_directories(${target}
        PRIVATE "${PACK_REPO_PATH}/Microchip/SAMC21_DFP/3.9.248/samc21n/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/mcc"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/ATSAMC21N18A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/mcc"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/ATSAMC21N18A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0")
endfunction()
function(NGen_GTron_AxC_M_default_default_ARM_GCC_compile_cpp_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "-x"
        "c++"
        "-mcpu=cortex-m0plus"
        "-mthumb"
        "-O1"
        "-ffunction-sections"
        "-fno-rtti"
        "-fno-exceptions"
        "-mlong-calls"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "__SAMC21N18A__"
        PRIVATE "default=default")
    target_include_directories(${target}
        PRIVATE "${PACK_REPO_PATH}/Microchip/SAMC21_DFP/3.9.248/samc21n/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/mcc"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/ATSAMC21N18A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/mcc"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/ATSAMC21N18A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0")
endfunction()
function(NGen_GTron_AxC_M_default_link_rule target)
    set(options
        "-gdwarf-2"
        "${MP_EXTRA_LD_PRE}"
        "-mthumb"
        "--specs=nosys.specs"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1"
        "-Wl,--gc-sections")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__SAMC21N18A__"
        PRIVATE "default=default")
endfunction()
function(NGen_GTron_AxC_M_default_objcopy_ihex_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=ihex --remove-section=.eeprom --remove-section=.fuse --remove-section=.lock --remove-section=.signature ${NGen_GTron_AxC_M_default_image_name} ${NGen_GTron_AxC_M_default_image_base_name}.hex
        WORKING_DIRECTORY ${NGen_GTron_AxC_M_default_output_dir})
endfunction()
function(NGen_GTron_AxC_M_default_objcopy_eep_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings --output-target=binary ${NGen_GTron_AxC_M_default_image_name} ${NGen_GTron_AxC_M_default_image_base_name}.eep
        WORKING_DIRECTORY ${NGen_GTron_AxC_M_default_output_dir})
endfunction()
function(NGen_GTron_AxC_M_default_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers --source ${NGen_GTron_AxC_M_default_image_name} > ${NGen_GTron_AxC_M_default_image_base_name}.lss
        WORKING_DIRECTORY ${NGen_GTron_AxC_M_default_output_dir})
endfunction()
function(NGen_GTron_AxC_M_default_objcopy_srec_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=srec --remove-section=.eeprom --remove-section=.fuse --remove-section=.lock --remove-section=.signature ${NGen_GTron_AxC_M_default_image_name} ${NGen_GTron_AxC_M_default_image_base_name}.srec
        WORKING_DIRECTORY ${NGen_GTron_AxC_M_default_output_dir})
endfunction()
