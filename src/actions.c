/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:22:22 by pzaw              #+#    #+#             */
/*   Updated: 2024/12/30 20:22:22 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	determine_forks(t_philo *philo, pthread_mutex_t **first_fork,
pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->l_fork;
		*second_fork = philo->r_fork;
	}
	else
	{
		*first_fork = philo->r_fork;
		*second_fork = philo->l_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		return ;
	}
	determine_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	show_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(second_fork);
	show_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	show_message("is eating", philo, philo->id);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philo_action(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!dead_loop(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (philosopher);
}
