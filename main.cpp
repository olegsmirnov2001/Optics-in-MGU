#include "MyLib.h"

//{ Classes: //

class pixel_t
    {
    vect_t pos;
    char bright;
    char radius;

    pixel_t () :
        pos (0, 0),
        bright (0)
        {}

    char* Print ()
        {
        char text [LengthText];

        sprintf (text, "%s %d", pos.Print (), bright);

        return text;
        }
    };

//}

//{ Constants: //

const COLORREF ColorDrawing = _RED;

const int LengthSpace = 50;
const rect_t AreaDrawing (LengthSpace, LengthSpace, Window.x - LengthSpace, Window.y - LengthSpace);

//}

//{ Prototypes List: //

template <template <typename, int> class Type, int Sz>
bool Main (array_t <Type, button_t, Sz> & buttons);
bool DrawAreaDrawing ();

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

    //matrix_t <pixel_t> window (Window);

    txBegin ();

    while (!Exit ())
        {
        if ((txMouseButtons () % 2 == 1) && (Inside (AreaDrawing, txMousePos ())))
            {
            SetColors (MulColor (ColorDrawing, brightMouse / 256.0));
            txCircle (txMousePos ().x, txMousePos ().y, radiusMouse);
            }

        //

        DoOperationsWithButtons (buttons);

        DrawAreaDrawing ();

        //

        txSleep (1);

        Clear ();
        }

    txEnd ();

    return true;
    }

bool DrawAreaDrawing ()
    {
    SetColors (5, _YELLOW, _NULL);
    DrawRect (AreaDrawing);

    return true;
    }













