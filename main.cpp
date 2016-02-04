#include "MyLib.h"

//{ Constants: //

const COLORREF ColorDrawing = _RED;

const int LengthSpace = 50;
const rect_t AreaDrawing (LengthSpace, LengthSpace, Window.x - LengthSpace, Window.y - LengthSpace);

//}

//{ Classes: //

class pixel_t
    {
    public:

    char bright;

    pixel_t () :
        bright (0)
        {}

    char* Print ()
        {
        char text [LengthText];

        sprintf (text, "%d", bright);

        return text;
        }

    bool SetIt (COLORREF color)
        {
        //printf ("I am not a mushroom\n");

        for (char moveColor = 0; moveColor <= 16; moveColor += 8)
            {
            char colorNow     = ((color        >> moveColor) & 0xFF);
            char colorDrawing = ((ColorDrawing >> moveColor) & 0xFF);

            if (colorDrawing != 0)
                {
                bright = 256 * colorNow / colorDrawing;

                //printf ("I Got It!!! %d\n", bright);

                return true;
                }
            }

        //printf ("I Got Nothing!!!\n");

        bright = 0;
        return true;
        }
    };

//}

//{ Prototypes List: //

template <template <typename, int> class Type, int Sz>
bool Main (array_t <Type, button_t, Sz> & buttons);
bool DrawAreaDrawing ();
bool GetMatrix (matrix_t <pixel_t> & window);
bool PrintMatrix (matrix_t <pixel_t> & window);

//}

int main ()
    {
    CreateMyWindow ();

    /*

    int a = 0, b = 0;
    scanf ("%d %d", &a, &b);
    printf ("%d %d", a, b);
    Sleep (10000);

    */

    array_t <stt, button_t, 0> buttons;
    SetButtons (buttons);

    Main (buttons);

    _txExit = true;
    return 0;
    }

template <template <typename, int> class Type, int Sz>
bool Main (array_t <Type, button_t, Sz> & buttons)
    {
    int radiusMouse = 0,
        brightMouse = 0;

    scanf ("%d %d", &radiusMouse, &brightMouse);

    matrix_t <pixel_t> window (Window);

    while (!Exit ())
        {
        PrintMatrix (window);

        if ((txMouseButtons () % 2 == 1) && (Inside (AreaDrawing, txMousePos ())))
            {
            SetColors (MulColor (ColorDrawing, brightMouse / 256.0));
            txCircle (txMousePos ().x, txMousePos ().y, radiusMouse);
            }

        GetMatrix (window);

        printf ("%s\n", window [1][1].Print ());

        txBegin ();

        //

        DoOperationsWithButtons (buttons);

        DrawAreaDrawing ();

        //

        txEnd ();

        txSleep (1);

        Clear ();
        }

    return true;
    }

bool DrawAreaDrawing ()
    {
    SetColors (5, _YELLOW, _NULL);
    DrawRect (AreaDrawing);

    return true;
    }

bool GetMatrix (matrix_t <pixel_t> & window)
    {
    for (int xNow = AreaDrawing.x1; xNow < AreaDrawing.x2; xNow++)
        for (int yNow = AreaDrawing.y1; yNow < AreaDrawing.y2; yNow++)
            window[xNow][yNow].SetIt (txGetPixel (xNow, yNow));

    return true;
    }

bool PrintMatrix (matrix_t <pixel_t> & window)
    {
    for (int xNow = AreaDrawing.x1; xNow < AreaDrawing.x2; xNow++)
        for (int yNow = AreaDrawing.y2; yNow < AreaDrawing.y2; yNow++)
            txSetPixel (xNow, yNow, MulColor (ColorDrawing, window[xNow][yNow].bright));

    return true;
    }











