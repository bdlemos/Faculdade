#include "operations.h"

#define BILLION  1000000000.0

double time_spent(struct timespec start, struct timespec end){
    return  (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / BILLION;
}

float get_user_time_exec(struct rusage end, struct rusage start) {
    if(end.ru_utime.tv_usec < start.ru_utime.tv_usec) {
        end.ru_utime.tv_usec = 10e6 + end.ru_utime.tv_usec - start.ru_utime.tv_usec;
        end.ru_utime.tv_sec = end.ru_utime.tv_sec - start.ru_utime.tv_sec;
    }

    return (end.ru_utime.tv_sec - start.ru_utime.tv_sec) + (end.ru_utime.tv_usec - start.ru_utime.tv_usec) / 10e6;
}

float get_sys_time_exec(struct rusage end,  struct rusage start) {
    if(end.ru_stime.tv_usec < start.ru_stime.tv_usec) {
        end.ru_stime.tv_usec = 10e6 + end.ru_stime.tv_usec - start.ru_stime.tv_usec;
        end.ru_stime.tv_sec =  end.ru_stime.tv_sec - start.ru_stime.tv_sec;
    }
    return (end.ru_stime.tv_sec - start.ru_stime.tv_sec) + (end.ru_stime.tv_usec - start.ru_stime.tv_usec) / 10e6;
}