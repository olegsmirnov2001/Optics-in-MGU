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

    button_pictures_t pictures;

    private:

    int condition;

    //

    public:

    button_t () :
        pos (),
        name ((char*) new char [LengthText]),
        colorLine (_NULL),
        colorFill (_NULL),
        colorName (_NULL),
        key (0),
        pictures (),
        condition (ConditionUsual)
        {
        DEBUG printf ("An object of type <<button_t>> has appeared, 1\n");
        }

    button_t (rect_t Apos, char * Aname, button_pictures_t& Apictures,
                                         COLORREF AcolorLine = _WHITE,
                                         COLORREF AcolorFill = _WHITE,
                                         COLORREF AcolorName = _BLACK,
                                         int Akey = 0) :
        pos (Apos),
        name ((char*) new char [LengthText]),
        colorLine (AcolorLine),
        colorFill (AcolorFill),
        colorName (AcolorName),
        key (Akey),
        condition (ConditionUsual),
        pictures ()
        {
        DEBUG printf ("An object of type <<button_t>> has appeared, 2\n");

        sprintf (name, Aname);

        for (int number = 0; number < AmountConditions; number++)
            pictures [number] = Apictures [number];
        }

    button_t (const button_t& button) :
        pos (button.pos),
        name ((char*) new char [LengthText]),
        colorLine (button.colorLine),
        colorFill (button.colorFill),
        colorName (button.colorName),
        key (button.key),
        condition ((char) ConditionUsual),
        pictures ()
        {
        DEBUG printf ("An object of type <<button_t>> has appeared, 3\n");

        sprintf (name, button.name);

        for (int number = 0; number < AmountConditions; number++)
            pictures [number] = button.pictures [number];
        }

    const button_t& operator = (const button_t& button)
        {
        pos = button.pos;
        sprintf (name, button.name);
        colorLine = button.colorLine;
        colorFill = button.colorFill;
        colorName = button.colorName;
        key = button.key;

        DEBUG printf ("An object of type <<button_t>> has been copied");

        for (int number = 0; number < AmountConditions; number++)
            pictures [number] = button.pictures [number];

        return *this;
        }

    ~button_t ()
        {
        DEBUG printf ("An object of type <<button_t>> has been deleted\n");

        delete [] name;
        }

    bool Set (rect_t Apos, char* Aname, button_pictures_t& Apictures,
              COLORREF AcolorLine = _WHITE, COLORREF AcolorFill = _WHITE, COLORREF AcolorName = _BLACK, char Akey = 0)
        {
        pos = Apos;
        sprintf (name, Aname);
        colorLine = AcolorLine;
        colorFill = AcolorFill;
        colorName = AcolorName;
        key = Akey;
        condition = ConditionUsual;

        for (int number = 0; number < AmountConditions; number++)
            pictures [number] = Apictures [number];

        return true;
        }

    bool Draw ()
        {
        DEBUG printf ("Begin of Drawing\n");
        DEBUG printf ("Pos - %s, name - %s\npicture - %p, cond - %d\n", pos.Print (), name, pictures [ConditionUsual], condition);

        if (pictures [condition] != NULL)
            {
            //printf ("condition - %d\n", condition);
            txBitBlt (txDC (), pos.x1, pos.y1, pos.x2 - pos.x1, pos.y2 - pos.y1, pictures [condition], 0, 0);
            }
        else
            {
            SetColors (1, colorLine, colorFill);
            DrawRect (pos);
            }

        txSetColor (colorName);
        txSelectFont ("Comic Sans MS", (pos.x2 - pos.x1) / 4, (pos.x2 - pos.x1) * 2/5 / 4, FW_BOLD);

        if (name [0] != '_')
            DrawText (pos, name);

        DEBUG printf ("end\n");

        return true;
        }

    int Check ()
        {
        if (condition != ConditionSet)
            {
            if (Inside (pos, txMousePos ()))
                condition = ConditionMouse;
            else
                condition = ConditionUsual;
            }

        return condition;
        }

    int& Condition ()
        {
        return condition;
        }

    bool Pressed ()
        {
        return (((Inside (pos, txMousePos ())) && (txMouseButtons () % 2 == 1)) || (GetAsyncKeyState (key)));
        }
    };

class scrollbar_t
    {
    public:

    rect_t pos;
    rect_t posName;

    int thinknessLines;
    int thinknessWheel;

    COLORREF colorLines;
    COLORREF colorWheel;
    COLORREF colorName;

    char* name;

    //

    scrollbar_t () :
        pos (0, 0, 0, 0),
        posName (0, 0, 0, 0),
        thinknessLines (1),
        thinknessWheel (1),
        colorLines (_WHITE),
        colorWheel (_GRAY),
        colorName (_BLACK),
        name (new char [LengthText])
        {}

    scrollbar_t (rect_t Apos, rect_t AposName, int AthinknessLines, int AthinknessWheel,
                 COLORREF AcolorLines, COLORREF AcolorWheel, COLORREF AcolorName, char* Aname) :
        pos (Apos),
        posName (AposName),
        thinknessLines (AthinknessLines),
        thinknessWheel (AthinknessWheel),
        colorLines (AcolorLines),
        colorWheel (AcolorWheel),
        colorName  (AcolorName),
        name (new char [LengthText])
        {
        sprintf (name, Aname);
        }

    ~scrollbar_t ()
        {
        delete [] name;
        }

    scrollbar_t (const scrollbar_t& scrollbar) :
        pos (scrollbar.pos),
        posName (scrollbar.posName),
        thinknessLines (scrollbar.thinknessLines),
        thinknessWheel (scrollbar.thinknessWheel),
        colorLines (scrollbar.colorLines),
        colorWheel (scrollbar.colorWheel),
        colorName  (scrollbar.colorName),
        name (new char [LengthText])
        {
        sprintf (name, scrollbar.name);
        }

    const scrollbar_t& operator= (const scrollbar_t& scrollbar)
        {
        pos = scrollbar.pos;
        posName = scrollbar.posName;
        thinknessLines = scrollbar.thinknessLines;
        thinknessWheel = scrollbar.thinknessWheel;
        colorLines = scrollbar.colorLines;
        colorWheel = scrollbar.colorWheel;
        colorName  = scrollbar.colorName;
        sprintf (name, scrollbar.name);

        return *this;
        }

    bool Draw (double value)
        {
        double xMiddle = (pos.x1 + pos.x2) / 2;

        txSetColor (colorLines, thinknessLines);

        txLine (pos.x1,  pos.y1, pos.x2,  pos.y1);
        txLine (pos.x1,  pos.y2, pos.x2,  pos.y2);
        txLine (xMiddle, pos.y1, xMiddle, pos.y2);

        //

        double yWheel = pos.y2 - (pos.y2 - pos.y1) * value;

        txSetColor (colorWheel, thinknessWheel);

        txLine (pos.x1, yWheel, pos.x2, yWheel);

        //

        txSetColor (colorName);
        txSelectFont ("Comic Sans MS", (posName.y2 - posName.y1) * 5/2 / 2.5, (posName.y2 - posName.y1) / 2.5, FW_BOLD);

        DrawText (posName, name);

        return true;
        }

    double ChangeValue (double * value, double maxvalue)
        {
        if ((Inside (pos, txMousePos ())) && (txMouseButtons () % 2 == 1))
            {
            double k = ((double) (pos.y2 - txMousePos ().y) / (pos.y2 - pos.y1));

            *value = maxvalue * k;
            }

        return *value;
        }

    bool DoEverything (int * value, int maxvalue)
        {
        this->ChangeValue ((double*) value, (double) maxvalue);
        this->Draw ((double) (*value) / (double) maxvalue);

        return true;
        }
    };

//{ //Constants:

const int NothingPressed  = -1;
const int NothingSelected = -1;

const int ButtonBrush  = 0;
const int ButtonRubber = 1;
const int ButtonLines  = 2;
const int ButtonCircle = 3;
const int ButtonClear  = 4;
const int ButtonBack   = 5;
const int ButtonKrest  = 6;

const int ScrollbarBright          = 0;
const int ScrollbarThinkness       = 1;
const int ScrollbarBrightInside    = 2;
const int ScrollbarThinknessInside = 2;

//}

//{ //Initializater list:

bool SetButtonsAndScrollbars (array_t <dyn, button_t> & buttons, array_t <dyn, scrollbar_t> & scrollbars,
                              pictures_t& pictures);
template <template <typename, int> class Type, int Sz>
int DoOperationsWithButtons (array_t <Type, button_t, Sz> & buttons, int * buttonPressed);

//}

bool SetButtonsAndScrollbars (array_t <dyn, button_t> & buttons, array_t <dyn, scrollbar_t> & scrollbars,
                              pictures_t& all_pictures)
    {
    FILE* f = fopen ("Resourses\\Buttons and scrollbars List.txt", "r");

    if (f == NULL)
        {
        AllGoneBad ((const char*) "The file (Buttons and scrollbars List.txt) hasn't been opened");
        return false;
        }

    int amountButtons = 0;
    fscanf (f, "Buttons::%d\n", &amountButtons);

    if (amountButtons != 0)
        {
        buttons.Move (amountButtons);

        for (int number = 0; number < buttons.sz; number++)
            {
            //sprintf (buttons[number].name, "This is a button %d\n", number);
            fgets (buttons[number].name, LengthText, f);

            DeleteSymbols (buttons[number].name, LengthText, '\n');

            fscanf (f, "%lg, %lg, %lg, %lg\n", &(buttons[number].pos.x1), &(buttons[number].pos.y1),
                                               &(buttons[number].pos.x2), &(buttons[number].pos.y2));

            DEBUG printf ("Number %d set: name - %s; pos - %s\n", number, buttons[number].name, buttons [number].pos.Print ());

            buttons [number].colorLine = _GRAY;
            buttons [number].colorFill = _WHITE;
            buttons [number].colorName = _BLACK;

            switch (number)
                {
                case ButtonBack:  buttons [number].pictures = all_pictures [PictureButtonBack];
                                  break;
                case ButtonKrest: buttons [number].pictures = all_pictures [PictureButtonKrest];
                                  break;
                default:          buttons [number].pictures = all_pictures [PictureButton];
                                  break;
                }
            }
        }

    int amountScrollbars = 0;
    fscanf (f, "\nScrollbars::%d\n", &amountScrollbars);

    if (amountScrollbars != 0)
        {
        scrollbars.Move (amountScrollbars);

        for (int number = 0; number < scrollbars.sz; number++)
            {
            fgets (scrollbars [number].name, LengthText, f);


            DeleteSymbols (scrollbars[number].name, LengthText, '\n');

            fscanf (f, "%lg, %lg, %lg, %lg; %lg\n", &(scrollbars [number].pos.x1), &(scrollbars [number].pos.y1),
                                                    &(scrollbars [number].pos.x2), &(scrollbars [number].pos.y2),
                                                    &(scrollbars [number].posName.y2));

            int xPos = (int)(scrollbars [number].pos.x2 - scrollbars [number].pos.x1);

            scrollbars [number].posName.x1 = scrollbars [number].pos.x1 - xPos;
            scrollbars [number].posName.x2 = scrollbars [number].pos.x2 + xPos;

            scrollbars [number].posName.y1 = scrollbars [number].pos.y2;

            scrollbars [number].colorLines = _YELLOW;
            scrollbars [number].colorWheel = _RED;
            scrollbars [number].colorName  = _BLACK;

            scrollbars [number].thinknessLines = 5;
            scrollbars [number].thinknessWheel = 10;
            }
        }

    fclose (f);

    return true;
    }

template <template <typename, int> class Type, int Sz>
int DoOperationsWithButtons (array_t <Type, button_t, Sz> & buttons, int * buttonPressed)
    {
    int selected = NothingSelected;

    for (int number = 0; number < buttons.sz; number++)
        {
        if (buttons [number].Pressed ())
            {
            if (*buttonPressed != number)
                {
                buttons [number].Condition () = (buttons [number].Condition () == ConditionSet) ?
                                                ConditionUsual : ConditionSet;

                if (buttons [number].Condition () == ConditionSet)
                    for (int num = 0; num < buttons.sz; num++)
                        if (num != number)
                            buttons [num].Condition () = ConditionUsual;

                *buttonPressed = number;
                }
            }
        else
            if (*buttonPressed == number)
                *buttonPressed = NothingPressed;

        buttons [number].Check ();
        buttons [number].Draw ();

        if (buttons [number].Condition () == ConditionSet)
            selected = number;
        }

    return selected;
    }

















