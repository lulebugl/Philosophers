#include "philo.h"

int	clean_memory(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo)
		{
			free(data->philo);
		}
		i--;
	}
	memset(data, 0, sizeof(t_data));
	return (0);
}