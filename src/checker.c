/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:22:30 by pzaw              #+#    #+#             */
/*   Updated: 2024/12/30 20:22:30 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal > time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			show_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos->num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			done++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (done == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*checker(void *philosopher)
{
	t_philo	*philos;

	philos = (t_philo *)philosopher;
	while (1)
	{
		if (check_dead(philos) == 1 || check_all_ate(philos) == 1)
			break ;
	}
	return (philosopher);
}
