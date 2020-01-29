void printf(char* str)
{
    unsigned short * videoMemory = (unsigned short *) 0xb8000;
    
    for(int i = 0; str[i] != '\0'; ++i)
        videoMemory[i] = (videoMemory[i] & 0xFF00 )| str[i] ;
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
    printf("Hello World!, Its Sekhar first OS\n");
    while(1);       //infinate loop
}