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
FINAL_IMAGE=${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/adc/plib_adc0.c ../src/config/default/peripheral/can/plib_can1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/default/peripheral/tc/plib_tc2.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/console/src/sys_console_usb_cdc.c ../src/config/default/system/debug/src/sys_debug.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/app.c ../src/Global_Vars.c ../src/Code_Dump/ext_flash.c ../src/Code_Dump/McuSwReset.c ../src/Code_Dump/tlv_flash.c ../src/TMC-API/tmc/helpers/CRC.c ../src/TMC-API/tmc/helpers/Functions.c ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c ../src/TMC-API/tmc/ramp/LinearRamp.c ../src/TMC-API/tmc/ramp/LinearRamp1.c ../src/TMC-API/tmc/ramp/Ramp.c ../src/tmc2209_uart/Step_Counter.c ../src/tmc2209_uart/TMC2209.c ../src/tmc2209_uart/TMC2209_motion.c ../src/tmc2209_uart/TMC2209_Simple_Rotation.c ../src/motor_dev/my_spi_func.c ../src/Bring_Up/spi.c ../src/freertos_daemon.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ${OBJECTDIR}/_ext/829342655/plib_tc2.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o ${OBJECTDIR}/_ext/944882569/sys_debug.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/Global_Vars.o ${OBJECTDIR}/_ext/1500443788/ext_flash.o ${OBJECTDIR}/_ext/1500443788/McuSwReset.o ${OBJECTDIR}/_ext/1500443788/tlv_flash.o ${OBJECTDIR}/_ext/1096015630/CRC.o ${OBJECTDIR}/_ext/1096015630/Functions.o ${OBJECTDIR}/_ext/1433801640/TMC4671.o ${OBJECTDIR}/_ext/33404887/LinearRamp.o ${OBJECTDIR}/_ext/33404887/LinearRamp1.o ${OBJECTDIR}/_ext/33404887/Ramp.o ${OBJECTDIR}/_ext/2089947380/Step_Counter.o ${OBJECTDIR}/_ext/2089947380/TMC2209.o ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o ${OBJECTDIR}/_ext/221583569/my_spi_func.o ${OBJECTDIR}/_ext/149991522/spi.o ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d ${OBJECTDIR}/_ext/60163342/plib_adc0.o.d ${OBJECTDIR}/_ext/60165182/plib_can1.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/60167341/plib_eic.o.d ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1865521619/plib_port.o.d ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d ${OBJECTDIR}/_ext/829342655/plib_tc2.o.d ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1832805299/sys_console.o.d ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o.d ${OBJECTDIR}/_ext/944882569/sys_debug.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1624415188/port.o.d ${OBJECTDIR}/_ext/1624415188/portasm.o.d ${OBJECTDIR}/_ext/1665200909/heap_1.o.d ${OBJECTDIR}/_ext/404212886/croutine.o.d ${OBJECTDIR}/_ext/404212886/list.o.d ${OBJECTDIR}/_ext/404212886/queue.o.d ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d ${OBJECTDIR}/_ext/404212886/timers.o.d ${OBJECTDIR}/_ext/404212886/event_groups.o.d ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/Global_Vars.o.d ${OBJECTDIR}/_ext/1500443788/ext_flash.o.d ${OBJECTDIR}/_ext/1500443788/McuSwReset.o.d ${OBJECTDIR}/_ext/1500443788/tlv_flash.o.d ${OBJECTDIR}/_ext/1096015630/CRC.o.d ${OBJECTDIR}/_ext/1096015630/Functions.o.d ${OBJECTDIR}/_ext/1433801640/TMC4671.o.d ${OBJECTDIR}/_ext/33404887/LinearRamp.o.d ${OBJECTDIR}/_ext/33404887/LinearRamp1.o.d ${OBJECTDIR}/_ext/33404887/Ramp.o.d ${OBJECTDIR}/_ext/2089947380/Step_Counter.o.d ${OBJECTDIR}/_ext/2089947380/TMC2209.o.d ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o.d ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o.d ${OBJECTDIR}/_ext/221583569/my_spi_func.o.d ${OBJECTDIR}/_ext/149991522/spi.o.d ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ${OBJECTDIR}/_ext/829342655/plib_tc2.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o ${OBJECTDIR}/_ext/944882569/sys_debug.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/Global_Vars.o ${OBJECTDIR}/_ext/1500443788/ext_flash.o ${OBJECTDIR}/_ext/1500443788/McuSwReset.o ${OBJECTDIR}/_ext/1500443788/tlv_flash.o ${OBJECTDIR}/_ext/1096015630/CRC.o ${OBJECTDIR}/_ext/1096015630/Functions.o ${OBJECTDIR}/_ext/1433801640/TMC4671.o ${OBJECTDIR}/_ext/33404887/LinearRamp.o ${OBJECTDIR}/_ext/33404887/LinearRamp1.o ${OBJECTDIR}/_ext/33404887/Ramp.o ${OBJECTDIR}/_ext/2089947380/Step_Counter.o ${OBJECTDIR}/_ext/2089947380/TMC2209.o ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o ${OBJECTDIR}/_ext/221583569/my_spi_func.o ${OBJECTDIR}/_ext/149991522/spi.o ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o

# Source Files
SOURCEFILES=../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/adc/plib_adc0.c ../src/config/default/peripheral/can/plib_can1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/default/peripheral/tc/plib_tc2.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/console/src/sys_console_usb_cdc.c ../src/config/default/system/debug/src/sys_debug.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/app.c ../src/Global_Vars.c ../src/Code_Dump/ext_flash.c ../src/Code_Dump/McuSwReset.c ../src/Code_Dump/tlv_flash.c ../src/TMC-API/tmc/helpers/CRC.c ../src/TMC-API/tmc/helpers/Functions.c ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c ../src/TMC-API/tmc/ramp/LinearRamp.c ../src/TMC-API/tmc/ramp/LinearRamp1.c ../src/TMC-API/tmc/ramp/Ramp.c ../src/tmc2209_uart/Step_Counter.c ../src/tmc2209_uart/TMC2209.c ../src/tmc2209_uart/TMC2209_motion.c ../src/tmc2209_uart/TMC2209_Simple_Rotation.c ../src/motor_dev/my_spi_func.c ../src/Bring_Up/spi.c ../src/freertos_daemon.c

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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/9ef70d5a104830632047f955615d0b23d88c2595 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60163342/plib_adc0.o: ../src/config/default/peripheral/adc/plib_adc0.c  .generated_files/flags/default/94537607e4a8e6754cafa69a4e09ffc1ba567ecb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc0.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ../src/config/default/peripheral/adc/plib_adc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/46e8aa18cc25ba24360478cfbcd2bf5f2a926540 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/8f088f86f8389e45b33d59dcc735f5fe291debbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/1549fa56995de89442bd8c291ba4352874f349d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/442d7c277fd7af6d33e7413af15509a6983aa684 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/48ded04e8056c49ecf09f5e4602445de69565832 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/7aae034e0947f1ac8e01f7592538a5f51faee23 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/db9568e89719193f3c4745fd029010369b69e20b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/3b55f4e2c617890339608cd1cb4ff9554ebc991e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/ae95c308a2aabe8b3099fb43939d2f68c7f3844c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/fb82d020e9497ea49263ff6bc5b01f5afcbdc1c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/359f266deb683b042684b8db20a155c0e14c3e0e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/default/60272e7e503fafead6c5589570a03c38a6940b7a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc2.o: ../src/config/default/peripheral/tc/plib_tc2.c  .generated_files/flags/default/3cd36087ff891309d30d5a47ac4a8629a74db097 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc2.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc2.o ../src/config/default/peripheral/tc/plib_tc2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/fc1e7c1474a913e5b4f375f7315121785264e94c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/af421ac51a64d1399ca512164d485251d78e0a6d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/2e095f3ed845ef584aa3b7754cd61f0a7b80a95e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  .generated_files/flags/default/c5cc4ba7345293e6a5570fd9b6fbe92a6803811b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  .generated_files/flags/default/8beb43488bf706fac53c68e414efa46c4ce1061b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o: ../src/config/default/system/console/src/sys_console_usb_cdc.c  .generated_files/flags/default/61fb451ace43382464000b43b5e11ab01abdd6e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o ../src/config/default/system/console/src/sys_console_usb_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/944882569/sys_debug.o: ../src/config/default/system/debug/src/sys_debug.c  .generated_files/flags/default/5a42a58655f6531e594734df1476af7f5014ea71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/944882569" 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/944882569/sys_debug.o.d" -o ${OBJECTDIR}/_ext/944882569/sys_debug.o ../src/config/default/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/296410b5911e44f0e408e4bde1e034dc0977dcb4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/f0adae87a3605f77143c8b268fb47f01b7a8ecbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/f7488ab0355e557764102dc49ab34e0fb89f8d2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/ed409295426f201849e1e0c0fa6e2f526127aa48 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/38da057d8165c93bd5c1b2af5dead7fafe0b8f0d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/18fc8d2e65f163a5d5541bb2b77ca12c773471d5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/b5ed6780c67d6684f6d6d6f587553436d430c9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/1e15a8c8f8bab04fbd356f1516d2591d18b8ac50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/8dc396fb3d04ee61355267967ed1dce6dc06b86b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/a3ce8b7aad052859cd10bd5f2a94217f1073b756 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/d065f16e4a67873f43feb5689d86924461b3c306 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/f83b73b278ecfa9ed014b107072a44fd64463afa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/cbe0112374342ba4aff2246ab78ca3515543fb10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/d4d679e37d8c349b44219e7502f1179fdfd5c40f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/73c3a06e82da64c77303e6eb6b9ac2dc60704404 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/752f97bb4cfa4da5c36bf9bb339f5452879e4ebe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/bb5f265e7ba29b35c1874c484b194beb80540506 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/7ebcc71ca39cdf50a9c09302fdd1c09e186f8a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/ede13185cac7334adb138b53e5c71a3dc2c6708e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/ccfdff141f8cbecd484972049d3ac83fce720732 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/Global_Vars.o: ../src/Global_Vars.c  .generated_files/flags/default/53f5551534ed0b28aa031981e4f8df145a519623 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Global_Vars.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Global_Vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Global_Vars.o.d" -o ${OBJECTDIR}/_ext/1360937237/Global_Vars.o ../src/Global_Vars.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/ext_flash.o: ../src/Code_Dump/ext_flash.c  .generated_files/flags/default/bfb4f549129f4e695e0d0d60b468edba44c3c84f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/ext_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/ext_flash.o.d" -o ${OBJECTDIR}/_ext/1500443788/ext_flash.o ../src/Code_Dump/ext_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/McuSwReset.o: ../src/Code_Dump/McuSwReset.c  .generated_files/flags/default/71e3bd45ad435229ef57c3f202ef71116f176f2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/McuSwReset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/McuSwReset.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/McuSwReset.o.d" -o ${OBJECTDIR}/_ext/1500443788/McuSwReset.o ../src/Code_Dump/McuSwReset.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/tlv_flash.o: ../src/Code_Dump/tlv_flash.c  .generated_files/flags/default/a7b9833083562b07d454f4313d1140365e7d3c71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/tlv_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/tlv_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/tlv_flash.o.d" -o ${OBJECTDIR}/_ext/1500443788/tlv_flash.o ../src/Code_Dump/tlv_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1096015630/CRC.o: ../src/TMC-API/tmc/helpers/CRC.c  .generated_files/flags/default/1652c46f74f94d5b44062c13cdb3b49a395f5f27 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1096015630" 
	@${RM} ${OBJECTDIR}/_ext/1096015630/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1096015630/CRC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1096015630/CRC.o.d" -o ${OBJECTDIR}/_ext/1096015630/CRC.o ../src/TMC-API/tmc/helpers/CRC.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1096015630/Functions.o: ../src/TMC-API/tmc/helpers/Functions.c  .generated_files/flags/default/6011d7cc6e5720e205d11405abbebe3af9d106ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1096015630" 
	@${RM} ${OBJECTDIR}/_ext/1096015630/Functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1096015630/Functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1096015630/Functions.o.d" -o ${OBJECTDIR}/_ext/1096015630/Functions.o ../src/TMC-API/tmc/helpers/Functions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1433801640/TMC4671.o: ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c  .generated_files/flags/default/5055475ef57b2f1198e2aec17af33a9fc27209b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1433801640" 
	@${RM} ${OBJECTDIR}/_ext/1433801640/TMC4671.o.d 
	@${RM} ${OBJECTDIR}/_ext/1433801640/TMC4671.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1433801640/TMC4671.o.d" -o ${OBJECTDIR}/_ext/1433801640/TMC4671.o ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/LinearRamp.o: ../src/TMC-API/tmc/ramp/LinearRamp.c  .generated_files/flags/default/51e6994bd4db0a9ebea3739152043232b800a2a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/LinearRamp.o.d" -o ${OBJECTDIR}/_ext/33404887/LinearRamp.o ../src/TMC-API/tmc/ramp/LinearRamp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/LinearRamp1.o: ../src/TMC-API/tmc/ramp/LinearRamp1.c  .generated_files/flags/default/5b20262250b39d46dfc231dd94c65ac8a71c14c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp1.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/LinearRamp1.o.d" -o ${OBJECTDIR}/_ext/33404887/LinearRamp1.o ../src/TMC-API/tmc/ramp/LinearRamp1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/Ramp.o: ../src/TMC-API/tmc/ramp/Ramp.c  .generated_files/flags/default/89413e294048467cd07209e6dff2cf00566f3b47 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/Ramp.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/Ramp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/Ramp.o.d" -o ${OBJECTDIR}/_ext/33404887/Ramp.o ../src/TMC-API/tmc/ramp/Ramp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/Step_Counter.o: ../src/tmc2209_uart/Step_Counter.c  .generated_files/flags/default/ad253b691bfda30c5ee1b8a19aa9e542bc69eb93 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/Step_Counter.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/Step_Counter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/Step_Counter.o.d" -o ${OBJECTDIR}/_ext/2089947380/Step_Counter.o ../src/tmc2209_uart/Step_Counter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209.o: ../src/tmc2209_uart/TMC2209.c  .generated_files/flags/default/d7cead6026be6890f743bf9b5615fa38eaa0eae8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209.o ../src/tmc2209_uart/TMC2209.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o: ../src/tmc2209_uart/TMC2209_motion.c  .generated_files/flags/default/1cff79da41f36bda5cb7ca9c4a21aa4a2b909e30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o ../src/tmc2209_uart/TMC2209_motion.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o: ../src/tmc2209_uart/TMC2209_Simple_Rotation.c  .generated_files/flags/default/b6ea652f4b3b01dcb34ddeafd96942497994b0b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o ../src/tmc2209_uart/TMC2209_Simple_Rotation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/221583569/my_spi_func.o: ../src/motor_dev/my_spi_func.c  .generated_files/flags/default/ff5f05ef33fadcff2685c24d77b0c8816f7eefba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/221583569" 
	@${RM} ${OBJECTDIR}/_ext/221583569/my_spi_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/221583569/my_spi_func.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/221583569/my_spi_func.o.d" -o ${OBJECTDIR}/_ext/221583569/my_spi_func.o ../src/motor_dev/my_spi_func.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/149991522/spi.o: ../src/Bring_Up/spi.c  .generated_files/flags/default/54c9b922e9bd995b112e520d094f2336d0c1baed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/149991522" 
	@${RM} ${OBJECTDIR}/_ext/149991522/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/149991522/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/149991522/spi.o.d" -o ${OBJECTDIR}/_ext/149991522/spi.o ../src/Bring_Up/spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/freertos_daemon.o: ../src/freertos_daemon.c  .generated_files/flags/default/be9c86dbdcaf35f5f779f8093bad121461b8d2df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/freertos_daemon.o.d" -o ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o ../src/freertos_daemon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/8411e9659b8d4341dbc82fd30766ba6821093b88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60163342/plib_adc0.o: ../src/config/default/peripheral/adc/plib_adc0.c  .generated_files/flags/default/907535c861ab84707287340838cd4c2b43c806e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc0.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ../src/config/default/peripheral/adc/plib_adc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/237f7c05b642c585b99c6d27bbea392c8f472c70 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/81ddd3ecb91e3a70db704725c78f6dd8139698cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/81ef6e633325fd0042fe5d5f0f581d626bb6c850 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/5b94bc9be28fd7b58dcf2528addc51837cb4793b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/699929600cf2453ac0a61b44e48aedf01765d0dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/33e1dff64fc755a01062150e0ad84dfbd4e9029f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/a29c3b4aada6bb18376b57eeed746db8b19ddc82 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/3bbc55eaa87ed97bd797fd5939d2685efaddd5b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/b15dc36e85cdcf6d40fd13a0b4d1bd46945bf383 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/753644437b75782ac65c92c71b6c76ef54410b51 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/c29bfa956504d00e325ca08d948e49e4c9014087 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/default/f98317ae917eb6d809c406146d494a4c47f69e3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc2.o: ../src/config/default/peripheral/tc/plib_tc2.c  .generated_files/flags/default/214881b35360030c7ef2afc026e0a205fee8d919 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc2.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc2.o ../src/config/default/peripheral/tc/plib_tc2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/943fdb50d517f708c792d8ee7d09846c555d8f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/9bd416a6649029051af717eb43ccc1466dfb5054 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/f815de909aefc652ac60672a2d2d6a366ee3ee54 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  .generated_files/flags/default/7f26b9284819e05dc745f45323b30d39b23237ca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  .generated_files/flags/default/6b905eea54b3357b61ff471c21ab5bb14d0f4327 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o: ../src/config/default/system/console/src/sys_console_usb_cdc.c  .generated_files/flags/default/6b8bc6e92e7239b08e07d2ad2c7ead05e841b5fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_usb_cdc.o ../src/config/default/system/console/src/sys_console_usb_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/944882569/sys_debug.o: ../src/config/default/system/debug/src/sys_debug.c  .generated_files/flags/default/ba86564b4837af49fb314e502f727527e177d311 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/944882569" 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/944882569/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/944882569/sys_debug.o.d" -o ${OBJECTDIR}/_ext/944882569/sys_debug.o ../src/config/default/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/fe6e2b04e142d0cb04e1fc1da9d70643fedb3eba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/bf540961e61611dd14a79b4ba8f5f85c919dd02a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/1c9878fbf40e8c35d523a603b6eecb4f89d3083f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/577e9e444a04feb6cffc3e640909a9d28ecf4ad1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/8a897dc815ea1b29fe4298e71d40d10ce96ded2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/a7993653627b85d9fd5719aa74a4ff360255d515 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/c44b666a113468568696cc58ea7fe21e39596222 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/d8812627be5cefb0f6a9efbbe00bc9ae449082fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/4b5fcf7aed8d3aad8cb55e481e152e4d547f33cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/933241bce2666bf47f81c96895abef0bcf61885b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/285ab84697ae50601b10a55100ced666ea3a0f31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/a39b5aa3c783aa9c9fc32b33e6db3a50efc04d43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/87fdc74eb620d6d118b0796f087fc52987b4eb84 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/2720d11a5c78105ad81ae5fcdd98a0e939320f07 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/c88b7a91ef40b9fe57ffcdd311763765e9271a91 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/5301b2bd610941a80c66fe00933e9ecac1b04108 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/d868699448f30aff4cf7142e6e37ce3e30edb19d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/f0292e0384359ecd70122f0e0bd9c678a0c233e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/40d7b2fa12f935e5212c39269a745f7301807b41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/df1dbba45a6ab013627935ad002ca7cc7522b04b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/Global_Vars.o: ../src/Global_Vars.c  .generated_files/flags/default/38818a5ea0533f59f3c1b1fc5c38d62225768666 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Global_Vars.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Global_Vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Global_Vars.o.d" -o ${OBJECTDIR}/_ext/1360937237/Global_Vars.o ../src/Global_Vars.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/ext_flash.o: ../src/Code_Dump/ext_flash.c  .generated_files/flags/default/67c6046eddf6a06a58e3d58c090813140dc8321a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/ext_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/ext_flash.o.d" -o ${OBJECTDIR}/_ext/1500443788/ext_flash.o ../src/Code_Dump/ext_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/McuSwReset.o: ../src/Code_Dump/McuSwReset.c  .generated_files/flags/default/4fe65f8d86d791416acaf0d59c4462546c6ca576 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/McuSwReset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/McuSwReset.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/McuSwReset.o.d" -o ${OBJECTDIR}/_ext/1500443788/McuSwReset.o ../src/Code_Dump/McuSwReset.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1500443788/tlv_flash.o: ../src/Code_Dump/tlv_flash.c  .generated_files/flags/default/3dbb4bb893930ba06b46d2c9ad7e380c599d1ff9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1500443788" 
	@${RM} ${OBJECTDIR}/_ext/1500443788/tlv_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500443788/tlv_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1500443788/tlv_flash.o.d" -o ${OBJECTDIR}/_ext/1500443788/tlv_flash.o ../src/Code_Dump/tlv_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1096015630/CRC.o: ../src/TMC-API/tmc/helpers/CRC.c  .generated_files/flags/default/92a5be33557f7f3ee59f514765bc809cbef0c40 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1096015630" 
	@${RM} ${OBJECTDIR}/_ext/1096015630/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1096015630/CRC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1096015630/CRC.o.d" -o ${OBJECTDIR}/_ext/1096015630/CRC.o ../src/TMC-API/tmc/helpers/CRC.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1096015630/Functions.o: ../src/TMC-API/tmc/helpers/Functions.c  .generated_files/flags/default/59224b8c7da9ddad074b42e8ac3b17cffb301678 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1096015630" 
	@${RM} ${OBJECTDIR}/_ext/1096015630/Functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1096015630/Functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1096015630/Functions.o.d" -o ${OBJECTDIR}/_ext/1096015630/Functions.o ../src/TMC-API/tmc/helpers/Functions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1433801640/TMC4671.o: ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c  .generated_files/flags/default/333124d5e2553016b03f4244aa6c2fe908d9fa2e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1433801640" 
	@${RM} ${OBJECTDIR}/_ext/1433801640/TMC4671.o.d 
	@${RM} ${OBJECTDIR}/_ext/1433801640/TMC4671.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1433801640/TMC4671.o.d" -o ${OBJECTDIR}/_ext/1433801640/TMC4671.o ../src/TMC-API/tmc/ic/TMC4671/TMC4671.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/LinearRamp.o: ../src/TMC-API/tmc/ramp/LinearRamp.c  .generated_files/flags/default/4b27a9bc2fd6cef97c9509a51b240b4efd466137 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/LinearRamp.o.d" -o ${OBJECTDIR}/_ext/33404887/LinearRamp.o ../src/TMC-API/tmc/ramp/LinearRamp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/LinearRamp1.o: ../src/TMC-API/tmc/ramp/LinearRamp1.c  .generated_files/flags/default/471f006d16293ca61da87839f453467ed3a3a32a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp1.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/LinearRamp1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/LinearRamp1.o.d" -o ${OBJECTDIR}/_ext/33404887/LinearRamp1.o ../src/TMC-API/tmc/ramp/LinearRamp1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33404887/Ramp.o: ../src/TMC-API/tmc/ramp/Ramp.c  .generated_files/flags/default/5ec976fd35d07e5572f088cf2a856bbd93ec5426 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/33404887" 
	@${RM} ${OBJECTDIR}/_ext/33404887/Ramp.o.d 
	@${RM} ${OBJECTDIR}/_ext/33404887/Ramp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33404887/Ramp.o.d" -o ${OBJECTDIR}/_ext/33404887/Ramp.o ../src/TMC-API/tmc/ramp/Ramp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/Step_Counter.o: ../src/tmc2209_uart/Step_Counter.c  .generated_files/flags/default/4ab38467536c8a392f77c7380ee53b49908ac595 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/Step_Counter.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/Step_Counter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/Step_Counter.o.d" -o ${OBJECTDIR}/_ext/2089947380/Step_Counter.o ../src/tmc2209_uart/Step_Counter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209.o: ../src/tmc2209_uart/TMC2209.c  .generated_files/flags/default/9f63331f42e377a8f57b08144db5bf0b49f640b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209.o ../src/tmc2209_uart/TMC2209.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o: ../src/tmc2209_uart/TMC2209_motion.c  .generated_files/flags/default/413c3b5389904f64c9e4efc98e8309863af07825 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209_motion.o ../src/tmc2209_uart/TMC2209_motion.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o: ../src/tmc2209_uart/TMC2209_Simple_Rotation.c  .generated_files/flags/default/b4ed78ba6d85fca85c2730ab1797b2ef3d0f4a86 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2089947380" 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o.d 
	@${RM} ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o.d" -o ${OBJECTDIR}/_ext/2089947380/TMC2209_Simple_Rotation.o ../src/tmc2209_uart/TMC2209_Simple_Rotation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/221583569/my_spi_func.o: ../src/motor_dev/my_spi_func.c  .generated_files/flags/default/d9821e25cce53b77b09ac07bce7d608e95a41dc9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/221583569" 
	@${RM} ${OBJECTDIR}/_ext/221583569/my_spi_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/221583569/my_spi_func.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/221583569/my_spi_func.o.d" -o ${OBJECTDIR}/_ext/221583569/my_spi_func.o ../src/motor_dev/my_spi_func.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/149991522/spi.o: ../src/Bring_Up/spi.c  .generated_files/flags/default/6bb4a531a354eb8d3717beb93e75736dd7aa518f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/149991522" 
	@${RM} ${OBJECTDIR}/_ext/149991522/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/149991522/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/149991522/spi.o.d" -o ${OBJECTDIR}/_ext/149991522/spi.o ../src/Bring_Up/spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/freertos_daemon.o: ../src/freertos_daemon.c  .generated_files/flags/default/d351412d6210e7583f5672bd9ead0b2c6e8a273f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../NextGen_GTron_AxC.X" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/NextGen_GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/src" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/freertos_daemon.o.d" -o ${OBJECTDIR}/_ext/1360937237/freertos_daemon.o ../src/freertos_daemon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	
else
${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/NextGen_GTron_AxC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
