#include <ncurses.h>

int menu();
void sign_in();
void login();
void settings();
void profile();
void score_table();

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    switch (menu())
    {
    case 0:
        sign_in();
        break;
    case 1:
        login();
        break;
    case 2:
        settings();
        break;
    case 3:
        profile();
        break;
    case 4:
        score_table();
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

    clear();
    return choice;
}