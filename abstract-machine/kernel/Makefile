NAME := kernel
SRCS := $(shell find . -name "*.c")
export ARCH := x86_64-qemu
export AM_HOME=/home/lq/ics2022/abstract-machine
include $(AM_HOME)/Makefile

debug:
	qemu-system-x86_64 -s -S build/kernel-x86_64-qemu &
	gdb -x init.gdb
