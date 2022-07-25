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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../HARDWARE/Led.c ../HARDWARE/HardWare.c ../HARDWARE/Key.c ../HARDWARE/Timer.c ../HARDWARE/Pwm.c ../HARDWARE/Adc.c ../HARDWARE/Spi.c ../HARDWARE/Ic.c ../SOC/Config.c ../SOC/Startup.s ../SYSTEM/Delay.s ../SYSTEM/Kernel.c ../SYSTEM/Error.c ../SYSTEM/Math.c ../SYSTEM/SinTab.s ../SYSTEM/Moto.c ../SYSTEM/Rotor.c ../USER/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/343451991/Led.o ${OBJECTDIR}/_ext/343451991/HardWare.o ${OBJECTDIR}/_ext/343451991/Key.o ${OBJECTDIR}/_ext/343451991/Timer.o ${OBJECTDIR}/_ext/343451991/Pwm.o ${OBJECTDIR}/_ext/343451991/Adc.o ${OBJECTDIR}/_ext/343451991/Spi.o ${OBJECTDIR}/_ext/343451991/Ic.o ${OBJECTDIR}/_ext/1360905368/Config.o ${OBJECTDIR}/_ext/1360905368/Startup.o ${OBJECTDIR}/_ext/1749661346/Delay.o ${OBJECTDIR}/_ext/1749661346/Kernel.o ${OBJECTDIR}/_ext/1749661346/Error.o ${OBJECTDIR}/_ext/1749661346/Math.o ${OBJECTDIR}/_ext/1749661346/SinTab.o ${OBJECTDIR}/_ext/1749661346/Moto.o ${OBJECTDIR}/_ext/1749661346/Rotor.o ${OBJECTDIR}/_ext/761542982/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/343451991/Led.o.d ${OBJECTDIR}/_ext/343451991/HardWare.o.d ${OBJECTDIR}/_ext/343451991/Key.o.d ${OBJECTDIR}/_ext/343451991/Timer.o.d ${OBJECTDIR}/_ext/343451991/Pwm.o.d ${OBJECTDIR}/_ext/343451991/Adc.o.d ${OBJECTDIR}/_ext/343451991/Spi.o.d ${OBJECTDIR}/_ext/343451991/Ic.o.d ${OBJECTDIR}/_ext/1360905368/Config.o.d ${OBJECTDIR}/_ext/1360905368/Startup.o.d ${OBJECTDIR}/_ext/1749661346/Delay.o.d ${OBJECTDIR}/_ext/1749661346/Kernel.o.d ${OBJECTDIR}/_ext/1749661346/Error.o.d ${OBJECTDIR}/_ext/1749661346/Math.o.d ${OBJECTDIR}/_ext/1749661346/SinTab.o.d ${OBJECTDIR}/_ext/1749661346/Moto.o.d ${OBJECTDIR}/_ext/1749661346/Rotor.o.d ${OBJECTDIR}/_ext/761542982/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/343451991/Led.o ${OBJECTDIR}/_ext/343451991/HardWare.o ${OBJECTDIR}/_ext/343451991/Key.o ${OBJECTDIR}/_ext/343451991/Timer.o ${OBJECTDIR}/_ext/343451991/Pwm.o ${OBJECTDIR}/_ext/343451991/Adc.o ${OBJECTDIR}/_ext/343451991/Spi.o ${OBJECTDIR}/_ext/343451991/Ic.o ${OBJECTDIR}/_ext/1360905368/Config.o ${OBJECTDIR}/_ext/1360905368/Startup.o ${OBJECTDIR}/_ext/1749661346/Delay.o ${OBJECTDIR}/_ext/1749661346/Kernel.o ${OBJECTDIR}/_ext/1749661346/Error.o ${OBJECTDIR}/_ext/1749661346/Math.o ${OBJECTDIR}/_ext/1749661346/SinTab.o ${OBJECTDIR}/_ext/1749661346/Moto.o ${OBJECTDIR}/_ext/1749661346/Rotor.o ${OBJECTDIR}/_ext/761542982/main.o

# Source Files
SOURCEFILES=../HARDWARE/Led.c ../HARDWARE/HardWare.c ../HARDWARE/Key.c ../HARDWARE/Timer.c ../HARDWARE/Pwm.c ../HARDWARE/Adc.c ../HARDWARE/Spi.c ../HARDWARE/Ic.c ../SOC/Config.c ../SOC/Startup.s ../SYSTEM/Delay.s ../SYSTEM/Kernel.c ../SYSTEM/Error.c ../SYSTEM/Math.c ../SYSTEM/SinTab.s ../SYSTEM/Moto.c ../SYSTEM/Rotor.c ../USER/main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP128MC506
MP_LINKER_FILE_OPTION=,--script="..\Linker\p33EP128MC506.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/343451991/Led.o: ../HARDWARE/Led.c  .generated_files/flags/default/503751d3dd2c49a9aa3c8dad19daacfbd6aa1205 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Led.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Led.c  -o ${OBJECTDIR}/_ext/343451991/Led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/HardWare.o: ../HARDWARE/HardWare.c  .generated_files/flags/default/b94374280c48e6be12f5bdaa6086216d9f724b81 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/HardWare.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/HardWare.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/HardWare.c  -o ${OBJECTDIR}/_ext/343451991/HardWare.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/HardWare.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Key.o: ../HARDWARE/Key.c  .generated_files/flags/default/8ebab8d95354427550d316317e303230fc1ddb75 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Key.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Key.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Key.c  -o ${OBJECTDIR}/_ext/343451991/Key.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Key.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Timer.o: ../HARDWARE/Timer.c  .generated_files/flags/default/1f40e337c502da8c700c18c9cf019deba12cf37 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Timer.c  -o ${OBJECTDIR}/_ext/343451991/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Pwm.o: ../HARDWARE/Pwm.c  .generated_files/flags/default/cb96d08f8e8c8f986cfb38e0c4a65cc514255c77 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Pwm.c  -o ${OBJECTDIR}/_ext/343451991/Pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Adc.o: ../HARDWARE/Adc.c  .generated_files/flags/default/a50e599810c72128c91d747d00765e65bdec4920 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Adc.c  -o ${OBJECTDIR}/_ext/343451991/Adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Spi.o: ../HARDWARE/Spi.c  .generated_files/flags/default/f893e1a40c82e91346e12ac4500d7db5c125d2d3 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Spi.c  -o ${OBJECTDIR}/_ext/343451991/Spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Ic.o: ../HARDWARE/Ic.c  .generated_files/flags/default/8474269bc660b3f474f85fa4e0bbfc87a8b93e35 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Ic.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Ic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Ic.c  -o ${OBJECTDIR}/_ext/343451991/Ic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Ic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360905368/Config.o: ../SOC/Config.c  .generated_files/flags/default/614bd2a1c62631da4297e1e798b9965eb415fa2 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1360905368" 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SOC/Config.c  -o ${OBJECTDIR}/_ext/1360905368/Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360905368/Config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Kernel.o: ../SYSTEM/Kernel.c  .generated_files/flags/default/f336971b236a9f1f9b2287444b9b70b3bf130a0b .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Kernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Kernel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Kernel.c  -o ${OBJECTDIR}/_ext/1749661346/Kernel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Kernel.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Error.o: ../SYSTEM/Error.c  .generated_files/flags/default/fb6acdfbce2aba41e6ff9b5341a27676ba1631fd .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Error.c  -o ${OBJECTDIR}/_ext/1749661346/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Error.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Math.o: ../SYSTEM/Math.c  .generated_files/flags/default/418bd16260540123b473836e0e878f95c4c26845 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Math.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Math.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Math.c  -o ${OBJECTDIR}/_ext/1749661346/Math.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Math.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Moto.o: ../SYSTEM/Moto.c  .generated_files/flags/default/f7eee64e8598f4a883d9883958d0fcf103068a89 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Moto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Moto.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Moto.c  -o ${OBJECTDIR}/_ext/1749661346/Moto.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Moto.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Rotor.o: ../SYSTEM/Rotor.c  .generated_files/flags/default/b9b15f5a75f11f1cf7b929ce34062a07f7ea934e .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Rotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Rotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Rotor.c  -o ${OBJECTDIR}/_ext/1749661346/Rotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Rotor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/761542982/main.o: ../USER/main.c  .generated_files/flags/default/bebf9f0e0d6b15d5042fbeaa55d7001870d9329d .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/761542982" 
	@${RM} ${OBJECTDIR}/_ext/761542982/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/761542982/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../USER/main.c  -o ${OBJECTDIR}/_ext/761542982/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/761542982/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/343451991/Led.o: ../HARDWARE/Led.c  .generated_files/flags/default/f347d7d0c38f9266bbb92a371615ae5bac602a07 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Led.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Led.c  -o ${OBJECTDIR}/_ext/343451991/Led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Led.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/HardWare.o: ../HARDWARE/HardWare.c  .generated_files/flags/default/376b7d10c1bda5ac9e3116bf799aeeb9633dc100 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/HardWare.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/HardWare.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/HardWare.c  -o ${OBJECTDIR}/_ext/343451991/HardWare.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/HardWare.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Key.o: ../HARDWARE/Key.c  .generated_files/flags/default/6d2f393c744f35b417d39c8962c95d3040402701 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Key.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Key.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Key.c  -o ${OBJECTDIR}/_ext/343451991/Key.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Key.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Timer.o: ../HARDWARE/Timer.c  .generated_files/flags/default/ed6866a90b39b4943f8cec9000d46b3bb3f67cfd .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Timer.c  -o ${OBJECTDIR}/_ext/343451991/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Timer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Pwm.o: ../HARDWARE/Pwm.c  .generated_files/flags/default/e620a22a7ea4c30276b06ab40dd64511ab744fba .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Pwm.c  -o ${OBJECTDIR}/_ext/343451991/Pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Adc.o: ../HARDWARE/Adc.c  .generated_files/flags/default/2cff27a0f476f7edf092fe8197bafda5b414686d .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Adc.c  -o ${OBJECTDIR}/_ext/343451991/Adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Adc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Spi.o: ../HARDWARE/Spi.c  .generated_files/flags/default/fd8c27318e38e58e89f8d011cf4b386dacb07d8d .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Spi.c  -o ${OBJECTDIR}/_ext/343451991/Spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Spi.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/343451991/Ic.o: ../HARDWARE/Ic.c  .generated_files/flags/default/7577a3bd111d6685aa10a325bbff947340389622 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/343451991" 
	@${RM} ${OBJECTDIR}/_ext/343451991/Ic.o.d 
	@${RM} ${OBJECTDIR}/_ext/343451991/Ic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HARDWARE/Ic.c  -o ${OBJECTDIR}/_ext/343451991/Ic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/343451991/Ic.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360905368/Config.o: ../SOC/Config.c  .generated_files/flags/default/f229ae01c202dd06ee0b003b962734f122a8aa94 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1360905368" 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SOC/Config.c  -o ${OBJECTDIR}/_ext/1360905368/Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360905368/Config.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Kernel.o: ../SYSTEM/Kernel.c  .generated_files/flags/default/53e3e70618397b4111e0ec89411e956511e69bc6 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Kernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Kernel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Kernel.c  -o ${OBJECTDIR}/_ext/1749661346/Kernel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Kernel.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Error.o: ../SYSTEM/Error.c  .generated_files/flags/default/2aa5256448ba50cdc455668628e104eb85d8d211 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Error.c  -o ${OBJECTDIR}/_ext/1749661346/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Error.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Math.o: ../SYSTEM/Math.c  .generated_files/flags/default/ec954c08220c8aabc8b390e59b6d09068c090fd4 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Math.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Math.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Math.c  -o ${OBJECTDIR}/_ext/1749661346/Math.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Math.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Moto.o: ../SYSTEM/Moto.c  .generated_files/flags/default/4435e30d9d172a60c34840992598dfb599202861 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Moto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Moto.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Moto.c  -o ${OBJECTDIR}/_ext/1749661346/Moto.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Moto.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Rotor.o: ../SYSTEM/Rotor.c  .generated_files/flags/default/9e5240999b5434db47ec2827f86ae5e01ea4b9eb .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Rotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Rotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SYSTEM/Rotor.c  -o ${OBJECTDIR}/_ext/1749661346/Rotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1749661346/Rotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/761542982/main.o: ../USER/main.c  .generated_files/flags/default/a818618d5e36e59a9fb4a05ac3a1d24fd43f1d23 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/761542982" 
	@${RM} ${OBJECTDIR}/_ext/761542982/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/761542982/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../USER/main.c  -o ${OBJECTDIR}/_ext/761542982/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/761542982/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../HARDWARE" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360905368/Startup.o: ../SOC/Startup.s  .generated_files/flags/default/34f8cf2bb381dc2696d8625fd799df648a7a15f0 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1360905368" 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Startup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Startup.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SOC/Startup.s  -o ${OBJECTDIR}/_ext/1360905368/Startup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1360905368/Startup.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Delay.o: ../SYSTEM/Delay.s  .generated_files/flags/default/8b91e38ca27031d84c1d1f2fd673df492860115d .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Delay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SYSTEM/Delay.s  -o ${OBJECTDIR}/_ext/1749661346/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1749661346/Delay.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/SinTab.o: ../SYSTEM/SinTab.s  .generated_files/flags/default/2f20518e8687bfae2c9e44d688b4d9d1e2b53244 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/SinTab.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/SinTab.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SYSTEM/SinTab.s  -o ${OBJECTDIR}/_ext/1749661346/SinTab.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1749661346/SinTab.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1360905368/Startup.o: ../SOC/Startup.s  .generated_files/flags/default/79443b24a12f3bcb665db8bb1287a25e5697daf9 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1360905368" 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Startup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360905368/Startup.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SOC/Startup.s  -o ${OBJECTDIR}/_ext/1360905368/Startup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1360905368/Startup.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/Delay.o: ../SYSTEM/Delay.s  .generated_files/flags/default/24656febcb1af26ac48e537233ff6775d3330d45 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/Delay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SYSTEM/Delay.s  -o ${OBJECTDIR}/_ext/1749661346/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1749661346/Delay.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1749661346/SinTab.o: ../SYSTEM/SinTab.s  .generated_files/flags/default/c1f526c5ed53e75620c4b3733ddd0c97cffd1a39 .generated_files/flags/default/ee71d62e67581db8c10a5a3b203d13aea51f1f0
	@${MKDIR} "${OBJECTDIR}/_ext/1749661346" 
	@${RM} ${OBJECTDIR}/_ext/1749661346/SinTab.o.d 
	@${RM} ${OBJECTDIR}/_ext/1749661346/SinTab.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SYSTEM/SinTab.s  -o ${OBJECTDIR}/_ext/1749661346/SinTab.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/1749661346/SinTab.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../Linker/p33EP128MC506.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../Linker/p33EP128MC506.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SPWM_CTL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
