#include "philo.h"

void	philo_think(t_philo *philo)
{
	show_message("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	show_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

// void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->r_fork);
// 	show_message("has taken a fork", philo, philo->id);
// 	if (philo->num_of_philos == 1)
// 	{
// 		ft_usleep(philo->time_to_die);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return ;
// 	}
// 	pthread_mutex_lock(philo->l_fork);
// 	show_message("has taken a fork", philo, philo->id);
// 	philo->eating = 1;
// 	show_message("is eating", philo, philo->id);
// 	pthread_mutex_lock(philo->meal_lock);
// 	philo->last_meal = get_current_time();
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(philo->meal_lock);
// 	ft_usleep(philo->time_to_eat);
// 	philo->eating = 0;
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }

// void	philo_eat(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;

//     // Determine the order of forks based on their memory addresses
//     if (philo->r_fork < philo->l_fork)
//     {
//         first_fork = philo->r_fork;
//         second_fork = philo->l_fork;
//     }
//     else
//     {
//         first_fork = philo->l_fork;
//         second_fork = philo->r_fork;
//     }

// 	if (philo->num_of_philos == 1)
// 	{
// 		ft_usleep(philo->time_to_die);
// 		return ;
// 	}

//     // Lock the forks in a consistent order
//     pthread_mutex_lock(first_fork);
//     show_message("has taken a fork", philo, philo->id);
//     pthread_mutex_lock(second_fork);
//     show_message("has taken a fork", philo, philo->id);

//     // Philosopher starts eating
//     philo->eating = 1;
//     show_message("is eating", philo, philo->id);
//     pthread_mutex_lock(philo->meal_lock);
//     philo->last_meal = get_current_time();
//     philo->meals_eaten++;
//     pthread_mutex_unlock(philo->meal_lock);
//     ft_usleep(philo->time_to_eat);
//     philo->eating = 0;

//     // Unlock the forks
//     pthread_mutex_unlock(second_fork);
//     pthread_mutex_unlock(first_fork);
// }

void	philo_eat(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		return ;
	}
	if (philo->l_fork < philo->r_fork) 
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	show_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	show_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}


void	*philo_action(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (philosopher);
}
