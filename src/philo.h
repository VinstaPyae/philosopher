#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t			thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//main
int	check_args(char **argv);
int	is_num(char *argv);

//init
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_input(t_philo *philo, char **argv);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);

//checker
void	*checker(void *philosopher);
void	show_message(char *str, t_philo *philo, int id);
int	philo_dead(t_philo *philo, size_t time_to_die);
int	check_dead(t_philo *philos);
int	check_all_ate(t_philo *philos);

//philo
int	philo_thread(t_program *program, pthread_mutex_t *forks);
int	dead_loop(t_philo *philo);

//utils
void	destroyer(char *str, t_program *program, pthread_mutex_t *forks);
int	ft_usleep(size_t millisec);
size_t	get_current_time(void);
int	ft_atoi(char *str);
int	ft_strlen(char *s);

//actions
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	*philo_action(void *philosopher);

#endif