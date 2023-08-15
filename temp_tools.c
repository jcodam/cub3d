#include "map.h"
#include "defines.h"
#include "stdio.h"

void	print_tiles(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			printf("tile x: %d, tile y: %d", map->tiles[i][j]->x, \
			map->tiles[i][j]->y);
			j++;
		}
		j = 0;
		i++;
	}
}