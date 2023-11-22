/*  Name:  Grady Baum                         */
/*  Date:  11/21/2023                             */
/*  Assignment:  SDP 2                          */
/*  Seat:  XX       Instructor:  KMK        Time:  08:00 */

#include "FEHLCD.h"
#include "FEHUtility.h"
class game
{
private:
    float x1 = 5, y1 = 20, y2 = 20, y3 = 130, x2 = 190, x3 = 5, x, y;
    float x4 = 190, y4 = 130;
    float i = 0, k = 0;
    float speed = 0.2;
    float car_x[6] = {0, 129, 204, 172, 33, 239};
    float car_speed[6] = {5, 4, 6, 7, 8, 2};
    float x_return_w = 80, y_return_w = 20;
    float x_w = 145, y_w = 40;
    bool touch = false;

public:
    void MainMenu();
    void Start();
    void Statistics();
    void Return();
    void Rules();
    void Refresh();
    void Credits();
    void Rectangle(float a, float b, float c, float d);
};

void game::MainMenu()
{

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
    game mine;
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    mine.MainMenu();

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
    /*Get rid of rectangles*/
    LCD.Clear();
    bool dead = false, check = false, color = false;

    while (!dead) // loop until dead
    {

        /*Waits for touch and updates screen accordingly*/
        while (!LCD.Touch(&x, &y))
        {
            Refresh();
        }

        while (LCD.Touch(&x, &y))
        {
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
            LCD.DrawCircle(159, k + 190, 9); // delete character
            k -= 20;
            LCD.SetFontColor(BLUE);
            LCD.DrawCircle(159, k + 19, 9); // new character

            Refresh();
        }
        Sleep(.05);
    }
    /*Say play game*/
    LCD.SetFontColor(RED);
    LCD.WriteAt("Play Game Here", 88, 88);
    Return();
}

/*moves the screen down*/
void game::Refresh()
{

/*builds map initially*/
    LCD.SetFontColor(GRAY);
    Rectangle(0, i, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[0], i, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 22.5, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 40, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[1], i + 42.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 60, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 80, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[2], i + 82.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 100, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 120, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[3], i + 122.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 140, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 160, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[4], i + 162.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 180, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 200, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[5], i + 202.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 220, 319, 20);

    LCD.SetFontColor(BLUE);
    LCD.DrawCircle(159, k + 190, 9);

    i += speed; //Updates location of grass+roads
    k += speed; //Updates location of character
    int j;

    for (j = 0; j < 6; j++)
    {
        car_x[j] += car_speed[j]; //Updates car location
    }

    LCD.SetFontColor(GRAY);
    Rectangle(0, i, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[0], i, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 22.5, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 40, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[1], i + 42.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 60, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 80, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[2], i + 82.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 100, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 120, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[3], i + 122.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 140, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 160, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[4], i + 162.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 180, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 200, 319, 20);
    LCD.SetFontColor(RED);
    Rectangle(car_x[5], i + 202.5, 25, 15);
    LCD.SetFontColor(GREEN);
    Rectangle(0, i + 220, 319, 20);

    LCD.SetFontColor(BLUE);
    LCD.DrawCircle(159, k + 190, 9);
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