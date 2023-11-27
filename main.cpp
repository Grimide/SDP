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
    float control_upx = 265, control_leftx = 247.5, control_rightx = 282.5;
    float control_upy = 172.5, control_leftRighty = 200;
    float control_size = 25;
    bool touch = false;
    float numCar = 6;
    car vroom[58];

public:
    float i = 0;
    float speed = 0.4;
    float y_character;
    float x_character;
    int stages_cleared = 0;
    int rows_traveled = 0;
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
    void Character();
    void Rectangle(float a, float b, float c, float d);
    void DrawBackground();
    void Countdown();
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

    /*make all cars*/
    vroom[0].CarMake(250, i + 2.5, 25, 15, 2);
    vroom[1].CarMake(64, i + 42.5, 25, 15, 6);
    vroom[2].CarMake(0, i + 82.5, 25, 15, 3);
    vroom[3].CarMake(18, i + 122.5, 25, 15, 4);
    vroom[4].CarMake(185, i + 162.5, 25, 15, 7);
    vroom[5].CarMake(117, i + 202.5, 25, 15, 3);

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
                LCD.SetFontColor(GREEN);
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
                LCD.SetFontColor(GREEN);
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
                LCD.SetFontColor(GREEN);
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
            speed += 0.2;
            stages_cleared++;
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
    LCD.SetFontColor(GOLD);
    LCD.WriteAt("Last game:", 95, 10);
    LCD.SetFontColor(GREEN);
    LCD.WriteAt("Rows traveled > \n\n\n\n", 3, 40);
    LCD.WriteAt(rows_traveled, 185, 40);

    LCD.WriteAt("Stages Cleared >", 3, 90);
    LCD.WriteAt(stages_cleared, 197, 90);

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
    Character();

    ControlButtons();
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
    LCD.SetFontColor(GREEN);
    LCD.WriteAt("GO!", 144, text_y);
    Sleep(0.75);
}

void game::Rules()
{
    LCD.Clear();

    LCD.WriteLine("\n\n\n   Click the up arrow\n       to go forward");
    LCD.SetFontColor(YELLOWGREEN);
    LCD.WriteLine("\n\n   Click the right arrow\n      to go right");
    LCD.SetFontColor(CYAN);
    LCD.WriteLine("\n\n   Click the left arrow\n       to go left");
    LCD.SetFontColor(CRIMSON);
    LCD.WriteLine("\n\n        Survive");

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

void game::Character()
{
    LCD.SetFontColor(VIOLET);
    LCD.DrawCircle(x_character, y_character, 9);
    LCD.FillCircle(x_character, y_character, 9);
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