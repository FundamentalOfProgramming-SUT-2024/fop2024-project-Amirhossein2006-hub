#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef struct
{
    // 1 -> Treasure Room, 3 -> Enchant Room, 2 -> Regular Room
    int type;
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    int is_in;
    int door1_x;
    int door2_x;
    int door3_x;
    int door1_y;
    int door2_y;
    int door3_y;
} Rooms;

typedef struct
{
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    int is_in;
} Corridors;

char map[30][120];

void room_position1(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position1(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void print_map1(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void room_position2(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position2(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void print_map2(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void room_position3(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position3(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void print_map3(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void room_position4(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position4(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void print_map4(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void print_map(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
int random_renge(int a, int b);
char weapon();
char spell();
char monster();
char food();

int main()
{
    srand(time(NULL));
    Rooms room1, room2, room3, room4, room5, room6;
    Corridors corridor1, corridor2, corridor3, corridor4, corridor5;

    for (int i = 0; i < 4; i++)
    {
        int t = random_renge(0, 3);
        if (t == 0)
        {
            room_position1(&room1, &room2, &room3, &room4, &room5, &room6);
            corridor_position1(&corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
            print_map1(i + 1, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
        }
        if (t == 1)
        {
            room_position2(&room1, &room2, &room3, &room4, &room5, &room6);
            corridor_position2(&corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
            print_map2(i + 1, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
        }
        if (t == 2)
        {
            room_position3(&room1, &room2, &room3, &room4, &room5, &room6);
            corridor_position3(&corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
            print_map3(i + 1, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
        }
        if (t == 3)
        {
            room_position4(&room1, &room2, &room3, &room4, &room5, &room6);
            corridor_position4(&corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
            print_map4(i + 1, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
        }
        print_map(i + 1, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, &room1, &room2, &room3, &room4, &room5, &room6);
        FILE *corridors;
        FILE *rooms;
        FILE *floors;
        switch (i + 1)
        {
            case 1:
            {
                rooms = fopen("rooms1.dat", "rb+");
                corridors = fopen("corridors1.dat", "rb+");
                floors = fopen("Floor_1.txt", "w");
                break;
            }
            case 2:
            {
                rooms = fopen("rooms2.dat", "rb+");
                corridors = fopen("corridors2.dat", "rb+");
                floors = fopen("Floor_2.txt", "w");
                break;
            }
            case 3:
            {
                rooms = fopen("rooms3.dat", "rb+");
                corridors = fopen("corridors3.dat", "rb+");
                floors = fopen("Floor_3.txt", "w");
                break;
            }
            case 4:
            {
                rooms = fopen("rooms4.dat", "rb+");
                corridors = fopen("corridors4.dat", "rb+");
                floors = fopen("Floor_4.txt", "w");
                break;
            }
        }
        for (int i = 0; i < 6; i++)
        {
            Rooms room;
            switch (i)
            {
            case 0:
                room = room1;
                break;
            case 1:
                room = room2;
                break;
            case 2:
                room = room3;
                break;
            case 3:
                room = room4;
                break;
            case 4:
                room = room5;
                break;
            case 5:
                room = room6;
                break;
            }

            fseek(rooms, i * sizeof(Rooms), SEEK_SET);
            fwrite(&room, sizeof(Rooms), 1, rooms);
        }
        fclose(rooms);
        for (int i = 0; i < 5; i++)
        {
            Corridors corridor;
            switch (i)
            {
            case 0:
                corridor = corridor1;
                break;
            case 1:
                corridor = corridor2;
                break;
            case 2:
                corridor = corridor3;
                break;
            case 3:
                corridor = corridor4;
                break;
            case 4:
                corridor = corridor5;
                break;
            }

            fseek(corridors, i * sizeof(Corridors), SEEK_SET);
            fwrite(&corridor, sizeof(Corridors), 1, corridors);
        }
        fclose(corridors);

        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 120; j++)
            {
                fprintf(floors, "%c", map[i][j]);
            }
            fprintf(floors, "\n");
        }
        fclose(floors);
    }
    return 0;
}

void room_position1(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    room1->type = 2;
    room1->s_x = random_renge(5, 7);
    room1->s_y = random_renge(1, 2);
    room1->e_x = room1->s_x + random_renge(6, 10);
    room1->e_y = room1->s_y + random_renge(5, 8);
    room1->is_in = 0;
    room1->door1_y = random_renge(room1->s_y + 2, room1->e_y - 4);
    room1->door1_x = room1->e_x;
    room1->door2_y = room1->e_y;
    room1->door2_x = random_renge(room1->s_x + 2, room1->e_x - 2);

    room2->type = 3;
    room2->s_x = random_renge(11, 15);
    room2->s_y = random_renge(12, 15);
    room2->e_x = room2->s_x + random_renge(6, 10);
    room2->e_y = room2->s_y + random_renge(6, 8);
    room2->is_in = 0;
    room2->door1_x = random_renge(room2->s_x + 2, room2->e_x - 2);
    room2->door1_y = room2->s_y;
    room2->door2_x = random_renge(room2->s_x + 2, room2->e_x - 2);
    room2->door2_y = room2->e_y;

    room3->type = 2;
    room3->s_x = random_renge(27, 33);
    room3->s_y = 17;
    room3->e_x = room3->s_x + random_renge(6, 10);
    room3->e_y = room3->s_y + 10;
    room3->is_in = 0;
    room3->door1_x = room3->s_x;
    room3->door1_y = random_renge(room2->e_y + 1, room3->e_y - 1);

    room4->type = 2;
    room4->s_x = random_renge(40, 50);
    room4->s_y = random_renge(6, 8);
    room4->e_x = room4->s_x + random_renge(6, 15);
    room4->e_y = room4->s_y + random_renge(6, 10);
    room4->is_in = 0;
    room4->door1_x = random_renge(room4->s_x + 2, room4->e_x - 2);
    room4->door1_y = room4->s_y;
    room4->door2_x = random_renge(room4->s_x + 4, room4->e_x - 2);
    room4->door2_y = room4->e_y;
    room4->door3_x = room4->e_x;
    room4->door3_y = random_renge(room4->s_y + 2, room4->e_y - 2);

    room5->type = 3;
    room5->s_x = random_renge(60, 65);
    room5->s_y = random_renge(19, 20);
    room5->e_x = room5->s_x + random_renge(5, 15);
    room5->e_y = room5->s_y + random_renge(6, 8);
    room5->door1_x = room5->s_x;
    room5->door1_y = random_renge(room5->s_y + 2, room5->e_y - 2);
    room5->is_in = 0;

    room6->type = 1;
    room6->s_x = random_renge(80, 90);
    room6->s_y = random_renge(2, 5);
    room6->e_x = room6->s_x + random_renge(8, 15);
    room6->e_y = room6->s_y + random_renge(10, 20);
    room6->door1_x = room6->s_x;
    room6->door1_y = random_renge(room6->s_y + 2, room6->e_y - 6);
    room6->is_in = 0;
}

void corridor_position1(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    corridor1->s_x = room1->door2_x;
    corridor1->s_y = room1->door2_y + 1;
    corridor1->e_x = room2->door1_x;
    corridor1->e_y = room2->door1_y - 1;
    corridor1->is_in = 0;

    corridor2->s_x = room2->door2_x;
    corridor2->s_y = room2->door2_y + 1;
    corridor2->e_x = room3->door1_x - 1;
    corridor2->e_y = room3->door1_y;
    corridor2->is_in = 0;

    corridor3->s_x = room1->door1_x + 1;
    corridor3->s_y = room1->door1_y;
    corridor3->e_x = room4->door1_x;
    corridor3->e_y = room4->door1_y - 1;
    corridor3->is_in = 0;

    corridor4->s_x = room4->door2_x;
    corridor4->s_y = room4->door2_y + 1;
    corridor4->e_x = room5->door1_x - 1;
    corridor4->e_y = room5->door1_y;
    corridor4->is_in = 0;

    if (room4->door3_y < room6->door1_y)
    {
        corridor5->s_y = room4->door3_y;
        corridor5->e_y = room6->door1_y;
    }
    else
    {
        corridor5->s_y = room6->door1_y;
        corridor5->e_y = room4->door3_y;
    }
    corridor5->s_x = room4->door3_x + 1;
    corridor5->e_x = room6->door1_x - 1;

    corridor5->is_in = 0;
}

void print_map1(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (room1->s_y <= i && i <= room1->e_y && room1->s_x <= j && j <= room1->e_x)
            {
                if (room1->s_x == j || j == room1->e_x)
                {
                    if (i == room1->door1_y && j == room1->door1_x)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room1->s_y == i || i == room1->e_y)
                {
                    if (j == room1->door2_x && i == room1->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                            
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room2->s_y <= i && i <= room2->e_y && room2->s_x <= j && j <= room2->e_x)
            {
                if (room2->s_x == j || j == room2->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room2->s_y == i || i == room2->e_y)
                {
                    if (j == room2->door1_x && i == room2->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room2->door2_x && i == room2->door2_y)
                    {
                        map[i][j] = '+';
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room3->s_y <= i && i <= room3->e_y && room3->s_x <= j && j <= room3->e_x)
            {
                if (room3->s_x == j || j == room3->e_x)
                {
                    if (j == room3->door1_x && i == room3->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room3->s_y == i || i == room3->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room4->s_y <= i && i <= room4->e_y && room4->s_x <= j && j <= room4->e_x)
            {
                if (room4->s_x == j || j == room4->e_x)
                {
                    if (j == room4->door3_x && i == room4->door3_y)
                    {
                        int a = random_renge(1, 3);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room4->s_y == i || i == room4->e_y)
                {
                    if (j == room4->door1_x && i == room4->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room4->door2_x && i == room4->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '_';
                        }
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room5->s_y <= i && i <= room5->e_y && room5->s_x <= j && j <= room5->e_x)
            {
                if (room5->s_x == j || j == room5->e_x)
                {
                    if (j == room5->door1_x && i == room5->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room5->s_y == i || i == room5->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room6->s_y <= i && i <= room6->e_y && room6->s_x <= j && j <= room6->e_x)
            {
                if (room6->s_x == j || j == room6->e_x)
                {
                    if (j == room6->door1_x && i == room6->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room6->s_y == i || i == room6->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else
            {
                map[i][j] = '-';
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (corridor1->s_x <= j && j <= corridor1->e_x)
            {
                if (i == corridor1->s_y)
                    map[i][j] = '#';
                if (j == corridor1->e_x && i > corridor1->s_y && i <= corridor1->e_y)
                    map[i][j] = '#';
            }

            if (corridor2->s_x <= j && j <= corridor2->e_x)
            {
                if (j == corridor2->s_x && i >= corridor2->s_y && i <= corridor2->e_y)
                    map[i][j] = '#';

                else if (i == corridor2->e_y)
                    map[i][j] = '#';
            }

            if (corridor3->s_x <= j && j <= corridor3->e_x)
            {                    
                if (i == corridor3->s_y)
                    map[i][j] = '#';

                else if (j == corridor3->e_x && i >= corridor3->s_y && i <= corridor3->e_y)
                    map[i][j] = '#';
            }

            if (corridor4->s_x <= j && j <= corridor4->e_x)
            {
                if (j == corridor4->s_x && i >= corridor4->s_y && i <= corridor4->e_y)
                    map[i][j] = '#';

                else if (i == corridor4->e_y)
                    map[i][j] = '#';
            }

            if (corridor5->s_x <= j && j <= corridor5->e_x)
            {
                if (j == (corridor5->s_x + corridor5->e_x) / 2)
                {
                    if (corridor5->s_y <= i && i <= corridor5->e_y)
                        map[i][j] = '#';
                }

                if (room4->door3_y < room6->door1_y)
                {
                    if (i == corridor5->s_y && corridor5->s_x <= j && j <= (corridor5->s_x + corridor5->e_x) / 2)
                        map[i][j] = '#';

                    if (i == corridor5->e_y && (corridor5->s_x + corridor5->e_x) / 2 <= j && j <= corridor5->e_x)
                        map[i][j] = '#';
                }
                else
                {
                    if (i == corridor5->e_y && corridor5->s_x <= j && j <= (corridor5->s_x + corridor5->e_x) / 2)
                        map[i][j] = '#';

                    if (i == corridor5->s_y && (corridor5->s_x + corridor5->e_x) / 2 <= j && j <= corridor5->e_x)
                        map[i][j] = '#';
                }
            }
        }
    }
}


void room_position2(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    room1->type = 2;
    room1->s_x = random_renge(55, 65);
    room1->s_y = 14;
    room1->e_x = room1->s_x + random_renge(6, 10);
    room1->e_y = room1->s_y + random_renge(6, 10);
    room1->is_in = 0;
    room1->door1_y = random_renge(room1->s_y + 2, room1->e_y - 4);
    room1->door1_x = room1->s_x;
    room1->door2_y = room1->e_y;
    room1->door2_x = random_renge(room1->s_x + 2, room1->e_x - 2);
    room1->door3_y = random_renge(room1->s_y + 2, room1->e_y - 2);
    room1->door3_x = room1->e_x;

    room2->type = 3;
    room2->s_x = random_renge(35, 44);
    room2->s_y = random_renge(1, 5);
    room2->e_x = room2->s_x + random_renge(6, 10);
    room2->e_y = room2->s_y + random_renge(6, 10);
    room2->is_in = 0;
    room2->door1_x = random_renge(room2->s_x + 2, room2->e_x - 2);
    room2->door1_y = room2->e_y;

    room3->type = 2;
    room3->s_x = random_renge(35, 44);
    room3->s_y = 20;
    room3->e_x = room3->s_x + random_renge(6, 10);
    room3->e_y = room3->s_y + random_renge(6, 9);
    room3->is_in = 0;
    room3->door1_x = room3->e_x;
    room3->door1_y = 25;
    room3->door2_x = room3->s_x;
    room3->door2_y = room3->e_y - 2;

    room4->type = 2;
    room4->s_x = random_renge(2, 10);
    room4->s_y = random_renge(16, 20);
    room4->e_x = room4->s_x + random_renge(6, 15);
    room4->e_y = room4->s_y + random_renge(6, 9);
    room4->is_in = 0;
    room4->door1_x = room4->e_x;
    room4->door1_y = random_renge(room4->s_y + 2, room4->e_y - 2);

    room5->type = 3;
    room5->s_x = random_renge(65, 70);
    room5->s_y = random_renge(1, 5);
    room5->e_x = room5->s_x + random_renge(10, 15);
    room5->e_y = room5->s_y + random_renge(6, 9);
    room5->door1_x = random_renge(room5->s_x + 4, room5->e_x - 2);
    room5->door1_y = room5->e_y;
    room5->door2_x = room5->e_x;
    room5->door2_y = random_renge(room5->s_y + 2, room5->e_y - 3);
    room5->is_in = 0;

    room6->type = 1;
    room6->s_x = random_renge(85, 90);
    room6->s_y = random_renge(5, 7);
    room6->e_x = room6->s_x + random_renge(8, 15);
    room6->e_y = room6->s_y + random_renge(10, 20);
    room6->door1_x = room6->s_x;
    room6->door1_y = random_renge(room6->s_y + 4, room6->e_y - 4);
    room6->is_in = 0;
}

void corridor_position2(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    corridor1->s_x = room2->door1_x;
    corridor1->s_y = room2->door1_y + 1;
    corridor1->e_x = room1->door1_x - 1;
    corridor1->e_y = room1->door1_y;
    corridor1->is_in = 0;

    corridor2->s_x = room3->door1_x + 1;
    corridor2->s_y = room1->door2_y + 1;
    corridor2->e_x = room1->door2_x;
    corridor2->e_y = room3->door1_y;
    corridor2->is_in = 0;

    corridor3->s_x = room4->door1_x + 1;
    corridor3->s_y = room4->door1_y;
    corridor3->e_x = room3->door2_x - 1;
    corridor3->e_y = room3->door2_y;
    corridor3->is_in = 0;

    corridor4->s_x = room1->door3_x + 1;
    corridor4->s_y = room5->door1_y + 1;
    corridor4->e_x = room5->door1_x;
    corridor4->e_y = room1->door3_y;
    corridor4->is_in = 0;


    corridor5->s_y = room5->door2_y;
    corridor5->e_y = room6->door1_y;
    corridor5->s_x = room5->door2_x + 1;
    corridor5->e_x = room6->door1_x - 1;
    corridor5->is_in = 0;
}

void print_map2(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (room1->s_y <= i && i <= room1->e_y && room1->s_x <= j && j <= room1->e_x)
            {
                if (room1->s_x == j || j == room1->e_x)
                {
                    if (i == room1->door1_y && j == room1->door1_x)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else if (i == room1->door3_y && j == room1->door3_x)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room1->s_y == i || i == room1->e_y)
                {
                    if (j == room1->door2_x && i == room1->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room2->s_y + 1][room2->s_x + 1] = '&';
                        }
                            
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room2->s_y <= i && i <= room2->e_y && room2->s_x <= j && j <= room2->e_x)
            {
                if (room2->s_x == j || j == room2->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room2->s_y == i || i == room2->e_y)
                {
                    if (j == room2->door1_x && i == room2->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room3->s_y <= i && i <= room3->e_y && room3->s_x <= j && j <= room3->e_x)
            {
                if (room3->s_x == j || j == room3->e_x)
                {
                    if (j == room3->door1_x && i == room3->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room3->door2_x && i == room3->door2_y)
                    {
                        map[i][j] = '/';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room3->s_y == i || i == room3->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room4->s_y <= i && i <= room4->e_y && room4->s_x <= j && j <= room4->e_x)
            {
                if (room4->s_x == j || j == room4->e_x)
                {
                    if (j == room4->door1_x && i == room4->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room4->s_y == i || i == room4->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room5->s_y <= i && i <= room5->e_y && room5->s_x <= j && j <= room5->e_x)
            {
                if (room5->s_x == j || j == room5->e_x)
                {
                    if (j == room5->door2_x && i == room5->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room2->s_y + 1][room2->s_x + 1] = '&';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room5->s_y == i || i == room5->e_y)
                {
                    if (j == room5->door1_x && i == room5->door1_y)
                    {
                        map[i][j] = '+';  
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room6->s_y <= i && i <= room6->e_y && room6->s_x <= j && j <= room6->e_x)
            {
                if (room6->s_x == j || j == room6->e_x)
                {
                    if (j == room6->door1_x && i == room6->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room6->s_y == i || i == room6->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else
            {
                map[i][j] = '-';
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (corridor1->s_x <= j && j <= corridor1->e_x)
            {
                if (i == corridor1->e_y)
                    map[i][j] = '#';
                if (j == corridor1->s_x && i >= corridor1->s_y && i < corridor1->e_y)
                    map[i][j] = '#';
            }

            if (corridor2->s_x <= j && j <= corridor2->e_x)
            {
                if (j == corridor2->e_x && i >= corridor2->s_y && i <= corridor2->e_y)
                    map[i][j] = '#';

                else if (i == corridor2->e_y)
                    map[i][j] = '#';
            }

            if (corridor3->s_x <= j && j <= corridor3->e_x)
            {                    
                if (j == (corridor3->s_x + corridor3->e_x) / 2)
                {
                    if (corridor3->s_y <= i && i <= corridor3->e_y)
                        map[i][j] = '#';
                }

                if (i == corridor3->s_y && corridor3->s_x <= j && j <= (corridor3->s_x + corridor3->e_x) / 2)
                    map[i][j] = '#';

                if (i == corridor3->e_y && (corridor3->s_x + corridor3->e_x) / 2 <= j && j <= corridor3->e_x)
                    map[i][j] = '#';
            }

            if (corridor4->s_x <= j && j <= corridor4->e_x)
            {
                if (j == corridor4->e_x && i >= corridor4->s_y && i <= corridor4->e_y)
                    map[i][j] = '#';

                else if (i == corridor4->e_y)
                    map[i][j] = '#';
            }

            if (corridor5->s_x <= j && j <= corridor5->e_x)
            {
                if (j == (corridor5->s_x + corridor5->e_x) / 2)
                {
                    if (corridor5->s_y <= i && i <= corridor5->e_y)
                        map[i][j] = '#';
                }

                if (i == corridor5->s_y && corridor5->s_x <= j && j <= (corridor5->s_x + corridor5->e_x) / 2)
                    map[i][j] = '#';

                if (i == corridor5->e_y && (corridor5->s_x + corridor5->e_x) / 2 <= j && j <= corridor5->e_x)
                    map[i][j] = '#';
            }
        }
    }
}


void room_position3(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    room1->type = 2;
    room1->s_x = random_renge(2, 5);
    room1->s_y = random_renge(1, 2);
    room1->e_x = room1->s_x + random_renge(6, 10);
    room1->e_y = room1->s_y + random_renge(5, 8);
    room1->is_in = 0;
    room1->door1_y = random_renge(room1->s_y + 2, room1->e_y - 2);
    room1->door1_x = room1->e_x;

    room2->type = 3;
    room2->s_x = random_renge(15, 20);
    room2->s_y = random_renge(10, 11);
    room2->e_x = room2->s_x + random_renge(6, 10);
    room2->e_y = room2->s_y + random_renge(6, 8);
    room2->is_in = 0;
    room2->door1_x = random_renge(room2->s_x + 2, room2->e_x - 2);
    room2->door1_y = room2->s_y;
    room2->door2_x = random_renge(room2->s_x + 2, room2->e_x - 2);
    room2->door2_y = room2->e_y;

    room3->type = 2;
    room3->s_x = random_renge(33, 38);
    room3->s_y = random_renge(19, 20);
    room3->e_x = room3->s_x + random_renge(6, 10);
    room3->e_y = room3->s_y + random_renge(6, 9);
    room3->is_in = 0;
    room3->door1_x = room3->s_x;
    room3->door1_y = random_renge(room3->s_y + 2, room3->e_y - 2);
    room3->door2_x = room3->e_x;
    room3->door2_y = random_renge(room3->s_y + 3, room3->e_y - 3);

    room4->type = 2;
    room4->s_x = random_renge(50, 60);
    room4->s_y = random_renge(19, 20);
    room4->e_x = room4->s_x + random_renge(6, 10);
    room4->e_y = room4->s_y + random_renge(6, 9);
    room4->is_in = 0;
    room4->door1_x = room4->s_x;
    room4->door1_y = room3->door2_y;
    room4->door2_x = room4->e_x;
    room4->door2_y = random_renge(room4->s_y + 2, room4->e_y - 2);

    room5->type = 3;
    room5->s_x = random_renge(72, 77);
    room5->s_y = random_renge(10, 11);
    room5->e_x = room5->s_x + random_renge(6, 10);
    room5->e_y = room5->s_y + random_renge(6, 8);
    room5->door1_x = random_renge(room5->s_x + 2, room5->e_x - 2);
    room5->door1_y = room5->e_y;
    room5->door2_x = room5->e_x;
    room5->door2_y = random_renge(room5->s_y + 2, room5->e_y - 2);
    room5->is_in = 0;

    room6->type = 1;
    room6->s_x = random_renge(90, 95);
    room6->s_y = 1;
    room6->e_x = room6->s_x + random_renge(6, 10);
    room6->e_y = room6->s_y + 9;
    room6->door1_x = random_renge(room6->s_x + 2, room6->e_x - 2);
    room6->door1_y = room6->e_y;
    room6->is_in = 0;
}

void corridor_position3(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    corridor1->s_x = room1->door1_x + 1;
    corridor1->s_y = room1->door1_y;
    corridor1->e_x = room2->door1_x;
    corridor1->e_y = room2->door1_y - 1;
    corridor1->is_in = 0;

    corridor2->s_x = room2->door2_x;
    corridor2->s_y = room2->door2_y + 1;
    corridor2->e_x = room3->door1_x - 1;
    corridor2->e_y = room3->door1_y;
    corridor2->is_in = 0;

    corridor3->s_x = room3->door2_x + 1;
    corridor3->s_y = room3->door2_y;
    corridor3->e_x = room4->door1_x - 1;
    corridor3->e_y = room4->door1_y;
    corridor3->is_in = 0;

    corridor4->s_x = room4->door2_x + 1;
    corridor4->s_y = room5->door1_y + 1;
    corridor4->e_x = room5->door1_x;
    corridor4->e_y = room4->door2_y;
    corridor4->is_in = 0;

    corridor5->s_x = room5->door2_x + 1;
    corridor5->s_y = room6->door1_y + 1;
    corridor5->e_x = room6->door1_x;
    corridor5->e_y = room5->door2_y;

    corridor5->is_in = 0;
}

void print_map3(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (room1->s_y <= i && i <= room1->e_y && room1->s_x <= j && j <= room1->e_x)
            {
                if (room1->s_x == j || j == room1->e_x)
                {
                    if (i == room1->door1_y && j == room1->door1_x)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room1->s_y == i || i == room1->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room2->s_y <= i && i <= room2->e_y && room2->s_x <= j && j <= room2->e_x)
            {
                if (room2->s_x == j || j == room2->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room2->s_y == i || i == room2->e_y)
                {
                    if (j == room2->door1_x && i == room2->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room2->door2_x && i == room2->door2_y)
                    {
                        int a = random_renge(1, 3);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room3->s_y <= i && i <= room3->e_y && room3->s_x <= j && j <= room3->e_x)
            {
                if (room3->s_x == j || j == room3->e_x)
                {
                    if (j == room3->door1_x && i == room3->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room3->door2_x && i == room3->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room3->s_y == i || i == room3->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room4->s_y <= i && i <= room4->e_y && room4->s_x <= j && j <= room4->e_x)
            {
                if (room4->s_x == j || j == room4->e_x)
                {
                    if (j == room4->door1_x && i == room4->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room4->door2_x && i == room4->door2_y)
                    {
                        int a = random_renge(1, 4);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room4->s_y == i || i == room4->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room5->s_y <= i && i <= room5->e_y && room5->s_x <= j && j <= room5->e_x)
            {
                if (room5->s_x == j || j == room5->e_x)
                {
                    if (j == room5->door2_x && i == room5->door2_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room5->s_y == i || i == room5->e_y)
                {
                    if (j == room5->door1_x && i == room5->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                    {
                        map[i][j] = '=';
                    }
                }
                else
                    map[i][j] = '.';
            }

            else if (room6->s_y <= i && i <= room6->e_y && room6->s_x <= j && j <= room6->e_x)
            {
                if (room6->s_x == j || j == room6->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room6->s_y == i || i == room6->e_y)
                {
                    if (j == room6->door1_x && i == room6->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                    {
                        map[i][j] = '=';
                    }
                }
                else
                    map[i][j] = '.';
            }

            else
            {
                map[i][j] = '-';
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (corridor1->s_x <= j && j <= corridor1->e_x)
            {
                if (i == corridor1->s_y)
                    map[i][j] = '#';
                if (j == corridor1->e_x && i > corridor1->s_y && i <= corridor1->e_y)
                    map[i][j] = '#';
            }

            if (corridor2->s_x <= j && j <= corridor2->e_x)
            {
                if (j == corridor2->s_x && i >= corridor2->s_y && i <= corridor2->e_y)
                    map[i][j] = '#';

                else if (i == corridor2->e_y)
                    map[i][j] = '#';
            }

            if (corridor3->s_x <= j && j <= corridor3->e_x)
            {                    
                if (i == corridor3->s_y)
                    map[i][j] = '#';
            }

            if (corridor4->s_x <= j && j <= corridor4->e_x)
            {
                if (j == corridor4->e_x && i >= corridor4->s_y && i <= corridor4->e_y)
                    map[i][j] = '#';

                else if (i == corridor4->e_y)
                    map[i][j] = '#';
            }

            if (corridor5->s_x <= j && j <= corridor5->e_x)
            {
                if (j == corridor5->e_x && i >= corridor5->s_y && i <= corridor5->e_y)
                    map[i][j] = '#';

                else if (i == corridor5->e_y)
                    map[i][j] = '#';
            }
        }
    }
}


void room_position4(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    room1->type = 2;
    room1->s_x = random_renge(1, 5);
    room1->s_y = 12;
    room1->e_x = room1->s_x + random_renge(6, 10);
    room1->e_y = room1->s_y + random_renge(6, 10);
    room1->is_in = 0;
    room1->door1_y = room1->e_y;
    room1->door1_x = random_renge(room1->s_x + 2, room1->e_x - 2);
    room1->door2_y = room1->s_y;
    room1->door2_x = random_renge(room1->s_x + 2, room1->e_x - 2);

    room2->type = 3;
    room2->s_x = random_renge(20, 25);
    room2->s_y = 20;
    room2->e_x = room2->s_x + random_renge(6, 10);
    room2->e_y = room2->s_y + random_renge(6, 8);
    room2->is_in = 0;
    room2->door1_x = room2->s_x;
    room2->door1_y = random_renge(room2->s_y + 3, room2->e_y - 2);
    room2->door2_x = room2->e_x;
    room2->door2_y = random_renge(room2->s_y + 2, room2->e_y - 4);

    room3->type = 2;
    room3->s_x = random_renge(40, 45);
    room3->s_y = 19;
    room3->e_x = room3->s_x + random_renge(10, 20);
    room3->e_y = room3->s_y + random_renge(6, 8);
    room3->is_in = 0;
    room3->door1_x = room3->s_x;
    room3->door1_y = room2->door2_y;

    room4->type = 2;
    room4->s_x = random_renge(20, 30);
    room4->s_y = random_renge(2, 5);
    room4->e_x = room4->s_x + random_renge(10, 15);
    room4->e_y = room4->s_y + random_renge(10, 12);
    room4->is_in = 0;
    room4->door1_x = room4->s_x;
    room4->door1_y = 12 - random_renge(2, 6);
    room4->door2_x = room4->e_x;
    room4->door2_y = random_renge(room4->s_y + 4, room4->e_y - 4);

    room5->type = 3;
    room5->s_x = random_renge(47, 50);
    room5->s_y = random_renge(4, 5);
    room5->e_x = room5->s_x + random_renge(15, 20);
    room5->e_y = room5->s_y + random_renge(10, 12);
    room5->door1_x = room5->s_x;
    room5->door1_y = room4->door2_y;
    room5->door2_x = room5->e_x;
    room5->door2_y = random_renge(room5->s_y + 2, room5->e_y - 8);
    room5->is_in = 0;

    room6->type = 1;
    room6->s_x = random_renge(80, 90);
    room6->s_y = 10;
    room6->e_x = room6->s_x + random_renge(10, 15);
    room6->e_y = room6->s_y + random_renge(6, 15);
    room6->door1_x = random_renge(room6->s_x + 2, room6->e_x - 2);
    room6->door1_y = room6->s_y;
    room6->is_in = 0;
}

void corridor_position4(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    corridor1->s_x = room1->door1_x;
    corridor1->s_y = room1->door1_y + 1;
    corridor1->e_x = room2->door1_x - 1;
    corridor1->e_y = room2->door1_y;
    corridor1->is_in = 0;

    corridor2->s_x = room2->door2_x + 1;
    corridor2->s_y = room2->door2_y;
    corridor2->e_x = room3->door1_x - 1;
    corridor2->e_y = room3->door1_y;
    corridor2->is_in = 0;

    corridor3->s_x = room1->door2_x;
    corridor3->s_y = room4->door1_y;
    corridor3->e_x = room4->door1_x - 1;
    corridor3->e_y = room1->door2_y - 1;
    corridor3->is_in = 0;

    corridor4->s_x = room4->door2_x + 1;
    corridor4->s_y = room4->door2_y;
    corridor4->e_x = room5->door1_x - 1;
    corridor4->e_y = room5->door1_y;
    corridor4->is_in = 0;


    corridor5->s_y = room5->door2_y;
    corridor5->e_y = room6->door1_y - 1;
    corridor5->s_x = room5->door2_x + 1;
    corridor5->e_x = room6->door1_x;
    corridor5->is_in = 0;
}

void print_map4(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (room1->s_y <= i && i <= room1->e_y && room1->s_x <= j && j <= room1->e_x)
            {
                if (room1->s_x == j || j == room1->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room1->s_y == i || i == room1->e_y)
                {
                    if (j == room1->door1_x && i == room1->door1_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                            
                    }
                    else if (j == room1->door2_x && i == room1->door2_y)
                    {
                        int a = random_renge(1, 3);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '_';
                        }
                            
                    }
                    else 
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room2->s_y <= i && i <= room2->e_y && room2->s_x <= j && j <= room2->e_x)
            {
                if (room2->s_x == j || j == room2->e_x)
                {
                    if (j == room2->door1_x && i == room2->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room2->door2_x && i == room2->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '@';
                            map[room1->s_y + 1][room1->s_x + 1] = '&';
                        }
                    }
                    else 
                        map[i][j] = '|';
                }
                else if (room2->s_y == i || i == room2->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room3->s_y <= i && i <= room3->e_y && room3->s_x <= j && j <= room3->e_x)
            {
                if (room3->s_x == j || j == room3->e_x)
                {
                    if (j == room3->door1_x && i == room3->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room3->s_y == i || i == room3->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room4->s_y <= i && i <= room4->e_y && room4->s_x <= j && j <= room4->e_x)
            {
                if (room4->s_x == j || j == room4->e_x)
                {
                    if (j == room4->door1_x && i == room4->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room4->door2_x && i == room4->door2_y)
                    {
                        int a = random_renge(1, 2);
                        if (a == 1)
                            map[i][j] = '+';
                        else
                        {
                            map[i][j] = '/';
                        }
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room4->s_y == i || i == room4->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room5->s_y <= i && i <= room5->e_y && room5->s_x <= j && j <= room5->e_x)
            {
                if (room5->s_x == j || j == room5->e_x)
                {
                    if (j == room5->door1_x && i == room5->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else if (j == room5->door2_x && i == room5->door2_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '|';
                }
                else if (room5->s_y == i || i == room5->e_y)
                {
                    map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else if (room6->s_y <= i && i <= room6->e_y && room6->s_x <= j && j <= room6->e_x)
            {
                if (room6->s_x == j || j == room6->e_x)
                {
                    map[i][j] = '|';
                }
                else if (room6->s_y == i || i == room6->e_y)
                {
                    if (j == room6->door1_x && i == room6->door1_y)
                    {
                        map[i][j] = '+';
                    }
                    else
                        map[i][j] = '=';
                }
                else
                    map[i][j] = '.';
            }

            else
            {
                map[i][j] = '-';
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (corridor1->s_x <= j && j <= corridor1->e_x)
            {
                if (i == corridor1->e_y)
                    map[i][j] = '#';
                if (j == corridor1->s_x && i >= corridor1->s_y && i < corridor1->e_y)
                    map[i][j] = '#';
            }

            if (corridor2->s_x <= j && j <= corridor2->e_x)
            {
                if (i == corridor2->s_y)
                    map[i][j] = '#';
            }

            if (corridor3->s_x <= j && j <= corridor3->e_x)                   
            {
                if (j == corridor3->s_x && i >= corridor3->s_y && i <= corridor3->e_y)
                    map[i][j] = '#';

                else if (i == corridor3->s_y)
                    map[i][j] = '#';
            }

            if (corridor4->s_x <= j && j <= corridor4->e_x)
            {
                if (i == corridor4->s_y)
                    map[i][j] = '#';
            }

            if (corridor5->s_x <= j && j <= corridor5->e_x)
            {
                if (j == corridor5->e_x && i >= corridor5->s_y && i <= corridor5->e_y)
                    map[i][j] = '#';

                else if (i == corridor5->s_y)
                    map[i][j] = '#';
            }
        }
    }
}


void print_map(int i, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    int x, y;

    { // (room 1)
        x = random_renge(room1->s_x + 2, room1->e_x - 2);
        y = random_renge(room1->s_y + 2, room1->e_y - 2);
        map[y][x] = 'O';

        x = random_renge(room1->s_x + 2, room1->e_x - 2);
        y = random_renge(room1->s_y + 2, room1->e_y - 2);
        map[y][x] = 'T';

        x = random_renge(room1->s_x + 1, room1->e_x - 1);
        y = random_renge(room1->s_y + 1, room1->e_y - 1);
        map[y][x] = food();

        x = random_renge(room1->s_x + 1, room1->e_x - 1);
        y = random_renge(room1->s_y + 1, room1->e_y - 1);
        map[y][x] = weapon();

        do
        {
            x = random_renge(room1->s_x + 2, room1->e_x - 2);
            y = random_renge(room1->s_y + 2, room1->e_y - 2);
        } while (map[y][x] != '.');
        map[y][x] = monster();
    }

    { // (room 2)
        x = random_renge(room2->s_x + 2, room2->e_x - 2);
        y = random_renge(room2->s_y + 2, room2->e_y - 2);
        map[y][x] = 'O';

        x = random_renge(room2->s_x + 2, room2->e_x - 2);
        y = random_renge(room2->s_y + 2, room2->e_y - 2);
        map[y][x] = 'T';

        x = random_renge(room2->s_x + 1, room2->e_x - 1);
        y = random_renge(room2->s_y + 1, room2->e_y - 1);
        map[y][x] = food();

        for (int i = 0; i < 3; i++)
        {
            x = random_renge(room2->s_x + 1, room2->e_x - 1);
            y = random_renge(room2->s_y + 1, room2->e_y - 1);
            map[y][x] = spell();
        }

        do
        {
            x = random_renge(room2->s_x + 2, room2->e_x - 2);
            y = random_renge(room2->s_y + 2, room2->e_y - 2);
        } while (map[y][x] != '.');
        int t = random_renge(1, 10);
        if (t == 1) map[y][x] = 'U';
        else if (t > 2) map[y][x] = monster();
    }

    { // (room 3)
        for (int i = 0; i < 4; i++)
        {
            x = random_renge(room3->s_x + 1, room3->e_x - 1);
            y = random_renge(room3->s_y + 1, room3->e_y - 1);
            map[y][x] = food();
        }
    
        for (int i = 0; i < 3; i++)
        {
            x = random_renge(room3->s_x + 1, room3->e_x - 1);
            y = random_renge(room3->s_y + 1, room3->e_y - 1);
            map[y][x] = weapon();
        }

        do
        {
            x = random_renge(room3->s_x + 2, room3->e_x - 2);
            y = random_renge(room3->s_y + 2, room3->e_y - 2);
        } while (map[y][x] != '.');
        int t = random_renge(1, 10);
        if (t == 1) map[y][x] = 'U';
        else if (t > 6) map[y][x] = monster();
    }

    { // (room 4)
        x = random_renge(room4->s_x + 2, room4->e_x - 2);
        y = random_renge(room4->s_y + 2, room4->e_y - 2);
        map[y][x] = 'O';

        x = random_renge(room4->s_x + 2, room4->e_x - 2);
        y = random_renge(room4->s_y + 2, room4->e_y - 2);
        map[y][x] = 'T';

        x = random_renge(room4->s_x + 1, room4->e_x - 1);
        y = random_renge(room4->s_y + 1, room4->e_y - 1);
        map[y][x] = food();

        x = random_renge(room4->s_x + 1, room4->e_x - 1);
        y = random_renge(room4->s_y + 1, room4->e_y - 1);
        map[y][x] = weapon();

        x = random_renge(room4->s_x + 1, room4->e_x - 1);
        y = random_renge(room4->s_y + 1, room4->e_y - 1);
        map[y][x] = spell();

        do
        {
            x = random_renge(room4->s_x + 2, room4->e_x - 2);
            y = random_renge(room4->s_y + 2, room4->e_y - 2);
        } while (map[y][x] != '.');
        int t = random_renge(1, 10);
        if (t == 1) map[y][x] = 'U';
        else map[y][x] = monster();
    }

    { // (room 5)
        x = random_renge(room5->s_x + 2, room5->e_x - 2);
        y = random_renge(room5->s_y + 2, room5->e_y - 2);
        map[y][x] = 'O';

        x = random_renge(room5->s_x + 1, room5->e_x - 1);
        y = random_renge(room5->s_y + 1, room5->e_y - 1);
        map[y][x] = food();

        for (int i = 0; i < 2; i++)
        {
            x = random_renge(room5->s_x + 1, room5->e_x - 1);
            y = random_renge(room5->s_y + 1, room5->e_y - 1);
            map[y][x] = 'G';
        }

        for (int i = 0; i < 5; i++)
        {
            x = random_renge(room5->s_x + 1, room5->e_x - 1);
            y = random_renge(room5->s_y + 1, room5->e_y - 1);
            map[y][x] = spell();
        }

        do
        {
            x = random_renge(room5->s_x + 2, room5->e_x - 2);
            y = random_renge(room5->s_y + 2, room5->e_y - 2);
        } while (map[y][x] != '.');
        int t = random_renge(1, 10);
        if (t == 1) map[y][x] = 'U';
        else if (t > 2) map[y][x] = monster();
    }

    { // (room 6)
        if (i != 4) room6->type = 2;
        
        for (int i = 0; i < 2; i++)
        {
            x = random_renge(room6->s_x + 2, room6->e_x - 2);
            y = random_renge(room6->s_y + 2, room6->e_y - 2);
            map[y][x] = 'O';
        }

        for (int i = 0; i < 4; i++)
        {
            x = random_renge(room6->s_x + 2, room6->e_x - 2);
            y = random_renge(room6->s_y + 2, room6->e_y - 2);
            map[y][x] = 'T';
        }

        int a = 5;
        if (i == 4) a = 10;
        for (int i = 0; i < a; i++)
        {
            x = random_renge(room6->s_x + 1, room6->e_x - 1);
            y = random_renge(room6->s_y + 1, room6->e_y - 1);
            map[y][x] = 'G';
        }

        x = random_renge(room6->s_x + 1, room6->e_x - 1);
        y = random_renge(room6->s_y + 1, room6->e_y - 1);
        map[y][x] = food();

        a = 2;
        if (i == 4) a = 5;
        for (int i = 0; i < a; i++)
        {
            x = random_renge(room6->s_x + 1, room6->e_x - 1);
            y = random_renge(room6->s_y + 1, room6->e_y - 1);
            map[y][x] = 'B';        
        }

        if (i != 4)
        {
            do
            {
                x = random_renge(room6->s_x + 2, room6->e_x - 2);
                y = random_renge(room6->s_y + 2, room6->e_y - 2);
            } while (map[y][x] != '.');
            int t = random_renge(1, 4);
            if (t > 1) map[y][x] = 'U';
            else map[y][x] = monster();
        }

    }

    int a = random_renge(1, 6);
    switch (a)
    {
        case 1:
        {
            x = random_renge(room1->s_x + 1, room1->e_x - 1);
            y = random_renge(room1->s_y + 1, room1->e_y - 1);
            break;
        }
        case 2:
        {
            x = random_renge(room2->s_x + 1, room2->e_x - 1);
            y = random_renge(room2->s_y + 1, room2->e_y - 1);
            break;
        }
        case 3:
        {
            x = random_renge(room3->s_x + 1, room3->e_x - 1);
            y = random_renge(room3->s_y + 1, room3->e_y - 1);
            break;
        }
        case 4:
        {
            x = random_renge(room4->s_x + 1, room4->e_x - 1);
            y = random_renge(room4->s_y + 1, room4->e_y - 1);
            break;
        }
        case 5:
        {
            x = random_renge(room5->s_x + 1, room5->e_x - 1);
            y = random_renge(room5->s_y + 1, room5->e_y - 1);
            break;
        }
        case 6:
        {
            x = random_renge(room6->s_x + 1, room6->e_x - 1);
            y = random_renge(room6->s_y + 1, room6->e_y - 1);
            break;
        }   
    
    }
    map[y][x] = '*';

    int stair_x = random_renge(room6->s_x + 1, room6->e_x - 1);
    int stair_y = random_renge(room6->s_y + 1, room6->e_y - 1);
    map[stair_y][stair_x] = '>';

    int s_x = random_renge(room1->s_x + 1, room1->e_x - 1);
    int s_y = random_renge(room1->s_y + 1, room1->e_y - 1);
    if (i == 1) map[s_y][s_x] = 'X';
    else map[s_y][s_x] = '<';
}

int random_renge(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

char weapon()
{
    int a = random_renge(1, 4);
    char w;
    switch (a)
    {
    case 1:
        w = 'S';
        break;
    case 2:
        w = 'D';
        break;
    case 3:
        w = 'W';
        break;
    case 4:
        w = 'A';
        break;
    }
    return w;
}

char spell()
{
    int a = random_renge(1, 3);
    char s;
    switch (a)
    {
    case 1:
        s = 'H';
        break;
    case 2:
        s = 'Z';
        break;
    case 3:
        s = 'C';
        break;
    }
    return s;
}

char monster()
{
    int a = random_renge(1, 4);
    char m;
    switch (a)
    {
    case 1:
        m = 'V';
        break;
    case 2:
        m = 'L';
        break;
    case 3:
        m = 'N';
        break;
    case 4:
        m = 'K';
        break;
    }
    return m;
}

char food()
{
    int a = random_renge(1, 3);
    char f;
    switch (a)
    {
    case 1:
        f = 'F';
        break;
    case 2:
        f = 'Q';
        break;
    case 3:
        f = 'E';
        break;
    }
    return f;
}

