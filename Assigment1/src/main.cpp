#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cassert>

#include <raylib.h>

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

    Font font;


    std::ifstream config_file("G:\\Code\\CS4300\\Assigment1\\build\\Debug\\res\\config.txt");

    if (!config_file.is_open())
    {
        std::cerr << "Failed to open file " << "\"res\\config.txt\"" << std::endl;
        exit(-1);
    }

    std::string type;

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
            if (!IsFontValid(font))
            {
                std::cerr << "Failed to load font: " << fData.font_name << "\n";
                exit(-1);
            }
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
    
    //SetTargetFPS(60);
    InitWindow(wData.width, wData.height, "Assigments 1 CS4300");

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

        for (size_t i = 0; i < circles.size(); i++)
        {
            circles[i]->draw();
        }

        for (size_t i = 0; i < rectangles.size(); i++)
        {
            //if (!IsFontValid(font))
            //{
            //    std::cerr << "Corrupted font" << std::endl;
            //}
            rectangles[i]->draw();
        }
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
