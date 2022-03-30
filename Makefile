ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

CROSS_COMPILE ?= aarch64-linux-gnu-

asm-objs = el1_boot.o el0_entry.o el1_vector.o
c-objs = main.o  pl011.o

kernel.bin: kernel.elf
	$(E) "  OBJCOPY " $@
	$(Q) $(CROSS_COMPILE)objcopy -O binary $< $@

kernel.elf: $(asm-objs) $(c-objs)
	$(E) "  LINK    " $@
	$(Q) $(CROSS_COMPILE)ld -T linker.ld -static $(asm-objs)  $(c-objs) -o kernel.elf

$(asm-objs): %.o: %.S
	$(E) "  CC      " $@
	$(Q) $(CROSS_COMPILE)gcc -nostdlib -nostartfiles -c $< -o $@

$(c-objs): %.o: %.c
	$(E) "  CC      " $@
	$(Q) $(CROSS_COMPILE)gcc -nostdlib -nostartfiles -c $< -o $@

run: kernel.elf
	qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -smp 2  -kernel kernel.elf

kill:
	killall qemu-system-aarch64

.PHONY: clean
clean:
	$(E) "  CLEAN   "
	$(Q) rm -f *.o kernel.elf kernel.bin
