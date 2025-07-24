#include "libft/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("maps/42.fdf", O_RDONLY);
    char *line;
    int count = 0;
    
    if (fd < 0)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    printf("Testing get_next_line:\n");
    while ((line = get_next_line(fd)) != NULL && count < 5)
    {
        printf("Line %d: %s", count + 1, line);
        free(line);
        count++;
    }
    
    close(fd);
    printf("Test completed.\n");
    return 0;
} 