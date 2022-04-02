/*************************************************************************
  > File Name: mem_ops.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Sat 02 Apr 2022 06:48:00 PM CST
 ************************************************************************/
#ifndef MEM_OPS_H
#define MEM_OPS_H

#define BIT(x)                 (1UL << (x))
#define MASK(x)                (BIT(x) - 1)
#define GENMASK(msb, lsb)      ((BIT((msb + 1) - (lsb)) - 1) << (lsb))
#define _FIELD_LSB(field)      ((field) & ~(field - 1))
#define FIELD_PREP(field, val) ((val) * (_FIELD_LSB(field)))
#define FIELD_GET(field, val)  (((val) & (field)) / _FIELD_LSB(field))

#define ALIGN_UP(x, a)   (((x) + ((a)-1)) & ~((a)-1))
#define ALIGN_DOWN(x, a) ((x) & ~((a)-1))

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

static inline u64 read64(u64 addr)
{
    u64 data;
    __asm__ volatile("ldr\t%0, [%1]" : "=r"(data) : "r"(addr) : "memory");
    return data;
}

static inline void write64(u64 addr, u64 data)
{
    __asm__ volatile("str\t%0, [%1]" : : "r"(data), "r"(addr) : "memory");
}

static inline u64 set64(u64 addr, u64 set)
{
    u64 data;
    __asm__ volatile("ldr\t%0, [%1]\n"
                     "\torr\t%0, %0, %2\n"
                     "\tstr\t%0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set)
                     : "memory");
    return data;
}

static inline u64 clear64(u64 addr, u64 clear)
{
    u64 data;
    __asm__ volatile("ldr\t%0, [%1]\n"
                     "\tbic\t%0, %0, %2\n"
                     "\tstr\t%0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(clear)
                     : "memory");
    return data;
}

static inline u64 mask64(u64 addr, u64 clear, u64 set)
{
    u64 data;
    __asm__ volatile("ldr\t%0, [%1]\n"
                     "\tbic\t%0, %0, %3\n"
                     "\torr\t%0, %0, %2\n"
                     "\tstr\t%0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set), "r"(clear)
                     : "memory");
    return data;
}

static inline u64 writeread64(u64 addr, u64 data)
{
    write64(addr, data);
    return read64(addr);
}

static inline u32 read32(u64 addr)
{
    u32 data;
    __asm__ volatile("ldr\t%w0, [%1]" : "=r"(data) : "r"(addr) : "memory");
    return data;
}

static inline void write32(u64 addr, u32 data)
{
    __asm__ volatile("str\t%w0, [%1]" : : "r"(data), "r"(addr) : "memory");
}

static inline u32 writeread32(u64 addr, u32 data)
{
    write32(addr, data);
    return read32(addr);
}

static inline u32 set32(u64 addr, u32 set)
{
    u32 data;
    __asm__ volatile("ldr\t%w0, [%1]\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstr\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set)
                     : "memory");
    return data;
}

static inline u32 clear32(u64 addr, u32 clear)
{
    u32 data;
    __asm__ volatile("ldr\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w2\n"
                     "\tstr\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(clear)
                     : "memory");
    return data;
}

static inline u32 mask32(u64 addr, u32 clear, u32 set)
{
    u32 data;
    __asm__ volatile("ldr\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w3\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstr\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set), "r"(clear)
                     : "memory");
    return data;
}

static inline u16 read16(u64 addr)
{
    u32 data;
    __asm__ volatile("ldrh\t%w0, [%1]" : "=r"(data) : "r"(addr) : "memory");
    return data;
}

static inline void write16(u64 addr, u16 data)
{
    __asm__ volatile("strh\t%w0, [%1]" : : "r"(data), "r"(addr) : "memory");
}

static inline u16 set16(u64 addr, u16 set)
{
    u16 data;
    __asm__ volatile("ldrh\t%w0, [%1]\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstrh\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set)
                     : "memory"

    );
    return data;
}

static inline u16 clear16(u64 addr, u16 clear)
{
    u16 data;
    __asm__ volatile("ldrh\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w2\n"
                     "\tstrh\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(clear)
                     : "memory");
    return data;
}

static inline u16 mask16(u64 addr, u16 clear, u16 set)
{
    u16 data;
    __asm__ volatile("ldrh\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w3\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstrh\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set), "r"(clear)
                     : "memory");
    return data;
}

static inline u16 writeread16(u64 addr, u16 data)
{
    write16(addr, data);
    return read16(addr);
}

static inline u8 read8(u64 addr)
{
    u32 data;
    __asm__ volatile("ldrb\t%w0, [%1]" : "=r"(data) : "r"(addr) : "memory");
    return data;
}

static inline void write8(u64 addr, u8 data)
{
    __asm__ volatile("strb\t%w0, [%1]" : : "r"(data), "r"(addr) : "memory");
}

static inline u8 set8(u64 addr, u8 set)
{
    u8 data;
    __asm__ volatile("ldrb\t%w0, [%1]\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstrb\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set)
                     : "memory");
    return data;
}

static inline u8 clear8(u64 addr, u8 clear)
{
    u8 data;
    __asm__ volatile("ldrb\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w2\n"
                     "\tstrb\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(clear)
                     : "memory");
    return data;
}

static inline u8 mask8(u64 addr, u8 clear, u8 set)
{
    u8 data;
    __asm__ volatile("ldrb\t%w0, [%1]\n"
                     "\tbic\t%w0, %w0, %w3\n"
                     "\torr\t%w0, %w0, %w2\n"
                     "\tstrb\t%w0, [%1]"
                     : "=&r"(data)
                     : "r"(addr), "r"(set), "r"(clear)
                     : "memory");
    return data;
}

static inline u8 writeread8(u64 addr, u8 data)
{
    write8(addr, data);
    return read8(addr);
}
#endif
