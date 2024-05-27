#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <math.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void signal_hanlder(){
	// this does nothing
}

typedef struct 
{
	int start_cell;
	int end_cell;
	char **background;
	char **foreground;

} pthread_args_t;


void* thread_function(void* arg) {
	
	pthread_args_t * args = (pthread_args_t*)arg;
	
	
	while (true) {
		
		pause();	
		for (int i = args->start_cell; i < args->end_cell; i++) {
			int row = i / 30; 
			int col = i % 30; 

			
			(*args->background)[i] = is_alive(row, col, *args->foreground);
		}
	}
}

int main(int argc , char *argv[])
{	

	if (argc < 2)
	{
		perror("Imput number of thread - max 12\n");
		return EXIT_FAILURE;
	}
	
	int number_of_threads = atoi(argv[1]);
	number_of_threads = number_of_threads % 12;

	struct sigaction sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_hanlder;

	sigaction(SIGUSR1, &sa, NULL);


	pthread_t threads[number_of_threads];
	pthread_args_t args[number_of_threads];

	int cells_per_thread = (int)ceil(30 * 30 / number_of_threads);



	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode

	char *foreground = create_grid();
	char *background = create_grid();
	char *tmp;


	for (int i = 0; i < number_of_threads; i++)
	{
		args[i].start_cell = i * cells_per_thread;
		args[i].end_cell = MIN((i + 1) * cells_per_thread, 900);
	
		args[i].foreground = &foreground;
		args[i].background = &background;

		
		pthread_create(&threads[i], NULL, thread_function, &args[i]);
	}
	



	init_grid(foreground);

	while (true)
	{
		draw_grid(foreground);

		for(int i = 0; i < number_of_threads; i++) {
			pthread_kill(threads[i], SIGUSR1);
		}
		usleep(500 * 1000);

		
		update_grid(foreground, background);
		tmp = foreground;
		foreground = background;
		background = tmp;
	}

	endwin(); // End curses mode
	destroy_grid(foreground);
	destroy_grid(background);

	return 0;
}
