ARMv8 Baremetal Code with SMP Support
=====================================

This is a demo project for learning ARMv8 Aarch64 ISA and ARMv8 assembly.

It supports:

- [x] boot from EL1 & return to EL0
- [x] el1 vector table
- [x] stdio on uart
- [x] shell for EL0
- [x] svc demo
- [x] brk instructions & debug monitor shell in EL1
- [x] external debug (likely cpu<->jtag2usb<->usb_drvier<->gdbserver<->gdb)
- [ ] SMP

It requires `qemu-system-aarch64` installed to run this project.

```bash
make run
```

# References

- [Arm® Architecture Reference Manual Armv8, for Armv8-A architecture profile](https://developer.arm.com/docs/ddi0487/ea/arm-architecture-reference-manual-armv8-for-armv8-a-architecture-profile)
- [Arm® Power State Coordination Interface - Platform Design Document](https://developer.arm.com/docs/den0022/d/arm-power-state-coordination-interface-platform-design-document)
- [ARM Cortex-A Series Programmer’s Guide for ARMv8-A](https://developer.arm.com/docs/den0024/a/preface)
- [Bare-metal Boot Code for ARMv8-A Processors](https://developer.arm.com/docs/dai0527/a/bare-metal-boot-code-for-armv8-a-processors)
- [The Linux Kernel](https://www.kernel.org)
