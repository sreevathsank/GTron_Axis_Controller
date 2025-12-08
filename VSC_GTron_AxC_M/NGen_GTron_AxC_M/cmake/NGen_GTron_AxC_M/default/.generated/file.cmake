# The following variables contains the files used by the different stages of the build process.
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assemble)
set_source_files_properties(${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/can_task.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/cmd_parser.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/freertos_hooks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/initialization.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/interrupts.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/libc_syscalls.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/osal/osal_freertos.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/adc/plib_adc0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/can/plib_can1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/clock/plib_clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/eic/plib_eic.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/evsys/plib_evsys.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/nvic/plib_nvic.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/nvmctrl/plib_nvmctrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/port/plib_port.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/rstc/plib_rstc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/tc/plib_tc2.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/tc/plib_tc4.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/wdt/plib_wdt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/startup_xc32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/stdio/xc32_monitor.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/system/console/src/sys_console.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/system/console/src/sys_console_uart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/system/debug/src/sys_debug.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/system/int/src/sys_int.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/debug_logger.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/health_task.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/croutine.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/event_groups.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/list.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/queue.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/stream_buffer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/third_party/rtos/FreeRTOS/Source/timers.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/tmc2209_motion.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/tmc4671_motion.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../startup_samc21n18a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../system_samc21n18a.c")
set_source_files_properties(${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile_cpp)
set_source_files_properties(${NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_link)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_ihex)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_eep)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_lss)
set(NGen_GTron_AxC_M_default_default_ARM_GCC_FILE_TYPE_objcopy_srec)

# The linker script used for the build.
set(NGen_GTron_AxC_M_default_LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/ATSAMC21N18A.ld")
set(NGen_GTron_AxC_M_default_image_name "default.elf")
set(NGen_GTron_AxC_M_default_image_base_name "default")

# The output directory of the final image.
set(NGen_GTron_AxC_M_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/NGen_GTron_AxC_M")

# The full path to the final image.
set(NGen_GTron_AxC_M_default_full_path_to_image ${NGen_GTron_AxC_M_default_output_dir}/${NGen_GTron_AxC_M_default_image_name})
