#include "libft/get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("maps/42.fdf", O_RDONLY);
    char *line;
    
    if (fd < 0)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Testing get_next_line:\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
    
    close(fd);
    return 0;
} 