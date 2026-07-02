#include "raylib.h"
#include <vector>
//Gives access to dynamic arrays (vector)
//Used for menu items, cart, petals in the project
#include <string>
#include <fstream>
#include <cstdlib>
//Provides rand() and atof() functions for random numbers and stringto float conversion in the code
#include <iostream>

using namespace std;
//making namespace of theme grouped all the colours and styles together, reducing code complexity

namespace Theme {
    Color BG = {255, 245, 250, 255};
    Color CARD = {255, 255, 255, 255};
    Color PRIMARY = {255, 105, 180, 255};
    Color ACCENT = {255, 20, 147, 255};
    Color TEXT = {50, 50, 50, 255};
}

//different scrrens below

enum Screen { LOGIN, HOME, MENU, CART, ADMIN, RATING, HISTORY };

//use of struct here is done to store name and price could also be doen by class
//struct simplified the use of it here

struct Item {
    string name;
    float price;
};

//this shows the structure for animated sakura petals represents position, horizontal speed and vertical speed
struct Petal {
    Vector2 pos;
    float speed;
    float drift;
};

vector<Petal> petals; //this is a dynamic type of list made from vectos which will represent all thwe petals in the project sxreens

//60 petals in number that will fall

void InitPetals(int count = 60)
{
    for(int i = 0; i < count; i++)
    {
        Petal p;
        p.pos = {(float)(rand() % 800), (float)(rand() % 600)};
        p.speed = 1.0f + (rand() % 30) / 20.0f;
        p.drift = (rand() % 20 - 10) / 10.0f;
        petals.push_back(p); //thiss will stire petals in the list of petals made aboeve
    }
}

void DrawPixelFlower(Vector2 pos, float size, Color c) //func to draw simple flowerusing sqares 
{
    int s = (int)size;
//draeing center pount and 4 petals

    DrawRectangle(pos.x, pos.y, s, s, c);
    DrawRectangle(pos.x + s, pos.y + s, s, s, c);
    DrawRectangle(pos.x - s, pos.y + s, s, s, c);
    DrawRectangle(pos.x + s, pos.y - s, s, s, c);
    DrawRectangle(pos.x - s, pos.y - s, s, s, c);
}

void UpdatePetals()
{
    for(auto &p : petals)
    {
        p.pos.y += p.speed;
        p.pos.x += p.drift;

        if(p.pos.y > 600) { p.pos.y = -10; p.pos.x = rand() % 800; }
        if(p.pos.x > 800) p.pos.x = 0;
        if(p.pos.x < 0) p.pos.x = 800;

        DrawPixelFlower(p.pos, 2, Color{255, 182, 193, 180});
    }
}

class UI {
public:
    bool Button(Rectangle r, const char* t)//reuable button for all screens showing polymorphism

    {
        Vector2 m = GetMousePosition();
        bool hover = CheckCollisionPointRec(m, r);

        DrawRectangleRounded(r, 0.3f, 10, //drawing button box in rectangle
            hover ? Theme::PRIMARY : Theme::CARD);

        DrawText(t, r.x + 15, r.y + 10, 20, //functi to display button text
            hover ? WHITE : Theme::TEXT);

        return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON); //will return 0 or true if button is clcked
    }
};

class App { //encapsulation being shown here via priv members of class
private: //composition
    UI ui;
    Screen screen = LOGIN;

    string user, pass;
    bool uActive = false, pActive = false;

    vector<Item> menu = {
        {"Espresso",132.5f},{"Green Tea",122.5f},{"Iced Latte",200.5f},
        {"Burger",172.98f},{"Pizza",532.5f},{"Spanish Latte",292.5f},
        {"Pina Colada",124.5f},{"Black Coffee",120.5f},
        {"Croissant",322.6f},{"Chocolate Pastry",192.7f},
        {"Chicken Sandwich",122.8f},{"Orange Tart",142.6f},
        {"Rice Bowl",172.9f},{"Beef Chowmein",352.2f},
        {"Fish & Chips",432.4f},{"Loaded Fries",151.7f},
        {"Cheese Burger",173.9f},{"Pasta",142.9f},
        {"Pizza Margherita",532.5f},{"Buffalo Wings",532.5f},
        {"Wrap",162.5f}
    };

    vector<pair<Item,int>> cart;

    int rating = 0;
    string comment;

    float scroll = 0;
    bool dragging = false;

public:

void SaveOrder()
{
    ofstream f("history.txt", ios::app);
    float total = 0;

    f << "\n--- ORDER ---\n";
    for(auto &c : cart)
    {
        f << c.second << " x " << c.first.name << "\n";
        total += c.first.price * c.second;//total being calc by item price * quantuty
    }
    f << "TOTAL: " << total << "\n";
}

void DrawMenu(Rectangle area)
{
    float contentH = menu.size() * 80;

    scroll += GetMouseWheelMove() * 40;
    if(scroll > 0) scroll = 0;
    if(scroll < area.height - contentH)
        scroll = area.height - contentH;

    BeginScissorMode(area.x, area.y, area.width, area.height);

    for(int i=0;i<(int)menu.size();i++)
    {
        float y = area.y + i*80 + scroll;
        Rectangle card = {area.x+20, y, area.width-40, 60};

        DrawRectangleRounded(card,0.3f,10,Theme::CARD);

        DrawText(menu[i].name.c_str(),
                 card.x+20, card.y+15, 20, Theme::TEXT);

        DrawText(TextFormat("Rs %.2f", menu[i].price),
                 card.x+420, card.y+15, 20, Theme::ACCENT);

        if(ui.Button({card.x+520, card.y+15, 60, 30}, "ADD"))
            cart.push_back({menu[i],1});
    }

    EndScissorMode();

   
    float barH = area.height * (area.height / contentH);
    if(barH < 30) barH = 30;

    Vector2 m = GetMousePosition();

    float ratio = -scroll / (contentH - area.height);
    float barY = area.y + ratio * (area.height - barH);

    Rectangle barArea = {area.x+area.width-8, area.y, 6, area.height};
    Rectangle bar = {barArea.x, barY, 6, barH};

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
       CheckCollisionPointRec(m, bar))
        dragging = true;

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        dragging = false;

    if(dragging)
    {
        float newY = m.y - barH/2;
        float minY = area.y;
        float maxY = area.y + area.height - barH;

        if(newY < minY) newY = minY;
        if(newY > maxY) newY = maxY;

        float t = (newY - area.y) / (area.height - barH);
        scroll = -(t * (contentH - area.height));
    }

    DrawRectangle(barArea.x, barArea.y, barArea.width, barArea.height, Fade(GRAY,0.3f));
    DrawRectangle(bar.x, bar.y, bar.width, bar.height, Theme::PRIMARY);
}

void Update()
{
    BeginDrawing();
    ClearBackground(Theme::BG);

    UpdatePetals();

    Vector2 m = GetMousePosition();
    int key = GetCharPressed();

    switch(screen)
    {

    
    case LOGIN:
    {
        DrawText("The Sakura Sip Cafe", 260, 60, 22, Theme::ACCENT);

        Rectangle u={260,150,280,45};
        Rectangle p={260,220,280,45};

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            uActive = CheckCollisionPointRec(m,u);
            pActive = CheckCollisionPointRec(m,p);
        }

        DrawRectangleRec(u,Theme::CARD);
        DrawRectangleRec(p,Theme::CARD);

        DrawText(user.c_str(), u.x+10, u.y+12, 20, Theme::TEXT);
        DrawText(string(pass.size(), '*').c_str(),
                 p.x+10, p.y+12, 20, Theme::TEXT);

        while(key > 0)
        {
            if(uActive && user.size()<20 && key>=32) user += (char)key;
            if(pActive && pass.size()<20 && key>=32) pass += (char)key;
            key = GetCharPressed();
        }

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            if(uActive && !user.empty()) user.pop_back();
            if(pActive && !pass.empty()) pass.pop_back();
        }

        if(ui.Button({300,300,200,45},"LOGIN"))
            screen = HOME;
    } break;

    
    case HOME:
    {
        DrawText("HOME",360,60,30,Theme::ACCENT);

        if(ui.Button({300,150,200,45},"MENU")) screen =  MENU;
        if(ui.Button({300,210,200,45},"CART")) screen =    CART;
        if(ui.Button({300,270,200,45},"ADMIN")) screen = ADMIN;
        if(ui.Button({300,330,200, 45},"RATING")) screen =   RATING;
        if(ui.Button({300,390,200,45},"HISTORY")) screen =  HISTORY;
    } break;

    
    case MENU:
    {
        DrawText("MENU",360,20,30,Theme::ACCENT);
        DrawMenu({50,80,700,480});

        if(ui.Button({20,20,100,40},"BACK"))
            screen = HOME;
    } break;

    
    case CART:
    {
        float y=120, total=0;

        for(int i=0;i<(int)cart.size();)
        {
            DrawText(cart[i].first.name.c_str(),100,y,20,Theme::TEXT);
            DrawText(TextFormat("x%d",cart[i].second),300,y,20,Theme::TEXT);

            if(ui.Button({400,y,30,30},"+")) cart[i].second++;
            if(ui.Button({440,y,30,30},"-"))
            {
                cart[i].second--;
                if(cart[i].second<=0) cart.erase(cart.begin()+i);
                else i++;
            }
            else i++;

            total += cart[i-1].first.price * cart[i-1].second;
            y += 40;
        }

        DrawText(TextFormat("TOTAL: Rs %.2f",total),100,500,25,Theme::PRIMARY);

        if(ui.Button({300,540,150,40},"CHECKOUT"))
        {
            SaveOrder();
            cart.clear();
        }

        if(ui.Button({20,20,100,40},"BACK"))
            screen = HOME;

    } break;

    
    case ADMIN:
    {
        static string n,p;
        static bool na=false,pa=false;

        Rectangle nBox={200,120,200,40};
        Rectangle pBox={420,120,200,40};

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            na = CheckCollisionPointRec(m,nBox);
            pa = CheckCollisionPointRec(m,pBox);
        }

        DrawRectangleRec(nBox,WHITE);
        DrawRectangleRec(pBox,WHITE);

        DrawText(n.c_str(),nBox.x+10,nBox.y+10,20,Theme::TEXT);
        DrawText(p.c_str(),pBox.x+10,pBox.y+10,20,Theme::TEXT);

        while(key>0)
        {
            if(na && n.size()<20 && key>=32) n+=(char)key;
            if(pa && p.size()<10 && key>=32) p+=(char)key;
            key = GetCharPressed();
        }

        if(ui.Button({650,120,100,40},"ADD"))
        {
            if(!n.empty() && !p.empty())
            {
                menu.push_back({n,(float)atof(p.c_str())});
                n.clear(); p.clear();
            }
        }

        float y=220;
        for(int i=0;i<(int)menu.size();i++)
        {
            DrawText(menu[i].name.c_str(),100,y,20,Theme::TEXT);
            DrawText(TextFormat("%.2f",menu[i].price),400,y,20,Theme::ACCENT);

            if(ui.Button({550,y,80,30},"DEL"))// for deleting item frim menu
            {
                menu.erase(menu.begin()+i);
                i--;
            }
            y+=40;
        }

        if(ui.Button({20,20,100,40},"BACK"))
            screen = HOME;

    } break;

    
    case RATING:
    {
        Vector2 mp = GetMousePosition();

        for(int i=0;i<5;i++)
        {
            Rectangle star = {(float)(300+i*40),150,30,30};

            if(CheckCollisionPointRec(mp, star) &&
               IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                rating = i+1;

            Color c = (i < rating) ? Theme::PRIMARY : LIGHTGRAY;

            DrawText("★", star.x, star.y, 30, c);
        }

        Rectangle box={200,240,400,120};
        DrawRectangleRec(box,WHITE);
        DrawRectangleLinesEx(box,2,Theme::PRIMARY);

        DrawText(comment.c_str(),box.x+10,box.y+10,20,Theme::TEXT);

        while(key>0)
        {
            if(comment.size()<100 && key>=32)
                comment += (char)key;
            key = GetCharPressed();
        }

        if(IsKeyPressed(KEY_BACKSPACE) && !comment.empty())
            comment.pop_back();

        if(ui.Button({300,380,150,40},"SUBMIT"))
        {
            ofstream f("ratings.txt",ios::app);
            f<<rating<<"/5 - "<<comment<<"\n";
            comment=""; rating=0;
        }

        if(ui.Button({20,20,100,40},"BACK"))
            screen = HOME;

    } break;

    
    case HISTORY:
    {
        ifstream f("history.txt");
        if(f.is_open() == false){
            cout<<"Unable To Open File."<<endl;
        }
        string line;
        int y=100;

        while(getline(f,line))
        {
            DrawText(line.c_str(),100,y,20,Theme::TEXT);
            y+=25;
        }

        if(ui.Button({20,20,100,40},"BACK"))
            screen = HOME;
    } break;
    }

    EndDrawing();
}
};

int main()
{
    InitWindow(800,600,"The Sakura Sip Cafe");
    SetTargetFPS(60);

    InitPetals();

    App app;
    while(!WindowShouldClose())
        app.Update();

    CloseWindow();
}

//project code above given