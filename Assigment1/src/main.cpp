#if 1
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cassert>

#include "raylib.h"

class A1Circle
{
    float m_x;
    float m_y;
  
    float m_sx;
    float m_sy;

    Color m_shapeColor;

    float m_radius;
    const std::string& m_name;

    Font m_font;
    Color m_fontColor;

public:
    A1Circle(float x, float y, float sx, float sy, float radius, const std::string &name, int r, int g, int b, Font font, int fr, int fg, int fb)
        : m_x(x)
        , m_y(y)
        , m_sx(sx)
        , m_sy(sy)
        , m_radius(radius)
        , m_name(name)
        , m_font(font)
    {
        m_shapeColor.r = r;
        m_shapeColor.g = g;
        m_shapeColor.b = b;
        m_shapeColor.a = 255;

        m_fontColor.r = fr;
        m_fontColor.g = fg;
        m_fontColor.b = fb;
        m_fontColor.a = 255;
    }

    ~A1Circle() {}

    void draw()
    {
        DrawCircle(m_x + m_radius, m_y + m_radius, m_radius, m_shapeColor);
        int textWidth = MeasureText(m_name.c_str(), 18);
        Vector2 textPositon = {};
        textPositon.x = m_x + (m_radius) - (static_cast<float>(textWidth) / 2);
        textPositon.y = m_y + (m_radius) - (static_cast<float>(18 / 2));
        // TODO: Fix the Font issue. For some reason in hava a font.texture.id == 0.
        // Because of that fuctions can't correctly work with it :(
        DrawText(m_name.c_str(), textPositon.x, textPositon.y, 18, m_fontColor);
    }

    void update(int windowWidth, int windowHeight)
    {
        m_x += m_sx;
        m_y += m_sy;

        if (m_x < 0 || m_x + m_radius * 2 > windowWidth)
        {
            m_sx = -(m_sx);
        }

        if (m_y < 0 || m_y + m_radius * 2 > windowHeight)
        {
            m_sy = -(m_sy);
        }
    } 
};

class A1Rectangle
{
    float m_x;
    float m_y;

    float m_sx;
    float m_sy;

    float m_width;
    float m_height;

    Color m_shapeColor;

    std::string m_name;

    Font m_font;
    Color m_fontColor;

public:
    A1Rectangle(float x, float y, float sx, float sy, float width, float height, std::string name, int r, int g, int b, Font font, int fr, int fg, int fb)
        : m_x(x)
        , m_y(y)
        , m_sx(sx)
        , m_sy(sy)
        , m_height(height)
        , m_width(width)
        , m_name(name)
        , m_font(font)
    {
        m_shapeColor.r = r;
        m_shapeColor.g = g;
        m_shapeColor.b = b;
        m_shapeColor.a = 255;

        m_fontColor.r = fr;
        m_fontColor.g = fg;
        m_fontColor.b = fb;
        m_fontColor.a = 255;
    }

    ~A1Rectangle() {}

    void draw()
    {
        DrawRectangle(m_x, m_y, m_width, m_height, m_shapeColor);
        int textWidth = MeasureText(m_name.c_str(), 18);
        Vector2 textPositon = {};
        textPositon.x = m_x + (m_width / 2) - (static_cast<float>(textWidth) / 2);
        textPositon.y = m_y + (m_height / 2) - (static_cast<float>(18 / 2));
        // TODO: Fix the Font issue. For some reason in hava a font.texture.id == 0.
        // Because of that fuctions can't correctly work with it :(
        DrawText(m_name.c_str(), textPositon.x, textPositon.y, 18, m_fontColor);
    }

    void update(int windowWidth, int windowHeight)
    {
        m_x += m_sx;
        m_y += m_sy;

        if (m_x < 0 || m_x + m_width > windowWidth)
        {
            m_sx = -(m_sx);
        }

        if (m_y < 0 || m_y + m_height > windowHeight)
        {
            m_sy = -(m_sy);
        }
    }
};

class WindowData {
public:
    int width = 0;
    int height = 0;
};

class FontData {
public:
    std::string font_name;
    int font_size;
    int r, g, b;
};

class CircleData {
public:
    std::string name;
    int x;
    int y;
    float sx;
    float sy;
    int r, g, b;
    int radius;
};

class RectangleData {
public:
    std::string name;
    int x;
    int y;
    float sx;
    float sy;
    int r, g, b;
    int w;
    int h;
};

std::string& pathToFile(const std::string& appPath, const std::string& relativePath) {
    size_t idx = appPath.find_last_of('\\');

    return appPath.substr(0, idx) + "\\" + relativePath;
};

int main(int argc, char** argv)
{
    /* === INITIALIZATION === */

    std::vector<std::shared_ptr<A1Rectangle>> rectangles;
    std::vector<std::shared_ptr<A1Circle>> circles;
    WindowData wData{};
    FontData fData{};
    CircleData cData{};
    RectangleData rData{};



    std::ifstream config_file("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\res\\config.txt");

    if (!config_file.is_open())
    {
        std::cerr << "Failed to open file " << "\"res\\config.txt\"" << std::endl;
        exit(-1);
    }

    std::string type;
    Font font;

    while (config_file >> type)
    {
        if (type == "Window")
        {
            config_file >> wData.width >> wData.height;
        }
        else if (type == "Font")
        {
            config_file >> fData.font_name;
            config_file >> fData.font_size;
            config_file >> fData.r >> fData.g >> fData.b;
            std::string fontPath = std::string("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\") + fData.font_name;
            font = LoadFontEx(fontPath.c_str(), fData.font_size, nullptr, 255);
            //if (!IsFontValid(font))
            //{
            //    std::cerr << "Failed to load font: " << fData.font_name << "\n";
            //    exit(-1);
            //}
            //assert(font.texture.id != 0 && "Failed to load font (texture.id == 0)");
        }
        else if (type == "Circle")
        {
            config_file >> cData.name;
            config_file >> cData.x >> cData.y;
            config_file >> cData.sx >> cData.sy;
            config_file >> cData.r >> cData.g >> cData.b;
            config_file >> cData.radius;

            circles.push_back(std::make_shared<A1Circle>(
                cData.x, cData.y,                       // Position
                cData.sx, cData.sy,                     // Velocity
                cData.radius,                           // Radius
                cData.name,                             // Name
                cData.r, cData.g, cData.b,              // Color
                font, fData.r, fData.g, fData.b));      // Font
        }         
        else if (type == "Rectangle")
        {
            config_file >> rData.name;
            config_file >> rData.x >> rData.x;
            config_file >> rData.sx >> rData.sy;
            config_file >> rData.r >> rData.g >> rData.b;
            config_file >> rData.w;
            config_file >> rData.h;

            rectangles.push_back(std::make_shared<A1Rectangle>(
                rData.x, rData.y,                       // Position
                rData.sx, rData.sy,                     // Velocity
                rData.w, rData.h,                       // Size
                rData.name,                             // Name
                rData.r, rData.g, rData.b,              // Color
                font, fData.r, fData.g, fData.b));      // Font
        }
        else
        {
            std::cerr << "Unknown \"" << type << "\"" << std::endl;
        }
    }
    config_file.close();

    std::cout << fData.font_name << " " << fData.font_size << std::endl;
    std::string fontPath = std::string("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\") + fData.font_name;

    SetTargetFPS(60);

    SetTextLineSpacing(16);

    //SetTargetFPS(60);
    InitWindow(wData.width, wData.height, "Assigments 1 CS4300");
    Font chikifont = LoadFontEx("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\res\\pixantiqua.ttf", 32, 0, 250);

    while (!WindowShouldClose())
    {
        /* === EVENTS === */

        /* === GAME LOGIC === */

        for (size_t i = 0; i < circles.size(); i++)
        {
            circles[i]->update(wData.width, wData.height);
        }

        for (size_t i = 0; i < rectangles.size(); i++)
        {
            rectangles[i]->update(wData.width, wData.height);
        }

        /* === RENDERING === */
        BeginDrawing();
        ClearBackground(BLACK);

        DrawFPS(0, 0);

        DrawTextEx(chikifont, "Hi, My name is Ren4", Vector2{ 10.f, 10.f }, 32.f, 2.f, MAGENTA);
        DrawTextEx(chikifont, "BiliBili", Vector2{ 20.0f, 100.0f }, (float)chikifont.baseSize, 2, LIME);

        for (size_t i = 0; i < circles.size(); i++)
        {
            circles[i]->draw();
        }

        for (size_t i = 0; i < rectangles.size(); i++)
        {
            rectangles[i]->draw();
        }
        
        EndDrawing();
    }

    UnloadFont(chikifont);
    UnloadFont(font);

    CloseWindow();

    return 0;
}
#else
/*******************************************************************************************
*
*   raylib [text] example - Font loading
*
*   NOTE: raylib can load fonts from multiple input file formats:
*
*     - TTF/OTF > Sprite font atlas is generated on loading, user can configure
*                 some of the generation parameters (size, characters to include)
*     - BMFonts > Angel code font fileformat, sprite font image must be provided
*                 together with the .fnt file, font generation cna not be configured
*     - XNA Spritefont > Sprite font image, following XNA Spritefont conventions,
*                 Characters in image must follow some spacing and order rules
*
*   Example originally created with raylib 1.4, last time updated with raylib 3.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - font loading");

    // Define characters to draw
    // NOTE: raylib supports UTF-8 encoding, following list is actually codified as UTF8 internally
    const char msg[256] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI\nJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmn\nopqrstuvwxyz{|}~¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ\nÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷\nøùúûüýþÿ";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // BMFont (AngelCode) : Font data and image atlas have been generated using external program
    //Font fontBm = LoadFont("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\res\\pixantiqua.fnt");

    // TTF font : Font data and atlas are generated directly from TTF
    // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    Font fontTtf = LoadFontEx("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\res\\pixantiqua.ttf", 32, 0, 250);

    SetTextLineSpacing(16);         // Set line spacing for multiline text (when line breaks are included '\n')

    bool useTtf = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_SPACE)) useTtf = true;
        else useTtf = false;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hold SPACE to use TTF generated font", 20, 20, 20, LIGHTGRAY);

        //if (!useTtf)
        //{
        //    DrawTextEx(fontBm, msg, Vector2{ 20.0f, 100.0f }, (float)fontBm.baseSize, 2, MAROON);
        //    DrawText("Using BMFont (Angelcode) imported", 20, GetScreenHeight() - 30, 20, GRAY);
        //}
        //else
        {
            DrawTextEx(fontTtf, msg, Vector2{ 20.0f, 100.0f }, (float)fontTtf.baseSize, 2, LIME);
            DrawText("Using TTF font generated", 20, GetScreenHeight() - 30, 20, GRAY);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadFont(fontBm);     // AngelCode Font unloading
    UnloadFont(fontTtf);    // TTF Font unloading

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
#endif