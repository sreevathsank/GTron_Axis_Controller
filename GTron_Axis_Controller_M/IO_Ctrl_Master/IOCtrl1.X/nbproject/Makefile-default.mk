#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/bsp/bsp.c ../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/can/plib_can1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/debug/src/sys_debug.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/system_state.c interrupt_callbacks.c freertos_daemon.c global_vars.c ../src/debug_logger.c init_funcs.c ../src/can.c ../src/cmd_parser.c ../src/watchdog_kicker.c ../src/led_driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1434821282/bsp.o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/944882569/sys_debug.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/system_state.o ${OBJECTDIR}/interrupt_callbacks.o ${OBJECTDIR}/freertos_daemon.o ${OBJECTDIR}/global_vars.o ${OBJECTDIR}/_ext/1360937237/debug_logger.o ${OBJECTDIR}/init_funcs.o ${OBJECTDIR}/_ext/1360937237/can.o ${OBJECTDIR}/_ext/1360937237/cmd_parser.o ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o ${OBJECTDIR}/_ext/1360937237/led_driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1434821282/bsp.o.d ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d ${OBJECTDIR}/_ext/60165182/plib_can1.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d ${OBJECTDIR}/_ext/60167341/plib_eic.o.d ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1865521619/plib_port.o.d ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1832805299/sys_console.o.d ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d ${OBJECTDIR}/_ext/944882569/sys_debug.o.d ${OBJECTDIR}/_ext/14461671/sys_dma.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1624415188/port.o.d ${OBJECTDIR}/_ext/1624415188/portasm.o.d ${OBJECTDIR}/_ext/1665200909/heap_1.o.d ${OBJECTDIR}/_ext/404212886/croutine.o.d ${OBJECTDIR}/_ext/404212886/list.o.d ${OBJECTDIR}/_ext/404212886/queue.o.d ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d ${OBJECTDIR}/_ext/404212886/timers.o.d ${OBJECTDIR}/_ext/404212886/event_groups.o.d ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/system_state.o.d ${OBJECTDIR}/interrupt_callbacks.o.d ${OBJECTDIR}/freertos_daemon.o.d ${OBJECTDIR}/global_vars.o.d ${OBJECTDIR}/_ext/1360937237/debug_logger.o.d ${OBJECTDIR}/init_funcs.o.d ${OBJECTDIR}/_ext/1360937237/can.o.d ${OBJECTDIR}/_ext/1360937237/cmd_parser.o.d ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o.d ${OBJECTDIR}/_ext/1360937237/led_driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1434821282/bsp.o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/944882569/sys_debug.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/system_state.o ${OBJECTDIR}/interrupt_callbacks.o ${OBJECTDIR}/freertos_daemon.o ${OBJECTDIR}/global_vars.o ${OBJECTDIR}/_ext/1360937237/debug_logger.o ${OBJECTDIR}/init_funcs.o ${OBJECTDIR}/_ext/1360937237/can.o ${OBJECTDIR}/_ext/1360937237/cmd_parser.o ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o ${OBJECTDIR}/_ext/1360937237/led_driver.o

# Source Files
SOURCEFILES=../src/config/default/bsp/bsp.c ../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/can/plib_can1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/debug/src/sys_debug.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/system_state.c interrupt_callbacks.c freertos_daemon.c global_vars.c ../src/debug_logger.c init_funcs.c ../src/can.c ../src/cmd_parser.c ../src/watchdog_kicker.c ../src/led_driver.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=ATSAMC21N18A
ProjectDir="D:\pendrive_stuff\git_repos\gtron-io-controller-fw\IO_Ctrl_Master\IOCtrl1.X"
ProjectName=IOCtrl1
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif
MDFUHostPath="D:\MPLAB X IDE\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pymdfu-bin.exe"
PYFWImageBuilderPath="D:\MPLAB X IDE\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pyfwimagebuilder-bin.exe"

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [python ${ProjectDir}\hex2bin_converter.py ${ImagePath}]"
	@python ${ProjectDir}\hex2bin_converter.py ${ImagePath}
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATSAMC21N18A
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\ATSAMC21N18A.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1434821282/bsp.o: ../src/config/default/bsp/bsp.c  .generated_files/flags/default/2f00a484c46066af3ba09f9e2f62e7fbef816b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1434821282" 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1434821282/bsp.o.d" -o ${OBJECTDIR}/_ext/1434821282/bsp.o ../src/config/default/bsp/bsp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/95608f12fe4f6cc0a5a77b8414c5d9935a4fd5ca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/a0c94e65af2347c5f7b22b294aa770e389dcfb1c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/7b28b8bc050da1bf62756e3a3514ab4e451b47cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/a9dc11f41f2d36af30645cd40bd8b4ef17dff87c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/b7448ffb547200c04dbdfa5d678b67e5fdeda814 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/14d135365f2681ad52927a732902be7f55e8d390 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/647066257afdf146d32807850605ea24805d32f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/c591c6300280bc530c6051167134c2f827058dd2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/b70a90312cd59e591c84500269f2f417472faeb3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/6e2838e9e9e269c4de61bb3a08875a9efe992a66 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/868a699a947176161315fc00834513711ee49178 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/535990c7433e14b618c1559bc11065b4bfe6ba4f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/8419abeb414186c8ad6bd1174bcf4bba50d1b648 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/2cf7731c674c34d17b70b15eb2955d56a6046e57 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  .generated_files/flags/default/57db87d3cbb031906972ad00222eeba88fc86aa9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  .generated_files/flags/default/8acde1eb63d0ff11f247a4b3deee890730a61bfc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/944882569/sys_debug.o: ../src/config/default/system/debug/src/sys_debug.c  .generated_files/flags/default/64fb27902f909d65a77bb785bc03f3ca57f401ea .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/944882569" 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/944882569/sys_debug.o.d" -o ${OBJECTDIR}/_ext/944882569/sys_debug.o ../src/config/default/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  .generated_files/flags/default/69804c9d374844415b5a3e8d136377afc5044025 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/436ac55dca11c22384374cd424854ab1c54e9526 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/fe30ee639774a9a4892acddaf67e14cae25cbeec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/fe9ad0bdcd3cbb70778ccd96d225ea382626dffb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/bdbc76a10ebf2ba1f9c1803f416f6d07d662ca72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/8946139665e62b50cb18fce8371280e31411df2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/2e18e3f0921aa44130288f718d06d5a4a4921682 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/c6c902511886ce8e2fc374059f6b971ee2b27e32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/6b1f29c8f6743f5891a8ec5807d574153430a1db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/a186bd8f8f2e5ed438b7a9b09b0fc52633be35b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/fb9a3d5b04a0c4ca9e807896eb26e8ca91ba82fe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/aa3e70a828e9bc2778885c58328eea9dcf3eeeae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/5c821530dc6b888ee546cef7e83d8fa4156f25dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/6f92ea96fad5bedf15e1be1179a7c8232106d814 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/959ff0a42571922952148751022fffa870f4349e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/39c7e2b0a093bd8175900fcacd811a13789f3aa3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/62c420de0cff265d5dfe5f5af4bccd4e40e8144e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/82e72be08a99182a7ecb20ae15efa0373acdf5b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/dd5029f1b8363caf67e0051998d032037987dda8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/fa2d935f6345c49356755e7008434dbd1bc76b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/system_state.o: ../src/system_state.c  .generated_files/flags/default/c88466752ebba82b4369487b7d97c6dc126bc66e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_state.o ../src/system_state.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/interrupt_callbacks.o: interrupt_callbacks.c  .generated_files/flags/default/7d650d63f7295b24b7b69ac47454917a8dd6b549 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt_callbacks.o.d 
	@${RM} ${OBJECTDIR}/interrupt_callbacks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/interrupt_callbacks.o.d" -o ${OBJECTDIR}/interrupt_callbacks.o interrupt_callbacks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/freertos_daemon.o: freertos_daemon.c  .generated_files/flags/default/bc801cb0e1b65fc3c5fbe7982eb114a5abd4dd28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/freertos_daemon.o.d 
	@${RM} ${OBJECTDIR}/freertos_daemon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/freertos_daemon.o.d" -o ${OBJECTDIR}/freertos_daemon.o freertos_daemon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/global_vars.o: global_vars.c  .generated_files/flags/default/b847a9b923f254d02a9f67b8de206a3ce27d7c97 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/global_vars.o.d 
	@${RM} ${OBJECTDIR}/global_vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/global_vars.o.d" -o ${OBJECTDIR}/global_vars.o global_vars.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/debug_logger.o: ../src/debug_logger.c  .generated_files/flags/default/f33dacb7641da60404481a79b5c5e54ca0e74c2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_logger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug_logger.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug_logger.o ../src/debug_logger.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/init_funcs.o: init_funcs.c  .generated_files/flags/default/2c5219952e364ee219837ae547e948eeb8d9a443 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init_funcs.o.d 
	@${RM} ${OBJECTDIR}/init_funcs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/init_funcs.o.d" -o ${OBJECTDIR}/init_funcs.o init_funcs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can.o: ../src/can.c  .generated_files/flags/default/e6d5ed6a6001b472432c17861596a38e1d636240 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can.o.d" -o ${OBJECTDIR}/_ext/1360937237/can.o ../src/can.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/cmd_parser.o: ../src/cmd_parser.c  .generated_files/flags/default/7c1736d6d4fdcf0d62f6d9ac560e9b849678e0e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cmd_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cmd_parser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/cmd_parser.o.d" -o ${OBJECTDIR}/_ext/1360937237/cmd_parser.o ../src/cmd_parser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o: ../src/watchdog_kicker.c  .generated_files/flags/default/6afefedf3d9eec54c5846c28792f6fad02f6ed50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o.d" -o ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o ../src/watchdog_kicker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/led_driver.o: ../src/led_driver.c  .generated_files/flags/default/b8a022f8e4f3d739b8c2f53b7327b5aed106938 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/led_driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/led_driver.o ../src/led_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1434821282/bsp.o: ../src/config/default/bsp/bsp.c  .generated_files/flags/default/d93ee33be7860c8398159562e4091923021c37cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1434821282" 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1434821282/bsp.o.d" -o ${OBJECTDIR}/_ext/1434821282/bsp.o ../src/config/default/bsp/bsp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/5e33d0afc492de4c8d96bdd9a80fab077858f08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/d8029e4881523faf3c9697a047faddfb331945f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/d18aa3814bc7a0957452c79e837c2e6ed57400fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/553d68f3914012bb4223ef03e9334c7813fd0316 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/27847da51e31a2b9b6fa6240ecec696ffb1733 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/2ef2c9e47e55d1dca34dee6f853f149956e15337 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/f8fc1bfcf4b0f571d47fe402b010a02e9ada3c1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/6739dc615d0067f1e3c56a020124a2d66d3ace9e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/ccbb6f8675dfff0d578768c4c6779b925530b202 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/c204babf790c10c08b378f495557df293127d200 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/555c741ca269e1ad547823b2d829886fb506ddb9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/d71bbec1a261b366d8af80d196bfab473549e8fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/5e39a6f4e51876f025c4e9b2ebcbe4b690c9c6fe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/88a21a3be0165266d94c71d3afd1e03dd4752488 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  .generated_files/flags/default/9f5b1ecf5cd06b5262ba20c3c57ee78bfef5528d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  .generated_files/flags/default/666b360ea29a5f6c560f197443c162c8ed364e7b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/944882569/sys_debug.o: ../src/config/default/system/debug/src/sys_debug.c  .generated_files/flags/default/fd46a90abd52a11980adfeabe093da91122d21ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/944882569" 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/944882569/sys_debug.o.d" -o ${OBJECTDIR}/_ext/944882569/sys_debug.o ../src/config/default/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  .generated_files/flags/default/b8eeedaea227079cf192e0297b5d78fd44d322dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/8de57c01bb6acc8eae8cee6df069845a78a6d9db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/4abe7a4acdbafcc9028a74c666d2a0ada9703147 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/bdeb12d8ba300d5feaf4d1b54bd1d8e86a01c28a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/f7f8e582fe96493f0926775a2d068537925b557 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/9f4fd6211a28443dcc9df61b483c1322a81f734 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/3845bb8456e0be84dfc4cffc365e2a49694413c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/6668c8556a66331b393137b6873d5d3ae0cf5396 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/99627c7218e95417223e9f60e560405c205f9ee3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/add797c558110579645856f1cecf31abe6205404 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/1111958c8d98d60b7f68b4803293796810683d36 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/f49fa842c339ab97294dfdf0a94ff872eb424325 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/8c61b94c5216218dcbee78dca3492bb85b1b97b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/ccec46970ff8025ca5c2c1e33e4b7573428a9aa9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/e7c49cc47c48f27b89d4e881cf2e05d1f491e239 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/79854ccc6da4c922decdd2340ede8b323ff03c06 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/8b9b0df625fe54b66246e3b692b8dc313e5a53a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/2ed5593815068e8217f461a6439131a062585124 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/daf98f344ca037df34c8ca35afda5563c73fd5c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/daa79c075bebd45dfc806b1e141287306d4c642e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/system_state.o: ../src/system_state.c  .generated_files/flags/default/b6784e8c0b0cbb4cff9b1da3d4bbc50fc7fe71a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_state.o ../src/system_state.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/interrupt_callbacks.o: interrupt_callbacks.c  .generated_files/flags/default/a216b7d13e01029bd9639a513db6ffe9ff54f51e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt_callbacks.o.d 
	@${RM} ${OBJECTDIR}/interrupt_callbacks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/interrupt_callbacks.o.d" -o ${OBJECTDIR}/interrupt_callbacks.o interrupt_callbacks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/freertos_daemon.o: freertos_daemon.c  .generated_files/flags/default/f8976150873eed115919b9cdcde3bb8c7252b082 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/freertos_daemon.o.d 
	@${RM} ${OBJECTDIR}/freertos_daemon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/freertos_daemon.o.d" -o ${OBJECTDIR}/freertos_daemon.o freertos_daemon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/global_vars.o: global_vars.c  .generated_files/flags/default/2367936615f8b1fc38bfbec368a857ef936391fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/global_vars.o.d 
	@${RM} ${OBJECTDIR}/global_vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/global_vars.o.d" -o ${OBJECTDIR}/global_vars.o global_vars.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/debug_logger.o: ../src/debug_logger.c  .generated_files/flags/default/a537146a7abc4a12a1cca4f4ff3fbd9b1112b2c2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_logger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug_logger.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug_logger.o ../src/debug_logger.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/init_funcs.o: init_funcs.c  .generated_files/flags/default/21af2b35b7fb41d55552018aeabecb2f4716bd84 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init_funcs.o.d 
	@${RM} ${OBJECTDIR}/init_funcs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/init_funcs.o.d" -o ${OBJECTDIR}/init_funcs.o init_funcs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can.o: ../src/can.c  .generated_files/flags/default/88ccc357b80000be28553c5caed5daf8010c7b2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can.o.d" -o ${OBJECTDIR}/_ext/1360937237/can.o ../src/can.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/cmd_parser.o: ../src/cmd_parser.c  .generated_files/flags/default/b0781bde33bc7b687176670a908b43a031b8928d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cmd_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cmd_parser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/cmd_parser.o.d" -o ${OBJECTDIR}/_ext/1360937237/cmd_parser.o ../src/cmd_parser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o: ../src/watchdog_kicker.c  .generated_files/flags/default/7dbe4671b07ae301abb187a3bbd047a5eaff95aa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o.d" -o ${OBJECTDIR}/_ext/1360937237/watchdog_kicker.o ../src/watchdog_kicker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/led_driver.o: ../src/led_driver.c  .generated_files/flags/default/9aaf936f92a4db7c51e1e4871c99baa056dac558 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/testing/IO_Controller_Test1/IOCtrl1.X" -I"D:/pendrive_stuff/git_repos/gtron-io-controller-fw/IO_Ctrl_Master/IOCtrl1.X" -I"../" -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/led_driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/led_driver.o ../src/led_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	
else
${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/IOCtrl1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
