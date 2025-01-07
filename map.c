#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int x_start;
    int x_end;
    int y_start;
    int y_end;
    int x_renge;
    int y_renge;
} Map;

char game_map[30][120];

int random_renge(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void room1(Map *map)
{
    map->x_start = random_renge(10, 100);
    map->y_start = random_renge(5, 15);
    map->x_renge = random_renge(6, 10);
    map->y_renge = random_renge(6, 10);
    map->x_end = map->x_start + map->x_renge;
    map->y_end = map->y_start + map->y_renge;

    for (int i = map->x_start; i <= map->x_end; i++)
    {
        game_map[map->y_start][i] = '#';
        game_map[map->y_end][i] = '#';
    }

    for (int i = map->y_start; i <= map->y_end; i++)
    {
        game_map[i][map->x_start] = '#';
        game_map[i][map->x_end] = '#';
    }
}

void room2(Map *map)
{
    map->x_start = random_renge(10, 100);
    map->y_start = random_renge(5, 15);
    map->x_renge = random_renge(6, 10);
    map->y_renge = random_renge(6, 10);
    map->x_end = map->x_start + map->x_renge;
    map->y_end = map->y_start + map->y_renge;
    
    for (int i = map->x_start; i <= map->x_end; i++)
    {
        game_map[map->y_start][i] = '#';
        game_map[map->y_end][i] = '#';
    }

    for (int i = map->y_start; i <= map->y_end; i++)
    {
        game_map[i][map->x_start] = '#';
        game_map[i][map->x_end] = '#';
    }
}

void map_maker(Map *map)
{
    map->x_start = random_renge(10, 100);
    map->y_start = random_renge(5, 15);
    map->x_renge = random_renge(4, 10);
    map->y_renge = random_renge(4, 10);
    map->x_end = map->x_start + map->x_renge;
    map->y_end = map->y_start + map->y_renge;

    for (int i = map->x_start; i <= map->x_end; i++)
    {
        game_map[map->y_start][i] = '#';
        game_map[map->y_end][i] = '#';
    }

    for (int i = map->y_start; i <= map->y_end; i++)
    {
        game_map[i][map->x_start] = '#';
        game_map[i][map->x_end] = '#';
    }
    
}

int main()
{
    initscr();
    srand(time(NULL));
    Map map;

    while (1)
    {
        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 120; j++)
            {
                game_map[i][j] = '.';
            }
            
        }

        clear();
        map_maker(&map);

        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 120; j++)
            {
                printw("%c", game_map[i][j]);
            }
        }
        refresh();
        getch();
    }
    
    endwin();
    return 0;
}