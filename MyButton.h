//{///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// À¿—— <<button_t>>///////////////////////////////////////////////////////
//}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class button_t
    {
    public:

    rect_t pos;

    char * name;

    COLORREF colorLine;
    COLORREF colorFill;
    COLORREF colorName;

    KEY key;

    HDC picture;

    private:

    bool pushed;

    //

    public:

    button_t () :
        pos (),
        name (),
        colorLine (_NULL),
        colorFill (_NULL),
        colorName (_NULL),
        key (0),
        picture (NULL),
        pushed (false)
        {}

    button_t (rect_t Apos, char * Aname, COLORREF AcolorLine = _WHITE,
                                         COLORREF AcolorFill = _WHITE,
                                         COLORREF AcolorName = _BLACK, HDC Apicture = NULL, int Akey = 0) :
        pos (Apos),
        name (Aname),
        colorLine (AcolorLine),
        colorFill (AcolorFill),
        colorName (AcolorName),
        key (Akey),
        picture (Apicture),
        pushed (false)
        {}

    ~button_t ()
        {
        txDeleteDC (picture);
        picture = NULL;
        }

    bool Set (rect_t Apos = rect_t (), char* Aname = "NOTHING IS WROTEN HERE", COLORREF AcolorLine = _WHITE,
                                                         COLORREF AcolorFill = _WHITE,
                                                         COLORREF AcolorName = _BLACK, HDC Apicture = NULL, int Akey = 0)
        {
        pos = Apos;
        sprintf (name, Aname);
        colorLine = AcolorLine;
        colorFill = AcolorFill;
        colorName = AcolorName;
        key = Akey;
        picture = Apicture;
        pushed = false;

        return true;
        }

    bool Draw ()
        {
        SetColors (1, colorLine, colorFill);
        DrawRect (pos);

        if (picture != NULL)
            txTransparentBlt (txDC (), pos.x1, pos.y1, pos.x2 - pos.x1, pos.y2 - pos.y1, picture, 0, 0);

        txSetColor (colorName);
        txSelectFont ("Comic Sans MS", (pos.y2 - pos.y1), (pos.y2 - pos.y1) * 2/5, FW_BOLD);

        DrawText (pos, name);
        Clear (_GREEN);

        return true;
        }

    bool Check ()
        {
        return pushed = ((Inside (pos, txMousePos ()) && (txMouseButtons () % 2 == 1)) || (GetAsyncKeyState (key)));
        }

    bool Pushed ()
        {
        return pushed;
        }
    };

template <template <typename, int> class Type, int Sz>
bool SetButtons (array_t <Type, button_t, Sz> & buttons)
    {
    if (Sz >= 1)
        buttons [0].Set (rect_t (100, 200, 200, 300), "First button", _RED, _GREEN, _YELLOW);

    if (Sz >= 2)
        buttons [1].Set (rect_t (500, 600, 700, 800), "Second button");

    for (int number = 2; number < Sz; number++)
        buttons [number].Set ();

    return true;
    }

template <template <typename, int> class Type, int Sz>
bool DoOperationsWithButtons (array_t <Type, button_t, Sz> & buttons)
    {
    for (int number = 0; number < Sz; number++)
        {
        buttons [number].Check ();
        buttons [number].Draw ();
        }

    return true;
    }
















