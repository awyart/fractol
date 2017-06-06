/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 13:59:47 by awyart            #+#    #+#             */
/*   Updated: 2017/06/04 18:49:50 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_define1_ev(t_ev ev[NBEVE])
{
	ev[0].key = 53;
	ev[1].key = 78;
	ev[2].key = 69;
	ev[3].key = 126;
	ev[4].key = 123;
	ev[5].key = 124;
	ev[6].key = 125;
	ev[7].key = 15;
	ev[8].key = iter+;
	ev[9].key = iter-;
	ev[10].key = stop;
	ev[11].key = info;
	ev[12].key = zauto;
}

static void	ft_define2_ev(t_ev ev[NBEVE])
{
	ev[0].f = &ft_exit;
	ev[1].f = &ft_zoom_in;
	ev[2].f = &ft_zoom_out;
	ev[3].f = &ft_evz;
	ev[4].f = &ft_evq;
	ev[5].f = &ft_evs;
	ev[6].f = &ft_evd;
	ev[7].f = &ft_reset;
	ev[8].f = &ft_iterp;
	ev[9].f = &ft_iterl;
	ev[10].f = &ft_mouse_stop;
	ev[11].f = &ft_put_info;
	ev[12].f = &ft_activate_zauto;
}

int			my_key_func(int keycode, t_env *env)
{
	int		i;
	t_ev	g_ev[NBEVE];

	i = -1;
	ft_define1_ev(g_ev);
	ft_define2_ev(g_ev);
	while (++i < NBEVE)
	{
		if (keycode == g_ev[i].key)
		{
			g_ev[i].f(env);
			break ;
		}
	}
	return (0);
}

int		ft_start(t_env *env)
{
	if (env->type == '1')
		ft_julia(env);
	else if (env->type == '2')
		ft_mandelbrot(env);
	else if (env->type == '3')
		ft_lianpounov(env);
	else if (env->type == '4')
		ft_burning(env);
	else
	{
		ft_putstr_fd("usage :\n1: fractale Julia\n2: fractale Mandelbrot", 0);
		return (0);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2)
	{
		ft_putstr_fd("usage :\n1: fractale Julia\n2: fractale Mandelbrot", 0);
		return (0);
	}
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (0);
	env->type = av[1][0];
	if (ft_init_mlx(env) == 1)
		return (0);
	ft_start(env);
	mlx_expose_hook(env->win, &ft_start, env);
	mlx_key_hook(env->win, my_key_func, env);
	mlx_hook(env->win, MOTION_NOTIFY, PTR_MOTION_MASK, mouse_move_hook, env);
	mlx_mouse_hook(env->win, mouse_move_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
