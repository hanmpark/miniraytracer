#include "mrt_math.h"
#include "mrt_render.h"

int	close_enough(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

double	solve_quadratic(double a, double b, double c, double ret)
{
	double	det;
	double	root1;
	double	root2;

	det = (b * b) - (4.0 * a * c);
	if (det < 0.0)
		return (ret);
	det = sqrt(det);
	root1 = (-b + det) / (2.0 * a);
	root2 = (-b - det) / (2.0 * a);
	if (root1 > 0.0 && root1 < root2)
		return (root1);
	else if (root2 > 0.0)
		return (root2);
	return (ret);
}
