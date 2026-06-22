#include  "..\..\BIOS.C"
#include  "..\..\PIT.C"
#include  "..\..\SYSTEM.C"

int main(){

    tick_t start;
    tick_t end;
    tick_t i;

    start = System_GetTicks();

    for(i=0;i<100000;i++)
    {
        System_GetTicks();
    }

    end = System_GetTicks();

    printf("%lu ticks, %lu ms\n", end-start,System_TicksToMS(end-start));

    return 0;
}   