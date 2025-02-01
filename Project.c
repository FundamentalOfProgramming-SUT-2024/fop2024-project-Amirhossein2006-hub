#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

typedef struct
{
    int id;
    char username[100];
    char password[100];
    char email[100];
    int score;
    int gold;
    int finished_games;
    int experience;
    int save_game;
    int level;
    int health;
    char favorite_animal[100];
} Player;

typedef struct
{
    int difficulty;
    int color;
} Game;

typedef struct
{
    int x;
    int y;
} Explorer_Position;

typedef struct
{
    char food[20];
    int count;
} Food_Count;

typedef struct
{
    Food_Count foods[10];
    int count;
} Food;

typedef struct
{
    char weapon[20];
    int count;
    int damage;
    int num_in_each;
    int board;
} Weapon_Count;

typedef struct
{
    Weapon_Count weapons[10];
    int count;
} Weapon;

typedef struct
{
    int health;
    int score;
    int experience;
    int gold;
    int level;
    int power;
    int speed;
    Weapon_Count current_weapon;
} Explorer;

typedef struct
{
    char spell[20];
    int id;
    int count;
    int time;
} Spell_Count;

typedef struct
{
    Spell_Count spells[10];
    int count;
} Spell;

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

typedef struct
{
    char name[30];
    int x;
    int y;
    int health;
    int movement;
    int room;
    int power;
} Monster;

char game_map[30][120];
clock_t start;
clock_t start_code;
int code, num_of_mistakes;
int ancient_key_value;
int monster_count;
int hunger = 20;

int menu();
void sign_in(Player *player);
int ivalue(char username[], char password[], char email[]);
int username_check(char username[]);
int password_check(char password[]);
int email_check(char email[]);
void login(Player *player);
int before_game_menu();
void settings(Game *game);
void score_table(Player *player);
void profile(Player *player);
int random_renge(int a, int b);
void load_map(int i, Explorer_Position *ep, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void whitch_room(Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
void print_room(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6);
void print_corridor(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5);
void print_map(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Rooms room);
void print_map2(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor);
void move_ivalue(int move, Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5);
void move_ivalue2(int move, Explorer_Position *ep);
void new_game(Explorer_Position *ep, Explorer *explorer, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void trap(Explorer_Position *ep, Explorer *explorer);
void stair(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Monster *monster);
void stair_save(Explorer *explorer, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
int stair_check(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Monster *monster);
int move_ivalue_help(Explorer_Position *ep);
int move_ivalue_help2(int y, int x);
void foods(Explorer_Position *ep, Explorer *explorer, Food *food);
void find_food(char name[], Food *food);
int food_show(Food *food);
void gold(Explorer_Position *ep, Explorer *explorer);
void black_gold(Explorer_Position *ep, Explorer *explorer);
void weapons(Explorer_Position *ep, Explorer *explorer, Weapon *weapon);
void find_weapon(char name[], Weapon *weapon);
int weapon_show(Weapon *weapon, Explorer *explorer);
void spells(Explorer_Position *ep, Explorer *explorer, Spell *spell);
void find_spell(char name[], Spell *spell);
int spell_show(Spell *spell, Explorer *explorer);
int end_game(Explorer_Position *ep, Explorer *explorer, Player *player);
void room_position(Explorer *explorer, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void corridor_position(Explorer *explorer, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
int exit_menu();
void save(Player *player, Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
void room_them_x(int i, int j, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6);
void room_them_y(int i, int j, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6);
void password(Explorer_Position *ep, Explorer *explorer, int *code);
int unlock_door();
void ancient_key(Explorer_Position *ep, Explorer *explorer);
void load_game(int *ex, Explorer_Position *ep, Explorer *explorer, Player *player, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void random_password(int length, char password[]);
int room(int x, int y, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void mace(int x, int y, Monster *monster, Explorer *explorer);
void sword(int x, int y, Monster *monster, Explorer *explorer);
void dagger(int x, int y, Monster *monster, Explorer *explorer);
void magic_wand(int x, int y, Monster *monster, Explorer *explorer);
void normal_arrow(int x, int y, Monster *monster, Explorer *explorer);
void m_room(Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6);
void monster_move(int room, Monster *monster, Explorer_Position *ep);
void monster_hit(Monster *monster, Explorer_Position *ep, Explorer *explorer);

int main()
{
    initscr();
    setlocale(LC_ALL, "en_US.UTF-8");
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();

    Player player;
    Game game;
    Explorer_Position ep;
    Explorer explorer;
    Food food;
    Weapon weapon;
    Spell spell;
    Rooms room1, room2, room3, room4, room5, room6;
    Corridors corridor1, corridor2, corridor3, corridor4, corridor5;
    Monster monster[20];

    game.difficulty = 0;
    game.color = 0;
    food.count = 0;

    weapon.count = 5;
    strcpy(weapon.weapons[0].weapon, "Mace");
    weapon.weapons[0].count = 1;
    weapon.weapons[0].damage = 5;
    weapon.weapons[0].num_in_each = 0;
    weapon.weapons[0].board = 0;
    strcpy(weapon.weapons[1].weapon, "Sword");
    weapon.weapons[1].count = 1;
    weapon.weapons[1].damage = 10;
    weapon.weapons[1].num_in_each = 0;
    weapon.weapons[1].board = 0;
    strcpy(weapon.weapons[2].weapon, "Dagger");
    weapon.weapons[2].count = 5;
    weapon.weapons[2].damage = 12;
    weapon.weapons[2].num_in_each = 10;
    weapon.weapons[2].board = 5;
    strcpy(weapon.weapons[3].weapon, "Magic Wand");
    weapon.weapons[3].count = 5;
    weapon.weapons[3].damage = 15;
    weapon.weapons[3].num_in_each = 8;
    weapon.weapons[3].board = 10;
    strcpy(weapon.weapons[4].weapon, "Normal Arrow");
    weapon.weapons[4].count = 5;
    weapon.weapons[4].damage = 5;
    weapon.weapons[4].num_in_each = 20;
    weapon.weapons[4].board = 5;

    spell.count = 0;
    code = 1000;
    ancient_key_value = 0;
    int ex = 0;
    srand(time(NULL));
    explorer.current_weapon = weapon.weapons[0];
    explorer.power = 1;
    explorer.speed = 1;

    switch (menu())
    {
    case 0:
        sign_in(&player);
        break;
    case 1:
        login(&player);
        break;
    }

    int choice;
    while (1)
    {
        switch (choice = before_game_menu())
        {
        case 0:
        {
            // while (system("./Map.out") != 0)
            //     clear();
            new_game(&ep, &explorer, monster, &room1, &room2, &room3, &room4, &room5, &room6);
            break;
        }
        case 1:
            if(player.save_game) load_game(&ex, &ep, &explorer, &player, monster, &room1, &room2, &room3, &room4, &room5, &room6);
            else
            {
                clear();
                mvprintw(15, 55, "No Saved Games!");
                getch();
                continue;
            }
            break;
        case 2:
            settings(&game);
            break;
        case 3:
            score_table(&player);
            break;
        case 4:
            profile(&player);
            break;
        }

        if (choice < 2) break;
    }

    int step_counter = 0;
    room_position(&explorer, &room1, &room2, &room3, &room4, &room5, &room6);
    corridor_position(&explorer, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
    load_map(explorer.level, &ep, monster, &room1, &room2, &room3, &room4, &room5, &room6);
    while (1)
    {
        whitch_room(&ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
        print_room(&ep, &explorer, game, room1, room2, room3, room4, room5, room6);
        print_corridor(&ep, &explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
        trap(&ep, &explorer);
        foods(&ep, &explorer, &food);
        gold(&ep, &explorer);
        black_gold(&ep, &explorer);
        weapons(&ep, &explorer, &weapon);
        spells(&ep, &explorer, &spell);
        password(&ep, &explorer, &code);
        ancient_key(&ep, &explorer);
        monster_hit(monster, &ep, &explorer);
        
        if (time(NULL) - start_code < 30) mvprintw(0, 75, "Wow! Your code is %d", code);
        
        if (explorer.health <= 0)
        {
            clear();
            mvprintw(15, 45, "Opps, You lose! Your health ended!");
            mvprintw(16, 45, "I hope to see you again :)");
            mvprintw(17, 45, "Press any key to exit...");
            save(&player, &explorer, &ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
            getch();
            break;
        }

        int move;

        if (game_map[ep.y][ep.x] == '>' || game_map[ep.y][ep.x] == '<') move = stair_check(&explorer, &ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5, monster);
        else move = tolower(getch());

        if (move == 'i')
        {
            char current_weapon[40];
            strcpy(current_weapon, explorer.current_weapon.weapon);
            if (weapon_show(&weapon, &explorer))
            {
                clear();
                if (explorer.current_weapon.count == 0)
                {
                    mvprintw(0, 25, "The number of %s Weapon is 0! You can't pick it any more!", explorer.current_weapon.weapon);
                    explorer.current_weapon = weapon.weapons[0];
                }
                else if (strcmp(current_weapon, explorer.current_weapon.weapon) != 0) mvprintw(0, 25, "Your selected weapon changed to %s!", explorer.current_weapon.weapon);
                else mvprintw(0, 25, "Your selected weapon doesn't change!");
                print_room(&ep, &explorer, game, room1, room2, room3, room4, room5, room6);
                print_corridor(&ep, &explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                getch();
            }
            step_counter--;
        }
        else if (move == 'o')
        {
            int choice = spell_show(&spell, &explorer);
            if (choice >= 0)
            {
                clear();
                print_room(&ep, &explorer, game, room1, room2, room3, room4, room5, room6);
                print_corridor(&ep, &explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                mvprintw(0, 25, "Wow! Your drinked %s Spell!", spell.spells[choice].spell);

                if (strcmp(spell.spells[choice].spell, "Health") == 0)
                    explorer.health = 100;
                else if (strcmp(spell.spells[choice].spell, "Speed") == 0)
                    explorer.speed = 2;
                else if (strcmp(spell.spells[choice].spell, "Damage") == 0)
                    explorer.power = 2;
                
                if (strcmp(spell.spells[choice].spell, "Health") != 0) spell.spells[choice].time = 20;
                getch();
            }
            else if (choice < -1)
            {
                choice += 4;
                mvprintw(0, 25, "The number of %s Spell is 0! You can't drink it any more!", spell.spells[choice].spell);
                getch();
            }
            step_counter--;
        }
        else if (move == 'p')
        {
            if (food_show(&food))
            {
                clear();
                print_room(&ep, &explorer, game, room1, room2, room3, room4, room5, room6);
                print_corridor(&ep, &explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                int a = random_renge(1, 4);
                if (a != 4)
                {
                    mvprintw(0, 25, "Wow! You eat a Food!");
                    if (hunger < 17) hunger += 3;
                    else hunger = 20;
                }
                else
                {
                    mvprintw(0, 25, "Opps! You eat a Rancid Food!");
                    explorer.health -= 2;
                }
                getch();
            }
            step_counter--;
        }
        else if (move == 'm')
        {
            room1.is_in = 1;
            room2.is_in = 1;
            room3.is_in = 1;
            room4.is_in = 1;
            room5.is_in = 1;
            room6.is_in = 1;
            corridor1.is_in = 1;
            corridor2.is_in = 1;
            corridor3.is_in = 1;
            corridor4.is_in = 1;
            corridor5.is_in = 1;
        }
        else if (move == 'f' && move_ivalue_help(&ep))
        {
            move = tolower(getch());
            move_ivalue2(move, &ep);
        }
        else if (move == 27)
        {
            if (exit_menu() == 1)
            {
                clear();
                mvprintw(15, 45, "Have a nice day!");
                mvprintw(16, 45, "I hope to see you again :)");
                mvprintw(17, 45, "Press any key to exit...");
                if(player.id != 0) save(&player, &explorer, &ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
                getch();
                break;
            }
            step_counter--;
        }
        else if (move == 32)
        {
            int x = ep.x;
            int y = ep.y;
            if (strcmp(explorer.current_weapon.weapon, "Mace") == 0)
            {
                mvprintw(0, 25, "Wow! You hit 8 near blocks with Mace!");
                mace(x, y, monster, &explorer);
                getch();
            }
            else if (strcmp(explorer.current_weapon.weapon, "Sword") == 0)
            {
                mvprintw(0, 25, "Wow! You hit 8 near blocks with Sword!");
                sword(x, y, monster, &explorer);
                getch();
            }
            else if (strcmp(explorer.current_weapon.weapon, "Dagger") == 0)
            {
                if (weapon.weapons[2].count == 0)
                    mvprintw(0, 25, "You don't have any more Daggers!");
                else
                {
                    mvprintw(0, 25, "Please select the way!");
                    dagger(x, y, monster, &explorer);
                    weapon.weapons[2].count--;
                }
                getch();
            }
            else if (strcmp(explorer.current_weapon.weapon, "Normal Arrow") == 0)
            {
                if (weapon.weapons[4].count == 0)
                    mvprintw(0, 25, "You don't have any more Normal Arrows!");
                else
                {
                    mvprintw(0, 25, "Please select the way!");
                    normal_arrow(x, y, monster, &explorer);
                    weapon.weapons[4].count--;
                }
                getch();
            }
            else if (strcmp(explorer.current_weapon.weapon, "Magic Wand") == 0)
            {
                if (weapon.weapons[3].count == 0)
                    mvprintw(0, 25, "You don't have any more Magic Wands!");
                else
                {
                    mvprintw(0, 25, "Please select the way!");
                    magic_wand(x, y, monster, &explorer);
                    weapon.weapons[3].count--;
                }
                getch();
            }
        }
        else 
        {
            if (explorer.speed == 1) move_ivalue(move, &ep, &explorer, game, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
            else 
            {
                move_ivalue(move, &ep, &explorer, game, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
                int y = ep.y;
                int x = ep.x;
                trap(&ep, &explorer);
                foods(&ep, &explorer, &food);
                gold(&ep, &explorer);
                black_gold(&ep, &explorer);
                weapons(&ep, &explorer, &weapon);
                spells(&ep, &explorer, &spell);
                ancient_key(&ep, &explorer);
                if (game_map[y + 1][x] != '@' && game_map[y - 1][x] != '@'  && game_map[y][x + 1] != '@' && game_map[y][x - 1] != '@') 
                    move_ivalue(move, &ep, &explorer, game, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
            }
        }
        clear();

        explorer.experience = ((time(NULL) - start) / 60) + ex; 
        step_counter++;
        if (step_counter % 20 == 0)
            hunger--;
        if (hunger != 20 && hunger != 0 && hunger % 5 == 0)
        {
            explorer.health -= 5;
            hunger--;
        }
        if (hunger == 0)
            explorer.health -= 20;

        for (int i = 0; i < spell.count; i++)
        {
            if (spell.spells[i].time != -1)
            {
                spell.spells[i].time--;
                if (spell.spells[i].time == 0 && strcmp(spell.spells[i].spell, "Speed") == 0)
                {
                    mvprintw(0, 25, "Opps! The effect of Speed Spell have ended!");
                    explorer.speed = 1;
                    spell.spells[i].time = -1;
                }
                if (spell.spells[i].time == 0 && strcmp(spell.spells[i].spell, "Speed") == 0)
                {
                    mvprintw(0, 25, "Opps! The effect of Damage Spell have ended!");
                    explorer.power = 1;
                    spell.spells[i].time = -1;
                }
            }
        }

        int r = room(ep.x, ep.y, &room1, &room2, &room3, &room4, &room5, &room6);
        monster_move(r, monster, &ep);

        if (end_game(&ep, &explorer, &player))
        {
            save(&player, &explorer, &ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
            break;
        }
    }

    refresh();
    endwin();
    return 0;
}

int menu()
{
    char menu_options[2][15] = {"Sign In", "Login"};
    int choice = 0;

    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(13 + i, 53, "%s", menu_options[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        int c = getch();

        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 1;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 1)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            break;
        }
    }

    return choice;
}

void sign_in(Player *player)
{
    clear();
    char username[100];
    char password[100];
    char email[100];
    char f_a[100];

    char menu_options[2][15] = {"Yes", "No"};
    int choice = 0;

    while (1)
    {
        mvprintw(14, 50, "Do you want a random password?");
        for (int i = 0; i < 2; i++)
        {
            mvprintw(16 + i, 55, "%s", menu_options[i]);
        }
        mvprintw(16 + choice, 52, "->");
        int c = getch();
        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 1;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 1)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            clear();
            break;
        }
        clear();
    }

    echo();
    curs_set(TRUE);

    mvprintw(11, 50, "Username: ");
    mvprintw(12, 50, "Password: ");
    mvprintw(13, 50, "Email: ");
    mvprintw(14, 50, "Favorite Animal (Password recovery): ");
    mvgetstr(11, 60, username);

    if (choice == 0)
    {
        int length = random_renge(8, 15);
        random_password(length, player->password);
        mvprintw(12, 60, "%s", player->password);
        strcpy(password, player->password);
    }

    else mvgetstr(12, 60, password);
    mvgetstr(13, 57, email);
    mvgetstr(14, 87, f_a);
    
    noecho();
    curs_set(FALSE);

    if (ivalue(username, password, email) == 0) sign_in(player);
    else
    {
        FILE *players_info = fopen("Players_Info.dat", "ab");
        FILE *id = fopen("id.txt", "r");
        int last_id;
        fscanf(id, "%d", &last_id);
        last_id++;
        fclose(id);
        id = fopen("id.txt", "w");
        fprintf(id, "%d", last_id);
        fclose(id);
        strcpy(player->username, username);
        strcpy(player->password, password);
        strcpy(player->email, email);
        strcpy(player->favorite_animal, f_a);
        player->score = 0;
        player->gold = 0;
        player->experience = 0;
        player->finished_games = 0;
        player->id = last_id;
        player->save_game = 0;
        player->health = 100;
        player->level = 1;

        fwrite(player, sizeof(Player), 1, players_info);
        fclose(players_info);
    }
    clear();
}

int ivalue(char username[], char password[], char email[])
{
    if (username_check(username) && password_check(password) && email_check(email)) return 1;

    return 0;
}

int username_check(char username[])
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    FILE *players_info = fopen("Players_Info.dat", "rb");

    while (!feof(players_info))
    {
        Player player;
        fread(&player, sizeof(Player), 1, players_info);
        if (strcmp(player.username, username) == 0)
        {
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(15, 45, "Username is already used");
            attroff(COLOR_PAIR(1));
            mvprintw(16, 46, "Press any key to reset");
            getch();
            fclose(players_info);
            return 0;
        }
    }
    fclose(players_info);
    return 1;
}

int password_check(char password[])
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    if (strlen(password) < 7)
    {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(15, 40, "Password length must be at least 7");
        attroff(COLOR_PAIR(1));
        mvprintw(16, 47, "Press any key to reset");
        getch();
        return 0;
    }

    int is_digit = 1, is_upper = 1, is_lower = 1;
    for (int i = 0; i < strlen(password); i++)
    {
        if (isdigit(password[i])) is_digit = 0;
        if (isupper(password[i])) is_upper = 0;
        if (islower(password[i])) is_lower = 0;
    }
    
    if (is_digit || is_upper || is_lower)
    {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(15, 15, "Password must include at least 1 digit, 1 uppercase charecter and 1 lowercase charecter");
        attroff(COLOR_PAIR(1));
        mvprintw(16, 45, "Press any key to reset");
        getch();
        return 0;
    }

    return 1;
}

int email_check(char email[])
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    int atCount = 0;
    int dotCount = 0;
    int atPosition = -1;
    int dotPosition = -1;

    for (int i = 0; i < strlen(email); i++) {
        char c = email[i];
        if (c == '@') 
        {
            atCount++;
            atPosition = i;
        }
        else if (c == '.') 
        {
            dotCount++;
            dotPosition = i;
        }
        else if (!isalnum(c) && c != '_' && c != '-') 
        {
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(15, 50, "Email invalid");
            attroff(COLOR_PAIR(1));
            mvprintw(16, 45, "Press any key to reset");
            getch();
            return 0;
        }
    }

    if (atCount != 1)
    {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(15, 50, "Email invalid");
        attroff(COLOR_PAIR(1));
        mvprintw(16, 45, "Press any key to reset");
        getch();
        return 0;
    }
    if (atPosition > dotPosition || dotPosition == -1 || dotPosition == strlen(email) - 1)
    {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(15, 50, "Email invalid");
        attroff(COLOR_PAIR(1));
        mvprintw(16, 45, "Press any key to reset");
        getch();
        return 0;
    }

    return 1;
}

void login(Player *player)
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    clear();
    char username[100];
    char password[100];

    attron(A_REVERSE);
    mvprintw(9, 35, "Login as guest (if you don't want just press down key)");
    attroff(A_REVERSE);
    mvprintw(10, 35, "Forget your password?!");
    mvprintw(12, 50, "Username: ");
    mvprintw(13, 50, "Password: ");

    int c = getch();
    if (c == KEY_DOWN)
    {
        mvprintw(9, 35, "                                                                ");
        mvprintw(9, 50, "Login as guest");
        attron(A_REVERSE);
        mvprintw(10, 35, "Forget your password?! (if you don't want just press down key)");
        attroff(A_REVERSE);
        int c = getch();

        if (c == KEY_DOWN)
        {
            mvprintw(10, 35, "                                                                            ");
            mvprintw(10, 50, "Forget your password?!");
            echo();
            curs_set(TRUE);
            mvgetstr(12, 60, username);
            mvgetstr(13, 60, password);
            noecho();
            curs_set(FALSE);
            FILE *players_info = fopen("Players_Info.dat", "rb");

            while (!feof(players_info))
            {
                Player p;
                fread(&p, sizeof(Player), 1, players_info);

                if (strcmp(p.username, username) == 0)
                {
                    if (strcmp(p.password, password) == 0)
                    {
                        fclose(players_info);
                        *player = p;
                        clear();
                        return;
                    }
                    else
                    {
                        clear();
                        attron(COLOR_PAIR(1));
                        mvprintw(15, 48, "Invalid password");
                        attroff(COLOR_PAIR(1));
                        mvprintw(16, 46, "Press any key to reset");
                        getch();
                        login(player);
                        return;
                    }
                }
            }
            fclose(players_info);
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(15, 48, "Invalid username");
            attroff(COLOR_PAIR(1));
            mvprintw(16, 46, "Press any key to reset");
            getch();
            login(player);
            return;
        }

        else if (c == 10)
        {
            clear();
            mvprintw(12, 50, "Username: ");
            mvprintw(13, 50, "Favorite Animal: ");
            echo();
            curs_set(TRUE);
            mvgetstr(12, 60, username);
            mvgetstr(13, 67, password);
            noecho();
            curs_set(FALSE);

            FILE *players_info = fopen("Players_Info.dat", "rb");

            while (!feof(players_info))
            {
                Player p;
                fread(&p, sizeof(Player), 1, players_info);

                if (strcmp(p.username, username) == 0)
                {
                    if (strcmp(p.favorite_animal, password) == 0)
                    {
                        fclose(players_info);
                        *player = p;
                        clear();
                        mvprintw(13, 50, "Your Password: %s", p.password);
                        getch();
                        return;
                    }
                    else
                    {
                        clear();
                        attron(COLOR_PAIR(1));
                        mvprintw(15, 48, "Invalid!");
                        attroff(COLOR_PAIR(1));
                        mvprintw(16, 46, "Press any key to reset");
                        getch();
                        login(player);
                        return;
                    }
                }
            }
            fclose(players_info);
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(15, 48, "Invalid username");
            attroff(COLOR_PAIR(1));
            mvprintw(16, 46, "Press any key to reset");
            getch();
            login(player);
            return;
        }
    }
    else if (c == 10)
    {
        strcpy(player->username, "Guest"); 
        strcpy(player->password, "NULL"); 
        strcpy(player->email, "NULL");
        player->id = 0;
        player->save_game = 0;

        player->score = 0;
        player->gold = 0;
        player->finished_games = 0;
        player->experience = 0;

        clear();
    }
}

int before_game_menu()
{
    clear();
    char menu_options[5][15] = {"New Game", "Load Game", "Settings", "Score Table", "Profile"};
    int choice = 0;

    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(11 + i, 53, "%s", menu_options[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        int c = getch();

        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 4;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 4)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            break;
        }
    }

    return choice;
}

void settings(Game *game)
{
    clear();
    mvprintw(13, 50, "Difficulty:");
    mvprintw(18, 50, "Charecter Color:");
    mvprintw(19, 53, "Yellow");
    mvprintw(20, 53, "Red");
    mvprintw(21, 53, "Green");
    mvprintw(22, 53, "Blue");
    char diff[3][10] = {"Easy", "Medium", "Hard"};
    char color[4][10] = {"Yellow", "Red", "Green", "Blue"};
    int choice = 0;

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(14 + i, 53, "%s", diff[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        int c = getch();

        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 2;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 2)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            game->difficulty = choice;
            break;
        }
    }

    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(19 + i, 53, "%s", color[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        int c = getch();

        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 3;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 3)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            game->color = choice;
            break;
        }
    }
    clear();
}

void score_table(Player *player)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    clear();
    Player players[100];
    int counter = 0;
    FILE *players_info = fopen("Players_Info.dat", "rb");

    while (!feof(players_info))
    {
        fread(&players[counter++], sizeof(Player), 1, players_info);
    }
    fclose(players_info);
    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                Player t = players[j];
                players[j] = players[j + 1];
                players[j + 1] = t;
            }
        }
    }

    mvprintw(2, 9, "username");
    mvprintw(2, 25, "email");
    mvprintw(2, 50, "score");
    mvprintw(2, 61, "gold");
    mvprintw(2, 72, "experience");

    for (int i = 0; i < counter - 1; i++)
    {
        if (i < 3)
            attron(COLOR_PAIR(i + 1));

        if (strcmp(players[i].username, player->username) == 0)
            mvprintw(4 + 2 * i, 2, "->");

        mvprintw(4 + 2 * i, 5, "(%1d) %-15s %-15s %10d %10d %10d", i + 1, players[i].username, players[i].email, players[i].score, players[i].gold, players[i].experience);

        if (i == 0) mvprintw(4 + 2 * i, 87, "(((LEGEND)))");
        if (i == 1) mvprintw(4 + 2 * i, 87, "(((GOAT)))");
        if (i == 2) mvprintw(4 + 2 * i, 87, "(((CHAMPION)))");
        if (i < 3)
            attroff(COLOR_PAIR(i + 1));
    }
    
    attron(A_REVERSE);
    mvprintw(0, 0, "Press Any Key To Back");
    attroff(A_REVERSE);

    getch();
}

void profile(Player *player)
{
    clear();

    mvprintw(3, 5, "Username: %s", player->username);
    mvprintw(5, 5, "E-Mail: %s", player->email);
    mvprintw(7, 5, "Score: %d", player->score);
    mvprintw(9, 5, "Gold Aquared: %d", player->gold);
    mvprintw(11, 5, "Finished Games: %d", player->finished_games);
    mvprintw(13, 5, "Experience: %d", player->experience);

    attron(A_REVERSE);
    mvprintw(0, 0, "Press Any Key To Back");
    attroff(A_REVERSE);

    getch();
}

int random_renge(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void load_map(int k, Explorer_Position *ep, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    FILE *map;

    switch (k)
    {
    case 1:
        map = fopen("Floor_1.txt", "r");
        break;
    case 2:
        map = fopen("Floor_2.txt", "r");
        break;
    case 3:
        map = fopen("Floor_3.txt", "r");
        break;
    case 4:
        map = fopen("Floor_4.txt", "r");
        break;
    }

    char temp[121];
    int counter = 0;
    int ivalue = 0;
    while (fgets(temp, sizeof(temp), map))
    {
        if (counter % 2 == 0)
        {
            for (int i = 0; i < 120; i++)
            {   
                if (k == 1 && temp[i] == 'X')
                {
                    ep->x = i;
                    ep->y = counter / 2;
                    temp[i] = '.';
                    ivalue = 1;
                }
                else if (k > 1 && temp[i] == '<')
                {
                    ep->x = i;
                    ep->y = counter / 2;
                    ivalue = 1;
                }
                else if (ivalue == 0 && temp[i] == '>')
                {
                    ep->x = i;
                    ep->y = counter / 2;
                }

                if (temp[i] == 'V')
                {
                    strcpy(monster[monster_count].name, "Deamon");
                    monster[monster_count].x = i;
                    monster[monster_count].y = counter / 2;
                    monster[monster_count].health = 5;
                    monster[monster_count].movement = 0;
                    monster[monster_count].room = room(i, counter / 2, room1, room2, room3, room4, room5, room6);
                    monster[monster_count].power = 2;
                    monster_count++;
                }

                else if (temp[i] == 'L')
                {
                    strcpy(monster[monster_count].name, "Fire Breathing Monster");
                    monster[monster_count].x = i;
                    monster[monster_count].y = counter / 2;
                    monster[monster_count].health = 10;
                    monster[monster_count].movement = 0;
                    monster[monster_count].room = room(i, counter / 2, room1, room2, room3, room4, room5, room6);
                    monster[monster_count].power = 4;
                    monster_count++;
                }

                else if (temp[i] == 'N')
                {
                    strcpy(monster[monster_count].name, "Gient");
                    monster[monster_count].x = i;
                    monster[monster_count].y = counter / 2;
                    monster[monster_count].health = 15;
                    monster[monster_count].movement = 5;
                    monster[monster_count].room = room(9, 6, room1, room2, room3, room4, room5, room6);
                    monster[monster_count].power = 6;
                    monster_count++;
                }

                else if (temp[i] == 'K')
                {
                    strcpy(monster[monster_count].name, "Snake");
                    monster[monster_count].x = i;
                    monster[monster_count].y = counter / 2;
                    monster[monster_count].health = 20;
                    monster[monster_count].movement = -1;
                    monster[monster_count].room = room(i, counter / 2, room1, room2, room3, room4, room5, room6);
                    monster[monster_count].power = 8;
                    monster_count++;
                }

                else if (temp[i] == 'U')
                {
                    strcpy(monster[monster_count].name, "Undeed");
                    monster[monster_count].x = i;
                    monster[monster_count].y = counter / 2;
                    monster[monster_count].health = 30;
                    monster[monster_count].movement = 5;
                    monster[monster_count].room = room(i, counter / 2, room1, room2, room3, room4, room5, room6);
                    monster[monster_count].power = 10;
                    monster_count++;
                }

                game_map[counter / 2][i] = temp[i];
            }
        }
        counter++;
    }
    fclose(map);
}

void whitch_room(Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    int x = ep->x, y = ep->y;

    if (room1->s_x <= x && x <= room1->e_x && room1->s_y <= y && y <= room1->e_y)
    {
        room1->is_in = 1;
    }
    
    else if (room2->s_x <= x && x <= room2->e_x && room2->s_y <= y && y <= room2->e_y)
    {
        room2->is_in = 1;
    }

    else if (room3->s_x <= x && x <= room3->e_x && room3->s_y <= y && y <= room3->e_y)
    {
        room3->is_in = 1;
    }

    else if (room4->s_x <= x && x <= room4->e_x && room4->s_y <= y && y <= room4->e_y)
    {
        room4->is_in = 1;
    }

    else if (room5->s_x <= x && x <= room5->e_x && room5->s_y <= y && y <= room5->e_y)
    {
        room5->is_in = 1;
    }

    else if (room6->s_x <= x && x <= room6->e_x && room6->s_y <= y && y <= room6->e_y)
    {
        room6->is_in = 1;
    }

    else if (corridor1->s_x <= x && x <= corridor1->e_x && corridor1->s_y <= y && y <= corridor1->e_y)
    {
        corridor1->is_in = 1;
    }

    else if (corridor2->s_x <= x && x <= corridor2->e_x && corridor2->s_y <= y && y <= corridor2->e_y)
    {
        corridor2->is_in = 1;
    }

    else if (corridor3->s_x <= x && x <= corridor3->e_x && corridor3->s_y <= y && y <= corridor3->e_y)
    {
        corridor3->is_in = 1;
    }

    else if (corridor4->s_x <= x && x <= corridor4->e_x && corridor4->s_y <= y && y <= corridor4->e_y)
    {
        corridor4->is_in = 1;
    }

    else if (corridor5->s_x <= x && x <= corridor5->e_x && corridor5->s_y <= y && y <= corridor5->e_y)
    {
        corridor5->is_in = 1;
    }
}

void print_room(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6)
{
    if (room1.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room1);
    }

    if (room2.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room2);
    }

    if (room3.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room3);
    }

    if (room4.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room4);
    }

    if (room5.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room5);
    }

    if (room6.is_in)
    {
       print_map(ep, explorer, game, room1, room2, room3, room4, room5, room6, room6);
    }
    
}

void print_corridor(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5)
{
    if (corridor1.is_in)
    {
       print_map2(ep, explorer, game, corridor1);
    }

    if (corridor2.is_in)
    {
       print_map2(ep, explorer, game, corridor2);
    }

    if (corridor3.is_in)
    {
       print_map2(ep, explorer, game, corridor3);
    }

    if (corridor4.is_in)
    {
       print_map2(ep, explorer, game, corridor4);
    }

    if (corridor5.is_in)
    {
       print_map2(ep, explorer, game, corridor5);
    }
}

void print_map(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Rooms room)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    for (int i = room.s_y; i <= room.e_y; i++)
    {
        for (int j = room.s_x; j <= room.e_x; j++)
        {
            if (game_map[i][j] == 'T') mvprintw(i, j, ".");
            else if (game_map[i][j] == 'F')
            {
                attron(COLOR_PAIR(2));
                mvprintw(i, j, "F");
                attroff(COLOR_PAIR(2));
            }
            else if (game_map[i][j] == 'G')
            {
                attron(COLOR_PAIR(1));
                mvprintw(i, j, "G");
                attroff(COLOR_PAIR(1));
            }
            else if (game_map[i][j] == 'B')
            {
                attron(COLOR_PAIR(1));
                mvprintw(i, j, "B");
                attroff(COLOR_PAIR(1));
            }

            else if (game_map[i][j] == 'M' ||
                     game_map[i][j] == 'D' ||
                     game_map[i][j] == 'W' ||
                     game_map[i][j] == 'A' ||
                     game_map[i][j] == 'S')
            {
                attron(COLOR_PAIR(4));
                mvprintw(i, j, "%c", game_map[i][j]);
                attroff(COLOR_PAIR(4));
            }

            else if (game_map[i][j] == 'd' ||
                     game_map[i][j] == 'w' ||
                     game_map[i][j] == 'a')
            {
                attron(COLOR_PAIR(4));
                mvprintw(i, j, "%c", game_map[i][j]);
                attroff(COLOR_PAIR(4));
            }

            else if (game_map[i][j] == 'H' ||
                     game_map[i][j] == 'Z' ||
                     game_map[i][j] == 'C')
            {
                attron(COLOR_PAIR(3));
                mvprintw(i, j, "%c", game_map[i][j]);
                attroff(COLOR_PAIR(3));
            }

            else if (game_map[i][j] == 'V' ||
                     game_map[i][j] == 'B' ||
                     game_map[i][j] == 'N' ||
                     game_map[i][j] == 'K' ||
                     game_map[i][j] == 'U')
            {
                attron(COLOR_PAIR(5));
                mvprintw(i, j, "%c", game_map[i][j]);
                attroff(COLOR_PAIR(5));
            }

            else if(game_map[i][j] == '=' || game_map[i][j] == '_') room_them_x(i, j, room1, room2, room3, room4, room5, room6);

            else if(game_map[i][j] == '|' || game_map[i][j] == '/') room_them_y(i, j, room1, room2, room3, room4, room5, room6);

            else if (game_map[i][j] == '@')
            {
                attron(COLOR_PAIR(2));
                mvprintw(i, j, "@");
                attroff(COLOR_PAIR(2));
            }

            else if (game_map[i][j] == '&')
            {
                attron(COLOR_PAIR(6));
                mvprintw(i, j, "&");
                attroff(COLOR_PAIR(6));
            }

            else if (game_map[i][j] == '*')
            {
                attron(COLOR_PAIR(1));
                mvprintw(i, j, "*");
                attroff(COLOR_PAIR(1));
            }

            else mvprintw(i, j, "%c", game_map[i][j]);
        }
    }
    attron(COLOR_PAIR(game.color + 1));
    mvprintw(ep->y, ep->x, "X");
    attroff(COLOR_PAIR(game.color + 1));
    
    mvprintw(29, 10, "Health : %d", explorer->health);
    mvprintw(29, 27, "Score : %d", explorer->score);
    mvprintw(29, 40, "Level : %d", explorer->level);
    mvprintw(29, 55, "Gold : %d", explorer->gold);
    mvprintw(29, 70, "Experience : %d", explorer->experience);
    mvprintw(29, 90, "Weapon : %s", explorer->current_weapon.weapon);
}

void print_map2(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    for (int i = corridor.s_y; i <= corridor.e_y; i++)
    {
        for (int j = corridor.s_x; j <= corridor.e_x; j++)
        {
            if (game_map[i][j] == '-') mvprintw(i, j, " ");
            else mvprintw(i, j, "#");
        }
    }
    attron(COLOR_PAIR(game.color + 1));
    mvprintw(ep->y, ep->x, "X");
    attroff(COLOR_PAIR(game.color + 1));
}

void move_ivalue(int move, Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5)
{
    init_pair(11, COLOR_WHITE, COLOR_BLACK);
    init_pair(12, COLOR_YELLOW, COLOR_BLACK);
    init_pair(13, COLOR_RED, COLOR_BLACK);
    if (move == 's')
    {
        if (move_ivalue_help(ep) && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x] != 'O' && move_ivalue_help2(ep->y + 1, ep->x))
        {
            ep->y++;
            if (game_map[ep->y][ep->x] == '_') 
            {
                game_map[ep->y][ep->x] = '+';
                mvprintw(0, 25, "Wow! You found a Hidden Door! Score increases!");
                explorer->score += 3;
                getch();
            }
            else if (game_map[ep->y][ep->x] == '@') 
            {
                if (unlock_door())
                {
                    clear();
                    game_map[ep->y][ep->x] = '+';
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    if(ancient_key_value == 0) mvprintw(0, 25, "Wow! Your opend the Door! Score increases!");
                    else
                    {
                        ancient_key_value--;
                        mvprintw(0, 25, "Wow! Your opend the Door By Ancient Key! You have %d number of keys now! Score increases!", ancient_key_value);
                    }
                    start_code -= 30;
                    explorer->score += 3;
                }
                else
                {
                    clear();
                    ep->y--;
                    num_of_mistakes++;
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    attron(COLOR_PAIR(num_of_mistakes + 10));
                    mvprintw(0, 25, "Opps! The code is false!");
                    if (num_of_mistakes == 3)
                    {
                        mvprintw(0, 25, "Opps! The code is false! The door locks forever!!!");
                        game_map[ep->y + 1][ep->x] = '=';
                    }
                    attroff(COLOR_PAIR(num_of_mistakes + 10));
                }
                getch();
            }
        }
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] != '|') && move_ivalue_help2(ep->y + 1, ep->x)) ep->y++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] == '+')) ep->y++;
    }

    else if (move == 'w')
    {
        if (move_ivalue_help(ep) && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x] != 'O' && move_ivalue_help2(ep->y - 1, ep->x))
        {
            ep->y--;
            if (game_map[ep->y][ep->x] == '_')
            {
                game_map[ep->y][ep->x] = '+';
                mvprintw(0, 25, "Wow! You found a Hidden Door! Score increases!");
                explorer->score += 3;
                getch();
            }
            else if (game_map[ep->y][ep->x] == '@') 
            {
                if (unlock_door())
                {
                    clear();
                    game_map[ep->y][ep->x] = '+';
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    if(ancient_key_value == 0) mvprintw(0, 25, "Wow! Your opend the Door! Score increases!");
                    else
                    {
                        ancient_key_value--;
                        mvprintw(0, 25, "Wow! Your opend the Door By Ancient Key! You have %d number of keys now! Score increases!", ancient_key_value);
                    }
                    start_code -= 30;
                    explorer->score += 3;
                }
                else
                {
                    clear();
                    ep->y++;
                    num_of_mistakes++;
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    attron(COLOR_PAIR(num_of_mistakes + 10));
                    mvprintw(0, 25, "Opps! The code is false!");
                    if (num_of_mistakes == 3)
                    {
                        mvprintw(0, 25, "Opps! The code is false! The door locks forever!!!");
                        game_map[ep->y - 1][ep->x] = '=';
                    }
                    attroff(COLOR_PAIR(num_of_mistakes + 10));
                }
                getch();
            }
        }
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] != '|') && move_ivalue_help2(ep->y - 1, ep->x)) ep->y--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] == '+')) ep->y--;
    }

    else if (move == 'd')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y][ep->x + 1] != 'O' && move_ivalue_help2(ep->y, ep->x + 1))
        {
            ep->x++;
            if (game_map[ep->y][ep->x] == '/')
            {
                game_map[ep->y][ep->x] = '+';
                mvprintw(0, 25, "Wow! You found a Hidden Door! Score increases!");
                explorer->score += 3;
                getch();
            }
            else if (game_map[ep->y][ep->x] == '@') 
            {
                if (unlock_door())
                {
                    clear();
                    game_map[ep->y][ep->x] = '+';
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    if(ancient_key_value == 0) mvprintw(0, 25, "Wow! Your opend the Door! Score increases!");
                    else
                    {
                        ancient_key_value--;
                        mvprintw(0, 25, "Wow! Your opend the Door By Ancient Key! You have %d number of keys now! Score increases!", ancient_key_value);
                    }
                    start_code -= 30;
                    explorer->score += 3;
                }
                else
                {
                    clear();
                    ep->x--;
                    num_of_mistakes++;
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    attron(COLOR_PAIR(num_of_mistakes + 10));
                    mvprintw(0, 25, "Opps! The code is false!");
                    if (num_of_mistakes == 3)
                    {
                        mvprintw(0, 25, "Opps! The code is false! The door locks forever!!!");
                        game_map[ep->y][ep->x + 1] = '=';
                    }
                    attroff(COLOR_PAIR(num_of_mistakes + 10));
                }
                getch();
            }
        }
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] != '=') && move_ivalue_help2(ep->y, ep->x + 1)) ep->x++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] == '+')) ep->x++;
    }

    else if (move == 'a')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y][ep->x - 1] != 'O' && move_ivalue_help2(ep->y, ep->x - 1))
        {
            ep->x--;
            if (game_map[ep->y][ep->x] == '/')
            {
                game_map[ep->y][ep->x] = '+';
                mvprintw(0, 25, "Wow! You found a Hidden Door! Score increases!");
                explorer->score += 3;
                getch();
            }
            else if (game_map[ep->y][ep->x] == '@') 
            {
                if (unlock_door())
                {
                    clear();
                    game_map[ep->y][ep->x] = '+';
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    if(ancient_key_value == 0) mvprintw(0, 25, "Wow! Your opend the Door! Score increases!");
                    else
                    {
                        ancient_key_value--;
                        mvprintw(0, 25, "Wow! Your opend the Door By Ancient Key! You have %d number of keys now! Score increases!", ancient_key_value);
                    }
                    start_code -= 30;
                    explorer->score += 3;
                }
                else
                {
                    clear();
                    ep->x++;
                    num_of_mistakes++;
                    move(0, 0);
                    print_room(ep, explorer, game, room1, room2, room3, room4, room5, room6);
                    print_corridor(ep, explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                    attron(COLOR_PAIR(num_of_mistakes + 10));
                    mvprintw(0, 25, "Opps! The code is false!");
                    if (num_of_mistakes == 3)
                    {
                        mvprintw(0, 25, "Opps! The code is false! The door locks forever!!!");
                        game_map[ep->y][ep->x - 1] = '=';
                    }
                    attroff(COLOR_PAIR(num_of_mistakes + 10));
                }
                getch();
            }
        }
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] != '=') && move_ivalue_help2(ep->y, ep->x + 1)) ep->x--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] == '+')) ep->x--;
    }

    else if (move == 'c')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x + 1] != 'O' && move_ivalue_help2(ep->y + 1, ep->x + 1))
        {
            ep->x++;
            ep->y++;
        }
    }

    else if (move == 'z')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x - 1] != 'O' && move_ivalue_help2(ep->y + 1, ep->x - 1))
        {
            ep->y++;
            ep->x--;
        }
    }

    else if (move == 'e')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x + 1] != 'O' && move_ivalue_help2(ep->y - 1, ep->x + 1))
        {
            ep->x++;
            ep->y--;
        }
    }

    else if (move == 'q')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x - 1] != 'O' && move_ivalue_help2(ep->y - 1, ep->x - 1))
        {
            ep->y--;
            ep->x--;
        }
    }
}

void move_ivalue2(int move, Explorer_Position *ep)
{
    if (move == 's')
    {
        while (move_ivalue_help(ep) && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x] != 'O' && game_map[ep->y + 1][ep->x] != '+' && game_map[ep->y + 1][ep->x] != '@') ep->y++;
    }

    else if (move == 'w')
    {
        while (move_ivalue_help(ep) && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x] != 'O' && game_map[ep->y - 1][ep->x] != '+' && game_map[ep->y - 1][ep->x] != '@') ep->y--;
    }

    else if (move == 'd')
    {
        while (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y][ep->x + 1] != 'O' && game_map[ep->y][ep->x + 1] != '+' && game_map[ep->y][ep->x + 1] != '@') ep->x++;
    }

    else if (move == 'a')
    {
        while (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y][ep->x - 1] != 'O' && game_map[ep->y][ep->x - 1] != '+' && game_map[ep->y][ep->x - 1] != '@') ep->x--;
    }
}

void new_game(Explorer_Position *ep, Explorer *explorer, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    start = time(NULL);
    clear();
    explorer->health = 100;
    explorer->score = 0;
    explorer->level = 1;
    explorer->gold = 0;
    explorer->experience = 0;
}

void trap(Explorer_Position *ep, Explorer *explorer)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == '^' || temp == 'T')
    {
        mvprintw(0, 25, "Opps! There Was a Trap!");
        explorer->health -= 10;
        game_map[ep->y][ep->x] = '^';
    }
}

void stair(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Monster *monster)
{
    FILE *map;
    int floor = explorer->level;

    switch (floor)
    {
    case 1:
        map = fopen("Floor_1.txt", "w");
        break;
    case 2:
        map = fopen("Floor_2.txt", "w");
        break;
    case 3:
        map = fopen("Floor_3.txt", "w");
        break;
    case 4:
        map = fopen("Floor_4.txt", "w");
        break;
    }

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 120; j++) {
            fprintf(map, "%c", game_map[i][j]);
        }
        fprintf(map, "\n");
    }

    fclose(map);
    stair_save(explorer, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
    if (game_map[ep->y][ep->x] == '>') explorer->level++;
    else explorer->level--;
    load_map(explorer->level, ep, monster, room1, room2, room3, room4, room5, room6);
    room_position(explorer, room1, room2, room3, room4, room5, room6);
    corridor_position(explorer, corridor1, corridor2, corridor3, corridor4, corridor5);
}

void stair_save(Explorer *explorer, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    FILE *rooms;
    FILE *corridors;

    switch (explorer->level)
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
                room = *room1;
                break;
            case 1:
                room = *room2;
                break;
            case 2:
                room = *room3;
                break;
            case 3:
                room = *room4;
                break;
            case 4:
                room = *room5;
                break;
            case 5:
                room = *room6;
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
                corridor = *corridor1;
                break;
            case 1:
                corridor = *corridor2;
                break;
            case 2:
                corridor = *corridor3;
                break;
            case 3:
                corridor = *corridor4;
                break;
            case 4:
                corridor = *corridor5;
                break;
        }

        fseek(corridors, i * sizeof(Corridors), SEEK_SET);
        fwrite(&corridor, sizeof(Corridors), 1, corridors);
    }
    fclose(corridors);
}

int stair_check(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5, Monster *monster)
{
    if (game_map[ep->y][ep->x] == '>') mvprintw(0, 25, "Wow! You reached the stair, press 'U' to go up!");
    else mvprintw(0, 25, "Wow! You reached the stair, press 'U' to go down!");
    int move = tolower(getch());

    if (move == 'u') stair(explorer, ep, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5, monster);
    else return move;
}

int move_ivalue_help(Explorer_Position *ep)
{
    if (game_map[ep->y][ep->x] == '.' || 
        game_map[ep->y][ep->x] == '^' ||
        game_map[ep->y][ep->x] == '>' || 
        game_map[ep->y][ep->x] == '<' ||
        game_map[ep->y][ep->x] == '&')
        return 1;

    else return 0;
}

int move_ivalue_help2(int y, int x)
{
    if (game_map[y][x] != 'V' &&
        game_map[y][x] != 'L' &&
        game_map[y][x] != 'N' &&
        game_map[y][x] != 'k' &&
        game_map[y][x] != 'U')
        return 1;

    else return 0;
}

void find_food(char name[], Food *food)
{
    int ivalue = 0;
    for (int i = 0; i < food->count; i++)
    {
        if (strcmp(food->foods[i].food, name) == 0)
        {
            ivalue = 1;
            food->foods[i].count++;
        }
    }
    if (ivalue == 0)
    {
        strcpy(food->foods[food->count].food, name);
        food->foods[food->count++].count = 1;
    }
}

void foods(Explorer_Position *ep, Explorer *explorer, Food *food)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == 'F')
    {
        mvprintw(0, 25, "Wow! You reach Food! Score increases!");
        find_food("Food", food);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 1;
    }
}

int food_show(Food *food)
{
    WINDOW *win;
    win = newwin(12, 32, 10, 45); 

    if (food->count > 0)
    {   
        int choice = 0;

        while (1)
        {
            mvwprintw(win, 0, 0, "--------------------------------");
            mvwprintw(win, 11, 0, "--------------------------------");
            for (int i = 0; i < 12; i++)
            {
                mvwprintw(win, i, 0, "|");
                mvwprintw(win, i, 31, "|");
            }

            for (int i = 0; i < food->count; i++)
            {
                mvwprintw(win, 1 + i, 5, "%s", food->foods[i].food);
                mvwprintw(win, 1 + i, 27, "(%d)", food->foods[i].count);
            }
            mvwprintw(win, 1 + food->count, 5, "Back");
            mvwprintw(win, 1 + choice, 2, "->");
            mvwprintw(win, 10, 2, "Hunger: ");
            for (int i = 0; i < hunger; i++)
            {
                mvwprintw(win, 10, 10 + i, "#");
            }
            wrefresh(win);
            int c = getch();
            if (c == KEY_UP)
            {
                if (choice != 0)
                    choice--;
                else
                    choice = food->count;
            }
            else if (c == KEY_DOWN)
            {
                if (choice != food->count)
                    choice++;
                else
                    choice = 0;
            }
            else if (c == 10)
            {
                break;
            }            
            wclear(win);
        }

        if (choice == food->count)
            return 0;
        
        food->foods[choice].count--;
        if(food->foods[choice].count == 0)
            food->count--;
        wrefresh(win);
        delwin(win);
        return 1;
    }
    else
    {
        mvwprintw(win, 0, 0, "--------------------------------");
        mvwprintw(win, 11, 0, "--------------------------------");
        for (int i = 0; i < 12; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 31, "|");
        }
        mvwprintw(win, 5, 12, "NO FOOD!");
        mvwprintw(win, 10, 2, "Hunger: ");
        for (int i = 0; i < hunger; i++)
        {
            mvwprintw(win, 10, 10 + i, "#");
        }
        wrefresh(win);
        getch();
        delwin(win);
        return 0;
    }
}

void gold(Explorer_Position *ep, Explorer *explorer)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == 'G')
    {
        int g = random_renge(1, 5);
        mvprintw(0, 25, "Wow! You reach %d gold!", g);
        explorer->gold += g;
        explorer->score += g * 2;
        game_map[ep->y][ep->x] = '.';
    }
}

void black_gold(Explorer_Position *ep, Explorer *explorer)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == 'B')
    {
        int g = random_renge(5, 10);
        mvprintw(0, 25, "Wow! You reach %d black gold!", g);
        explorer->gold += g;
        explorer->score += g * 2;
        game_map[ep->y][ep->x] = '.';
    }
}

void find_weapon(char name[], Weapon *weapon)
{
    for (int i = 0; i < weapon->count; i++)
    {
        if (strcmp(weapon->weapons[i].weapon, name) == 0)
        {
            weapon->weapons[i].count += weapon->weapons[i].num_in_each;
        }
    }
}

void weapons(Explorer_Position *ep, Explorer *explorer, Weapon *weapon)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == 'M')
    {
        mvprintw(0, 25, "Wow! You reach Mace! Score increases!");
        find_weapon("Mace", weapon);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 3;
    }

    else if (temp == 'D')
    {
        mvprintw(0, 25, "Wow! You reach Dagger! Score increases!");
        find_weapon("Dagger", weapon);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 3;
    }

    else if (temp == 'W')
    {
        mvprintw(0, 25, "Wow! You reach Magic Wand! Score increases!");
        find_weapon("Magic Wand", weapon);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 3;
    }

    else if (temp == 'A')
    {
        mvprintw(0, 25, "Wow! You reach Normal Arrow! Score increases!");
        find_weapon("Normal Arrow", weapon);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 3;
    }

    else if (temp == 'S')
    {
        mvprintw(0, 25, "Wow! You reach Sword! Score increases!");
        find_weapon("Sword", weapon);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 3;
    }

    else if (temp == 'd')
    {
        mvprintw(0, 25, "Wow! You reach Dagger!");
        weapon->weapons[2].count++;
        game_map[ep->y][ep->x] = '.';
    }

    else if (temp == 'w')
    {
        mvprintw(0, 25, "Wow! You reach Magic Wand!");
        weapon->weapons[3].count++;
        game_map[ep->y][ep->x] = '.';
    }

    else if (temp == 'a')
    {
        mvprintw(0, 25, "Wow! You reach Normal Arrow!");
        weapon->weapons[4].count++;
        game_map[ep->y][ep->x] = '.';
    }
}

int weapon_show(Weapon *weapon, Explorer *explorer)
{
    WINDOW *win;
    win = newwin(20, 50, 5, 30);

    int choice = 0;

    while (1)
    {
        mvwprintw(win, 0, 0, "--------------------------------------------------");
        mvwprintw(win, 19, 0, "--------------------------------------------------");
        for (int i = 0; i < 20; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 49, "|");
        }

        mvwprintw(win, 1, 2, "Short Renge Weapons:");
        for (int i = 0; i < 2; i++)
        {
            mvwprintw(win, 2 + i, 5, "%s", weapon->weapons[i].weapon);
            mvwprintw(win, 2 + i, 20, "Damage: %d", weapon->weapons[i].damage);
            mvwprintw(win, 2 + i, 44, "(%d)", weapon->weapons[i].count);
        }

        mvwprintw(win, 5, 2, "Long Renge Weapons:");
        for (int i = 2; i < 5; i++)
        {
            mvwprintw(win, 4 + i, 5, "%s", weapon->weapons[i].weapon);
            mvwprintw(win, 4 + i, 20, "Damage: %d", weapon->weapons[i].damage);
            mvwprintw(win, 4 + i, 33, "Board: %d", weapon->weapons[i].board);
            mvwprintw(win, 4 + i, 44, "(%d)", weapon->weapons[i].count);
        }
        mvwprintw(win, 18, 5, "Back");
        if (choice < 2) mvwprintw(win, 2 + choice, 2, "->");
        else if(choice != weapon->count) mvwprintw(win, 4 + choice, 2, "->");
        else if (choice == weapon->count) mvwprintw(win, 18, 2, "->");
        wrefresh(win);
        int c = getch();
        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = weapon->count;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != weapon->count)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            break;
        }            
        wclear(win);
    }

    if (choice == weapon->count)
        return 0;

    explorer->current_weapon = weapon->weapons[choice];
    wrefresh(win);
    delwin(win);
    return 1;
}

void find_spell(char name[], Spell *spell)
{
    int ivalue = 0;
    for (int i = 0; i < spell->count; i++)
    {
        if (strcmp(spell->spells[i].spell, name) == 0)
        {
            ivalue = 1;
            spell->spells[i].count++;
        }
    }
    if (ivalue == 0)
    {
        strcpy(spell->spells[spell->count].spell, name);
        spell->spells[spell->count].count = 1;
        spell->spells[spell->count].id = spell->count;
        spell->spells[spell->count].time = -1;
        spell->count++;
    }
}

void spells(Explorer_Position *ep, Explorer *explorer, Spell *spell)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == 'H')
    {
        mvprintw(0, 25, "Wow! You reach Health Spell! Score increases!");
        find_spell("Health", spell);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 4;
    }

    else if (temp == 'Z')
    {
        mvprintw(0, 25, "Wow! You reach Speed Spell! Score increases!");
        find_spell("Speed", spell);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 4;
    }

    else if (temp == 'C')
    {
        mvprintw(0, 25, "Wow! You reach Damage Spell! Score increases!");
        find_spell("Damage", spell);
        game_map[ep->y][ep->x] = '.';
        explorer->score += 4;
    }
}

int spell_show(Spell *spell, Explorer *explorer)
{
    WINDOW *win;
    win = newwin(12, 25, 10, 45); 

    int choice = 0;

    while (1)
    {
        mvwprintw(win, 0, 0, "-------------------------");
        mvwprintw(win, 11, 0, "-------------------------");
        for (int i = 0; i < 12; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 24, "|");
        }

        for (int i = 0; i < spell->count; i++)
        {
            mvwprintw(win, 1 + i, 5, "%s", spell->spells[i].spell);
            mvwprintw(win, 1 + i, 20, "(%d)", spell->spells[i].count);
        }

        mvwprintw(win, 1 + spell->count, 5, "Back");
        mvwprintw(win, 1 + choice, 2, "->");
        wrefresh(win);
        int c = getch();
        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = spell->count;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != spell->count)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            break;
        }            
        wclear(win);
    }

    if (choice == spell->count)
        return -1;
    else if (spell->spells[choice].count == 0)
        return (spell->spells[choice].id - 4);
    spell->spells[choice].count--;  
    wrefresh(win);
    delwin(win);
    return spell->spells[choice].id;
}

int end_game(Explorer_Position *ep, Explorer *explorer, Player *player)
{
    if (explorer->level == 4 && game_map[ep->y][ep->x] == '>')
    {
        clear();
        mvprintw(15, 45, "Congradulations!!! You have finished the game.");
        mvprintw(16, 45, "I hope to see you again :)");
        mvprintw(17, 45, "Press any key to exit...");
        getch();
        player->experience = explorer->experience;
        player->finished_games++;
        player->gold = explorer->gold;
        player->score = explorer->score;
        return 1;
    }

    return 0;
}

void room_position(Explorer *explorer, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    FILE *rooms;

    switch (explorer->level)
    {
        case 1:
        {
            rooms = fopen("rooms1.dat", "rb");
            break;
        }
        case 2:
        {
            rooms = fopen("rooms2.dat", "rb");
            break;
        }
        case 3:
        {
            rooms = fopen("rooms3.dat", "rb");
            break;
        }
        case 4:
        {
            rooms = fopen("rooms4.dat", "rb");
            break;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        Rooms room;
        fseek(rooms, i * sizeof(Rooms), SEEK_SET);
        fread(&room, sizeof(Rooms), 1, rooms);
        switch (i)
        {
        case 0:
            *room1 = room;
            break;
        case 1:
            *room2 = room;
            break;
        case 2:
            *room3 = room;
            break;
        case 3:
            *room4 = room;
            break;
        case 4:
            *room5 = room;
            break;
        case 5:
            *room6 = room;
            break;
        }
    }
}

void corridor_position(Explorer *explorer, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    FILE *corridors;

    switch (explorer->level)
    {
        case 1:
        {
            corridors = fopen("corridors1.dat", "rb");
            break;
        }
        case 2:
        {
            corridors = fopen("corridors2.dat", "rb");
            break;
        }
        case 3:
        {
            corridors = fopen("corridors3.dat", "rb");
            break;
        }
        case 4:
        {
            corridors = fopen("corridors4.dat", "rb");
            break;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        Corridors corridor;
        fseek(corridors, i * sizeof(Corridors), SEEK_SET);
        fread(&corridor, sizeof(Corridors), 1, corridors);
        switch (i)
        {
        case 0:
            *corridor1 = corridor;
            break;
        case 1:
            *corridor2 = corridor;
            break;
        case 2:
            *corridor3 = corridor;
            break;
        case 3:
            *corridor4 = corridor;
            break;
        case 4:
            *corridor5 = corridor;
            break;
        }
    }
}

int exit_menu()
{
    WINDOW *win;
    win = newwin(12, 25, 10, 45);    

    char menu_options[2][15] = {"Resume", "Save & Exit"};
    int choice = 0;

    while (1)
    {
        mvwprintw(win, 0, 0, "-------------------------");
        mvwprintw(win, 11, 0, "-------------------------");
        for (int i = 0; i < 12; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 24, "|");
        }

        for (int i = 0; i < 2; i++)
        {
            mvwprintw(win, 5 + i, 8, "%s", menu_options[i]);
        }
        mvwprintw(win, 5 + choice, 5, "->");
        wrefresh(win);
        int c = getch();
        if (c == KEY_UP)
        {
            if (choice != 0)
                choice--;
            else
                choice = 1;
        }
        else if (c == KEY_DOWN)
        {
            if (choice != 1)
                choice++;
            else
                choice = 0;
        }
        else if (c == 10)
        {
            break;
        }
        wclear(win);
    }

    wclear(win);
    int choice2 = 0;
    if (choice == 1)
    {
        char menu_options2[2][15] = {"No", "Yes"};

        while (1)
        {
            mvwprintw(win, 0, 0, "-------------------------");
            mvwprintw(win, 11, 0, "-------------------------");
            for (int i = 0; i < 12; i++)
            {
                mvwprintw(win, i, 0, "|");
                mvwprintw(win, i, 24, "|");
            }

            mvwprintw(win, 3, 6, "Are You Sure?!");

            for (int i = 0; i < 2; i++)
            {
                mvwprintw(win, 5 + i, 8, "%s", menu_options2[i]);
            }
            mvwprintw(win, 5 + choice2, 5, "->");
            wrefresh(win);
            int c = getch();
            if (c == KEY_UP)
            {
                if (choice2 != 0)
                    choice2--;
                else
                    choice2 = 1;
            }
            else if (c == KEY_DOWN)
            {
                if (choice2 != 1)
                    choice2++;
                else
                    choice2 = 0;
            }
            else if (c == 10)
            {
                break;
            }
            wclear(win);
        }
    }

    wrefresh(win);
    delwin(win);
    return choice2;
}

void save(Player *player, Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    FILE *player_info = fopen("Players_Info.dat", "rb+");

    fseek(player_info, (player->id - 1) * sizeof(Rooms), SEEK_SET);
    player->experience = explorer->experience;
    player->gold = explorer->gold;
    player->score = explorer->score;
    player->save_game = 1;
    player->health = explorer->health;
    player->level = explorer->level;
    fwrite(player, sizeof(Player), 1, player_info);
    fclose(player_info);

    FILE *map;
    int floor = explorer->level;

    switch (floor)
    {
    case 1:
        map = fopen("Floor_1.txt", "w");
        break;
    case 2:
        map = fopen("Floor_2.txt", "w");
        break;
    case 3:
        map = fopen("Floor_3.txt", "w");
        break;
    case 4:
        map = fopen("Floor_4.txt", "w");
        break;
    }

    game_map[ep->y][ep->x] = 'X';
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 120; j++) {
            fprintf(map, "%c", game_map[i][j]);
        }
        fprintf(map, "\n");
    }

    fclose(map);
    stair_save(explorer, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
}

void room_them_x(int i, int j, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6)
{
    if ((i == room1.s_y || i == room1.e_y) && (room1.s_x <= j && j <= room1.e_x) && room1.type != 2)
    {
        attron(COLOR_PAIR(room1.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room1.type));
    }
    else if ((i == room2.s_y || i == room2.e_y) && (room2.s_x <= j && j <= room2.e_x) && room2.type != 2)
    {
        attron(COLOR_PAIR(room2.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room2.type));
    }
    else if ((i == room3.s_y || i == room3.e_y) && (room3.s_x <= j && j <= room3.e_x) && room3.type != 2)
    {
        attron(COLOR_PAIR(room3.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room3.type));
    }
    else if ((i == room4.s_y || i == room4.e_y) && (room4.s_x <= j && j <= room4.e_x) && room4.type != 2)
    {
        attron(COLOR_PAIR(room4.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room4.type));
    }
    else if ((i == room5.s_y || i == room5.e_y) && (room5.s_x <= j && j <= room5.e_x) && room5.type != 2)
    {
        attron(COLOR_PAIR(room5.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room5.type));
    }
    else if ((i == room6.s_y || i == room6.e_y) && (room6.s_x <= j && j <= room6.e_x) && room6.type != 2)
    {
        attron(COLOR_PAIR(room6.type));
        mvprintw(i, j, "=");
        attroff(COLOR_PAIR(room6.type));
    }
    else mvprintw(i, j, "=");
}

void room_them_y(int i, int j, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6)
{
    if ((j == room1.s_x || j == room1.e_x) && (room1.s_y <= i && i <= room1.e_y) && room1.type != 2)
    {
        attron(COLOR_PAIR(room1.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room1.type));
    }
    else if ((j == room2.s_x || j == room2.e_x) && (room2.s_y <= i && i <= room2.e_y) && room2.type != 2)
    {
        attron(COLOR_PAIR(room2.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room2.type));
    }
    else if ((j == room3.s_x || j == room3.e_x) && (room3.s_y <= i && i <= room3.e_y) && room3.type != 2)
    {
        attron(COLOR_PAIR(room3.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room3.type));
    }
    else if ((j == room4.s_x || j == room4.e_x) && (room4.s_y <= i && i <= room4.e_y) && room4.type != 2)
    {
        attron(COLOR_PAIR(room4.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room4.type));
    }
    else if ((j == room5.s_x || j == room5.e_x) && (room5.s_y <= i && i <= room5.e_y) && room5.type != 2)
    {
        attron(COLOR_PAIR(room5.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room5.type));
    }
    else if ((j == room6.s_x || j == room6.e_x) && (room6.s_y <= i && i <= room6.e_y) && room6.type != 2)
    {
        attron(COLOR_PAIR(room6.type));
        mvprintw(i, j, "|");
        attroff(COLOR_PAIR(room6.type));
    }
    else mvprintw(i, j, "|");
}

void password(Explorer_Position *ep, Explorer *explorer, int *code)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == '&')
    {
        *code = random_renge(1000, 9999);
        start_code = time(NULL);
    }
}

int unlock_door()
{
    if (ancient_key_value == 0)
    {
        WINDOW *win;
        win = newwin(12, 25, 10, 45);    

        mvwprintw(win, 0, 0, "-------------------------");
        mvwprintw(win, 11, 0, "-------------------------");
        for (int i = 0; i < 12; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 24, "|");
        }

        mvwprintw(win, 4, 2, "Please enter the code");
        wrefresh(win);

        curs_set(TRUE);
        echo();
        int user_code;
        mvwscanw(win, 6, 10, "%d", &user_code);
        noecho();
        curs_set(FALSE);
        delwin(win);

        if (user_code == code) return 1;
        else return 0;
    }

    return 1;
}

void ancient_key(Explorer_Position *ep, Explorer *explorer)
{
    char temp = game_map[ep->y][ep->x];

    if (temp == '*')
    {
        mvprintw(0, 25, "Wow! found an Ancient Key!");
        game_map[ep->y][ep->x] = '.';
        ancient_key_value++;
    }
}

void load_game(int *ex, Explorer_Position *ep, Explorer *explorer, Player *player, Monster *monster, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    start = time(NULL);
    clear();
    explorer->health = player->health;
    explorer->score = player->score;
    explorer->level = player->level;
    explorer->gold = player->gold;
    explorer->experience = player->experience;
    *ex = player->experience;
}

void random_password(int length, char password[])
{
    char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < length; i++) 
    {
        int temp = random_renge(0, 62);
        password[i] = chars[temp];
    }
    password[length] = '\0';

    if (password_check(password) == 0)
        random_password(length, password);
}

int room(int x, int y, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6)
{
    if (room1->s_x <= x && x <= room1->e_x && room1->s_y <= y && y <= room1->e_y)
    {
        return 1;
    }
    
    else if (room2->s_x <= x && x <= room2->e_x && room2->s_y <= y && y <= room2->e_y)
    {
        return 2;
    }

    else if (room3->s_x <= x && x <= room3->e_x && room3->s_y <= y && y <= room3->e_y)
    {
        return 3;
    }

    else if (room4->s_x <= x && x <= room4->e_x && room4->s_y <= y && y <= room4->e_y)
    {
        return 4;
    }

    else if (room5->s_x <= x && x <= room5->e_x && room5->s_y <= y && y <= room5->e_y)
    {
        return 5;
    }

    else if (room6->s_x <= x && x <= room6->e_x && room6->s_y <= y && y <= room6->e_y)
    {
        return 6;
    }

    return 0;
}

void mace(int x, int y, Monster *monster, Explorer *explorer)
{
    for (int i = 0; i < monster_count; i++)
    {
        int m_x = monster[i].x;
        int m_y = monster[i].y;

        if ((m_x == x + 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
            (m_x == x - 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
            (m_y == y + 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)) || 
            (m_y == y - 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)))
        {
            if (monster[i].health > 0)
            {
                monster[i].health -= 5 * explorer->power;
                mvprintw(0, 25, "Wow! You hit a %s with Mace!        ", monster[i].name);
                explorer->score += 1;
                if (monster[i].health <= 0)
                {
                    game_map[m_y][m_x] = '.';
                    mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[i].name);
                    explorer->score += 5;
                }
            }
        }
    }
}

void sword(int x, int y, Monster *monster, Explorer *explorer)
{
    for (int i = 0; i < monster_count; i++)
    {
        int m_x = monster[i].x;
        int m_y = monster[i].y;

        if ((m_x == x + 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
            (m_x == x - 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
            (m_y == y + 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)) || 
            (m_y == y - 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)))
        {
            if (monster[i].health > 0)
            {
                monster[i].health -= 10 * explorer->power;
                mvprintw(0, 25, "Wow! You hit a %s with Sword!        ", monster[i].name);
                explorer->score += 1;
                if (monster[i].health <= 0)
                {
                    game_map[m_y][m_x] = '.';
                    mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[i].name);
                    explorer->score += 5;
                }
            }
        }
    }
}

void dagger(int x, int y, Monster *monster, Explorer *explorer)
{
    int way = getch();
    mvprintw(0, 25, "Wow! You throwed a Dagger!");

    if (way == 'w')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y - i][x] == '=' || game_map[y - i][x] == '+' || game_map[y - i][x] == '@' || game_map[y - i][x] == '_')
            {
                game_map[y - i + 1][x] = 'd';
                ivalue = 0;
            }

            else if (game_map[y - i][x] == 'V' || game_map[y - i][x] == 'L' || game_map[y - i][x] == 'N' || game_map[y - i][x] == 'K' || game_map[y - i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y - i && monster[j].x == x)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Dagger!", monster[j].name);
                        monster[j].health -= 12 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y - i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y - 5][x] = 'd';
    }

    else if (way == 's')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y + i][x] == '=' || game_map[y + i][x] == '+' || game_map[y + i][x] == '@' || game_map[y + i][x] == '_')
            {
                game_map[y + i - 1][x] = 'd';
                ivalue = 0;
            }

            else if (game_map[y + i][x] == 'V' || game_map[y + i][x] == 'L' || game_map[y + i][x] == 'N' || game_map[y + i][x] == 'K' || game_map[y + i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y + i && monster[j].x == x)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Dagger!", monster[j].name);
                        monster[j].health -= 12 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y + i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y + 5][x] = 'd';
    }

    else if (way == 'd')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y][x + i] == '|' || game_map[y][x + i] == '+' || game_map[y][x + i] == '@' || game_map[y][x + i] == '/')
            {
                game_map[y][x + i - 1] = 'd';
                ivalue = 0;
            }

            else if (game_map[y][x + i] == 'V' || game_map[y][x + i] == 'L' || game_map[y][x + i] == 'N' || game_map[y][x + i] == 'K' || game_map[y][x + i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x + i)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Dagger!", monster[j].name);
                        monster[j].health -= 12 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x + i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x + 5] = 'd';
    }

    else if (way == 'a')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y][x - i] == '|' || game_map[y][x - i] == '+' || game_map[y][x - i] == '@' || game_map[y][x - i] == '/')
            {
                game_map[y][x - i + 1] = 'd';
                ivalue = 0;
            }

            else if (game_map[y][x - i] == 'V' || game_map[y][x - i] == 'L' || game_map[y][x - i] == 'N' || game_map[y][x - i] == 'K' || game_map[y][x - i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x - i)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Dagger!", monster[j].name);
                        monster[j].health -= 12 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x - i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x - 5] = 'd';
    }
}

void magic_wand(int x, int y, Monster *monster, Explorer *explorer)
{
    int way = getch();
    mvprintw(0, 25, "Wow! You throwed a Magic!");

    if (way == 'w')
    {
        int ivalue = 1;
        for (int i = 0; i <= 10 && ivalue; i++)
        {
            if (game_map[y - i][x] == '=' || game_map[y - i][x] == '+' || game_map[y - i][x] == '@' || game_map[y - i][x] == '_')
            {
                game_map[y - i + 1][x] = 'w';
                ivalue = 0;
            }

            else if (game_map[y - i][x] == 'V' || game_map[y - i][x] == 'L' || game_map[y - i][x] == 'N' || game_map[y - i][x] == 'K' || game_map[y - i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y - i && monster[j].x == x)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Magic!", monster[j].name);
                        monster[j].health -= 15 * explorer->power;
                        monster[j].movement = 0;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y - i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y - 10][x] = 'w';
    }

    else if (way == 's')
    {
        int ivalue = 1;
        for (int i = 0; i <= 10 && ivalue; i++)
        {
            if (game_map[y + i][x] == '=' || game_map[y + i][x] == '+' || game_map[y + i][x] == '@' || game_map[y + i][x] == '_')
            {
                game_map[y + i - 1][x] = 'w';
                ivalue = 0;
            }

            else if (game_map[y + i][x] == 'V' || game_map[y + i][x] == 'L' || game_map[y + i][x] == 'N' || game_map[y + i][x] == 'K' || game_map[y + i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y + i && monster[j].x == x)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Magic!", monster[j].name);
                        monster[j].health -= 15 * explorer->power;
                        monster[j].movement = 0;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y + i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y + 10][x] = 'w';
    }

    else if (way == 'd')
    {
        int ivalue = 1;
        for (int i = 0; i <= 10 && ivalue; i++)
        {
            if (game_map[y][x + i] == '|' || game_map[y][x + i] == '+' || game_map[y][x + i] == '@' || game_map[y][x + i] == '/')
            {
                game_map[y][x + i - 1] = 'w';
                ivalue = 0;
            }

            else if (game_map[y][x + i] == 'V' || game_map[y][x + i] == 'L' || game_map[y][x + i] == 'N' || game_map[y][x + i] == 'K' || game_map[y][x + i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x + i)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Magic!", monster[j].name);
                        monster[j].health -= 15 * explorer->power;
                        monster[j].movement = 0;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x + i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x + 10] = 'w';
    }

    else if (way == 'a')
    {
        int ivalue = 1;
        for (int i = 0; i <= 10 && ivalue; i++)
        {
            if (game_map[y][x - i] == '|' || game_map[y][x - i] == '+' || game_map[y][x - i] == '@' || game_map[y][x - i] == '/')
            {
                game_map[y][x - i + 1] = 'w';
                ivalue = 0;
            }

            else if (game_map[y][x - i] == 'V' || game_map[y][x - i] == 'L' || game_map[y][x - i] == 'N' || game_map[y][x - i] == 'K' || game_map[y][x - i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x - i)
                    {
                        mvprintw(0, 25, "Wow! You hit a %s with Magic!", monster[j].name);
                        monster[j].health -= 15 * explorer->power;
                        monster[j].movement = 0;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x - i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x - 10] = 'w';
    }
}

void normal_arrow(int x, int y, Monster *monster, Explorer *explorer)
{
    int way = getch();
    mvprintw(0, 25, "Wow! You throwed a Normal Arrow!");

    if (way == 'w')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y - i][x] == '=' || game_map[y - i][x] == '+' || game_map[y - i][x] == '@' || game_map[y - i][x] == '_')
            {
                game_map[y - i + 1][x] = 'a';
                ivalue = 0;
            }

            else if (game_map[y - i][x] == 'V' || game_map[y - i][x] == 'L' || game_map[y - i][x] == 'N' || game_map[y - i][x] == 'K' || game_map[y - i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y - i && monster[j].x == x)
                    {
                        mvprintw(0, 23, "Wow! You hit a %s with Normal Arrow!", monster[j].name);
                        monster[j].health -= 5 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y - i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y - 5][x] = 'a';
    }

    else if (way == 's')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y + i][x] == '=' || game_map[y + i][x] == '+' || game_map[y + i][x] == '@' || game_map[y + i][x] == '_')
            {
                game_map[y + i - 1][x] = 'a';
                ivalue = 0;
            }

            else if (game_map[y + i][x] == 'V' || game_map[y + i][x] == 'L' || game_map[y + i][x] == 'N' || game_map[y + i][x] == 'K' || game_map[y + i][x] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y + i && monster[j].x == x)
                    {
                        mvprintw(0, 23, "Wow! You hit a %s with Normal Arrow!", monster[j].name);
                        monster[j].health -= 5 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y + i][x] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y + 5][x] = 'a';
    }

    else if (way == 'd')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y][x + i] == '|' || game_map[y][x + i] == '+' || game_map[y][x + i] == '@' || game_map[y][x + i] == '/')
            {
                game_map[y][x + i - 1] = 'a';
                ivalue = 0;
            }

            else if (game_map[y][x + i] == 'V' || game_map[y][x + i] == 'L' || game_map[y][x + i] == 'N' || game_map[y][x + i] == 'K' || game_map[y][x + i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x + i)
                    {
                        mvprintw(0, 23, "Wow! You hit a %s with Normal Arrow!", monster[j].name);
                        monster[j].health -= 5 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x + i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x + 5] = 'a';
    }

    else if (way == 'a')
    {
        int ivalue = 1;
        for (int i = 0; i <= 5 && ivalue; i++)
        {
            if (game_map[y][x - i] == '|' || game_map[y][x - i] == '+' || game_map[y][x - i] == '@' || game_map[y][x - i] == '/')
            {
                game_map[y][x - i + 1] = 'a';
                ivalue = 0;
            }

            else if (game_map[y][x - i] == 'V' || game_map[y][x - i] == 'L' || game_map[y][x - i] == 'N' || game_map[y][x - i] == 'K' || game_map[y][x - i] == 'U')
            {
                for (int j = 0; j < monster_count; j++)
                {
                    if (monster[j].y == y && monster[j].x == x - i)
                    {
                        mvprintw(0, 23, "Wow! You hit a %s with Normal Arrow!", monster[j].name);
                        monster[j].health -= 5 * explorer->power;
                        explorer->score += 1;
                        if (monster[j].health <= 0)
                        {
                            game_map[y][x - i] = '.';
                            mvprintw(0, 65, "Wow! You killed a %s! Score increases!", monster[j].name);
                            explorer->score += 5;
                        }
                        ivalue = 0;
                        break;
                    }
                }
            }
        }
        if (ivalue) game_map[y][x - 5] = 'a';
    }
}

void monster_move(int room, Monster *monster, Explorer_Position *ep)
{
    for (int i = 0; i < monster_count; i++)
    {
        if (monster[i].room == room && monster[i].movement != 0)
        {
            int m_x = monster[i].x;
            int m_y = monster[i].y;
            int x = ep->x;
            int y = ep->y;

            if (!((m_x == x + 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
                (m_x == x - 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
                (m_y == y + 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)) || 
                (m_y == y - 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x))))
            {
                char m = game_map[monster[i].y][monster[i].x];
                game_map[monster[i].y][monster[i].x] = '.';
                
                if (m_x > x)
                {
                    monster[i].x--;
                }
                if (m_x < x)
                {
                    monster[i].x++;
                }
                if (m_y > y)
                {
                    monster[i].y--;
                }
                if (m_y < y)
                {
                    monster[i].y++;
                }
                game_map[monster[i].y][monster[i].x] = m;
                monster[i].movement--;
            }           
        } 
    } 
}

void monster_hit(Monster *monster, Explorer_Position *ep, Explorer *explorer)
{
    for (int i = 0; i < monster_count; i++)
    {
        if (monster[i].health > 0)
        {
            int m_x = monster[i].x;
            int m_y = monster[i].y;
            int x = ep->x;
            int y = ep->y;

            if ((m_x == x + 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
                (m_x == x - 1 && (m_y == y + 1 || m_y == y - 1 || m_y == y)) || 
                (m_y == y + 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)) || 
                (m_y == y - 1 && (m_x == x + 1 || m_x == x - 1 || m_x == x)))
            {
                mvprintw(0, 25, "Opps! The %s hits you! Damage : %d", monster[i].name, monster[i].power);
                explorer->health -= monster[i].power;
            } 
        }          
    }
}

