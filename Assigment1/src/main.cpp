#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>

#include <raylib.h>

class A1Circle
{
    float m_x;
    float m_y;
  
    float m_sx;
    float m_sy;

    int r, g, b;

    float m_radius;
    const std::string& m_name;

public:
    A1Circle(float x, float y, float sx, float sy, float radius, int r, int g, int b, const std::string &name)
        : m_x(x)
        , m_y(y)
        , m_sx(sx)
        , m_sy(sy)
        , m_radius(radius)
        , r(r), g(g), b(b)
        , m_name(name)
    {}

    ~A1Circle() {}

    void draw(Font font)
    {
        Color color = {};
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = 255;
        DrawCircle(m_x + m_radius, m_y + m_radius, m_radius, color);
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

    int r, g, b;

    const std::string& m_name;

public:
    A1Rectangle(float x, float y, float sx, float sy, float width, float height, int r, int g, int b, const std::string& name)
        : m_x(x)
        , m_y(y)
        , m_sx(sx)
        , m_sy(sy)
        , m_height(height)
        , m_width(width)
        , r(r), g(g), b(b)
        , m_name(name)
    {}

    ~A1Rectangle() {}

    void draw(Font font)
    {
        if (!IsFontValid(font))
        {
            std::cerr << "Corrupted font\n";
        }

        Color color = {};
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = 255;
        DrawRectangle(m_x, m_y, m_width, m_height, color);
        Vector2 textSize = MeasureTextEx(font, m_name.c_str(), font.baseSize, 1.f);
        Vector2 textPositon = {};
        textPositon.x = 0;
        textPositon.y = 0;
        // TODO: Fix the Font issue. For some reason in hava a font.texture.id == 0.
        // Because of that fuctions can't correctly work with it :(
        DrawTextEx(font, m_name.c_str(), textPositon, font.baseSize, 5, RED);
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

    std::cout << "File opened successfully\n";

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
            font = LoadFontEx(fontPath.c_str(), fData.font_size, nullptr, 250);
            if (!IsFontValid(font))
            {
                std::cerr << "Failed to load font: " << fData.font_name << "\n";
                exit(-1);
            }
        }
        else if (type == "Circle")
        {
            config_file >> cData.name;
            config_file >> cData.x >> cData.y;
            config_file >> cData.sx >> cData.sy;
            config_file >> cData.r >> cData.g >> cData.b;
            config_file >> cData.radius;

            circles.push_back(std::make_shared<A1Circle>(
                cData.x, cData.y,           // Position
                cData.sx, cData.sy,         // Velocity
                cData.radius,               // Radius
                cData.r, cData.g, cData.b,  // Color
                cData.name));               // Name
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
                rData.x, rData.y,           // Position
                rData.sx, rData.sy,         // Velocity
                rData.w, rData.h,           // Size
                rData.r, rData.g, rData.b,  // Color
                rData.name));               // Name
        }
        else
        {
            std::cerr << "Unknown \"" << type << "\"" << std::endl;
        }
    }
    

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

        for (size_t i = 0; i < circles.size(); i++)
        {
            circles[i]->draw(font);
        }

        for (size_t i = 0; i < rectangles.size(); i++)
        {
            rectangles[i]->draw(font);
        }
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
