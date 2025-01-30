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
    int health;
    int score;
    int experience;
    int gold;
    int level;
} Explorer;

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
} Weapon_Count;

typedef struct
{
    Weapon_Count weapons[10];
    int count;
} Weapon;

typedef struct
{
    char spell[20];
    int count;
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
    char name[10];
    int health;
    int movement;
} Monster;

char game_map[30][120];
clock_t start;
clock_t start_code;
int code, num_of_mistakes;
int ancient_key_value;

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
void load_map(int i, Explorer_Position *ep);
void whitch_room(Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
void print_room(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6);
void print_corridor(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5);
void print_map(Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Rooms room);
void print_map2(Explorer_Position *ep, Explorer *explorer, Game game, Corridors corridor);
void move_ivalue(int move, Explorer_Position *ep, Explorer *explorer, Game game, Rooms room1, Rooms room2, Rooms room3, Rooms room4, Rooms room5, Rooms room6, Corridors corridor1, Corridors corridor2, Corridors corridor3, Corridors corridor4, Corridors corridor5);
void move_ivalue2(int move, Explorer_Position *ep);
void new_game(Explorer_Position *ep, Explorer *explorer);
void trap(Explorer_Position *ep, Explorer *explorer);
void stair(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
void stair_save(Explorer *explorer, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
int stair_check(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5);
int move_ivalue_help(Explorer_Position *ep);
void foods(Explorer_Position *ep, Explorer *explorer, Food *food);
void find_food(char name[], Food *food);
int food_show(Food *food);
void gold(Explorer_Position *ep, Explorer *explorer);
void black_gold(Explorer_Position *ep, Explorer *explorer);
void weapons(Explorer_Position *ep, Explorer *explorer, Weapon *weapon);
void find_weapon(char name[], Weapon *weapon);
void weapon_show(Weapon weapon);
void spells(Explorer_Position *ep, Explorer *explorer, Spell *spell);
void find_spell(char name[], Spell *spell);
void spell_show(Spell spell);
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
void load_game(int *ex, Explorer_Position *ep, Explorer *explorer, Player *player);
void random_password(int length, char password[]);

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

    game.difficulty = 0;
    game.color = 0;
    food.count = 0;
    weapon.count = 1;
    strcpy(weapon.weapons[0].weapon, "Mace");
    weapon.weapons[0].count = 1;
    spell.count = 0;
    code = 1000;
    ancient_key_value = 0;
    int ex = 0;
    srand(time(NULL));

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
            new_game(&ep, &explorer);
            break;
        }
        case 1:
            if(player.save_game) load_game(&ex, &ep, &explorer, &player);
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

        if (game_map[ep.y][ep.x] == '>' || game_map[ep.y][ep.x] == '<') move = stair_check(&explorer, &ep, &room1, &room2, &room3, &room4, &room5, &room6, &corridor1, &corridor2, &corridor3, &corridor4, &corridor5);
        else move = tolower(getch());

        if (move == 'i')
        { 
            weapon_show(weapon);
            step_counter--;
        }
        else if (move == 'o')
        {
            spell_show(spell);
            step_counter--;
        }
        else if (move == 'p')
        {
            if (food_show(&food))
            {
                clear();
                print_room(&ep, &explorer, game, room1, room2, room3, room4, room5, room6);
                print_corridor(&ep, &explorer, game, corridor1, corridor2, corridor3, corridor4, corridor5);
                mvprintw(0, 25, "Wow! You eat a food!");
                if (explorer.health <= 90) explorer.health += 10;
                else explorer.health = 100;
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
        else move_ivalue(move, &ep, &explorer, game, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
        clear();

        explorer.experience = ((time(NULL) - start) / 60) + ex; 
        step_counter++;
        if (step_counter % 10 == 0)
        {
            explorer.health -= 2;
        }

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

void load_map(int k, Explorer_Position *ep)
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
                attron(COLOR_PAIR(5));
                mvprintw(i, j, "B");
                attroff(COLOR_PAIR(5));
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

            else if (game_map[i][j] == 'H' ||
                     game_map[i][j] == 'Z' ||
                     game_map[i][j] == 'C')
            {
                attron(COLOR_PAIR(3));
                mvprintw(i, j, "%c", game_map[i][j]);
                attroff(COLOR_PAIR(3));
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
    
    mvprintw(29, 15, "Health : %d", explorer->health);
    mvprintw(29, 35, "Score : %d", explorer->score);
    mvprintw(29, 50, "Level : %d", explorer->level);
    mvprintw(29, 65, "Gold : %d", explorer->gold);
    mvprintw(29, 80, "Experience : %d", explorer->experience);
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
        if (move_ivalue_help(ep) && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x] != 'O') 
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
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] != '|')) ep->y++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] == '+')) ep->y++;
    }

    else if (move == 'w')
    {
        if (move_ivalue_help(ep) && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x] != 'O')
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
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] != '|')) ep->y--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] == '+')) ep->y--;
    }

    else if (move == 'd')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y][ep->x + 1] != 'O')
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
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] != '=')) ep->x++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] == '+')) ep->x++;
    }

    else if (move == 'a')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y][ep->x - 1] != 'O')
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
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] != '=')) ep->x--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] == '+')) ep->x--;
    }

    else if (move == 'c')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x + 1] != 'O')
        {
            ep->x++;
            ep->y++;
        }
    }

    else if (move == 'z')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y + 1][ep->x] != '=' && game_map[ep->y + 1][ep->x - 1] != 'O')
        {
            ep->y++;
            ep->x--;
        }
    }

    else if (move == 'e')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x + 1] != 'O')
        {
            ep->x++;
            ep->y--;
        }
    }

    else if (move == 'q')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y - 1][ep->x] != '=' && game_map[ep->y - 1][ep->x - 1] != 'O')
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

void new_game(Explorer_Position *ep, Explorer *explorer)
{
    start = time(NULL);
    clear();
    load_map(1, ep);
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

void stair(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
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
    load_map(explorer->level, ep);
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

int stair_check(Explorer *explorer, Explorer_Position *ep, Rooms *room1, Rooms *room2, Rooms *room3, Rooms *room4, Rooms *room5, Rooms *room6, Corridors *corridor1, Corridors *corridor2, Corridors *corridor3, Corridors *corridor4, Corridors *corridor5)
{
    if (game_map[ep->y][ep->x] == '>') mvprintw(0, 25, "Wow! You reached the stair, press 'U' to go up!");
    else mvprintw(0, 25, "Wow! You reached the stair, press 'U' to go down!");
    int move = tolower(getch());

    if (move == 'u') stair(explorer, ep, room1, room2, room3, room4, room5, room6, corridor1, corridor2, corridor3, corridor4, corridor5);
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
    win = newwin(12, 25, 10, 45); 

    if (food->count > 0)
    {   
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

            for (int i = 0; i < food->count; i++)
            {
                mvwprintw(win, 1 + i, 5, "%s", food->foods[i].food);
                mvwprintw(win, 1 + i, 20, "(%d)", food->foods[i].count);
            }
            mvwprintw(win, 1 + food->count, 5, "Back");
            mvwprintw(win, 1 + choice, 2, "->");
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
        mvwprintw(win, 0, 0, "-------------------------");
        mvwprintw(win, 11, 0, "-------------------------");
        for (int i = 0; i < 12; i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, 24, "|");
        }
        mvwprintw(win, 5, 9, "NO FOOD!");
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
    int ivalue = 0;
    for (int i = 0; i < weapon->count; i++)
    {
        if (strcmp(weapon->weapons[i].weapon, name) == 0)
        {
            ivalue = 1;
            weapon->weapons[i].count++;
        }
    }
    if (ivalue == 0)
    {
        strcpy(weapon->weapons[weapon->count].weapon, name);
        weapon->weapons[weapon->count++].count = 1;
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
}

void weapon_show(Weapon weapon)
{
    WINDOW *win;
    win = newwin(12, 25, 10, 45);    

    for (int i = 0; i < weapon.count; i++)
    {
        mvwprintw(win, 1 + i, 2, "%s", weapon.weapons[i].weapon);
        mvwprintw(win, 1 + i, 20, "(%d)", weapon.weapons[i].count);
    }

    mvwprintw(win, 0, 0, "-------------------------");
    mvwprintw(win, 11, 0, "-------------------------");
    for (int i = 0; i < 12; i++)
    {
        mvwprintw(win, i, 0, "|");
        mvwprintw(win, i, 24, "|");
    }

    wrefresh(win);
    getch();
    delwin(win);
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
        spell->spells[spell->count++].count = 1;
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

void spell_show(Spell spell)
{
    WINDOW *win;
    win = newwin(12, 25, 10, 45);    

    for (int i = 0; i < spell.count; i++)
    {
        mvwprintw(win, 1 + i, 2, "%s", spell.spells[i].spell);
        mvwprintw(win, 1 + i, 20, "(%d)", spell.spells[i].count);
    }

    mvwprintw(win, 0, 0, "-------------------------");
    mvwprintw(win, 11, 0, "-------------------------");
    for (int i = 0; i < 12; i++)
    {
        mvwprintw(win, i, 0, "|");
        mvwprintw(win, i, 24, "|");
    }

    wrefresh(win);
    getch();
    delwin(win);
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

void load_game(int *ex, Explorer_Position *ep, Explorer *explorer, Player *player)
{
    start = time(NULL);
    clear();
    load_map(player->level, ep);
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

