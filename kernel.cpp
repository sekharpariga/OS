#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"

#define SCREEN_X 80
#define SCREEN_Y 25

void printf(char* str)
{
    uint16_t * videoMemory = (uint16_t *) 0xb8000;

    static uint8_t x = 0, y = 0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                y++;
                x = 0;
                break;
            default :
                videoMemory[SCREEN_X*y + x] = (videoMemory[SCREEN_X*y + x] & 0xFF00) | str[i] ;
                x++;
        }

        if(x >= SCREEN_X)                 // completion of screen right side size
        {
            y++;
            x =0;
        }

        if(y >= SCREEN_Y)                  // completion of bottom of screen
        {
            for(y = 0; y < SCREEN_Y; y++)
                for(x = 0; x < SCREEN_X ; x++)
                    videoMemory[SCREEN_X*y + x] = (videoMemory[SCREEN_X*y + x] & 0xFF00) | ' ' ;
            x = 0;
            y = 0;
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
    printf("Hello Sekhar, Welcome to myOS  :)");
    printf("\nDo you Want to see more of me ?\n");

    globalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);
    KeyboardDriver keyboard(&interrupts);
    interrupts.Activate();
    while(1);       //infinite loop
}
