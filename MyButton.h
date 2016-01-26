//{///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// À¿—— <<button_t>>///////////////////////////////////////////////////////
//}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class button_t
    {
    public:

    rect_t pos;

    char* name;

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

    button_t (rect_t Apos, char* Aname, COLORREF AcolorLine = _WHITE,
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

    button_t (const button_t&);
    const button_t& operator = (const button_t&);

    bool Draw ()
        {
        SetColors (1, colorLine, colorFill);
        DrawRect (pos);

        if (picture != NULL)
            txTransparentBlt (txDC (), pos.x1, pos.y1, pos.x2 - pos.x1, pos.y2 - pos.y1, picture, 0, 0);

        txSetColor (colorName);
        txSelectFont ("Comic Sans MS", (pos.y2 - pos.y1), (pos.y2 - pos.y1) * 2/5, FW_BOLD);
        DrawText (pos, name);

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


















