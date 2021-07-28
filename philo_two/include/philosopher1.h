#ifndef PHILOSOPHER1_H
# define PHILOSOPHER1_H

# include <stdbool.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef unsigned long	t_time_useconds;
typedef unsigned long	t_useconds;

typedef enum e_fork
{
	AVAILABLE,
	IN_USE,
}			t_fork;

typedef enum e_status
{
	FAILURE,
	SUCCESS,
	CASUALTY,
}			t_status;

typedef struct s_input
{
	size_t			n;
	t_useconds		time_to_die;
	t_useconds		time_to_eat;
	t_useconds		time_to_sleep;
	long			must_eat_n;
}		t_input;

typedef struct s_globals
{
	t_fork			*forks;
	pthread_mutex_t	lock;
	size_t			n;
	void			*phs;
	bool			casualty;
}		t_globals;

typedef struct s_ph
{
	size_t			id;
	pthread_t		threadid;
	t_time_useconds	last_meal;

	size_t			left_fork;
	size_t			right_fork;
	t_useconds		time_to_die;
	t_useconds		time_to_eat;
	t_useconds		time_to_sleep;
	long			must_eat_n;

	t_globals		*g;
}		t_ph;

bool	phs_await(t_ph *phs, size_t n);
t_ph	*phs_create(t_input input, t_globals *g);
bool	phs_start(t_ph *phs, size_t n);

bool	exit_error(const char *str);

t_time_useconds epoch_useconds(void);
void	usleep_accurate(t_useconds time);


t_useconds	ph_life_expectancy(const t_ph *ph);
bool	casualty(t_ph *ph);

void	ph_consume_meal(t_ph *ph);

void	ph_print_status(const char *status, const t_ph *ph);
void	ph_die(t_ph *ph);
void	ph_delay(t_ph *ph, t_useconds time);
void	ph_sleep(t_ph *ph);
void	*ph_thread(void *philosoper);


#endif