#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0

#define Air 0
#define Wall 1
#define Player 2
#define Enemy 3

#define MapSize 16

//Don't read this you are hurting yourself for no reason
//I don't encourage suicide, but it still less painful than reading my code

void PrintMap(int Map[MapSize][MapSize]) {
    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            switch (Map[i][j]) {
                case Air:
                    printf(" ");
                    break;
                case Wall:
                    printf("#");
                    break;
                case Player:
                    printf("X");
                    break;
                case Enemy:
                    printf("*");
                    break;
            }
        }
        printf("\n");
    }
}

void PrintLeaderboard() {
    char Name[32];
    char Point[32];
    int SizeFile = 0;
    int Char;
    FILE *PointerFile;

    PointerFile = fopen("Score.txt", "r");

    if (PointerFile == NULL)
    {
        printf("no leaderboard\n");
    }
    else
    {
        Char = getc(PointerFile);
        while (Char != EOF)
        {
            if (Char == '\n')
            {
                SizeFile = SizeFile + 1;
            }
            Char = getc(PointerFile);
        }

        fclose(PointerFile);
        PointerFile = fopen("Score.txt", "r");

        for (int i =0; i < SizeFile; i++)
        {
            fscanf(PointerFile, "%32s", Name);
            printf("%s made ", Name);
            fscanf(PointerFile, "%32s", Point);
            printf("%s Point\n", Point);
        }
        fclose(PointerFile);
    }
}

void Game() {
    srand(time(NULL));

    char input;
    int Map[MapSize][MapSize];
    int PlayerX = MapSize / 2;
    int PlayerY = MapSize / 2;
    int EnemyX;
    int EnemyY;
    int EnemyDead = 0;
    int frames = 0;
    _Bool GameRunning;

    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            if (i == 0 || i == MapSize-1 || j == 0 || j == MapSize-1)
            {
                Map[i][j] = Wall;
            } else
            {
                Map[i][j] = Air;
            }
        }
    }

    Map[PlayerX][PlayerY] = Player;

    for (int i = 0; i < 10; i ++)
    {
        EnemyX = rand() % MapSize;
        EnemyY = rand() % MapSize;
        if (Map[EnemyX][EnemyY] == Air) {
            Map[EnemyX][EnemyY] = Enemy;
        } else {
            EnemyDead += 1;
        }
    }

    GameRunning = true;

    while (GameRunning) {
        PrintMap(Map);
        scanf(" %c", &input);
        frames += 1;
        switch (input) {
            default:
                frames -= 1;
                break;
            case 'z':
                if (Map[PlayerX - 1][PlayerY] == Wall) {
                    break;
                }
                else if (Map[PlayerX - 1][PlayerY] == Enemy)
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerX -= 1;
                    Map[PlayerX][PlayerY] = Player;
                    EnemyDead += 1;
                }
                else
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerX -= 1;
                    Map[PlayerX][PlayerY] = Player;
                }
                break;
            case 's':
                if (Map[PlayerX + 1][PlayerY] == Wall) {
                    break;
                }
                else if (Map[PlayerX + 1][PlayerY] == Enemy)
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerX += 1;
                    Map[PlayerX][PlayerY] = Player;
                    EnemyDead += 1;
                }
                else
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerX += 1;
                    Map[PlayerX][PlayerY] = Player;
                }
                break;
            case 'd':
                if (Map[PlayerX][PlayerY + 1] == Wall) {
                    break;
                }
                else if (Map[PlayerX][PlayerY + 1] == Enemy)
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerY += 1;
                    Map[PlayerX][PlayerY] = Player;
                    EnemyDead += 1;
                }
                else
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerY += 1;
                    Map[PlayerX][PlayerY] = Player;
                }
                break;
            case 'q':
                if (Map[PlayerX][PlayerY - 1] == Wall) {
                    break;
                }
                else if (Map[PlayerX][PlayerY - 1] == Enemy)
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerY -= 1;
                    Map[PlayerX][PlayerY] = Player;
                    EnemyDead += 1;
                }
                else
                {
                    Map[PlayerX][PlayerY] = Air;
                    PlayerY -= 1;
                    Map[PlayerX][PlayerY] = Player;
                }
                break;
        }
        if (Map[PlayerX][PlayerY] == Enemy){
            EnemyDead += 1;
            Map[PlayerX][PlayerY] = 0;
        }
        if (EnemyDead == 10) {
            GameRunning = false;
        }
    }

    PrintLeaderboard();

    FILE *PointerFile;
    char Name[32];
    char Point[32];
    sprintf(Point, "%i", 1000 - frames);

    printf("Name (32 character max and no space) :");
    scanf("%32s", Name);

    PointerFile = fopen("Score.txt", "a");

    fwrite("\n", 1, 1, PointerFile);
    fwrite(Name, 1, sizeof Name, PointerFile);
    fwrite(" ", 1, 1, PointerFile);
    fwrite(Point, 1, sizeof Point, PointerFile);

    fclose(PointerFile);
}

int main() {
    _Bool run = true;
    int choice;

    while (run) {
        printf("1 : start the game\n");
        printf("2 : leaderboard\n");
        printf("3 : quit the menu\n");

        scanf("%i", &choice);
        switch (choice) {
            default:
                printf("error\n");
                break;
            case 1:
                Game();
                break;
            case 2:
                PrintLeaderboard();
                break;
            case 3:
                run = false;
                break;
        }
    }
    return 0;
}
