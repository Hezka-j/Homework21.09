#include "Head.h"
#include"Func.h"
using namespace std;
int main()
{
    system("title Maze"); // смена текста в заголовке консольлного окна

    // дескриптор (идентификатор), уникальный номер окна консоли
    //HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    RemoveCursor(100,false);
    // скрываем мигающий курсор в консоли
    

    const int height = 25; // высота
    const int width = 80; // ширина
    int maze[height][width] = {};//заготовка для лабиринта ввиде двумерноо массива заполненного 0

    
    GenerateMaze(maze,width,height);
    PrintMaze(maze,width,height);

    
    //пример установки курсора в любые координаты консоли
    COORD position; // координати гг
    position.X = 0;
    position.Y = 2;

    SetCursor(position.X, position.Y, MAGENTA, "", (char)2);

    COORD heals;
    heals.X = 0;
    heals.Y = 0;
    int coins = 0, health = 100;
    bool ok = true;
    bool norm = true;
    while (true)
    {

        int code = _getch();//get character -получуние кода нажатой клавиши        
        SetCursor(position.X, position.Y, BLACK, "", (char)0);

        if (code == 224)//если нажата какая-то стрелка
        {
            code = _getch();
        }
        if (heals.X > 0 && !ok)
        {
            SetCursor(heals.X, heals.Y, GREEN, "", (char)43);
            ok = true;
        }
        if (code == RIGHT and maze[position.Y][position.X + 1] != WALL) //right               
            position.X++;
        else if (code == LEFT and maze[position.Y][position.X - 1] != WALL)//left           
            position.X--;
        else if (code == UP and maze[position.Y - 1][position.X] != WALL)//up    
            position.Y--;
        else if (code == DOWN and maze[position.Y + 1][position.X] != WALL)//down    
            position.Y++;
        
        SetCursor(position.X, position.Y, MAGENTA, "", (char)2);
        ///////////////////////////////////////////////////////////////////////////////

        SetCursor(width + 2, 1, YELLOW, "COINS:", (char)0);
        SetCursor(width + 8, 1, YELLOW, to_string(coins), (char)0);

        SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
        SetCursor(width + 9, 2, RED, to_string(health), (char)0);

        
        
        if (maze[position.Y][position.X] == COIN)
        {

            coins++;
            maze[position.Y][position.X] = HALL;
            
            SetCursor(width + 2, 1, YELLOW, "COINS:", (char)0);
            SetCursor(width + 8, 1, YELLOW, to_string(coins), (char)0);

        }
        else if (maze[position.Y][position.X] == ENEMY)
        {

            health -= 25;
            maze[position.Y][position.X] = HALL;

            SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
            SetCursor(width + 9, 2, RED, to_string(health), (char)0);

            if (health <= 0)
            {
                DefeatGame();
                main();
            }
        }

        else if (maze[position.Y][position.X] == HEAL)
        {

            if (health == 100)
            {
                if (ok)
                {
                    heals.X = position.X;
                    heals.Y = position.Y;
                    ok = false;
                }

            }
            else
            {
                ok = true;
                health += 25;
                maze[position.Y][position.X] = HALL;
            }
            
            SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
            SetCursor(width + 9, 2, RED, to_string(health), (char)0);
        }
        ///////////////////////////////////////////////////////////////////////////////
        //проверка на выход
        
        if (position.Y == height - 3 and position.X == width - 1)
        {
            WinGame();
            main();
        }

    }

    Sleep(INFINITE);//пауза на 10 сек

    //коридоры - 0
    //стены - 1
    //монетки - 2
    //враги - 3

}
//232 былo 220 стало итого 12 строк