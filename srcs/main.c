/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 01:50:56 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/24 01:51:33 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_trace.h"

int	main(int argc, char **argv)
{
	t_trace	*trace;

	if ((int)getuid() < 0)
	{
		ft_fprintf(1, "ft_traceroute: you do not have the necessary rights\n");
	}
	trace = singleton_trace();
	if (trace == NULL)
		return (0);
	if (!load_flag_list(trace))
		return (0);
	if (argc > 1)
	{
		if (!load_flags(trace, argc, argv))
			return (0);
		if (!set_flags_values(trace))
			return (false);
		if (trace->dest_ip)
		{
			printf("ft_traceroute to %s (%s), %d hops max, %d byte packets\n", trace->shost, trace->dest_ip, trace->max_hop, trace->sweepminsize);
			trace->launch(trace);
		}
		else
		{
			if (trace->shost == NULL)
				trace->shost = ft_strdup("");
			ft_fprintf(1, "ft_traceroute: cannot resolve %s: Unknow host\n", trace->shost);
		}
	}
	else
	{
		print_help(trace);
	}
	destruct_trace(trace);
	return (0);
}
