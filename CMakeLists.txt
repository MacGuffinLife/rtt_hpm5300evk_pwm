CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR hpmicro)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "/Users/macguffin/Usr/HpmSDK/toochain/riscv32-unknown-elf-newlib-multilib-2023.10.18-macos-intel/bin/riscv32-unknown-elf-gcc")
SET(CMAKE_ASM_COMPILER "/Users/macguffin/Usr/HpmSDK/toochain/riscv32-unknown-elf-newlib-multilib-2023.10.18-macos-intel/bin/riscv32-unknown-elf-gcc")
SET(CMAKE_C_FLAGS " -mcmodel=medlow  -DUSE_NONVECTOR_MODE=1  -ffunction-sections -fdata-sections -fno-common  -gdwarf-2 -O0 -DFLASH_XIP=1 -std=gnu11")
SET(CMAKE_ASM_FLAGS " -mcmodel=medlow  -DUSE_NONVECTOR_MODE=1  -ffunction-sections -fdata-sections -fno-common  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "/Users/macguffin/Usr/HpmSDK/toochain/riscv32-unknown-elf-newlib-multilib-2023.10.18-macos-intel/bin/riscv32-unknown-elf-g++")
SET(CMAKE_CXX_FLAGS " -mcmodel=medlow  -DUSE_NONVECTOR_MODE=1  -ffunction-sections -fdata-sections -fno-common  -gdwarf-2 -O0 -DFLASH_XIP=1 -Woverloaded-virtual -fno-exceptions -fno-rtti ")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "/Users/macguffin/Usr/HpmSDK/toochain/riscv32-unknown-elf-newlib-multilib-2023.10.18-macos-intel/bin/riscv32-unknown-elf-objcopy")
SET(CMAKE_SIZE "/Users/macguffin/Usr/HpmSDK/toochain/riscv32-unknown-elf-newlib-multilib-2023.10.18-macos-intel/bin/riscv32-unknown-elf-size")

SET(CMAKE_EXE_LINKER_FLAGS " -mcmodel=medlow   --specs=nano.specs --specs=nosys.specs  -u _printf_float -u _scanf_float -nostartfiles -Wl,--gc-sections  -O0 -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/flash_rtt.ld -Wl,--gc-sections,--print-memory-usage")

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)

PROJECT(rtthread C CXX ASM)

INCLUDE_DIRECTORIES(
	applications
	board
	rt-thread/components/libc/compilers/newlib
	rt-thread/components/libc/compilers/common/include
	rt-thread/components/drivers/include
	libraries/drivers
	rt-thread/components/finsh
	.
	rt-thread/include
	rt-thread/components/legacy
	rt-thread/libcpu/risc-v/common
	libraries/hpm_sdk/arch
	libraries/hpm_sdk/drivers/inc
	libraries/hpm_sdk/soc/ip
	libraries/hpm_sdk/components/debug_console
	libraries/hpm_sdk/components/touch
	libraries/hpm_sdk/components/usb
	libraries/hpm_sdk/components/dma_mgr
	rt-thread/components/libc/posix/io/epoll
	rt-thread/components/libc/posix/io/eventfd
	rt-thread/components/libc/posix/io/poll
	rt-thread/components/libc/posix/ipc
	libraries/hpm_sdk/soc/HPM5361
	libraries/hpm_sdk/soc/HPM5361/boot
	startup/HPM5361
)

ADD_DEFINITIONS(
	-DD25
	-DHPM5361
	-DHPMSOC_HAS_HPMSDK_DMAV2
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-D_POSIX_C_SOURCE=1
	-D_REENT_SMALL
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	applications/ws2812.c
	applications/main.c
	board/rtt_board.c
	board/board.c
	board/fal_flash_port.c
	board/pinmux.c
	rt-thread/components/libc/compilers/common/cctype.c
	rt-thread/components/libc/compilers/common/cstdlib.c
	rt-thread/components/libc/compilers/common/cstring.c
	rt-thread/components/libc/compilers/common/ctime.c
	rt-thread/components/libc/compilers/common/cunistd.c
	rt-thread/components/libc/compilers/common/cwchar.c
	rt-thread/components/libc/compilers/newlib/syscalls.c
	rt-thread/components/drivers/core/device.c
	rt-thread/components/drivers/ipc/completion_comm.c
	rt-thread/components/drivers/ipc/completion_up.c
	rt-thread/components/drivers/ipc/condvar.c
	rt-thread/components/drivers/ipc/dataqueue.c
	rt-thread/components/drivers/ipc/pipe.c
	rt-thread/components/drivers/ipc/ringblk_buf.c
	rt-thread/components/drivers/ipc/ringbuffer.c
	rt-thread/components/drivers/ipc/waitqueue.c
	rt-thread/components/drivers/ipc/workqueue.c
	rt-thread/components/drivers/pin/pin.c
	rt-thread/components/drivers/serial/serial_v2.c
	libraries/drivers/drv_uart_v2.c
	libraries/drivers/drv_gpio.c
	rt-thread/components/finsh/msh.c
	rt-thread/components/finsh/cmd.c
	rt-thread/components/finsh/msh_parse.c
	rt-thread/components/finsh/shell.c
	rt-thread/src/clock.c
	rt-thread/src/components.c
	rt-thread/src/cpu_up.c
	rt-thread/src/idle.c
	rt-thread/src/ipc.c
	rt-thread/src/irq.c
	rt-thread/src/klibc/kstdio.c
	rt-thread/src/klibc/kstring.c
	rt-thread/src/kservice.c
	rt-thread/src/mem.c
	rt-thread/src/mempool.c
	rt-thread/src/object.c
	rt-thread/src/scheduler_comm.c
	rt-thread/src/scheduler_up.c
	rt-thread/src/thread.c
	rt-thread/src/timer.c
	rt-thread/components/legacy/ipc/workqueue_legacy.c
	rt-thread/libcpu/risc-v/common/cpuport.c
	rt-thread/libcpu/risc-v/common/context_gcc.S
	rt-thread/libcpu/risc-v/common/interrupt_gcc.S
	rt-thread/libcpu/risc-v/common/trap_common.c
	libraries/hpm_sdk/drivers/src/hpm_dmav2_drv.c
	libraries/hpm_sdk/drivers/src/hpm_gpio_drv.c
	libraries/hpm_sdk/drivers/src/hpm_pcfg_drv.c
	libraries/hpm_sdk/drivers/src/hpm_pllctl_drv.c
	libraries/hpm_sdk/drivers/src/hpm_pllctlv2_drv.c
	libraries/hpm_sdk/drivers/src/hpm_pmp_drv.c
	libraries/hpm_sdk/drivers/src/hpm_uart_drv.c
		libraries/hpm_sdk/drivers/src/hpm_pwm_drv.c
	libraries/hpm_sdk/components/debug_console/hpm_debug_console.c
	libraries/hpm_sdk/components/dma_mgr/hpm_dma_mgr.c
	libraries/hpm_sdk/soc/HPM5361/hpm_l1c_drv.c
	libraries/hpm_sdk/soc/HPM5361/hpm_otp_drv.c
	libraries/hpm_sdk/soc/HPM5361/boot/hpm_bootheader.c
	libraries/hpm_sdk/soc/HPM5361/system.c
	libraries/hpm_sdk/soc/HPM5361/hpm_sysctl_drv.c
	libraries/hpm_sdk/soc/HPM5361/hpm_clock_drv.c
	startup/HPM5361/startup.c
	startup/HPM5361/toolchains/gcc/port_gcc.S
	startup/HPM5361/toolchains/gcc/start.S
	startup/HPM5361/trap.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
	COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf rtthread.bin
	COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
)

# if custom.cmake is exist, add it
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
endif()
