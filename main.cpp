/*  Name:  Grady Baum                         */
/*  Date:  11/21/2023                             */
/*  Assignment:  SDP 2                          */
/*  Seat:  XX       Instructor:  KMK        Time:  08:00 */

#include "FEHLCD.h"
#include "FEHUtility.h"

class car
{
private:
    float car_x;
    float car_y;
    float width;
    float height;

public:
    float car_speed;
    void Collision();
    void CarMake(float a, float b, float c, float d, float e);
    void CarMove();
    void CarInitial();
};

class game
{
private:
    float x1 = 5, y1 = 20, y2 = 20, y3 = 130, x2 = 190, x3 = 5, x, y;
    float x4 = 190, y4 = 130;
    float x_return_w = 80, y_return_w = 20;
    float x_w = 145, y_w = 40;
    bool touch = false;
    float numCar = 6;
    car vroom[58];

public:
    float i = 0;
    float speed = 0.4;
    float y_character;
    float x_character;
    bool dead = false, check = false, color = false;

    void MainMenu();
    void Start();
    void Statistics();
    void Return();
    void Rules();
    void Refresh();
    void Credits();
    void Rectangle(float a, float b, float c, float d);
    void DrawBackground();
} game1;

void game::MainMenu()
{
    /*Remake game playable*/
    dead = false;
    /*Start Rectangle*/
    LCD.Clear();
    LCD.SetFontColor(WHITE);
    Rectangle(x1, y1, x_w, y_w);
    LCD.SetFontColor(RED);
    LCD.WriteAt("Start", x1 + 40, y1 + 12);

    /*Statistics Rectangle*/
    LCD.SetFontColor(WHITE);
    Rectangle(x2, y2, x_w, y_w);
    LCD.SetFontColor(GREEN);
    LCD.WriteAt("Statistics", x2 + 4, y2 + 12);

    /*Rules*/
    LCD.SetFontColor(WHITE);
    Rectangle(x3, y3, x_w, y_w);
    LCD.SetFontColor(BLUE);
    LCD.WriteAt("Rules", x3 + 40, y3 + 12);

    /*Credits*/
    LCD.SetFontColor(WHITE);
    Rectangle(x4, y4, x_w, y_w);
    LCD.SetFontColor(MAGENTA);
    LCD.WriteAt("Credits", x4 + 25, y4 + 12);

    /*Crossy Road!*/
    LCD.SetFontColor(GOLDENROD);
    LCD.WriteAt("Crossy Road", 98, 88);

    while (!LCD.Touch(&x, &y))
    {
    }

    // Touch - use x and y
    while (!touch)
    {
        while (LCD.Touch(&x, &y))
        {
            if (x > x1 && x < x1 + x_w && y > y1 && y < y1 + y_w)
            {
                Start();
                touch = true;
            }

            else if (x > x2 && x < x2 + x_w && y > y2 && y < y2 + y_w)
            {
                Statistics();
            }
            else if (x > x3 && x < x3 + x_w && y > y3 && y < y3 + y_w)
            {
                Rules();
            }
            else if (x > x4 && x < x4 + x_w && y > y4 && y < y4 + y_w)
            {
                Credits();
            }
            Sleep(0.01);
        }
    }
}

int main()
{
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    game1.MainMenu();

    while (1)
    {
        LCD.Update();
        // Never end
    }
    return 0;
}

/*Easier rectangles*/
void game::Rectangle(float startX, float startY, float width, float height)
{
    LCD.DrawRectangle(startX, startY, width, height);
    LCD.FillRectangle(startX, startY, width, height);
}

/*They click start*/
void game::Start()
{
    int p, k;
    /*initialize*/
    i = 0;
    y_character = 150;
    x_character = 159;

    /*Get rid of rectangles*/
    LCD.Clear();

    vroom[0].CarMake(250, i + 2.5, 25, 15, 2);
    vroom[1].CarMake(64, i + 42.5, 25, 15, 6);
    vroom[2].CarMake(0, i + 82.5, 25, 15, 3);
    vroom[3].CarMake(18, i + 122.5, 25, 15, 4);
    vroom[4].CarMake(185, i + 162.5, 25, 15, 7);
    vroom[5].CarMake(117, i + 202.5, 25, 15, 3);

    DrawBackground();
    Sleep(3.0);

    while (!dead) // loop until dead
    {
        for (k = 0; k < game1.numCar; k++)
        {
            vroom[k].Collision();
        }
        if (dead)
        {
            break;
        }
        /*Waits for touch and updates screen accordingly*/
        while (!LCD.Touch(&x, &y))
        {
            Refresh();
            for (p = 0; p < numCar; p++)
            {
                vroom[p].Collision();
            }
            if (dead)
            {
                break;
            }
        }
        if (dead)
        {
            break;
        }
        while (LCD.Touch(&x, &y))
        {
        }
        if (!color) // Correctly assigns color to replace previous character
        {
            LCD.SetFontColor(GREEN);
            color = true;
        }
        else if (color)
        {
            LCD.SetFontColor(GRAY);
            color = false;
        }
        LCD.DrawCircle(x_character, y_character, 9); // delete character
        y_character -= 20;
        LCD.SetFontColor(BLUE);
        LCD.DrawCircle(x_character, y_character, 9); // new character
        int n;
        Refresh();
        for (k = 0; k < game1.numCar; k++)
        {
            vroom[k].Collision();
        }
    }
    /*Say play game*/
    LCD.Clear();
    LCD.SetFontColor(RED);
    LCD.WriteAt("Play Game Here", 88, 88);
    Return();
}

/*moves the screen down*/
void game::Refresh()
{
    int k;

    DrawBackground();

    for (k = 0; k < numCar; k++)
    {
        vroom[k].CarInitial();
    }
    for (k = 0; k < game1.numCar; k++)
    {
        vroom[k].Collision();
    }
    if (!dead)
    {

        i += speed;           // Updates location of grass+roads
        y_character += speed; // Updates location of character
        int j;

        if (y_character >= 239)
        {
            dead = true;
        }
        else if (y_character <= 0)
        {
            speed += 0.4;
            Start();
            for (j = 0; j < numCar; j++)
            {
                vroom[j].car_speed += 0.75;
            }
        }
    }
    if (!dead)
    {
        /*Redraw the map*/
        DrawBackground();
        for (k = 0; k < game1.numCar; k++)
        {
            vroom[k].Collision();
        }
    }
    if (!dead)
    {
        for (k = 0; k < numCar; k++)
        {
            vroom[k].CarMove();
        }
        for (k = 0; k < game1.numCar; k++)
        {
            vroom[k].Collision();
        }
    }
}

/*They click Statistics*/
void game::Statistics()
{
    /*Get rid of rectangles*/
    LCD.Clear();

    /*Show Statistics*/
    LCD.SetFontColor(GREEN);
    LCD.WriteAt("Max time: ", 3, 10);
    LCD.WriteAt(x1, 120, 10);

    LCD.WriteAt("Distance Travelled: ", 3, 60);
    LCD.WriteAt(x2, 230, 60);

    // wait for return
    Return();
}

void game::DrawBackground()
{

    int k;

    /*builds map initially*/
    LCD.SetFontColor(GRAY);
    Rectangle(0, i, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 20, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 40, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 60, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 80, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 100, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 120, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 140, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 160, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 180, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 200, 319, 20);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 220, 319, 20);

    for (k = 0; k < numCar; k++)
    {
        vroom[k].CarInitial();
    }
    LCD.SetFontColor(BLUE);
    LCD.DrawCircle(x_character, y_character, 9);
}

void game::Rules()
{
    LCD.Clear();

    LCD.WriteLine("   Click the top of the\n  screen to go forward");
    LCD.SetFontColor(PURPLE);
    LCD.WriteLine("\n\n  Click the bottom of the\n  screen to go down");
    LCD.SetFontColor(YELLOWGREEN);
    LCD.WriteLine("\n\n  Click the right of the\n  screen to go right");
    LCD.SetFontColor(CYAN);
    LCD.WriteLine("\n\n  Click the left of the\n  screen to go left");
    LCD.SetFontColor(CRIMSON);
    LCD.WriteLine("\n\n      Survive");

    Return();
}

void game::Credits()
{
    /*Get rid of rectangles*/
    LCD.Clear();

    LCD.SetFontColor(MAGENTA);
    LCD.WriteAt("Grady Baum", 102, 120);
    LCD.WriteAt("Adam Ballas", 97, 80);

    Return();
}

void game::Return()
{
    /*Make return button*/
    LCD.SetFontColor(GRAY);
    Rectangle(200, 200, x_return_w, y_return_w);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Return", 205, 204);
    bool waitingForReturn = true;

    // wait for return button to be pressed
    while (waitingForReturn)
    {
        while (LCD.Touch(&x, &y))
        {
            if (x > 200 && x < 200 + x_return_w && y > 200 && y < 200 + y_return_w)
            {
                MainMenu();
                waitingForReturn = false;
            }
        }
    }
}

void car::Collision()
{
    if ((game1.x_character >= car_x && game1.x_character <= car_x + 25) && (game1.y_character >= car_y && game1.y_character <= car_y + 15))
    {
        game1.dead = true;
    }
}

void car::CarInitial()
{
    LCD.SetFontColor(RED);
    game1.Rectangle(car_x, car_y, width, height);
}

void car::CarMake(float a, float b, float c, float d, float e)
{
    car_speed = e;
    car_x = a;
    car_y = b;
    width = c;
    height = d;
}
void car::CarMove()
{
    LCD.SetFontColor(GRAY);
    game1.Rectangle(car_x, car_y, width, height);
    if (car_x >= 319)
    {
        car_x = 0;
    }
    if (car_y >= 239)
    {
        car_y = 0;
    }
    car_x += car_speed;
    car_y += game1.speed;

    LCD.SetFontColor(RED);
    game1.Rectangle(car_x, car_y, width, height);
    Collision();
}