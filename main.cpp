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
    float x_return_w = 80, y_return_w = 20;
    float x_w = 145, y_w = 40;
    bool touch = false;

public:
    void MainMenu();
    void Start();
    void Statistics();
    void Return();
    void Rules();
    void Credits();
    void Rectangle(float a, float b, float c, float d);
    int main();
} Instance;

/*RETURN BUTTON*/

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

    /*Say play game*/
    LCD.SetFontColor(RED);
    LCD.WriteAt("Play Game Here", 88, 88);
    Return();
    
}
/*They click start*/
void game::Statistics()
{
    /*Get rid of rectangles*/
    LCD.Clear();

    /*Show Statistics*/
    LCD.SetFontColor(GREEN);
    LCD.WriteRC("Longest survival time: ", 3, 1);
    LCD.WriteRC("Distance Travelled: ", 5, 1);

    // wait for return
    Return();
}

void game::Rules()
{
    LCD.Clear();

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