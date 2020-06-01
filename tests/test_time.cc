#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

uint32_t lruclock = static_cast<uint32_t>(::time(nullptr));
int main()
{
    printf("自 1970-01-01 起的秒数 = %ld\n", lruclock);
    sleep(3);
    printf("自 1970-01-01 起的秒数 = %ld\n", lruclock);
    return (0);
}