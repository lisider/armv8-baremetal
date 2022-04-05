/*************************************************************************
  > File Name: el1_handler.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Thu 31 Mar 2022 10:36:11 PM CST
 ************************************************************************/
#include "stdio.h"
#include "shell.h"
#include "dlib.h"
#include "sreg_ops.h"

static char *m_table[0x10] = {
    [0x00] = "EL0t", //
    [0x04] = "EL1t", //
    [0x05] = "EL1h", //
    [0x08] = "EL2t", //
    [0x09] = "EL2h", //
};

static char *ec_table[0x40] = {
    [0x00] = "unknown",
    [0x01] = "wf*",
    [0x03] = "c15 mcr/mrc",
    [0x04] = "c15 mcrr/mrrc",
    [0x05] = "c14 mcr/mrc",
    [0x06] = "ldc/stc",
    [0x07] = "FP off",
    [0x08] = "VMRS access",
    [0x09] = "PAC off",
    [0x0a] = "ld/st64b",
    [0x0c] = "c14 mrrc",
    [0x0d] = "branch target",
    [0x0e] = "illegal state",
    [0x11] = "svc in a32",
    [0x12] = "hvc in a32",
    [0x13] = "smc in a32",
    [0x15] = "svc in a64",
    [0x16] = "hvc in a64",
    [0x17] = "smc in a64",
    [0x18] = "other mcr/mrc/sys",
    [0x19] = "SVE off",
    [0x1a] = "eret",
    [0x1c] = "PAC failure",
    [0x20] = "instruction abort (lower)",
    [0x21] = "instruction abort (current)",
    [0x22] = "pc misaligned",
    [0x24] = "data abort (lower)",
    [0x25] = "data abort (current)",
    [0x26] = "sp misaligned",
    [0x28] = "FP exception (a32)",
    [0x2c] = "FP exception (a64)",
    [0x2f] = "SError",
    [0x30] = "BP (lower)",
    [0x31] = "BP (current)",
    [0x32] = "step (lower)",
    [0x33] = "step (current)",
    [0x34] = "watchpoint (lower)",
    [0x35] = "watchpoint (current)",
    [0x38] = "bkpt (a32)",
    [0x3a] = "vector catch (a32)",
    [0x3c] = "brk (a64)",
};


void brk_handler(){
    shell_debug();
}

void svc_handler(){
    printf("%s\n",__func__);
    printf("syscall number is %d\n",pt_regs->regs[8]);
}

void el021_sync_handler(struct pt_regs * p){
    printf("%s\n",__func__);
    pt_regs = p;
    u64 esr = mrs(ESR_EL1);
    int EC = (esr&0xfc000000)>>26;
    int IL = (esr&0x02000000)>>25;
    int ISS= (esr&0x01ffffff);

    printf("EC :%08X,IL :%08X,ISS :%08X\n",EC,IL,ISS);
    printf("Previous Exception Level: %s\n",m_table[mrs(SPSR_EL1)&0xF]);
    printf("Previous Execution State: %s\n",(mrs(SPSR_EL1)&0x10) == 1 ?"aarch32":"aarch64");
    printf("Current  Exception class: %s\n",ec_table[EC]);
    printf("Current  Exception Level: EL%d\n", ( mrs(CurrentEL) >> 2) & 0x3);
    //printf("Current  Execution State: %s\n",(mrs(PSTATE)&0x10) == 1 ?"aarch32":"aarch64");
    // it seems that there's no way to read PSTATE
    // please goto DDI0487E_armv8_A_architecture_reference_manual.pdf P366 for
    // "Instructions for accessing the PSTATE fields"
    //
    // HCR_EL2[31] Execution state control
    //      : 0b0 Lower levels are all AArch32
    //      : 0b1 The Execution state for EL1 is AArch64,The Execution state
    //      for EL0 is determined by the current value of PSTATE.nRW when
    //      executing at EL0
    // From DEN0024A_v8_architecture_PG.pdf P35,we We see a sentence that
    // "However, a 32-bit operating system cannot host a 64-bit application and
    // a 32-bit hypervisor cannot host a 64-bit guest operating system."
    //
    // now EL0 PSTATE[4] is 0 , EL0 AArch64
    // EL1 must be AArch64

    switch(EC){
        case 0X15:{
                      svc_handler();
                      break;
                  }
        case 0x3C:{
                      brk_handler();
                      asm("stp x0,x1,[sp , #-16]!");
                      asm("MRS X0,ELR_EL1");
                      asm("ADD X0,X0,4");
                      asm("MSR ELR_EL1,X0");
                      asm("ldp x0,x1,[sp], #16");
                      break;
                  }
    }

    return ;
}
