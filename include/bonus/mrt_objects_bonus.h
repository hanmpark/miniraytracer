/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_objects_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:17:28 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 12:40:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_OBJECTS_BONUS_H
# define MRT_OBJECTS_BONUS_H

typedef enum e_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	CAP,
	SIDE
}	t_type;

/* OBJECT INTERSECTION */

bool	hit_object(t_obj *object, t_ray ray, t_hit *hit);

bool	hit_sphere(t_obj *object, t_ray ray, t_hit *hit);
bool	hit_plane(t_obj *object, t_ray ray, t_hit *hit);
bool	hit_cylinder(t_obj *object, t_ray ray, t_hit *hit);
bool	hit_cone(t_obj *object, t_ray ray, t_hit *hit);

/* SET UP CLOSEST HIT */

void	set_closest_hit(t_fvec3 cam_pos, t_hit *hit, t_obj *o);

#endif