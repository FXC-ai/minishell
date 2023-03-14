#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Received signal %d\n", sig);
}

dfg "" '' dfgdf


int main() {


    /*
        struct  sigaction 
        {
            union __sigaction_u __sigaction_u; 
            sigset_t sa_mask;                   
            int     sa_flags;                   
        };

    */

    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    while (1) {
        printf("Waiting for signal...\n");
        sleep(1);
    }
    return 0;
}