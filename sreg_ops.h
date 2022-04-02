/*************************************************************************
  > File Name: sreg.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Sat 02 Apr 2022 04:37:29 PM CST
 ************************************************************************/

#ifndef SREG_OPS_H
#define SREG_OPS_H


// barrier
#define sysop(op) __asm__ volatile(op ::: "memory")

// string
#define _concat(a, _1, b, ...) a##b
#define _sr_tkn_S(_0, _1, op0, op1, CRn, CRm, op2) s##op0##_##op1##_c##CRn##_c##CRm##_##op2
#define _sr_tkn(a) a
#define sr_tkn(...) _concat(_sr_tkn, __VA_ARGS__, )(__VA_ARGS__)


// system reg rw ops
#define __mrs(reg)                                                                                 \
    ({                                                                                             \
        u64 val;                                                                                   \
        __asm__ volatile("mrs\t%0, " #reg : "=r"(val));                                            \
        val;                                                                                       \
    })
#define _mrs(reg) __mrs(reg)

#define __msr(reg, val)                                                                            \
    ({                                                                                             \
        u64 __val = (u64)val;                                                                      \
        __asm__ volatile("msr\t" #reg ", %0" : : "r"(__val));                                      \
    })
#define _msr(reg, val) __msr(reg, val)

#define mrs(reg)      _mrs(sr_tkn(reg))
#define msr(reg, val) _msr(sr_tkn(reg), val)
#define msr_sync(reg, val)                                                                         \
    ({                                                                                             \
        _msr(sr_tkn(reg), val);                                                                    \
        sysop("isb");                                                                              \
    })


// system reg bit rw ops
#define reg_clr(reg, bits)      _msr(sr_tkn(reg), _mrs(sr_tkn(reg)) & ~(bits))
#define reg_set(reg, bits)      _msr(sr_tkn(reg), _mrs(sr_tkn(reg)) | bits)
#define reg_mask(reg, clr, set) _msr(sr_tkn(reg), (_mrs(sr_tkn(reg)) & ~(clr)) | set)

#define reg_clr_sync(reg, bits)                                                                    \
    ({                                                                                             \
        reg_clr(sr_tkn(reg), bits);                                                                \
        sysop("isb");                                                                              \
    })
#define reg_set_sync(reg, bits)                                                                    \
    ({                                                                                             \
        reg_set(sr_tkn(reg), bits);                                                                \
        sysop("isb");                                                                              \
    })
#define reg_mask_sync(reg, clr, set)                                                               \
    ({                                                                                             \
        reg_mask(sr_tkn(reg), clr, set);                                                           \
        sysop("isb");                                                                              \
    })

static const unsigned int get_exception_level(void)
{
    u64 lvl = mrs(CurrentEL);

    return (lvl >> 2) & 0x3;
}

#endif
