// enumeration - перечисление
	// набор целочисленных констант
	// читаемость кода существенно повышается
enum Colors { BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };
enum Keys { LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, ENTER = 13, ESCAPE = 27, SPACE = 32 };
enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, HEAL = 4 };
void SetCursor(int x, int y, Colors color, string text, char t)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, color);
	cout << text;
	cout << t;
	cout << "\n";
}
void RemoveCursor(int dwSize, bool bVisible)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100; // 1...100
	SetConsoleCursorInfo(h, &info);
}
void GenerateMaze(int maze[][80], int width,int height)
{
    srand(time(0));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            maze[y][x] = rand() % 5;
            // установка стен по бокам (делаем рамки)
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
            {
                maze[y][x] = WALL;


            }
            //определение точки входа и выхода из лабиринта
            if (x == 0 && y == 2 || x == width - 1 && y == height - 3 || x == width - 2 && y == height - 3 || x == 1 && y == 2 || x == 2 && y == 2)
            {
                maze[y][x] = HALL;
            }
            if (maze[y][x] == ENEMY)
            {
                int r;
                r = rand() % 10;
                if (r != 0)
                {
                    maze[y][x] = HALL;
                }
            }
            else if (maze[y][x] == HEAL)
            {
                int j;
                j = rand() % 20;
                if (j != 0)
                {
                    maze[y][x] = HALL;
                }
            }          
        }
        
    }
}
void PrintMaze(int maze[][80],int width,int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (maze[y][x] == HALL)
            {
                SetCursor(x, y, BLACK, "", (char)0);
            }
            else if (maze[y][x] == WALL)
            {
                SetCursor(x, y, WHITE, "", (char)178);
            }
            else if (maze[y][x] == COIN)
            {
                SetCursor(x, y, YELLOW, "", (char)46);
            }
            else if (maze[y][x] == ENEMY)
            {
                SetCursor(x, y, RED, "", (char)1);
            }
            else if (maze[y][x] == HEAL)
            {
                SetCursor(x, y, GREEN, "", (char)43);
            }
        }
        cout << "\n";
    }
}

void DefeatGame()
{
    int answer;
    answer = MessageBoxA(0, "You death", "Loser", MB_YESNO);
    system("cls");
    if (answer == IDYES)
    {
        int great;
        great = MessageBoxA(0, "Okay", "t_t", MB_OK);
    }
    else
    {
        exit(0);
    }
}
void WinGame()
{
    int user;
    user = MessageBoxA(0, "You win", "Congratulations", MB_YESNO);
    system("cls");
    if (user == IDYES)
    {
        int great;
        great = MessageBoxA(0, "Good job", "^_^", MB_OK);
    }
    else
    {
        exit(0);

    }
}
