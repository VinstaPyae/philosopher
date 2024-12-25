#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	philo_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	server;
	int			i;

	if (pthread_create(&server, NULL, &checker, program->philos) != 0)
		destroyer("Server thread error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_action,
				&program->philos[i]) != 0)
			destroyer("Philo thread error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(server, NULL) != 0)
		destroyer("Server thread join error!", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroyer("Philo thread join error!", program, forks);
		i++;
	}
	return (0);
}