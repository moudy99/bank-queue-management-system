//#include <iostream>
#include <windows.h>
#include <conio.h>
#include <queue>
#include "Customer.h"
#include "Bank.h"
using namespace std;



//////////CHange the cursor
COORD coord = { 0, 0 };

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Function of change color ==>
void color(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

// hide the cursor -->
void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//show cursor
void show_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; // The size of the cursor
    info.bVisible = TRUE; // Make the cursor visible
    SetConsoleCursorInfo(consoleHandle, &info);
}

////// Display MEnu function --->
int display_menu(string& title, vector<string>& options, int x, int y, int xx) {
    int selected_option = 0;
    int keypressed;
    do {
        hide_cursor();
        system("cls");
        color(7);
        gotoxy(x, y);
        //Display the title of menu ==>
        cout << title << endl;
        for (int i = 0; i < options.size(); i++) {
            gotoxy(x + xx, y + (i + 2) * 2); // change the position ===>
            if (selected_option == i) {
                color(10); // Color for the select option
                cout << ">";
            }
            else {
                color(12); // COlor fot the rest of options
            }
            cout << " " + options[i];
        }

        keypressed = _getch();
        //get the preeeese key ==>
        if (keypressed == 224) {
            keypressed = _getch();
            /////// Key up ==>
            if (keypressed == 72) {
                if (selected_option > 0) {
                    selected_option--;
                }
                else {
                    selected_option = (int)options.size() - 1;
                }
            }
            //.///.// For press down
            else if (keypressed == 80) {
                if (selected_option < (int)options.size() - 1) {
                    selected_option++;
                }
                else {
                    selected_option = 0;
                }
            }
        }
        else if (keypressed == 13) {
            return selected_option;
        }

    } while (true);
}


///////////////////////////////////////////////////////////////////////////////////////

int main() {

    Bank CIB_bank;

    CIB_bank.Add(5, 4, false);
    CIB_bank.Add(14, 3, true);
    CIB_bank.Add(11, 2, false);
    CIB_bank.Add(8, 5, false);
    CIB_bank.Add(9, 6, false);
    CIB_bank.Add(3, 7, false);
    CIB_bank.Add(15, 8, false);
    CIB_bank.Add(2, 4, true);
    CIB_bank.Add(7, 3, false);
    CIB_bank.Add(4, 2, false);
    CIB_bank.Add(6, 1, false);
    CIB_bank.Add(1, 5, false);
    CIB_bank.Add(10, 3, true);
    CIB_bank.Add(12, 6, false);
    CIB_bank.Add(13, 7, false);
    CIB_bank.Add(15, 8, false);





    CIB_bank.Start_simulation();




    return 0;
}


