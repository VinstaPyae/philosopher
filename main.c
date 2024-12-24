#include "philo.h"

int	is_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| is_num(argv[1] == 1))
		return (printf("Invlid amount of philosophers!\n"), 1);
	if (ft_atoi(argv[2]) <= 0 || is_num(argv[2]) == 1)
		return (printf("Invlid time to die!\n"), 1);
	if (ft_atoi(argv[3]) <= 0 || is_num(argv[3]) == 1)
		return (printf("Invlid time to eat!\n"), 1);
	if (ft_atoi(argv[4]) <= 0 || is_num(argv[4]) == 1)
		return (printf("Invlid time to sleep!\n"), 1);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || is_num(argv[5]) == 1))
		return (printf("Invlid times for philosophers to eat!\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (printf("Invalid argument amount!\n"), 1);
	if (check_args(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	philo_thread(program, forks);
}