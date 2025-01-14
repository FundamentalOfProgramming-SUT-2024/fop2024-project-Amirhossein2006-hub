#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char username[100];
    char password[100];
    char email[100];
    int score;
    int gold;
    int finished_games;
    int experience;
} Player;

typedef struct
{
    int difficulty;
    int color;
} Game;

typedef struct
{
    char temp[1000];
    int score;
} Score;

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

// typedef struct
// {
//     int x1_start;
//     int x1_end;
//     int y1_start;
//     int y1_end;
//     int x1_renge;
//     int y1_renge;
// } Map;

char game_map[30][120];
char floor1[30][120];
char floor2[30][120];
char floor3[30][120];
char floor4[30][120];

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
//int random(int a, int b);
//void map_maker(Map *map);
void load_map(int i, Explorer_Position *ep);
void print_map(Explorer_Position *ep, Explorer *explorer, Game game);
void move_ivalue(int move, Explorer_Position *ep);
void new_game(Explorer_Position *ep, Explorer *explorer);
void trap(Explorer_Position *ep, Explorer *explorer);
void stair(Explorer *explorer, Explorer_Position *ep);
int stair_check(Explorer *explorer, Explorer_Position *ep);
int move_ivalue_help(Explorer_Position *ep);


int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();

    Player player;
    Game game;
    //Map map;
    Explorer_Position ep;
    Explorer explorer;
    game.difficulty = 0;
    game.color = 0;

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
            new_game(&ep, &explorer);
            break;
        }
        case 1:
            //resume(player);
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

        if (choice < 1) break;
    }

    while (1)
    {
        print_map(&ep, &explorer, game);
        trap(&ep, &explorer);
        int move;

        if (game_map[ep.y][ep.x] == '>') move = stair_check(&explorer, &ep);
        else move = tolower(getch());

        move_ivalue(move, &ep);
        clear();
    }

    char c = getch();
    refresh();
    endwin();
    return 0;
}

int menu()
{
    char menu_options[5][15] = {"Sign In", "Login"};
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

    echo();
    curs_set(TRUE);

    mvprintw(11, 50, "Username: ");
    mvprintw(12, 50, "Password: ");
    mvprintw(13, 50, "Email: ");
    mvgetstr(11, 60, username);
    mvgetstr(12, 60, password);
    mvgetstr(13, 57, email);
    
    noecho();
    curs_set(FALSE);

    if (ivalue(username, password, email) == 0) sign_in(player);
    else
    {
        FILE *players_info = fopen("Players_Info.txt", "a");
        fprintf(players_info, "username: (%s), password: (%s), email: (%s)\n", username, password, email);
        fclose(players_info);

        FILE *players_score = fopen("Players_Score.txt", "a");
        fprintf(players_score, "Username: (%s), Score: (0), Gold Aquared: (0), Finished Games: (0), Time Played: (0)\n", username);
        fclose(players_score);

        strcpy(player->username, username);
        strcpy(player->password, password);
        strcpy(player->email, email);
        player->score = 0;
        player->gold = 0;
        player->experience = 0;
        player->finished_games = 0;
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
    FILE *players_info = fopen("Players_Info.txt", "r");

    char temp[1000];
    while (fgets(temp, sizeof(temp), players_info))
    {
        char user[100];
        int j = 0;
        for (int i = 11; temp[i] != ')'; i++)
            user[j++] = temp[i];
        
        user[j] = '\0';
        if (strcmp(user, username) == 0)
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
    mvprintw(11, 50, "Username: ");
    mvprintw(12, 50, "Password: ");

    int c = getch();
    if (c == KEY_DOWN)
    {
        mvprintw(9, 35, "Login as guest (if you don't want just press down key)");
        echo();
        curs_set(TRUE);
        mvgetstr(11, 60, username);
        mvgetstr(12, 60, password);
        noecho();
        curs_set(FALSE);
        FILE *players_info = fopen("Players_Info.txt", "r");

        char temp[1000];
        while (fgets(temp, sizeof(temp), players_info))
        {
            char user[100], pass[100];
            int j = 0, k = 0;
            for (int i = 11; temp[i] != ')'; i++)
                user[j++] = temp[i];
            user[j] = '\0';

            if (strcmp(user, username) == 0)
            {
                for (int i = 25 + j; temp[i] != ')'; i++)
                    pass[k++] = temp[i];
                pass[k] = '\0';

                if (strcmp(pass, password) == 0)
                {
                    strcpy(player->username, user); 
                    strcpy(player->password, pass); 
                    strcpy(player->email, "NULL");
                    fclose(players_info);

                    FILE *players_score = fopen("Players_Score.txt", "r");
                    char a[100];
                    int b, c, d, e;
                    while (fscanf(players_score, "Username: (%99[^)]), Score: (%d), Gold Aquared: (%d), Finished Games: (%d), Time Played: (%d)", a, &b, &c, &d, &e))
                    {
                        if (strcmp(user, a) == 0)
                        {
                            player->score = b;
                            player->gold = c;
                            player->finished_games = d;
                            player->experience = e;
                        }
                    }
                    
                    fclose(players_score);
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
        strcpy(player->username, "Guest"); 
        strcpy(player->password, "NULL"); 
        strcpy(player->email, "NULL");

        player->score = 0;
        player->gold = 0;
        player->finished_games = 0;
        player->experience = 0;

        // FILE *players_info = fopen("Players_Info.txt", "a");
        // fprintf(players_info, "username: (%s), password: (%s), email: (%s)\n", player->username, player->password, player->email);
        // fclose(players_info);

        // FILE *players_score = fopen("Players_Score.txt", "a");
        // fprintf(players_score, "Username: (%s), Score: (0), Gold Aquared: (0), Finished Games: (0), Time Played: (0)\n", player->username);
        // fclose(players_score);

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
    Score players[100];
    int counter = 0;
    FILE *players_score = fopen("Players_Score.txt", "r");

    char temp[1000];
    while (fgets(temp, sizeof(temp), players_score))
    {
        char score[100];
        int j = 0, k = 0;
        for (int i = 11; temp[i] != ')'; i++)
            j++;

        for (int i = 22 + j; temp[i] != ')'; i++)
            score[k++] = temp[i];
        score[k] = '\0';

        Score s;
        strcpy(s.temp, temp);
        s.score = strtol(score, NULL, 10);
        players[counter++] = s;
    }
    fclose(players_score);
    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                Score t = players[j];
                players[j] = players[j + 1];
                players[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < counter; i++)
    {
        char user[100];
        int k = 0;
        for (int j = 11; players[i].temp[j] != ')'; j++)
            user[k++] = players[i].temp[j];
        
        user[k] = '\0';

        if (i < 3)
            attron(COLOR_PAIR(i + 1));

        if (strcmp(user, player->username) == 0)
            mvprintw(2 + 2 * i, 2, "->");

        mvprintw(2 + 2 * i, 5, "(%d) %s", i + 1, players[i].temp);

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
    mvprintw(5, 5, "Score: %d", player->score);
    mvprintw(7, 5, "Gold Aquared: %d", player->gold);
    mvprintw(9, 5, "Finished Games: %d", player->finished_games);
    mvprintw(11, 5, "Experience: %d", player->experience);

    attron(A_REVERSE);
    mvprintw(0, 0, "Press Any Key To Back");
    attroff(A_REVERSE);

    getch();
}

// int random(int a, int b)
// {
//     return rand() % (b - a + 1) + a;
// }

// void map_maker(Map *map)
// {
//     map->x1_start = random(10, 100);
//     map->y1_start = random(5, 15);
//     map->x1_renge = random(4, 10);
//     map->y1_renge = random(4, 10);
// }

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
    while (fgets(temp, sizeof(temp), map))
    {
        if (counter % 2 == 0)
        {
            for (int i = 0; i < 120; i++)
            {   
                if (temp[i] == 'X')
                {
                    ep->x = i;
                    ep->y = counter / 2;
                    if (k > 1) temp[i] = '<';
                    else temp[i] = '.';
                }

                game_map[counter / 2][i] = temp[i];
            }
        }
        counter++;
    }

    fclose(map);
}

void print_map(Explorer_Position *ep, Explorer *explorer, Game game)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            if (game_map[i][j] == '-') printw(" ");
            else if (game_map[i][j] == 'T') printw(".");
            else printw("%c", game_map[i][j]);
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

void move_ivalue(int move, Explorer_Position *ep)
{
    if (move == 's')
    {
        if (move_ivalue_help(ep) && game_map[ep->y + 1][ep->x] != '_' && game_map[ep->y + 1][ep->x] != 'O') ep->y++;
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] == '.')) ep->y++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y + 1][ep->x] == '#' || game_map[ep->y + 1][ep->x] == '+')) ep->y++;
    }

    else if (move == 'w')
    {
        if (move_ivalue_help(ep) && game_map[ep->y - 1][ep->x] != '_' && game_map[ep->y - 1][ep->x] != 'O') ep->y--;
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] == '.')) ep->y--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y - 1][ep->x] == '#' || game_map[ep->y - 1][ep->x] == '+')) ep->y--;
    }

    else if (move == 'd')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y][ep->x + 1] != 'O') ep->x++;
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] == '.')) ep->x++;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x + 1] == '#' || game_map[ep->y][ep->x + 1] == '+')) ep->x++;
    }

    else if (move == 'a')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y][ep->x - 1] != 'O') ep->x--;
        else if (game_map[ep->y][ep->x] == '+' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] == '.')) ep->x--;
        else if (game_map[ep->y][ep->x] == '#' && (game_map[ep->y][ep->x - 1] == '#' || game_map[ep->y][ep->x - 1] == '+')) ep->x--;
    }

    else if (move == 'c')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y + 1][ep->x] != '_' && game_map[ep->y + 1][ep->x + 1] != 'O')
        {
            ep->x++;
            ep->y++;
        }
    }

    else if (move == 'z')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y + 1][ep->x] != '_' && game_map[ep->y + 1][ep->x - 1] != 'O')
        {
            ep->y++;
            ep->x--;
        }
    }

    else if (move == 'e')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x + 1] != '|' && game_map[ep->y - 1][ep->x] != '_' && game_map[ep->y - 1][ep->x + 1] != 'O')
        {
            ep->x++;
            ep->y--;
        }
    }

    else if (move == 'q')
    {
        if (move_ivalue_help(ep) && game_map[ep->y][ep->x - 1] != '|' && game_map[ep->y - 1][ep->x] != '_' && game_map[ep->y - 1][ep->x - 1] != 'O')
        {
            ep->y--;
            ep->x--;
        }
    }
}

void new_game(Explorer_Position *ep, Explorer *explorer)
{
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

void stair(Explorer *explorer, Explorer_Position *ep)
{
    FILE *map;
    int floor = explorer->level;
    explorer->level++;

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

    //game_map[ep->y][ep->x] = 'X';
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 120; j++) {
            fprintf(map, "%c", game_map[i][j]);
        }
        fprintf(map, "\n");
    }

    fclose(map);
    load_map(floor + 1, ep);
}

int stair_check(Explorer *explorer, Explorer_Position *ep)
{
    mvprintw(0, 25, "Wow! You reached the stair, press 'U' to go up!");
    int move = tolower(getch());

    if (move == 'u') stair(explorer, ep);
    else return move;
}

int move_ivalue_help(Explorer_Position *ep)
{
    if (game_map[ep->y][ep->x] == '.' || 
        game_map[ep->y][ep->x] == '^' ||
        game_map[ep->y][ep->x] == '>' || 
        game_map[ep->y][ep->x] == '<')
        return 1;

    else return 0;
}



