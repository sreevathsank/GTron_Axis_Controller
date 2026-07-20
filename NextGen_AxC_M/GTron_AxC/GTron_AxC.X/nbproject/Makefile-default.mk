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
FINAL_IMAGE=${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/dbg_print/dbg_print.c ../src/dbg_print/dbg_transport.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/config/default/peripheral/can/plib_can1.c ../src/tmc4671_task.c ../src/can_gatekeeper_task.c ../src/tmc2209_task.c ../src/supervisor_task.c ../src/debug_task.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/init_functions.c ../src/can_isr_callbacks.c ../src/can_state.c ../src/can_protocol.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/984881635/dbg_print.o ${OBJECTDIR}/_ext/984881635/dbg_transport.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o ${OBJECTDIR}/_ext/1360937237/supervisor_task.o ${OBJECTDIR}/_ext/1360937237/debug_task.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/1360937237/init_functions.o ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o ${OBJECTDIR}/_ext/1360937237/can_state.o ${OBJECTDIR}/_ext/1360937237/can_protocol.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1865521619/plib_port.o.d ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/984881635/dbg_print.o.d ${OBJECTDIR}/_ext/984881635/dbg_transport.o.d ${OBJECTDIR}/_ext/1624415188/port.o.d ${OBJECTDIR}/_ext/1624415188/portasm.o.d ${OBJECTDIR}/_ext/1665200909/heap_1.o.d ${OBJECTDIR}/_ext/404212886/croutine.o.d ${OBJECTDIR}/_ext/404212886/list.o.d ${OBJECTDIR}/_ext/404212886/queue.o.d ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d ${OBJECTDIR}/_ext/404212886/timers.o.d ${OBJECTDIR}/_ext/404212886/event_groups.o.d ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/60165182/plib_can1.o.d ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o.d ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o.d ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o.d ${OBJECTDIR}/_ext/1360937237/supervisor_task.o.d ${OBJECTDIR}/_ext/1360937237/debug_task.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d ${OBJECTDIR}/_ext/1360937237/init_functions.o.d ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o.d ${OBJECTDIR}/_ext/1360937237/can_state.o.d ${OBJECTDIR}/_ext/1360937237/can_protocol.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/984881635/dbg_print.o ${OBJECTDIR}/_ext/984881635/dbg_transport.o ${OBJECTDIR}/_ext/1624415188/port.o ${OBJECTDIR}/_ext/1624415188/portasm.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/60165182/plib_can1.o ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o ${OBJECTDIR}/_ext/1360937237/supervisor_task.o ${OBJECTDIR}/_ext/1360937237/debug_task.o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/1360937237/init_functions.o ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o ${OBJECTDIR}/_ext/1360937237/can_state.o ${OBJECTDIR}/_ext/1360937237/can_protocol.o

# Source Files
SOURCEFILES=../src/config/default/osal/osal_freertos.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rstc/plib_rstc.c ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/dbg_print/dbg_print.c ../src/dbg_print/dbg_transport.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/main.c ../src/config/default/peripheral/can/plib_can1.c ../src/tmc4671_task.c ../src/can_gatekeeper_task.c ../src/tmc2209_task.c ../src/supervisor_task.c ../src/debug_task.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/init_functions.c ../src/can_isr_callbacks.c ../src/can_state.c ../src/can_protocol.c

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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/d2e7898a4fcdc58b02530e304dba166418fd6dba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/eaed4a2b52cb9476d1ae2b1c0984d3438ff48f61 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/a8180920f5079d9c0e92f8848cf7dd7150706de5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/f59f0b7246dc83e7c8fe97c712e6934566e9c7fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/280409fa78c6b218b15665bab4005fcd2d423055 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/e19dd806489a32b5099e62b63b1aa29c893e9381 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/aac05942f2780603fb22dbff6f9ed93b4b830b2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/e73edc679f07e9c6c3c6840d4bc6c38b6e69f9be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/df0dbeb16065f2dd1bdc60949997f3e1aa7d1ee5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/7af72ff600beba290258fbdf44219e790abebcab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/d991eec22f498c2efe9f83940e7b43b6efae5e3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/695d19e7e7e5fe1559237cffed5ff2cdf62a8515 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/5793829a2dff9ad59e2331c18663e64e12b6aaac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/b9aa90edc7722254a2b2a8c3d85a2acfdaa4564d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/96c09639f20a8453881bf00c6942a4bc5b650382 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/56df13cea382be7877656c2849cd4a8077cf651 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/e41db4a69193774e6d0b2b52c93715c5428171e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/52eeca30f749680f287bb26680c70e9cab11fc79 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/8fd25b67778d332dea075f42796e010513aba554 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/984881635/dbg_print.o: ../src/dbg_print/dbg_print.c  .generated_files/flags/default/925de1e1ee36648c9c6479132dee5e23edcf54f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/984881635" 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_print.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/984881635/dbg_print.o.d" -o ${OBJECTDIR}/_ext/984881635/dbg_print.o ../src/dbg_print/dbg_print.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/984881635/dbg_transport.o: ../src/dbg_print/dbg_transport.c  .generated_files/flags/default/8abe59475b1f4a42a73a4e32e58ff758d64d1c49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/984881635" 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_transport.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/984881635/dbg_transport.o.d" -o ${OBJECTDIR}/_ext/984881635/dbg_transport.o ../src/dbg_print/dbg_transport.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/15d76c4cbc2c9fe254d88629d989bab40c6418dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/fa6ba5a19d66c131e2c4f6cf4a854e5eef5a662d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/78daea4e79ee02c606d89970bb521afb158286bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/502770696ea1c914b0679cdfdb8a6c47be471a4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/237f44a74618f2a934cde6441c9c277d20d6cf28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/860032afacb7ff97dad970fa92e86d5aad371a5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/f9692b9959fe729fef08f132fd4c8169b90e5bbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/bc154ad9d36208205e2804aa819f21cddf2bee2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/f6319733bb6bb7a5fad844e39ba7ee3d4b594e20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/92ac40171c44270179145cdc1787f499b8bfd2bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/4c01b4e780f421b43b1a0daedca95095547a5172 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/ea822709842f801730516c7422a5d19212952e21 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/tmc4671_task.o: ../src/tmc4671_task.c  .generated_files/flags/default/f1e8c721f0ce1eb938122c7cb09bd5ea840353c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/tmc4671_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o ../src/tmc4671_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o: ../src/can_gatekeeper_task.c  .generated_files/flags/default/e29f4bb1dce41557efb3086dcfdde6f52d17d8ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o ../src/can_gatekeeper_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/tmc2209_task.o: ../src/tmc2209_task.c  .generated_files/flags/default/9f80e84f451827cd96727694660881ec438f5938 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/tmc2209_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o ../src/tmc2209_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/supervisor_task.o: ../src/supervisor_task.c  .generated_files/flags/default/37707accbea57d1d24e5b883fa1dde85922e0b17 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/supervisor_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/supervisor_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/supervisor_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/supervisor_task.o ../src/supervisor_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/debug_task.o: ../src/debug_task.c  .generated_files/flags/default/ef70b191755016822606f261a9b1e88a42f6689c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug_task.o ../src/debug_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/81f846a5210fd4820564e9ff182f1b3a1ec29065 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/347e3b08d4ba2ced2fbf752376a16b238996efa0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/default/88ef8424c7554dd961b1e82519390947f6bad746 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/flags/default/e0f7ce82841ae4369da80dadb5353c472aa29a22 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/init_functions.o: ../src/init_functions.c  .generated_files/flags/default/733ca4b023a4579f700bb05ffe47b8b3609082ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/init_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/init_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/init_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/init_functions.o ../src/init_functions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o: ../src/can_isr_callbacks.c  .generated_files/flags/default/5aaf732fb3eb53b76f58c3a28bbf0345ac529cb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o ../src/can_isr_callbacks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_state.o: ../src/can_state.c  .generated_files/flags/default/96cfa005795ec65ac61ef2c8e42e86700f742e94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_state.o ../src/can_state.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_protocol.o: ../src/can_protocol.c  .generated_files/flags/default/f32a1b808bd64ea9ef18f546a8da165f2b2d2adf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_protocol.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_protocol.o ../src/can_protocol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  .generated_files/flags/default/679aa99715e8f8c6c343f986fac23c642c331f25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/c3733b5685f9cb91f071e627779a0a6e39e7f889 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/759f5d0477fbdb3adfb2073d56b36d30086de699 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/129e9ad00249bc290aa083cce175627b36ee39c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/b07f55342090334035581e5e3ac027b280f40281 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/f7c6a8a3ea31148038d35a3b538f40563ded090b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/6a2585ca2a19bbb926d13adc37eef00ca6299e0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865585090/plib_rstc.o: ../src/config/default/peripheral/rstc/plib_rstc.c  .generated_files/flags/default/129f471ada0f7e444407817e3f851631fcdf087c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865585090" 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865585090/plib_rstc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865585090/plib_rstc.o.d" -o ${OBJECTDIR}/_ext/1865585090/plib_rstc.o ../src/config/default/peripheral/rstc/plib_rstc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c  .generated_files/flags/default/7c3cbee4e59e20f4689057b99285d62cb273c3cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom7_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom7_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/ad68f6c4357ced06404f862b5202be79f24b9102 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/e9eb417a56b9fbce5d0145837314a3f0e833e77 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/e3babc7ee39647b3ea00bfc7dc4af6f75f8cee5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/cccfa9a2b4eb183b68a202161653e04ff7a95840 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/e42448a25b58f7e64c248f12eaf15034a8ad489b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/e2f6cec1c7f25180d7c5922bebdcdbcb397eb722 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/ba05f1dc8cef778b56f07f249b67adea20b772a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/b81f3423bd49e857d5e92cc418a31e4e7f347363 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  .generated_files/flags/default/e0c331dd338c7698e89be1b0004fd9d634f40131 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/8c241ba0e7ec5e9cfb14f7d270813477569f816a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/984881635/dbg_print.o: ../src/dbg_print/dbg_print.c  .generated_files/flags/default/5e6621254a00f80590b74401912824725d1a48c0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/984881635" 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_print.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/984881635/dbg_print.o.d" -o ${OBJECTDIR}/_ext/984881635/dbg_print.o ../src/dbg_print/dbg_print.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/984881635/dbg_transport.o: ../src/dbg_print/dbg_transport.c  .generated_files/flags/default/167d47b2b95dcb2e94a6506940e60f2b03c76337 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/984881635" 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/984881635/dbg_transport.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/984881635/dbg_transport.o.d" -o ${OBJECTDIR}/_ext/984881635/dbg_transport.o ../src/dbg_print/dbg_transport.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c  .generated_files/flags/default/840b8c4027e4b7d7802896cac6520951e5ac450b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/port.o.d" -o ${OBJECTDIR}/_ext/1624415188/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1624415188/portasm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c  .generated_files/flags/default/70a260c4a949e679235f845446f767a39aa97952 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1624415188" 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1624415188/portasm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1624415188/portasm.o.d" -o ${OBJECTDIR}/_ext/1624415188/portasm.o ../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portasm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/6b54b856492c166e19167cde070fd2997805fdce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  .generated_files/flags/default/8fbf6e8ea50740d43e8461e012eb5070314b4f4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/default/18ee1276da2fad46fbf4bbaa7f5a556b425d7475 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/default/c53c0efe29f392716d239682df0942a4cb34912 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  .generated_files/flags/default/49263b51afa60c75148dd92cb88ff5e53249080d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/default/9a866f11ef8a9b19b552959edc17110b9025989f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  .generated_files/flags/default/95d96645cf8ebb5b0b33e90f7bfe62146fb22be6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  .generated_files/flags/default/c4c552492a7cc3f7618a280f054add22e342a46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/d7219d8cb79ba0519bfc0bf3d1cdc0730d8c0357 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can1.o: ../src/config/default/peripheral/can/plib_can1.c  .generated_files/flags/default/87bb378223779fdcc8159f2981873feb588c51c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can1.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can1.o ../src/config/default/peripheral/can/plib_can1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/tmc4671_task.o: ../src/tmc4671_task.c  .generated_files/flags/default/211fba00ea1e7f0e424bcc4cc1e8c786b072d73 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/tmc4671_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/tmc4671_task.o ../src/tmc4671_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o: ../src/can_gatekeeper_task.c  .generated_files/flags/default/3b290a7a92c26154951ccc762c5576d833deec30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_gatekeeper_task.o ../src/can_gatekeeper_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/tmc2209_task.o: ../src/tmc2209_task.c  .generated_files/flags/default/ebf3ece61a8e4a1191d9b4f2049fa346df21e202 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/tmc2209_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/tmc2209_task.o ../src/tmc2209_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/supervisor_task.o: ../src/supervisor_task.c  .generated_files/flags/default/e0f95d47c45f7222dbdd8a4b0c26100d20a0f0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/supervisor_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/supervisor_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/supervisor_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/supervisor_task.o ../src/supervisor_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/debug_task.o: ../src/debug_task.c  .generated_files/flags/default/e4651ae93972aba06352b367db2537463579fd1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug_task.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug_task.o ../src/debug_task.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c  .generated_files/flags/default/e36d4974ea9c2d3de04c453f8df1e52960de8fed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom3_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom3_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/8f637bdf9766ec160a532f65e5445d1cbcaed442 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/default/db503665798c360b53fd429427402dd54f768af1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom5_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/flags/default/9e715f64304d7f738c146a3ce3516d7c5b632dc7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/init_functions.o: ../src/init_functions.c  .generated_files/flags/default/9f7d550d141fa7ec478101ec9267f83697ae7e90 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/init_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/init_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/init_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/init_functions.o ../src/init_functions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o: ../src/can_isr_callbacks.c  .generated_files/flags/default/1a7e9c251fcc92b149c7d37d91d29fe53162e457 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_isr_callbacks.o ../src/can_isr_callbacks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_state.o: ../src/can_state.c  .generated_files/flags/default/c4f8748226f2adf7da42cf09776cdeeb130cdb1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_state.o ../src/can_state.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/can_protocol.o: ../src/can_protocol.c  .generated_files/flags/default/86d8168dd72089d35f680b115d42299c8b48aea4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21N18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/GTron_AxC.X" -I"D:/pendrive_stuff/git_repos/gtron-axis-controller-fw/NextGen_AxC_M/GTron_AxC/src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_protocol.o.d" -o ${OBJECTDIR}/_ext/1360937237/can_protocol.o ../src/can_protocol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	
else
${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMC21N18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/GTron_AxC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
