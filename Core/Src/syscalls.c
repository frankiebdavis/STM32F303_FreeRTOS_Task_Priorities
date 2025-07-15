#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

/* ITM configuration for SWO printf output */
#define DEMCR               (*(volatile uint32_t*) 0xE000EDFCU)
#define ITM_STIMULUS_PORT0  (*(volatile uint32_t*) 0xE0000000)
#define ITM_TRACE_EN        (*(volatile uint32_t*) 0xE0000E00)

void ITM_SendChar(uint8_t ch)
{
    DEMCR |= (1 << 24);            // Enable trace
    ITM_TRACE_EN |= (1 << 0);      // Enable Stimulus Port 0

    while (!(ITM_STIMULUS_PORT0 & 1)); // Wait until ready
    ITM_STIMULUS_PORT0 = ch;
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    for (int i = 0; i < len; i++)
    {
        ITM_SendChar(ptr[i]);
    }
    return len;
}

/* Optional newlib stubs — keep minimal for embedded */
int _close(int file)             { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file)           { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _kill(int pid, int sig)     { errno = EINVAL; return -1; }
void _exit(int status)          { while (1) {} }
int _getpid(void)               { return 1; }
