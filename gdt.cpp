#include "gdt.h"

globalDescriptorTable::globalDescriptorTable()
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024, 0x9A),
dataSegmentSelector(0,64*1024*1024, 0x92)
{

    uint32_t i[2];
    i[0] = (uint32_t) this;
    i[1] = sizeof(globalDescriptorTable) << 16;

    asm volatile("lgdt (%0)": : "p" (((uint8_t *) i) +2));

}