class buffer_t
    {
    public:

    vect_t sz;
    int datasz;

    unsigned char* data;

    BITMAPINFO bitmapInfo;

    //

    buffer_t () :
        sz (0, 0),
        datasz (0),
        data (NULL),
        bitmapInfo ()
        {}

    buffer_t (vect_t bufferSz) :
        sz (bufferSz),
        datasz ((((int) sz.x) * 3 + ((int) sz.x) % 4) * ((int) sz.y)),
        data (new unsigned char [datasz]),
        bitmapInfo ({{sizeof (BITMAPINFOHEADER), sz.x, sz.y, 1, 24, BI_RGB, 0, 0, 0}, {{}}})
        {}

    buffer_t (int bufferSzX, int bufferSzY) :
        sz (bufferSzX, bufferSzY),
        datasz ((((int) sz.x) * 3 + ((int) sz.x) % 4) * ((int) sz.y)),
        data (new unsigned char [datasz]),
        bitmapInfo ({{sizeof (BITMAPINFOHEADER), sz.x, sz.y, 1, 24, BI_RGB, 0, 0, 0}, {{}}})
        {}

    bool PutPixel (int x, int y, COLORREF color)
        {
        int sizeX = ((int) sz.x) * 3 + ((int) sz.x) % 4;
        int index = sizeX * y + 3 * x;

        if (!(0 <= index && index < datasz))
            return false;

        data [index + 2] = (color      ) & 0xFF;
        data [index + 1] = (color >> 8 ) & 0xFF;
        data [index    ] = (color >> 16) & 0xFF;

        //if (((x == 1549) && (y == 840)) || ((x == 250) && (y == 840)))
        //    printf ("Buffer:: %d %d - %d\n", x, y, color);

        return true;
        }

    COLORREF GetPixel (int x, int y)
        {
        int sizeX = ((int) sz.x) * 3 + ((int) sz.x) % 4;
        int index = sizeX * y + 3 * x;

        if (!(0 <= index && index < datasz))
            return Nothing;

        return RGB (data [index + 2],
                    data [index + 1],
                    data [index    ]);
        }
    };

//{ //Initializater list: //

void Flush (HDC picture, buffer_t buffer, rect_t area);
void FlushBack (HDC picture, buffer_t buffer, rect_t area);

//}

void Flush (HDC picture, buffer_t buffer, rect_t area)
    {
    Win32::SetDIBitsToDevice (picture, (int) area.x1, (int) area.y1, (int) area.x (), (int) area.y (),
                                       (int) area.x1, (int) area.y1, (int) area.y1  , (int) area.y (),
                                       buffer.data, &buffer.bitmapInfo, DIB_RGB_COLORS);
    }

void FlushBack (HDC picture, buffer_t buffer, rect_t area)
    {
    Win32::GetDIBits         (picture, (HBITMAP) Win32::GetCurrentObject (picture, OBJ_BITMAP),
                             (unsigned int)(Window.y - area.y2), (unsigned int)area.y2, buffer.data, &buffer.bitmapInfo, DIB_RGB_COLORS);

    }























