#include "../Canvas.hpp"
#include "../Color.hpp"
#include "../util.hpp"

bool testCreateCanvas()
{
    Canvas c = Canvas(10,20);
    bool complete = true;
    int height = c.Height();
    int width = c.Width();
    for(int i = 0; i<width; i++)
    {
        for(int j =0; j<height; j++)
        {
            complete &= c[i][j] == Color();
        }
    }
    return c.Height() == 20 && c.Width() == 10 && complete;
}

bool testWriteCanvas()
{
    Canvas c = Canvas(10,20);
    Color red = Color(1,0,0);

    c[2][3] = red;

    return c[2][3] == red;
}

bool testSaveCanvas()
{
    Canvas c = Canvas(5,3);
    Color c1 = Color(1.5, 0,0);
    Color c2 = Color(0,0.5,0);
    Color c3 = Color(-0.5, 0,1);

    c[0][0] = c1;
    c[2][1] = c2;
    c[4][2] = c3;

    c.save("img.ppm");
    return true;
}