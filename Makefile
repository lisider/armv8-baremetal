ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

CROSS_COMPILE ?= aarch64-linux-gnu-
export LOG_DIR=$(shell  echo output/`date +"%Y_%m_%d_%H_%M_%S"`)

asm-objs = el1_boot.o el0_entry.o el1_vector.o
c-objs = main.o  pl011.o



kernel.elf.asm: kernel.elf
	$(E) "  OBJDUMP " $@
	$(Q) $(CROSS_COMPILE)objdump -D  $< > $@

kernel.bin: kernel.elf
	$(E) "  OBJCOPY " $@
	$(Q) $(CROSS_COMPILE)objcopy -O binary $< $@

kernel.elf: $(asm-objs) $(c-objs)
	$(E) "  LINK    " $@
	$(Q) $(CROSS_COMPILE)ld -T linker.ld -static $(asm-objs)  $(c-objs) -o kernel.elf

$(asm-objs): %.o: %.S
	$(E) "  CC      " $@
	$(Q) $(CROSS_COMPILE)gcc -g -nostdlib -nostartfiles -c $< -o $@

$(c-objs): %.o: %.c
	$(E) "  CC      " $@
	$(Q) $(CROSS_COMPILE)gcc -g -nostdlib -nostartfiles -c $< -o $@

run: kernel.elf
	qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -smp 2  -kernel kernel.elf  2>&1 | tee log_run.txt

debug_run: kernel.elf
	qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -smp 2  -kernel kernel.elf  -s -S 2>&1 | tee log_run.txt

debug_gdb:
	gdb-multiarch -x gdb_init -tui

kill:
	killall qemu-system-aarch64

help:
	@echo target list:
	@cat Makefile   |grep ":" |egrep -v "asm-objs|c-objs|PHONY|target" | cut -d ":" -f1 | sed s/^/'\t'/g

.PHONY: clean
clean:
	$(E) "  CLEAN   "
	$(Q) rm -f *.o kernel.elf kernel.bin kernel.elf.asm
	$(Q)$(shell [ ! -e output  ] && mkdir output)
	$(Q)$(shell [ -e log_run.txt ] && mkdir ${LOG_DIR} && mv log* ${LOG_DIR})
