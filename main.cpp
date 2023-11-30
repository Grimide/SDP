/*  Name:  Grady Baum                         */
/*  Date:  11/21/2023                             */
/*  Assignment:  SDP 2                          */
/*  Seat:  XX       Instructor:  KMK        Time:  08:00 */

#include "FEHLCD.h"
#include "FEHUtility.h"
#include <random>
#include <FEHImages.h>

class car
{
private:
    float car_x;
    float width;
    float height;

public:
    float car_y;
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
    float control_upx = 265, control_leftx = 247.5, control_rightx = 282.5;
    float control_upy = 172.5, control_leftRighty = 200;
    float control_size = 25;
    bool touch = false;
    car vroom[58];

public:
    float i = 0;
    FEHImage gecko;
    int ub = 10, lb = 0;
    int top_x = 319;
    float speed = 0.4;
    float y_character;
    float x_character;
    int numCar = 6;
    int colors[7] = {GREEN, KHAKI, DARKGREEN, DARKBLUE, TEAL, HONEYDEW, HOTPINK};
    int backgroundColor = colors[0];
    int stages_cleared = 0, max_stages_cleared = 0;
    int last_rows, last_stages;
    int rows_traveled = 0, max_rows_traveled = 0;
    float side_speed = 20;
    float character_size = 9;
    bool dead = false, check = false, color = false;

    void MainMenu();
    void Start();
    void Statistics();
    void Return();
    void Rules();
    void Refresh();
    void Credits();
    void ControlButtons();
    void RulesPage2();
    void Character();
    void Rectangle(float a, float b, float c, float d);
    void DrawBackground();
    void Countdown();
    void Point_Ticker();
    void Driving_tips();
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
    LCD.WriteAt("Chicken Crossing", 75, 88);

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

    game1.gecko.Open("GeckoFEH.pic");
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    game1.MainMenu();

    game1.gecko.Close();

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
    int p, k, m, j;
    int color_top = 8, color_bottom = 0;

    /*initialize*/
    i = 0;
    y_character = 150;
    x_character = 159;

    /*Get rid of rectangles*/
    LCD.Clear();

    /*make all cars with random x and random speeds*/

    vroom[0].CarMake(rand() % top_x, i + 2.5, 25, 15, rand() % (ub - lb + 1) + lb);
    vroom[1].CarMake(rand() % top_x, i + 42.5, 25, 15, rand() % (ub - lb + 1) + lb);
    vroom[2].CarMake(rand() % top_x, i + 82.5, 25, 15, rand() % (ub - lb + 1) + lb);
    vroom[3].CarMake(rand() % top_x, i + 122.5, 25, 15, rand() % (ub - lb + 1) + lb);
    vroom[4].CarMake(rand() % top_x, i + 162.5, 25, 15, rand() % (ub - lb + 1) + lb);
    vroom[5].CarMake(rand() % top_x, i + 202.5, 25, 15, rand() % (ub - lb + 1) + lb);

    if (stages_cleared > 0)
    {
        /*adds car per level*/
        if (stages_cleared == 1)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 2.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
        else if (stages_cleared == 2)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 42.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
        else if (stages_cleared == 3)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 82.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
        else if (stages_cleared == 4)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 122.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
        else if (stages_cleared == 5)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 162.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
        else if (stages_cleared == 6)
        {
            vroom[game1.numCar].CarMake(rand() % top_x, i + 202.5, 25, 15, rand() % (ub - lb + 1) + lb);
            game1.numCar++;
            backgroundColor = colors[rand() % (color_top - color_bottom + 1) + color_bottom];
        }
    }

    DrawBackground();
    Countdown();

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
        /*if click to move up*/
        if ((x >= control_upx && x <= control_upx + control_size) && (y >= control_upy && y <= control_upy + control_size))
        {
            if (!color) // Correctly assigns color to replace previous character
            {
                LCD.SetFontColor(backgroundColor);
                color = true;
            }
            else if (color)
            {
                LCD.SetFontColor(GRAY);
                color = false;
            }
            LCD.DrawCircle(x_character, y_character, 9); // delete character
            LCD.FillCircle(x_character, y_character, 9);
            y_character -= 20;
            Character(); // new character
            rows_traveled++;
            Refresh();
            for (k = 0; k < game1.numCar; k++)
            {
                vroom[k].Collision();
            }
        }
        /*if click to move left*/
        else if ((x >= control_leftx && x <= control_leftx + control_size) && (y >= control_leftRighty && y <= control_leftRighty + control_size))
        {
            if (!color)
            {
                LCD.SetFontColor(backgroundColor);
            }
            else if (color)
            {
                LCD.SetFontColor(GRAY);
            }
            LCD.DrawCircle(x_character, y_character, 9); // delete character
            LCD.FillCircle(x_character, y_character, 9);
            x_character -= side_speed;
            Character(); // new character
            Refresh();
            for (k = 0; k < game1.numCar; k++)
            {
                vroom[k].Collision();
            }
        }

        /*If click to move right*/
        else if ((x >= control_rightx && x <= control_rightx + control_size) && (y >= control_leftRighty && y <= control_leftRighty + control_size))
        {
            if (!color)
            {
                LCD.SetFontColor(backgroundColor);
            }
            else if (color)
            {
                LCD.SetFontColor(GRAY);
            }
            LCD.DrawCircle(x_character, y_character, 9); // delete character
            LCD.FillCircle(x_character, y_character, 9);
            x_character += side_speed;
            Character(); // new character
            Refresh();
            for (k = 0; k < game1.numCar; k++)
            {
                vroom[k].Collision();
            }
        }
    }

    /*Store new max values*/
    if (rows_traveled > max_rows_traveled)
    {
        max_rows_traveled = rows_traveled;
    }
    if (stages_cleared > max_stages_cleared)
    {
        max_stages_cleared = stages_cleared;
    }

    /*for stats page*/
    last_rows = rows_traveled;
    last_stages = stages_cleared;

    /*clear memory*/
    stages_cleared = 0;
    rows_traveled = 0;

    /*Say play game*/
    Driving_tips();
    numCar = 6;
    backgroundColor = colors[0];
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

    Point_Ticker();

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
            speed += 0.15;
            stages_cleared++;

            Start();
        }
        Point_Ticker();
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
    LCD.SetFontColor(GOLD);
    LCD.WriteAt("Last game:", 95, 10);
    LCD.SetFontColor(backgroundColor);
    LCD.WriteAt("Rows Traveled > \n\n\n\n", 3, 40);
    LCD.WriteAt(last_rows, 185, 40);

    LCD.WriteAt("Stages Cleared >", 3, 70);
    LCD.WriteAt(last_stages, 197, 70);

    /*Show all time statistics(this session)*/
    LCD.SetFontColor(GOLD);
    LCD.WriteAt("All Time:", 95, 110);
    LCD.SetFontColor(HOTPINK);
    LCD.WriteAt("Rows Traveled > \n\n\n\n", 3, 140);
    LCD.WriteAt(max_rows_traveled, 185, 140);

    LCD.WriteAt("Stages Cleared >", 3, 170);
    LCD.WriteAt(max_stages_cleared, 197, 170);

    // wait for return
    Return();
}

void game::DrawBackground()
{

    int k;

    /*builds map initially*/
    LCD.SetFontColor(GRAY);
    Rectangle(0, i, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 20, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 40, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 60, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 80, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 100, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 120, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 140, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 160, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 180, 319, 20);
    LCD.SetFontColor(GRAY);
    Rectangle(0, i + 200, 319, 20);
    LCD.SetFontColor(backgroundColor);
    Rectangle(0, i + 220, 319, 20);

    for (k = 0; k < numCar; k++)
    {
        vroom[k].CarInitial();
    }
    Character();

    ControlButtons();
    Point_Ticker();
}

void game::Countdown()
{
    float text_x = 153.5;
    float text_y = 92.5;
    float countdown_x = 140, countdown_y = 80;
    float countdown_size = 40;

    LCD.SetFontColor(WHITE);
    Rectangle(countdown_x, countdown_y, countdown_size, countdown_size);
    LCD.SetFontColor(BROWN);
    LCD.WriteAt("3", text_x, text_y);
    Sleep(0.75);
    LCD.SetFontColor(WHITE);
    Rectangle(countdown_x, countdown_y, countdown_size, countdown_size);
    LCD.SetFontColor(SILVER);
    LCD.WriteAt("2", text_x, text_y);
    Sleep(0.75);
    LCD.SetFontColor(WHITE);
    Rectangle(countdown_x, countdown_y, countdown_size, countdown_size);
    LCD.SetFontColor(GOLD);
    LCD.WriteAt("1", text_x, text_y);
    Sleep(0.75);
    LCD.SetFontColor(WHITE);
    Rectangle(countdown_x, countdown_y, countdown_size, countdown_size);
    LCD.SetFontColor(backgroundColor);
    LCD.WriteAt("GO!", 144, text_y);
    Sleep(0.75);
}

void game::Rules()
{
    LCD.Clear();

    LCD.WriteLine("\n\n   Click the up arrow\n       to go forward");
    LCD.SetFontColor(YELLOWGREEN);
    LCD.WriteLine("\n\n   Click the right arrow\n      to go right");
    LCD.SetFontColor(CYAN);
    LCD.WriteLine("\n\n   Click the left arrow\n       to go left");
    LCD.SetFontColor(CRIMSON);
    LCD.WriteLine("\n\n        Survive");

    RulesPage2();
}

void game::RulesPage2()
{

    bool waitingforReturn = true;
    LCD.SetFontColor(BLUEVIOLET);
    Rectangle(20, 200, x_return_w, y_return_w);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Page 2", 25, 204);

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
            else if (x > 20 && x < 20 + x_return_w && y > 200 && y < 200 + y_return_w)
            {
                LCD.Clear();
                LCD.SetFontColor(TAN);
                LCD.WriteLine("    Reaching the top \n   Starts a new level\n\n");
                LCD.SetFontColor(ROYALBLUE);
                LCD.WriteLine("  Each level moves quicker \n and adds a car   \n ");
                LCD.SetFontColor(DARKGOLDENROD);
                LCD.WriteLine("   Your score is tracked \n in the top-left corner\n");
                Return();
            }
        }
    }
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

void game::Character()
{
    /*LCD.SetFontColor(VIOLET);
    LCD.DrawCircle(x_character, y_character, 9);
    LCD.FillCircle(x_character, y_character, 9);*/

    gecko.Draw(x_character, y_character - 9);
}

void game::ControlButtons()
{
    /*Create the movement buttons*/
    LCD.SetFontColor(BLUEVIOLET);
    Rectangle(control_leftx, control_leftRighty, control_size, control_size);
    Rectangle(control_rightx, control_leftRighty, control_size, control_size);
    Rectangle(control_upx, control_upy, control_size, control_size);

    /*make them have arrows*/
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("->", control_rightx + 2, control_leftRighty + 4);
    LCD.WriteAt("<-", control_leftx - 2, control_leftRighty + 4);
    LCD.WriteAt("^", control_upx + 5.5, control_upy + 2.5);
    LCD.WriteAt("|", control_upx + 5.5, control_upy + 7);
}

void game::Point_Ticker()
{
    LCD.SetFontColor(WHITE);
    Rectangle(5, 5, 30, 18);
    if (rows_traveled < 10)
    {
        LCD.SetFontColor(BROWN);
        LCD.WriteAt(rows_traveled, 13.75, 7.5);
    }
    else if (rows_traveled < 100)
    {
        LCD.SetFontColor(GOLD);
        LCD.WriteAt(rows_traveled, 7.5, 7.5);
    }
}

void game::Driving_tips() // finish later
{
    LCD.Clear();
    LCD.SetFontColor(GOLDENROD);
    LCD.WriteLine("      Driving Tips:\n");
    LCD.SetFontColor(WHITE);
    LCD.WriteLine("\n\n      - Be Sober");
    LCD.WriteLine("\n\n      - Be Aware");
    LCD.WriteLine("\n\n      - Be Smart");
}

void car::Collision()
{
    if ((game1.x_character + 7 >= car_x && game1.x_character - 7 <= car_x + 25) && (game1.y_character >= car_y && game1.y_character <= car_y + 15))
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
    game1.ControlButtons();
}