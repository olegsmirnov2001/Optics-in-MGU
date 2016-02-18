#include "Includes\\MyLib.h"

//{ Defines: //

//#define print(COLORREF color) ((color) & 0xFF), ((color >> 8) & 0xFF), ((color >> 16) & 0xFF)

//}

//{ Constants: //

const COLORREF ColorDrawing = _RED;

const COLORREF ColorResult = _YELLOW;

const COLORREF ColorLoading = _GREEN;

const rect_t AreaDrawing (340, 50, 490, 200); //(340, 50, 1260, 1150);
const rect_t AreaResult  (340, 50, 490, 200);

const int BeginSizePreviousPushes = 256;

const int ToolBrush  = 0;
const int ToolRubber = 1;
const int ToolRuler  = 2;
const int ToolCircle = 3;
const int ToolEllips = 4;

const int MaxRadiusMouse = 100;
const int MaxBright      = 250;

const int BeginRadiusMouse  = 5;
const int BeginBrightMouse  = 250;
const int BeginBrightInside = 0;

const int BeginSizePreviousPushes = 256;

//}

//{ Classes: //

class pixel_t
    {
    public:

    unsigned char bright;

    pixel_t () :
        bright (0)
        {}

    char* Print ()
        {
        static char text [LengthText];

        sprintf (text, "%d", bright);

        return text;
        }

    char* Print () const
        {
        static char text [LengthText];

        sprintf (text, "%d", bright);

        return text;
        }

    bool SetIt (COLORREF color)
        {
        //printf ("I am not a mushroom\n");

        unsigned char colorNow     = 0;
        unsigned char colorDrawing = 0;

        for (int moveColor = 0; moveColor <= 16; moveColor += 8)
            {
            colorNow     = ((color        >> moveColor) & 0xFF);
            colorDrawing = ((ColorDrawing >> moveColor) & 0xFF);

            if (colorDrawing != 0)
                {
                bright = 256.0 * colorNow / colorDrawing;

                //printf ("I Got It!!! %d %d ^^ %d\n", colorNow, colorDrawing, bright);

                return true;
                }
            }

        printf ("I Got Nothing!!!\n");

        bright = 0;
        return false;
        }

    COLORREF Color ()
        {
        return MulColor (ColorDrawing, bright / 256.0);
        }
    };

//}

//{ Prototypes List: //

bool CreatingPicture (matrix_t <unsigned char> & picture);
bool Drawing (int tool, int toolBefore, array_t <dyn, vect_t> & previousPushes, int * amountPreviousPushes,
              int radiusMouse, int brightMouse, int brightInside);
bool DrawAreaDrawing ();
bool LoadBuffer (buffer_t * buffer);
bool GenerateResultBuffer (buffer_t * buffer, matrix_t <unsigned char> & result);
bool SaveBuffer (buffer_t * buffer, matrix_t <unsigned char> & picture);
bool DrawResult (matrix_t <unsigned char> & result);

//}

int main ()
    {
    CreateMyWindow ();

    matrix_t <unsigned char> picture ((int) AreaDrawing.x (), (int) AreaDrawing.y ());
    matrix_t <unsigned char> result  ((int) AreaDrawing.x (), (int) AreaDrawing.y ());

    CreatingPicture (picture);

    GenerateResult (picture, result);

    DrawResult (result);

    //_txExit = true;
    return 0;
    }

bool CreatingPicture (matrix_t <unsigned char> & picture)
    {
    //{ Initializing pictures

    pictures_t pictures;
    HDC background;
    LoadPictures   (pictures);
    LoadBackground (&background);

    //}

    //{ Initializing buttons & scrollbars

    array_t <dyn, button_t> buttons (0);
    array_t <dyn, scrollbar_t> scrollbars (0);
    SetButtonsAndScrollbars (buttons, scrollbars, pictures);

    int buttonPressed = NothingPressed;

    //}

    //{ Creating buffers

    HDC bufferTerm = txCreateCompatibleDC (AreaDrawing.x (), AreaDrawing.y ());

    buffer_t bufferPerm (Window);
    LoadBuffer (&bufferPerm);

    //}

    //{ Creating some other things

    int radiusMouse  = BeginRadiusMouse,
        brightMouse  = BeginBrightMouse,
        brightInside = BeginBrightInside;

    int tool       = NothingSelected;
    int toolBefore = NothingSelected;

    //}

    //{ Creating an array with previous pushes

    int amountPreviousPushes = 0;
    array_t <dyn, vect_t> previousPushes (BeginSizePreviousPushes);

<<<<<<< HEAD
    //}
=======
    int amountPreviousPushes = 0;
    array_t <dyn, vect_t> previousPushes (BeginSizePreviousPushes);
>>>>>>> origin/master

    txBegin ();

    while ((!Exit ()) && (tool != ButtonKrest)) //Main loop
        {
        DEBUG printf ("Amounts: %d - %d\n", amountPreviousPushes, previousPushes.sz);

<<<<<<< HEAD
        txBitBlt (txDC (), AreaDrawing.x1,  AreaDrawing.y1, AreaDrawing.x (), AreaDrawing.y (), bufferTerm, 0, 0);

        Drawing (tool, toolBefore, previousPushes, &amountPreviousPushes, radiusMouse, brightMouse, brightInside);

        txBitBlt (bufferTerm, 0, 0, AreaDrawing.x (), AreaDrawing.y (),
                  txDC (), AreaDrawing.x1, AreaDrawing.y1);

        DrawBackground (background);
=======
        if ((txMouseButtons () % 2 == 1) && (Inside (AreaDrawing, txMousePos ())))
            {
            amountPreviousPushes++;
            if (amountPreviousPushes > previousPushes.sz)
                previousPushes.Move (previousPushes.sz * 2);

            previousPushes [amountPreviousPushes - 1] = vect_t (txMousePos ());
            }
        else
            {
            if (amountPreviousPushes > 0)
                {
                if (amountPreviousPushes == 2)
                    {
                    DrawLine (previousPushes [0], previousPushes [1]);
                    }

                if (amountPreviousPushes >= 3)
                    {
                    DrawCatmullRom (previousPushes [amountPreviousPushes - 3], previousPushes [amountPreviousPushes - 2],
                                    previousPushes [amountPreviousPushes - 1], previousPushes [amountPreviousPushes - 1],
                                    radiusMouse, brightMouse, ColorDrawing);
                    }

                amountPreviousPushes = 0;
                previousPushes.Move (BeginSizePreviousPushes);
                }
            }

        if (amountPreviousPushes == 1)
            {
            SetColors (MulColor (ColorDrawing, brightMouse / 256.0));
            txCircle (txMousePos ().x, txMousePos ().y, radiusMouse);
            }

        if (amountPreviousPushes == 3)
            {
            DrawCatmullRom (previousPushes [0], previousPushes [0], previousPushes [1], previousPushes [2],
                            radiusMouse, brightMouse, ColorDrawing);
            }

        if (amountPreviousPushes >= 4)
            {
            array_t <stt, vect_t, 4> newPoints (previousPushes, amountPreviousPushes - 4);
            DrawCatmullRom (newPoints, radiusMouse, brightMouse, ColorDrawing);
            }
>>>>>>> origin/master

        Flush (txDC(), bufferPerm, AreaDrawing);

        txTransparentBlt (txDC (), AreaDrawing.x1,  AreaDrawing.y1, AreaDrawing.x (), AreaDrawing.y (), bufferTerm, 0, 0);

        if (((toolBefore != tool) && (tool != ButtonBack)) || ((tool == ButtonLines) && (amountPreviousPushes == 1)) ||
            ((tool == ButtonCircle) && (amountPreviousPushes == 1)))
            FlushBack (txDC(), bufferPerm, AreaDrawing);

        DrawAreaDrawing ();

        //

        toolBefore = tool;
        tool = DoOperationsWithButtons (buttons, &buttonPressed);

        scrollbars [ScrollbarThinkness].DoEverything (&radiusMouse, MaxRadiusMouse);
        scrollbars [ScrollbarBright   ].DoEverything (&brightMouse, MaxBright);

        if (tool == ButtonCircle)
            scrollbars [ScrollbarBrightInside].DoEverything (&brightInside, MaxBright);

        //

        txSleep (1);

        while (GetAsyncKeyState (VK_SPACE))
            txSleep (10);
        }

    txEnd ();

    //{ Here I'm copying everything from termorary to permanent buffer again

    Flush (txDC(), bufferPerm, AreaDrawing);
    txTransparentBlt (txDC (), AreaDrawing.x1,  AreaDrawing.y1, AreaDrawing.x (), AreaDrawing.y (), bufferTerm, 0, 0);
    FlushBack (txDC(), bufferPerm, AreaDrawing);

    //}

    //{ Here I'm deleting DCs and saving data

    DeletePictures (pictures);
    txDeleteDC (background);
    txDeleteDC (bufferTerm);

    SaveBuffer (&bufferPerm, picture);

    //}

    Clear ();

    return true;
    }

bool Drawing (int tool, int toolBefore, array_t <dyn, vect_t> & previousPushes, int * amountPreviousPushes,
              int radiusMouse, int brightMouse, int brightInside)
    {
    COLORREF colorNow       = _BLACK,
             colorNowInside = _BLACK;

    if ((tool == ButtonBrush) || (tool == ButtonLines) || (tool == ButtonRubber) || (tool == ButtonCircle))
        colorNow = (tool == ButtonRubber) ? (RGB (0, 0, 1)) : (MulColor (ColorDrawing, brightMouse / 256.0));

    if (tool == ButtonCircle)
        colorNowInside = MulColor (ColorDrawing, brightInside / 256.0);

    if ((txMouseButtons () % 2 == 1) && (Inside (AreaDrawing, txMousePos ())))
        {
        (*amountPreviousPushes)++;
        if (*amountPreviousPushes > previousPushes.sz)
            previousPushes.Move (previousPushes.sz * 2);

        previousPushes [*amountPreviousPushes - 1] = vect_t (txMousePos ());
        }
    else
        {
        if (*amountPreviousPushes > 0)
            {
            if ((tool == ButtonBrush) || (tool == ButtonRubber))
                {
                if (*amountPreviousPushes == 2)
                    {
                    SetColors (radiusMouse * 2, colorNow, colorNow);
                    DrawLine (previousPushes [0], previousPushes [1]);
                    }

                if (*amountPreviousPushes >= 3)
                    {
                    DrawCatmullRom (previousPushes [*amountPreviousPushes - 3], previousPushes [*amountPreviousPushes - 2],
                                    previousPushes [*amountPreviousPushes - 1], previousPushes [*amountPreviousPushes - 1],
                                    (char) radiusMouse, colorNow);
                    }
                }

            if (*amountPreviousPushes > BeginSizePreviousPushes)
                previousPushes.Move (BeginSizePreviousPushes);

            *amountPreviousPushes = 0;
            }
        }

    if ((tool == ButtonBrush) || (tool == ButtonRubber))
        {
        if (*amountPreviousPushes == 1)
            {
            SetColors (colorNow);
            txCircle (txMousePos ().x, txMousePos ().y, radiusMouse);
            }

        if (*amountPreviousPushes == 3)
            {
            DrawCatmullRom (previousPushes [0], previousPushes [0], previousPushes [1], previousPushes [2],
                            (char) radiusMouse, colorNow);
            }

        if (*amountPreviousPushes >= 4)
            {
            array_t <stt, vect_t, 4> newPoints (previousPushes, *amountPreviousPushes - 4);
            DrawCatmullRom (newPoints, (char) radiusMouse, colorNow);
            //txSetColor (colorNow, radiusMouse * 2);
            //DrawLine (previousPushes [amountPreviousPushes - 3], previousPushes [amountPreviousPushes - 2]);
            }
        }

    if ((tool == ButtonClear) && (toolBefore != ButtonClear))
        {
        SetColors (RGB (0, 0, 1));
        DrawRect (AreaDrawing);
        }

    if ((tool == ButtonBack) && (toolBefore != ButtonBack))
        {
        Clear ();
        }

    if ((tool == ButtonLines) && (*amountPreviousPushes >= 2))
        {
        Clear ();
        txSetColor (colorNow, radiusMouse * 2);
        DrawLine (previousPushes [0], previousPushes [*amountPreviousPushes - 1]);
        }

    if ((tool == ButtonCircle) && (*amountPreviousPushes >= 2))
        {
        Clear ();
        SetColors (colorNow, colorNowInside);
        DrawEllipse (previousPushes [0], previousPushes [*amountPreviousPushes - 1], radiusMouse * 2);
        }

    return true;
    }

bool DrawAreaDrawing ()
    {
    SetColors (5, _YELLOW, _NULL);
    DrawRect (AreaDrawing);

    return true;
    }

<<<<<<< HEAD
bool LoadBuffer (buffer_t * buffer)
    {
    FILE* f = fopen ("Resourses\\Save point.txt", "r");
    if (f == NULL)
        {
        AllGoneBad ("The saving file hasn't opened");
        return false;
        }

    vect_t szBuffer (0, 0);
    if (fscanf (f, "%lg %lg", &(szBuffer.x), &(szBuffer.y)) == 0)
        AllGoneBad ("Something is strange");

    DEBUG printf ("size in file - %s\n", szBuffer.Print ());
    DEBUG printf ("size in prog - %s\n", AreaDrawing.Print ());

    bool AllOk = (szBuffer.x == (int) AreaDrawing.x ()) && (szBuffer.y == (int) AreaDrawing.y ());

    if (!AllOk)
        {
        printf ("The saving file size and now size are not same\n");
        }
    else
        {
        pixel_t pixel;

        for (int xNow = 0; xNow < AreaDrawing.x (); xNow++)
        for (int yNow = 0; yNow < AreaDrawing.y (); yNow++)
            {
            fscanf (f, "%d", &(pixel.bright));

            buffer->PutPixel (xNow + (int) AreaDrawing.x1, yNow, pixel.Color ());
            }
        }

    fclose (f);

    return AllOk;
    }

bool GenerateResultBuffer (buffer_t * buffer, matrix_t <unsigned char> & result)
    {
    if (!((result.sz1 == (int) AreaResult.x ()) && (result.sz2 == (int) AreaResult.y ())))
        return false;

    for (int number1 = 0; number1 < result.sz1; number1++)
    for (int number2 = 0; number2 < result.sz2; number2++)
        buffer->PutPixel (number1 + (int) AreaResult.x1, number2, MulColor (ColorResult, result [number1][number2] / 256.0));

    return true;
    }

bool SaveBuffer (buffer_t * buffer, matrix_t <unsigned char> & picture)
    {
    FILE* f = fopen ("Resourses\\Save point.txt", "w+");
    if (f == NULL)
        {
        AllGoneBad ("The saving file hasn't opened");
        return false;
        }

    fprintf (f, "%lg %lg\n", AreaDrawing.x (), AreaDrawing.y ());

    pixel_t pixel;

    txSetColor (ColorLoading, 1);

    for (int xNow = 0; xNow < AreaDrawing.x (); xNow++)
        {
        for (int yNow = 0; yNow < AreaDrawing.y (); yNow++)
            {
            pixel.SetIt (buffer->GetPixel (xNow + (int) AreaDrawing.x1, yNow));
            fprintf (f, "%s\n", pixel.Print ());

            picture [xNow][yNow] = pixel.bright;
            }

        txLine (xNow + AreaDrawing.x1, AreaDrawing.y1, xNow + AreaDrawing.x1, AreaDrawing.y2);
        }

    fclose (f);

    return true;
    }

bool DrawResult (matrix_t <unsigned char> & result)
    {
    txClearConsole ();

    buffer_t buffer (Window);

    GenerateResultBuffer (&buffer, result);

    Flush (txDC (), buffer, AreaResult);

    printf ("It happened!!!\n");

    //DrawAreaDrawing (); //!!! Just if AreaDrawing == AreaResult

    return true;
    }

/* ј это - костыли.  огда € начинал писать этот код, € исользовал их и еще ~100 таких же.

=======
>>>>>>> origin/master
bool ClearEdges ()  // это - адский костыль
    {
    for (int xNow = 0; xNow < Window.x; xNow++)
        {
        for (int yNow = 0; yNow < AreaDrawing.y1; yNow++)
            DirectTXPutPixel (xNow, yNow, _BLACK);
        for (int yNow = AreaDrawing.y2; yNow <= Window.y; yNow++)
            DirectTXPutPixel (xNow, yNow, _BLACK);
        }

    for (int yNow = AreaDrawing.y1; yNow < AreaDrawing.y2; yNow++)
        {
        for (int xNow = 0; xNow < AreaDrawing.x1; xNow++)
            DirectTXPutPixel (xNow, yNow, _BLACK);
        for (int xNow = AreaDrawing.x2; xNow < Window.x; xNow++)
            DirectTXPutPixel (xNow, yNow, _BLACK);
        }

    return true;
    }

bool GetPicture (matrix_t <pixel_t> & window)
    {
    for (int xNow = AreaDrawing.x1; xNow < AreaDrawing.x2; xNow++)
        for (int yNow = AreaDrawing.y1; yNow < AreaDrawing.y2; yNow++)
            window[xNow][yNow].SetIt (txGetPixel (xNow, yNow));

    return true;
    }

bool PrintPicture (matrix_t <pixel_t> & window)
    {
    for (int xNow = AreaDrawing.x1; xNow < AreaDrawing.x2; xNow++)
        for (int yNow = AreaDrawing.y2; yNow < AreaDrawing.y2; yNow++)
            txSetPixel (xNow, yNow, MulColor (ColorDrawing, window[xNow][yNow].bright));

    return true;
    }
*/













