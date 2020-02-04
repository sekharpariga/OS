#include "types.h"
#include "gdt.h"

void printf(char* str)
{
    uint16_t * videoMemory = (uint16_t *) 0xb8000;

    static uint8_t x = 0, y = 0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        if(str[i] == '\n')
        {
            y += 1;
            x = 0;
        }
        if( y <= 80 & x <= 25)
        {
            videoMemory[i + (80*x) + y] = (videoMemory[i + (80*x) + y] & 0xFF00 )| str[i] ;
        }
        else
        {
            if(x == 25)
            {
                x = 0;
                y += 1;
            }
            if( y == 255)
            {
                for(uint8_t x1 = 0; x1 <25; x1++)
                    for(uint8_t y1 = 0; y1 < 80; y1++ )
                    {
                         videoMemory[(80*x1) + y1] = (videoMemory[ (80*x1) + y1] & 0xFF00 ) | ' ' ;
                    }
                    x = 0;
                    y = 0;
            }
        }
        
    }
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(void* multiboot_structure, uint32_t  magicnumber)
{
    printf("How are you Sekhar, Welcome to OS World\n");
    printf("Thank you, my pleasure");
    printf("Your welcome :)");
    globalDescriptorTable gdt;
    while(1);       //infinite loop
}
