#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <sys/resource.h>   // for sleep()

double time_spent(struct timespec start, struct timespec end);
float get_user_time_exec(struct rusage end, struct rusage start);
float get_sys_time_exec(struct rusage end,  struct rusage start);