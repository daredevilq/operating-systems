#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("Received signal: %d\n", signum);
}

int main() {
    // Ustawienie funkcji obsługi sygnału SIGUSR1
    signal(SIGUSR1, handler);

    // Tworzenie i ustawienie zestawu sygnałów
    sigset_t pending_signals, old_mask, new_mask;
    sigemptyset(&pending_signals); // Czyszczenie zestawu sygnałów

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    sigprocmask(SIG_SETMASK, &new_mask, NULL);
    // Wysłanie sygnału SIGUSR1
    kill(getpid(), SIGUSR1);

    // Sprawdzenie, które sygnały są oczekujące
    sigpending(&pending_signals);

    // Sprawdzenie, czy SIGUSR1 jest oczekujący
    if (sigismember(&pending_signals, SIGUSR1)) {
        printf("SIGUSR1 is pending\n");

        // Zastąpienie maski procesu zestawem oczekujących sygnałów
        sigsuspend(&pending_signals);

        // Po obsłudze sygnału, przywrócenie poprzedniej maski
        sigprocmask(SIG_SETMASK, &old_mask, NULL);
    }

    return 0;
}
