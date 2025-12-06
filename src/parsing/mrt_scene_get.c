#include "mrt_parsing.h"

static void	sanitize_lines(char **rt_scene)
{
	char	*sanitized_line;
	int		i;

	i = -1;
	while (rt_scene[++i])
	{
		sanitized_line = ft_strtrim(rt_scene[i], " \t");
		free(rt_scene[i]);
		rt_scene[i] = sanitized_line;
	}
}

static bool	has_rt_extension(const char *filename)
{
	int	filename_len;

	filename_len = (int)ft_strlen(filename);
	if (filename_len < 3)
		return (false);
	return (!c_strcmp(filename + filename_len - 3, ".rt"));
}

char	**get_rt_scene(char *filename)
{
	int		fd;
	char	*rt_scene;
	char	**formatted_scene;

	if (!has_rt_extension(filename))
		return (error_array(ERR_FILE));
	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (error_array(ERR_OPEN));
	rt_scene = c_readfd(fd);
	close(fd);
	if (!rt_scene)
		return (error_array(ERR_READ));
	formatted_scene = c_split_func(rt_scene, &c_isnl);
	free(rt_scene);
	sanitize_lines(formatted_scene);
	return (formatted_scene);
}
