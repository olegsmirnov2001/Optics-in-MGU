//{ //Constants:: //

const int AmountButtonPictures = 3;

const int PictureButton      = 0;
const int PictureButtonBack  = 1;
const int PictureButtonKrest = 2;

const int AmountConditions = 3;

const int ConditionUsual = 0;
const int ConditionMouse = 1;
const int ConditionSet   = 2;

//}

//{ //Typedefs:: //

typedef array_t <stt, HDC,                   AmountConditions> button_pictures_t;
typedef array_t <stt, button_pictures_t, AmountButtonPictures> pictures_t;

//}

//{ //Initializater list:: //

bool LoadBackground (HDC * background);
bool LoadPictures (pictures_t& pictures);
bool DeletePictures (pictures_t& pictures);
bool DrawBackground (HDC background);

//}

bool LoadBackground (HDC * background)
    {
    *background = txLoadImage ("Resourses\\Pictures\\background.bmp");

    if (*background == NULL)
        AllGoneBad ("The background hasn't loaded");

    return (*background != NULL);
    }

bool LoadPictures (pictures_t& pictures)
    {
    pictures [PictureButton][ConditionUsual] = txLoadImage ("Resourses\\Pictures\\button1.bmp");
    pictures [PictureButton][ConditionMouse] = txLoadImage ("Resourses\\Pictures\\button2.bmp");
    pictures [PictureButton][ConditionSet  ] = txLoadImage ("Resourses\\Pictures\\button3.bmp");

    pictures [PictureButtonBack][ConditionUsual] = txLoadImage ("Resourses\\Pictures\\back21.bmp");
    pictures [PictureButtonBack][ConditionMouse] = txLoadImage ("Resourses\\Pictures\\back22.bmp");
    pictures [PictureButtonBack][ConditionSet  ] = txLoadImage ("Resourses\\Pictures\\back23.bmp");

    pictures [PictureButtonKrest][ConditionUsual] =
    pictures [PictureButtonKrest][ConditionMouse] =
    pictures [PictureButtonKrest][ConditionSet  ] = txLoadImage ("Resourses\\Pictures\\krest.bmp");

    for (int number = 0; number < AmountButtonPictures; number++)
    for (int num    = 0; num    < AmountConditions    ; num   ++)
        if (pictures [number][num] == NULL)
            {
            char text [LengthText];
            sprintf (text, "A picture with number %d - %d hasn't loaded", number, num);
            AllGoneBad (text);
            }

    return true;
    }

bool DeletePictures (pictures_t& pictures)
    {
    for (int number = 0; number < AmountButtonPictures; number++)
    for (int num    = 0; num    < AmountConditions    ; num   ++)
        if (pictures [number][num] != NULL)
            {
            txDeleteDC (pictures [number][num]);
            pictures [number][num] = NULL;
            }

    return true;
    }

bool DrawBackground (HDC background)
    {
    return txBitBlt (txDC (), 0, 0, Window.x, Window.y, background, 0, 0);
    }



















