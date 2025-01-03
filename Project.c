#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char username[100];
    char password[100];
    char email[100];
} Player;

int menu();
void sign_in(Player player);
int ivalue(char username[], char password[], char email[]);
int username_check(char username[]);
int password_check(char password[]);
int email_check(char email[]);
void login(Player player);
int ivalue2(char username[], char password[]);
void settings();
void profile();
void score_table();

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();

    Player player;
    switch (menu())
    {
    case 0:
        sign_in(player);
        break;
    case 1:
        login(player);
        break;
    case 2:
        //settings();
        break;
    case 3:
        //profile();
        break;
    case 4:
        //score_table();
        break;
    }

    char c = getch();
    refresh();
    endwin();
    return 0;
}

int menu()
{
    char menu_options[5][15] = {"Sign In", "Login", "Settings", "Profile", "Score Table"};
    int choice = 0;

    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(12 + i, 53, "%s", menu_options[i]);
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

void sign_in(Player player)
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

        strcpy(player.username, username);
        strcpy(player.password, password);
        strcpy(player.email, email);
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

void login(Player player)
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
                    strcpy(player.username, user); 
                    strcpy(player.password, pass); 
                    strcpy(player.email, "NULL");
                    fclose(players_info);
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
        strcpy(player.username, "Guest"); 
        strcpy(player.password, "NULL"); 
        strcpy(player.email, "NULL");
        clear();
    }
}



