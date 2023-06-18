#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>   // for sleep()
#include "fibFact.h"
#include "operations.h"


int main(int argc, char **argv){
    
    struct timespec start_clock, end_clock;
    struct rusage start_user, end_user;

    clock_gettime(CLOCK_REALTIME, &start_clock);
    getrusage(RUSAGE_SELF, &start_user);
    int n = 20;

    if (*argv[1] == '1'){
        for (int i = 1; i <= n; i++) Rfact(i);
        
        clock_gettime(CLOCK_REALTIME, &end_clock);
        getrusage(RUSAGE_SELF, &end_user);
        
        printf("Recursive - Total time for 1<= x <= n\nThe clock time is %f seconds \nThe user time is %f seconds \nThe system time is %f seconds\n\n", 
                time_spent(start_clock, end_clock), get_user_time_exec(end_user, start_user), get_sys_time_exec(end_user, start_user));
        
        clock_gettime(CLOCK_REALTIME, &start_clock);
        getrusage(RUSAGE_SELF, &start_user);

        for (int i = 1; i <= n; i++) fact(i);
        
        clock_gettime(CLOCK_REALTIME, &end_clock);
        getrusage(RUSAGE_SELF, &end_user);
        
        printf("Iterative - Total time for 1<= x <= n\nThe clock time is %f seconds \nThe user time is %f seconds \nThe system time is %f seconds\n\n", 
                time_spent(start_clock, end_clock), get_user_time_exec(end_user, start_user), get_sys_time_exec(end_user, start_user));
        
        printf("Fatorial de %d iterativo: %llu\n", 5,fact(5));
        printf("Fatorial de %d recursivo: %llu\n", 5,Rfact(5));
        
    }
    else {
        for (int i = 1; i <= n; i++) Rfib(i);
        
        clock_gettime(CLOCK_REALTIME, &end_clock);
        getrusage(RUSAGE_SELF, &end_user);
        
        printf("Recursive - Total time for 1<= x <= n\nThe clock time is %f seconds \nThe user time is %f seconds \nThe system time is %f seconds\n\n", 
                time_spent(start_clock, end_clock), get_user_time_exec(end_user, start_user), get_sys_time_exec(end_user, start_user));
        
        clock_gettime(CLOCK_REALTIME, &start_clock);
        getrusage(RUSAGE_SELF, &start_user);

        for (int i = 1; i <= n; i++) fib(i);
        
        clock_gettime(CLOCK_REALTIME, &end_clock);
        getrusage(RUSAGE_SELF, &end_user);
        
        printf("Iterative - Total time for 1<= x <= n\nThe clock time is %f seconds \nThe user time is %f seconds \nThe system time is %f seconds\n\n", 
                time_spent(start_clock, end_clock), get_user_time_exec(end_user, start_user), get_sys_time_exec(end_user, start_user));
        
        printf("Fibonacci de %d iterativo: %llu\n", 5,fib(5));
        printf("Fibonacci de %d recursivo: %llu\n", 5,Rfib(5));
        
    }
    return 0;
}