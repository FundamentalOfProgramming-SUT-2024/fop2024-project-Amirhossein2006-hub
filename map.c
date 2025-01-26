#include <stdio.h>

typedef struct
{
    // 1 -> Treasure Room, 3 -> Enchant Room, 2 -> Regular Room
    int type;
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    int is_in;
} Rooms;

typedef struct
{
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    int is_in;
} Corridors;

void room_position(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);

int main()
{
    Rooms room1, room2, room3, room4, room5, room6;
    Corridors corridor1, corridor2, corridor3, corridor4, corridor5;

    room_position(&room1, &room2, &room3, &room4, &room5, &room6);
    corridor_position(&corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
    for (int i = 0; i < 4; i++)
    {
        FILE *corridors;
        FILE *rooms;
        switch (i + 1)
        {
            case 1:
            {
                rooms = fopen("rooms1.dat", "rb+");
                corridors = fopen("corridors1.dat", "rb+");
                break;
            }
            case 2:
            {
                rooms = fopen("rooms2.dat", "rb+");
                corridors = fopen("corridors2.dat", "rb+");
                break;
            }
            case 3:
            {
                rooms = fopen("rooms3.dat", "rb+");
                corridors = fopen("corridors3.dat", "rb+");
                break;
            }
            case 4:
            {
                rooms = fopen("rooms4.dat", "rb+");
                corridors = fopen("corridors4.dat", "rb+");
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
    }

    return 0;
}

void room_position(Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    room1->type = 2;
    room1->s_x = 11;
    room1->s_y = 1;
    room1->e_x = 20;
    room1->e_y = 6;
    room1->is_in = 0;

    room2->type = 3;
    room2->s_x = 17;
    room2->s_y = 13;
    room2->e_x = 26;
    room2->e_y = 18;
    room2->is_in = 0;

    room3->type = 2;
    room3->s_x = 35;
    room3->s_y = 23;
    room3->e_x = 44;
    room3->e_y = 28;
    room3->is_in = 0;

    room4->type = 3;
    room4->s_x = 67;
    room4->s_y = 19;
    room4->e_x = 76;
    room4->e_y = 24;
    room4->is_in = 0;

    room5->type = 2;
    room5->s_x = 57;
    room5->s_y = 7;
    room5->e_x = 66;
    room5->e_y = 12;
    room5->is_in = 0;

    room6->type = 1;
    room6->s_x = 94;
    room6->s_y = 9;
    room6->e_x = 103;
    room6->e_y = 17;
    room6->is_in = 0;


}

void corridor_position(Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    corridor1->s_x = 21;
    corridor1->s_y = 3;
    corridor1->e_x = 61;
    corridor1->e_y = 6;
    corridor1->is_in = 0;

    corridor2->s_x = 16;
    corridor2->s_y = 7;
    corridor2->e_x = 21;
    corridor2->e_y = 12;
    corridor2->is_in = 0;

    corridor3->s_x = 24;
    corridor3->s_y = 19;
    corridor3->e_x = 39;
    corridor3->e_y = 22;
    corridor3->is_in = 0;

    corridor4->s_x = 63;
    corridor4->s_y = 13;
    corridor4->e_x = 70;
    corridor4->e_y = 18;
    corridor4->is_in = 0;

    corridor5->s_x = 67;
    corridor5->s_y = 10;
    corridor5->e_x = 93;
    corridor5->e_y = 11;
    corridor5->is_in = 0;
}