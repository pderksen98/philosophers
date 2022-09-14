/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 16:23:20 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/14 16:25:35 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


t_mutex	mutex_init(void)
{
	t_mutex	m;

	m = (t_mutex)malloc(sizeof(t_mutex));
	if (!m)
		ft_error("Malloc error\n");
	m.on = 
}









t_mutex	*mutex_init(void)
{
	t_mutex	*m;
​
	m = (t_mutex *)malloc(sizeof(t_mutex));
	if (m == NULL)
		return (NULL);
	m->on = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
	{
		free(m);
		return (NULL);
	}
	if (pthread_mutex_init(&m->wait, NULL) != 0)
	{
		free(m);
		pthread_mutex_destroy(&m->mutex);
		return (NULL);
	}
	return (m);
}