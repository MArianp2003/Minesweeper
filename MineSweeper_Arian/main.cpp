#include <bits/stdc++.h>
#include "clui.h"

using namespace std;

struct propertis_p{
    char name[100];
    int number_of_row = 5;
    int number_of_column = 5;
    char _map[50][50];
    char gaming[50][50];
    int bombs = 4;
    int number_of_flags = bombs;
    int score = 0;
    bool losing = false;
};

struct slot{
    char name[100];
    int number_of_row;
    int number_of_column;
    char _map[50][50];
    char gaming[50][50];
    int bombs = 0;
    int number_of_flags = bombs;
    bool losing = false;
    bool is_clear = true;
    int index_point;
};

slot save_slot[4];
int number_of_users = 1;
int index_of_player = 0;
propertis_p player[10];

void show()
{
    for(int i = 1 ; i < player[index_of_player].number_of_row + 1 ; i++)
    {
        for(int j = 1 ; j < player[index_of_player].number_of_column + 1 ;j++)
        {
            switch(player[index_of_player]._map[i][j])
            {
            case 15:
                change_color_rgb(255 , 112 , 112); // red
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            default :
                change_color_rgb(13 , 239 , 255); // blue
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            }
        }
        cout << endl;
    }
    reset_color();
}

void show_gaming()
{
    for(int i = 1 ; i < player[index_of_player].number_of_row + 1; i++)
    {
        for(int j = 1 ; j < player[index_of_player].number_of_column + 1 ;j++)
        {
            switch(player[index_of_player].gaming[i][j])
            {
            case 15:
                change_color_rgb(255 , 112 , 112); // red
                cout << player[index_of_player].gaming[i][j] << ' ';
                break;
            case 16:
                change_color_rgb(255 , 244 , 87); //yellow
                cout << player[index_of_player].gaming[i][j] << ' ';
                break;
            case 35 :
                change_color_rgb(139 , 247 , 109); //green
                cout << player[index_of_player].gaming[i][j] << ' ';
                break;
            case 48 :
                change_color_rgb(0 , 0 , 0); //invisible
                cout << player[index_of_player].gaming[i][j] << ' ';
                break;
            default :
                change_color_rgb(13 , 239 , 255); // blue
                cout << player[index_of_player].gaming[i][j] << ' ';
                break;
            }
        }
        cout << endl;
    }
    reset_color();
}

void making()
{
    srand(time(NULL));
    for(int i = 0 ; i < player[index_of_player].number_of_row + 2; i++)
        for(int j = 0; j < player[index_of_player].number_of_column + 2 ; j++)
            player[index_of_player]._map[i][j] = 48;
    for(int i = 0 ; i < player[index_of_player].bombs ; i++)
    {
        int x = (rand() % player[index_of_player].number_of_row) + 1;
        int y = (rand() % player[index_of_player].number_of_column) + 1;
        if(player[index_of_player]._map[x][y] != 15)
            player[index_of_player]._map[x][y] = 15;
        else
            i--;
    }
    for(int i = 1 ; i < player[index_of_player].number_of_row + 1; i++)
    {
        for(int j = 1 ; j < player[index_of_player].number_of_column + 1; j++)
        {
            if(player[index_of_player]._map[i][j] != 15)
            {
                int cnt = 0;
                if(player[index_of_player]._map[i - 1][j - 1] == 15)
                    cnt++;
                if(player[index_of_player]._map[i - 1][j] == 15)
                    cnt++;
                if(player[index_of_player]._map[i - 1][j + 1] == 15)
                    cnt++;
                if(player[index_of_player]._map[i][j - 1] == 15)
                    cnt++;
                if(player[index_of_player]._map[i][j + 1] == 15)
                    cnt++;
                if(player[index_of_player]._map[i + 1][j - 1] == 15)
                    cnt++;
                if(player[index_of_player]._map[i + 1][j] == 15)
                    cnt++;
                if(player[index_of_player]._map[i + 1][j + 1] == 15)
                    cnt++;
                player[index_of_player]._map[i][j] += cnt;
            }
        }
    }
    player[index_of_player].number_of_flags = player[index_of_player].bombs;
    for(int i = 0; i < player[index_of_player].number_of_row + 2; i++)
        for(int j = 0; j < player[index_of_player].number_of_column + 2; j++)
            player[index_of_player].gaming[i][j] = '#';
    player[index_of_player].losing = false;
}

void lose()
{
    play_beep();
    clear_screen();
    change_color_rgb(232,201,158);
    cout << "You lost:(\nThe game was : \n\n";
    reset_color();
    show();
    change_color_rgb(232,201,158);
    cout << "\nPress a key to continue...";
    getch();
}

void zero_shower(int x ,int y)
{
    if(player[index_of_player].gaming[x - 1][y - 1] != 16)
        player[index_of_player].gaming[x - 1][y - 1] = player[index_of_player]._map[x - 1][y - 1];
    if(player[index_of_player].gaming[x - 1][y] != 16)
        player[index_of_player].gaming[x - 1][y] = player[index_of_player]._map[x - 1][y];
    if(player[index_of_player].gaming[x - 1][y + 1] != 16)
        player[index_of_player].gaming[x - 1][y + 1] = player[index_of_player]._map[x - 1][y + 1];
    if(player[index_of_player].gaming[x][y - 1] != 16)
        player[index_of_player].gaming[x][y - 1] = player[index_of_player]._map[x][y - 1];
    if(player[index_of_player].gaming[x][y] != 16)
        player[index_of_player].gaming[x][y] = player[index_of_player]._map[x][y];
    if(player[index_of_player].gaming[x][y + 1] != 16)
        player[index_of_player].gaming[x][y + 1] = player[index_of_player]._map[x][y + 1];
    if(player[index_of_player].gaming[x + 1][y - 1] != 16)
        player[index_of_player].gaming[x + 1][y - 1] = player[index_of_player]._map[x + 1][y - 1];
    if(player[index_of_player].gaming[x + 1][y] != 16)
        player[index_of_player].gaming[x + 1][y] = player[index_of_player]._map[x + 1][y];
    if(player[index_of_player].gaming[x + 1][y + 1] != 16)
        player[index_of_player].gaming[x + 1][y + 1] = player[index_of_player]._map[x + 1][y + 1];
}

void open(int x , int y)
{
    if(player[index_of_player]._map[x][y] == 15)
    {
        if(player[index_of_player].gaming[x][y] == 16)
        {
            play_beep();
            cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
            cout << "                                                                               ";
            cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
            change_color_rgb(232,201,158);
            cout << "It's flagged , you can not open this.\n";
            delay(500);
            reset_color();
            cursor_to_pos(x , 2*y - 1);
        }
        else
            player[index_of_player].losing = true;
    }
    else if(player[index_of_player].gaming[x][y] == 16)
    {
        play_beep();
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        cout << "                                                                               ";
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        change_color_rgb(232,201,158);
        cout << "It's flagged , you can not open this.\n";
        delay(500);
        reset_color();
        cursor_to_pos(x , 2*y - 1);
    }
    else if(player[index_of_player].gaming[x][y] != '#')
    {
        play_beep();
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        cout << "                                                                               ";
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        change_color_rgb(232,201,158);
        cout << "It's already opened.\n";
        delay(300);
        reset_color();
        cursor_to_pos(x , 2 * y - 1);
    }
    else
    {
        if(player[index_of_player]._map[x][y] == '0')
        {
            zero_shower(x , y);
            for(int i = 1 ; i < player[index_of_player].number_of_row + 1 ; i++)
                for(int j = 1 ; j < player[index_of_player].number_of_column + 1 ; j++)
                    if(player[index_of_player].gaming[i][j] == '0')
                        zero_shower(i , j);
            for(int i = player[index_of_player].number_of_row ; i >= 1 ; i--)
                for(int j = player[index_of_player].number_of_column ; j >= 1 ; j--)
                    if(player[index_of_player].gaming[i][j] == '0')
                        zero_shower(i , j);
            for(int i = 1 ; i < player[index_of_player].number_of_row + 1 ; i++)
                for(int j = player[index_of_player].number_of_column ; j >= 1 ; j--)
                    if(player[index_of_player].gaming[i][j] == '0')
                        zero_shower(i , j);
            for(int i = player[index_of_player].number_of_row; i >= 1 ; i--)
                for(int j = 1; j < player[index_of_player].number_of_column + 1 ; j++)
                    if(player[index_of_player].gaming[i][j] == '0')
                        zero_shower(i , j);
        }
        else
            player[index_of_player].gaming[x][y] = player[index_of_player]._map[x][y];
        clear_screen();
    }
}

void flag(int x , int y)
{
    if(player[index_of_player].gaming[x][y] == 16)
    {
        player[index_of_player].number_of_flags++;
        player[index_of_player].gaming[x][y] = 35;
        clear_screen();
    }
    else if(player[index_of_player].gaming[x][y] == 35)
    {
        if(player[index_of_player].number_of_flags > 0)
        {
            player[index_of_player].number_of_flags--;
            player[index_of_player].gaming[x][y] = 16;
            clear_screen();
        }
        else
        {
            play_beep();
            cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
            cout << "                                                                                 ";
            cursor_to_pos(player[index_of_player].number_of_column + 13 , 1);
            change_color_rgb(232,201,158);
            cout << "There's no left flag , in order to flag this locatin, unflag the other locations.";
            delay(1500);
            reset_color();
            cursor_to_pos(x , 2*y - 1);
        }
    }
    else
    {
        play_beep();
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        cout << "                                                                               ";
        cursor_to_pos(player[index_of_player].number_of_row + 13 , 1);
        change_color_rgb(232,201,158);
        cout << "You can not flag this one , this is an open location..\n";
        delay(500);
        reset_color();
        cursor_to_pos(x , 2*y - 1);
    }
}

bool winning()
{
    int number_of_dentified = 0;
    for(int i = 1; i < player[index_of_player].number_of_row + 1 ; i++)
    {
        for(int j = 1 ; j < player[index_of_player].number_of_column + 1 ; j++)
        {
            if(player[index_of_player].gaming[i][j] == 16)
                continue;
            else if(player[index_of_player].gaming[i][j] != '#')
                number_of_dentified++;
        }
    }
    if(number_of_dentified == player[index_of_player].number_of_row * player[index_of_player].number_of_column - player[index_of_player].bombs)
        return true;
    else
        return false;
}

void show_winning()
{
    srand(time(NULL));
    for(int i = 1 ; i < player[index_of_player].number_of_row + 1 ; i++)
    {
        int r = 0, g = 0, b = 0;
        for(int j = 1 ; j < player[index_of_player].number_of_column + 1 ;j++)
        {
            switch(player[index_of_player]._map[i][j])
            {
            case 15:
                {
                    switch(rand() % 3)
                    {
                    case 0:
                        r = 255;
                        break;
                    case 1:
                        g = 255;
                        break;
                    case 2:
                        b = 255;
                        break;
                    }
                    if(r != 0)
                    {
                        switch(rand() % 2)
                        {
                        case 0:
                            g = rand() % 256;
                            b = rand() % 151;
                            break;
                        case 1:
                            b = rand() % 256;
                            g = rand() % 151;
                            break;
                        }
                    }
                    else if(g != 0)
                    {
                        switch(rand() % 2)
                        {
                        case 0:
                            r = rand() % 256;
                            b = rand() % 151;
                            break;
                        case 1:
                            b = rand() % 256;
                            r = rand() % 151;
                            break;
                        }
                    }
                    else if(b != 0)
                    {
                        switch(rand() % 2)
                        {
                        case 0:
                            g = rand() % 256;
                            r = rand() % 151;
                            break;
                        case 1:
                            r = rand() % 256;
                            g = rand() % 151;
                            break;
                        }
                    }
                }
                change_color_rgb(r , g , b); // random
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            case 16:
                change_color_rgb(255 , 244 , 87); //yellow
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            case 35 :
                change_color_rgb(139 , 247 , 109); //green
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            default :
                change_color_rgb(13 , 239 , 255); // blue
                cout << player[index_of_player]._map[i][j] << ' ';
                break;
            }
        }
        cout << endl;
    }
    reset_color();
}

void orders()
{
    change_color_rgb(232,201,158);
    cout << endl;
    cout << "How to play : " << endl;
    cout << "Move up : w or W" << endl;
    cout << "Move down : s or S" << endl;
    cout << "Move right : d or D" << endl;
    cout << "Move left : a or A" << endl;
    cout << "Open location : Space" << endl;
    cout << "Save the game : o or O" << endl;
    cout << "Flag or unflag location : f or F" << endl;
    cout << "End the game whitout saving: q or Q" << endl;
    cout << "(keyboard : Eng)" << endl;
    cout << endl;
    reset_color();
}

void change_difficulty(char get_dif)
{
    change_color_rgb(232,201,158);
    switch(get_dif)
    {
    case '1':
        //Easy
        player[index_of_player].bombs = 4;
        player[index_of_player].number_of_row = 5;
        player[index_of_player].number_of_column = 5;
        player[index_of_player].number_of_flags = player[index_of_player].bombs;
        player[index_of_player].losing = false;
        break;
    case '2':
        //Meduim
        player[index_of_player].bombs = 28;
        player[index_of_player].number_of_row = 12;
        player[index_of_player].number_of_column = 12;
        player[index_of_player].number_of_flags = player[index_of_player].bombs;
        player[index_of_player].losing = false;
        break;
    case '3':
        //Hard
        player[index_of_player].bombs = 96;
        player[index_of_player].number_of_row = 20;
        player[index_of_player].number_of_column = 20;
        player[index_of_player].number_of_flags = player[index_of_player].bombs;
        player[index_of_player].losing = false;
        break;
    case '4':
        //Custom
        do
        {
            cursor_to_pos(14 , 1);
            cout << "                                                                             ";
            cursor_to_pos(14 , 1);
            cout << "Enter the number of row (Please enter an integer and min 5 and max 20) : ";
            cin >> player[index_of_player].number_of_row;
            if(!(5 <= player[index_of_player].number_of_row && player[index_of_player].number_of_row <= 20))
                cout << "Invalid amount , try again";
        }while(!(5 <= player[index_of_player].number_of_row && player[index_of_player].number_of_row <= 20));
        do
        {
            cursor_to_pos(15 , 1);
            cout << "                                                                             ";
            cursor_to_pos(15 , 1);
            cout << "Enter the number of column (Please enter an integer min 5 and max 20) : ";
            cin >> player[index_of_player].number_of_column;
            if(!(5 <= player[index_of_player].number_of_column && player[index_of_player].number_of_column <= 20))
                cout << "Invalid amount , try again";
        }while(!(5 <= player[index_of_player].number_of_column && player[index_of_player].number_of_column <= 20));
        do
        {
            cursor_to_pos(16 , 1);
            cout << "                                                                             ";
            cursor_to_pos(16 , 1);
            cout << "Enter the amount of bomb (Please enter an integer and min 4 and max 96 : ";
            cin >> player[index_of_player].bombs;
            if(!(4 <= player[index_of_player].bombs && player[index_of_player].bombs <= 96) || player[index_of_player].bombs >= player[index_of_player].number_of_row * player[index_of_player].number_of_column)
                cout << "Invalid amount , try again";
        }while(!(4 <= player[index_of_player].bombs && player[index_of_player].bombs <= 96) || player[index_of_player].bombs >= player[index_of_player].number_of_row * player[index_of_player].number_of_column);
        break;
    }
    reset_color();
}

int len(char a[])
{
    int i = 0;
    while(a[i] != '\0')
        i++;
    return i;
}

void saving()
{
    clear_screen();
    change_color_rgb(232,201,158);
    int index_of_saving;
    while(1)
    {
        cout << "Which slot do you want to save at (a number between 1 and 4) ? ";
        char c;
        c = getch();
        index_of_saving = c - 49;
        if(save_slot[index_of_saving].is_clear == true)
        {
            save_slot[index_of_saving].index_point = index_of_player;
            save_slot[index_of_saving].is_clear = false;
            save_slot[index_of_saving].bombs = player[index_of_player].bombs;
            save_slot[index_of_saving].number_of_row = player[index_of_player].number_of_row;
            save_slot[index_of_saving].number_of_column = player[index_of_player].number_of_column;
            save_slot[index_of_saving].number_of_flags = player[index_of_player].number_of_flags;
            save_slot[index_of_saving].losing = player[index_of_player].losing;
            for(int i = 0 ; i < player[index_of_player].number_of_row + 2 ; i++)
            {
                for(int j = 0 ; j < player[index_of_player].number_of_column + 2 ; j++)
                {
                    save_slot[index_of_saving]._map[i][j] = player[index_of_player]._map[i][j];
                    save_slot[index_of_saving].gaming[i][j] = player[index_of_player].gaming[i][j];
                }
            }
            for(int i = 0; i < len(player[index_of_player].name) ; i++)
                save_slot[index_of_saving].name[i] = player[index_of_player].name[i];
            break;
        }
        else
        {
            cout << "\nIt is already full , do you want to overwrite it ? 1.Yes 2.No";
            char y_n = getch();
            if(y_n == '1')
            {
                save_slot[index_of_saving].index_point = index_of_player;
                save_slot[index_of_saving].is_clear = false;
                save_slot[index_of_saving].bombs = player[index_of_player].bombs;
                save_slot[index_of_saving].number_of_row = player[index_of_player].number_of_row;
                save_slot[index_of_saving].number_of_column = player[index_of_player].number_of_column;
                save_slot[index_of_saving].number_of_flags = player[index_of_player].number_of_flags;
                save_slot[index_of_saving].losing = player[index_of_player].losing;
                for(int i = 0 ; i < player[index_of_player].number_of_row + 2 ; i++)
                {
                    for(int j = 0 ; j < player[index_of_player].number_of_column + 2 ; j++)
                    {
                        save_slot[index_of_saving]._map[i][j] = player[index_of_player]._map[i][j];
                        save_slot[index_of_saving].gaming[i][j] = player[index_of_player].gaming[i][j];
                    }
                }
            for(int i = 0; i < len(player[index_of_player].name) ; i++)
                save_slot[index_of_saving].name[i] = player[index_of_player].name[i];
            break;
            }
            else
                clear_screen();
        }
    }
}

void game_playing()
{
    bool returning = true;
    int row;
    int column;
    if(player[index_of_player].number_of_column % 2 == 0 || player[index_of_player].number_of_row% 2 == 0)
        row = column = 1;
    else
    {
        row = (player[index_of_player].number_of_row + 1) / 2;
        column = player[index_of_player].number_of_column;
    }
    while(returning) // if this while ends , then this playing game is ended , whether losing or winning
    {
        clear_screen();
        cursor_to_pos(1,1);
        show_gaming();
        orders();
        cursor_to_pos(row , column);
        char choice;
        while(1) // entrance from key board
        {
            choice = getch();
            if(choice == 'W' || choice == 'w')
            {
                if(row == 1) row = player[index_of_player].number_of_row;
                else row -= 1;
            }
            else if(choice == 'A' || choice == 'a')
            {
                if(column == 1) column = player[index_of_player].number_of_column * 2 - 1;
                else column -= 2;
            }
            else if(choice == 'S' || choice == 's')
            {
                if(row == player[index_of_player].number_of_row) row = 1;
                else row += 1;
            }
            else if(choice == 'D' || choice == 'd')
            {
                if(column == player[index_of_player].number_of_column * 2 - 1) column = 1;
                else column += 2;
            }
            else if(choice == 'q' || choice == 'Q' || choice == 32 || choice == 'F' || choice == 'f' || choice == 'O' || choice == 'o')
            {
                break;// it's going to flag or open the selected cell
            }
            else
            {
                play_beep();
                cursor_to_pos((player[index_of_player].number_of_row + 13) , 1);
                cout << "                                                                                 ";
                cursor_to_pos((player[index_of_player].number_of_row + 13) , 1);
                change_color_rgb(232,201,158);
                cout << "Invalid key! please try again.";
                delay(200);
                reset_color();
                cursor_to_pos(row , column);
            }
            cursor_to_pos(row , column);
        }
        switch(choice)
        {
        case 32:
            open(row , (column + 1) / 2);
            break;
        case 'F':
        case 'f':
            flag(row , (column + 1) / 2);
            break;
        case 'O':
        case 'o':
            saving();
            returning = false;
            break;
        case 'Q':
        case 'q':
            return;
            break;
        }
        if(winning())
        {
            clear_screen();
            change_color_rgb(232,201,158);
            cout << "Well done! , you won :)\nThe game was : \n\n";
            reset_color();
            show_winning();
            change_color_rgb(232,201,158);
            int n = (player[index_of_player].number_of_row + player[index_of_player].number_of_column) / 2;
            player[index_of_player].score += ( n * n * n / 5 ) * pow((5 * sqrt(player[index_of_player].bombs) / (2 * n)) , n / 2 );
            cout << "\nPress a key to continue...";
            getch();
            break; // out of the while and the game is ended
        }
        if(player[index_of_player].losing)
        {
            lose();
            break; // out of the while and the game is ended
        }
    }
}

bool comparing(char a[] , char b[])
{
    if(len(a) != len(b))
        return false;
    for(int i = 0 ; i < len(a) ; i++)
        if(a[i] != b[i])
            return false;
    return true;
}

void change_name()
{

    clear_screen();
    change_color_rgb(232,201,158);
    char tmp[50];
    cout << "Enter your name : ";
    cin.getline(tmp , 50);
    bool flag = true;
    for(int i = 0; i < number_of_users ; i++)
    {
        if(comparing(tmp , player[i].name))
        {
            index_of_player = i;
            flag = false;
            break;
        }
    }
    if(flag)
    {
        number_of_users++;
        index_of_player = number_of_users - 1;
        for(int i = 0; i < len(tmp) ; i++)
            player[index_of_player].name[i] = tmp[i];
    }
    reset_color();
}

void load_game(char which_cell)
{
    //loading and clearing slot
    index_of_player = save_slot[which_cell - 49].index_point;
    player[index_of_player].bombs = save_slot[which_cell - 49].bombs;
    player[index_of_player].number_of_row = save_slot[which_cell - 49].number_of_row;
    player[index_of_player].number_of_column = save_slot[which_cell - 49].number_of_column;
    player[index_of_player].number_of_flags = save_slot[which_cell - 49].number_of_flags;
    for(int i = 0 ; i < save_slot[which_cell - 49].number_of_row + 2; i++)
    {
        for(int j = 0 ; j < save_slot[which_cell - 49].number_of_column + 2; j++)
        {
            player[index_of_player].gaming[i][j] = save_slot[which_cell - 49].gaming[i][j];
            player[index_of_player]._map[i][j] = save_slot[which_cell - 49]._map[i][j];
        }
    }
    for(int i = 0 ; i < len(save_slot[which_cell - 49].name) ; i++)
        player[index_of_player].name[i] = save_slot[which_cell - 49].name[i];
    save_slot[which_cell - 49].is_clear = true;
}

void leaderboard()
{
    clear_screen();
    change_color_rgb(232,201,158);
    int tmp_score[10];
    int tmp_index_player[10];
    for(int i = 0; i < 10 ; i++)
    {
        tmp_score[i] = player[i].score;
        tmp_index_player[i] = i;
    }
    for(int i = 0; i < 10 ; i++)
    {
        for(int j = i + 1 ; j< 10 ; j++)
        {
            if(tmp_score[i] < tmp_score[j])
            {
                int t = tmp_score[i];
                tmp_score[i] = tmp_score[j];
                tmp_score[j] = t;
                t = tmp_index_player[i];
                tmp_index_player[i] = tmp_index_player[j];
                tmp_index_player[j] = t;
            }
        }
    }
    cout << "Name                         Score" << endl << endl;
    for(int i = 0 ; i < 5 ; i++)
    {
        if(tmp_score[i] != 0)
        {
            cout << i + 1 << "." << player[tmp_index_player[i]].name;
            cursor_to_pos(i + 3 , 30);
            cout << tmp_score[i] << endl;
        }
    }
    cout << endl << endl;
    cout << "Press a key to continue...";
    getch();
}

int main()
{
    init_clui();
    for(int i = 0; i < 10 ; i++)
        for(int j = 0; j < 50 ; j++)
            player[i].name[j] = 0;
    change_color_rgb(210 , 235 , 52);
    cout << "Welcome to minesweeper:)" << endl;
    cout << "press a key to start" << endl;
    reset_color();
    getch();
    clear_screen();
    change_color_rgb(232,201,158);
    cout << "Enter your name : ";
    cin.getline(player[index_of_player].name , 50);
    reset_color();
    while(1)
    {
        //Menu
        clear_screen();
        change_color_rgb(232,201,158);
        cout << "Player : " << player[index_of_player].name << endl << endl;
        cout << "1.New game" << endl;
        cout << "2.Load game" << endl;
        cout << "3.Change name" << endl;
        cout << "4.Leaderboard" << endl;
        cout << "5.Quit" << endl;
        reset_color();
        char selected_menu = getch();
        if(selected_menu == '1')
        {
            //New game
            change_color_rgb(232,201,158);
            cout << endl;
            cout << "1.Easy (5 * 5 & 4 bombs)" << endl;
            cout << "2.Medium (12 * 12 & 28 bombs)" << endl;
            cout << "3.Hard (20 * 20 & 96 bombs)" << endl;
            cout << "4.Manual Adjusment" << endl;
            char get_dif = getch();
            do
            {
                if((get_dif == '1' || get_dif == '2' || get_dif == '3' || get_dif == '4'))
                {
                    change_difficulty(get_dif);
                }
                else
                {
                    change_color_rgb(232,201,158);
                    cursor_to_pos(14 , 1);
                    cout << "Invalid key!Try again";
                    delay(300);
                    cursor_to_pos(14 , 1);
                    cout << "                                                              ";
                    cursor_to_pos(14 , 1);
                    reset_color();
                    get_dif = getch();
                }
            }while(!(get_dif == '1' || get_dif == '2' || get_dif == '3' || get_dif == '4'));
            making();
            game_playing();
        }
        else if(selected_menu == '2')
        {
            //Load game
            change_color_rgb(232,201,158);
            while(1)
            {
                clear_screen();
                cout << "Which slot do you want to load (Please enter and integer netween 1 and 4 and to quit press Q or q) : ";
                char which_slot;
                which_slot = getch();
                if('1' <= which_slot && which_slot <= '4')
                {
                    if(save_slot[which_slot - 49].is_clear)
                    {
                        cout << "\nThis slot is empty , find a full one";
                        delay(400);
                    }
                    else
                    {
                        load_game(which_slot);
                        game_playing();
                        break;
                    }
                }
                else if(which_slot == 'q' || which_slot == 'Q')
                    break;
                else
                {
                    cout << "\nInvalid key , try again";
                    delay(400);
                }
            }
            reset_color();
        }
        else if(selected_menu == '3')
        {
            //Change game
            change_name();
        }
        else if(selected_menu == '4')
        {
            //Leaderboard
            leaderboard();
        }
        else if(selected_menu == '5')
        {
            //Quit
            break; // out of the while and ends program
        }
        else
        {
            cursor_to_pos(9 , 1);
            change_color_rgb(232,201,158);
            cout << "Invalid key! Try again";
            reset_color();
            delay(200);
        }
    }
}
