double MyCatmullRom (array_t <stt, double, 4> & y, double t);
void DrawCatmullRom (array_t <stt, vect_t, 4> & points, char radiusMouse, char brightMouse, COLORREF colorDrawing);
void DrawCatmullRom (vect_t point1, vect_t point2, vect_t point3, vect_t point4,
                     char radiusMouse, char brightMouse, COLORREF colorDrawing);

double MyCatmullRom (array_t <stt, double, 4> & y, double t)
    {
    double m0 = (y[2] - y[0]) / 2,
           m1 = (y[3] - y[1]) / 2;

    double t2   = t*t,
           t3   = t2 * t,
           t3_2 = t3 * 2,
           t2_3 = t2 * 3;

    double hermite00 =  t3_2 - t2_3 + 1;
    double hermite10 =  t3   - t2*2 + t;
    double hermite01 = -t3_2 + t2_3;
    double hermite11 =  t3   - t2;

    return hermite00 * y[1] + hermite10 * m0 +
           hermite01 * y[2] + hermite11 * m1;
    }

void DrawCatmullRom (array_t <stt, vect_t, 4> & points, char radiusMouse, char brightMouse, COLORREF colorDrawing)
    {
    //SetColors (radiusMouse, MulColor (colorDrawing, brightMouse / 256.0), MulColor (colorDrawing, brightMouse / 256.0));
    //txLine (points[1].x, points[1].y, points[2].x, points [2].y);

    const int amountPixels = std::max (abs (points[2].x - points[1].x), abs (points[2].y - points[1].y)) + 1;

    array_t <stt, double, 4> xPoint,
                             yPoint;

    for (int number = 0; number < 4; number++)
        {
        xPoint [number] = points [number].x;
        yPoint [number] = points [number].y;
        }

    vect_t pixel;

    SetColors (MulColor (colorDrawing, brightMouse / 256.0));

    for (int number = 0; number <= amountPixels; number++)
        {
        pixel.x = MyCatmullRom (xPoint, (double) number / (double) amountPixels);
        pixel.y = MyCatmullRom (yPoint, (double) number / (double) amountPixels);

        txCircle (pixel.x, pixel.y, radiusMouse);
        }
    }

void DrawCatmullRom (vect_t point0, vect_t point1, vect_t point2, vect_t point3,
                     char radiusMouse, char brightMouse, COLORREF colorDrawing)
    {
    array_t <stt, vect_t, 4> points;

    points [0] = point0;
    points [1] = point1;
    points [2] = point2;
    points [3] = point3;

    DrawCatmullRom (points, radiusMouse, brightMouse, colorDrawing);
    }

























