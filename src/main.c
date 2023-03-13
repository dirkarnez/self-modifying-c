#include <windows.h> 
 
__declspec(noinline) void hello() 
{ 
    volatile int flag = 0; 
 
    if (flag) { 
        printf("shouldn't print\n"); 
    } 
    else { 
        printf("should print\n"); 
    } 
} 
 
int _tmain(int argc, _TCHAR* argv[]) 
{ 
    // Get address of code, as byte (char) pointer. 
    char * fn = &hello; 
 
    // Change protection. 
    DWORD ignore; 
    VirtualProtect(fn, 128, PAGE_EXECUTE_READWRITE, &ignore); 
 
    // Find JZ instruction. 
    while (*fn != 0x74) { 
        fn++; 
    } 
 
    // Replace by NOP. 
    fn[0] = fn[1] = 0x90; 
 
    // Call. 
    hello(); 
 
    return 0; 
} 
