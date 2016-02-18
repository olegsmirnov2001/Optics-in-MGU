//{ //Constants://

const double Lambda = 0.63; // mkm

const double K = 2 * PI / Lambda;

const double Z = 100.0; // mkm
const double Z_2 = Z * Z;

const vect_t D (1.0, 1.0);

const vect_t SizePicture (10.0, 10.0); // mkm
const vect_t SizeResult  (10.0, 10.0); // mkm

const double N0 = 1.33;
const double N  = 1.05;

const double Vel = K * N0 * (N - 1);

const double MaxThinkness = 10.0; // mkm

//}

//{ //Initializater list://

bool GenerateResult (matrix_t <unsigned char> & picture, matrix_t <unsigned char> & result);
inline double Thinkness (unsigned char a);
inline vect_t F (double thinkness, double po);
inline vect_t E0 (double thinkness);
inline vect_t StepenE (double a);
inline unsigned char I (double x, double y);

//}

bool GenerateResult (matrix_t <unsigned char> & picture, matrix_t <unsigned char> & result)
    {
    //printf ("Started generation\n");

    if (!((picture.sz1 == result.sz1) && (picture.sz2 == result.sz2)))
        return false;

    const int szx = picture.sz1,
              szy = picture.sz2;

    const vect_t Middle (szx / 2, szy / 2);

    const vect_t StepPicture ((double) SizePicture.x / D.x, (double) SizePicture.y / D.y);
    const vect_t StepResult  ((double) SizeResult.x  / szx, (double) SizeResult.y  / szy);

    double valueX = 0.0;
    double valueY = 0.0;

    vect_t delta  (0, 0);
    vect_t resultLoop (0, 0);
    double po = 0;

    //printf ("%d %d\n", szx, szy);
    //printf ("%s\n", Middle.Print ());
    //printf ("%s\n", StepPicture.Print ());
    //printf ("%s\n", StepResult .Print ());
    //printf ("%Lf %Lf\n", valueX, valueY);

    //printf ("\n%lg\n", K);

    //txSleep (10000);

    //printf ("Started looping\n");

    //FILE* f = fopen ("Resourses\\Dump.txt", "w");

    for (int x0 = 0; x0 < szx; x0 += 1)
    for (int y0 = 0; y0 < szy; y0 += 1)
        {
        valueX = 0.0;
        valueY = 0.0;

        for (double x = 0; x < szx; x += D.y)
        for (double y = 0; y < szy; y += D.y)
            {
            delta.x = (x - Middle.x) * StepPicture.x - (x0 - Middle.x) * StepResult.x;
            delta.y = (y - Middle.y) * StepPicture.y - (y0 - Middle.y) * StepResult.y;

            po = sqrt (delta.x * delta.x + delta.y * delta.y + Z_2);

            resultLoop = F (Thinkness (picture [(int) x][(int) y]), po);

            valueX += resultLoop.x;
            valueY += resultLoop.y;

            //txClearConsole ();

            //fprintf (f, "\n\n\nLoop with x0=%-4d, y0=%-4d, x=%-4.0lf, y=%-4.0lf\n\n", x0, y0, x, y);
            //fprintf (f, "deltaX=%-5lg, deltaY=%-5lg, po=%-10lg\n\n", delta.x, delta.y, po);
            //fprintf (f, "result:\n"
            //            "x=%-015.10lg\n"
            //            "y=%-015.10lg\n\n", resultLoop.x, resultLoop.y);
            //fprintf (f, "value:\n"
            //            "x=%-10.10lg\n"
            //            "y=%-10.10lg\n\n\n\n", valueX, valueY);

            //$(resultLoop.x);
            //$(resultLoop.y);
            //$n;
            //$(valueX);
            //$(valueY);
            //$n;
            //
            //getch ();

            //txSleep (1);
            }

        result [x0][y0] = I (valueX, valueY);

        //fprintf (f, "\n\nLine ¹ %d;%d\nValue = %d\nResult=(%lg; %lg)\n", x0, y0, result [x0][y0], valueX, valueY);

        if (y0 == 0)
            printf ("Line %d/%d\n", x0, szx);

        //if (x0 >= 50 && y0 >= 50)
        //    printf ("%3d %3d; %6lf %6lf; %10lf, %6lf %6lf\n", x0, y0, valueX, valueY, po, resultLoop.x, resultLoop.y);

        //if (I (value) != 0)
        //    printf ("WOW!!!\n");
        //if (I (value) == 0)
        //    printf ("oops - %lg %lg\n", value.x, value.y);
        //else
        //    {
        //    printf ("result - %lg, %lg, %lg\n", I (value), (double) value.x / 100000000, (double) value.y / 100000000);
        //    txSleep (100);
        //    }
        //if (y0 == 0)
        //    {
        //    printf ("line - %d %d; value - %lg\n", x0, y0, I (value));
        //    }
        }

    return true;
    }

inline double Thinkness (unsigned char a)
    {
    return MaxThinkness * a / 256.0;
    }

inline vect_t F (double thinkness, double po)
    {
    vect_t returned = E0 (thinkness) * StepenE (K * po) / po * D.x * D.y;

    return returned;
    }

inline vect_t E0 (double thinkness)
    {
    return (vect_t (1, 0) - StepenE (Vel * thinkness));
    }

inline vect_t StepenE (double a)
    {
    return vect_t (cos (a), sin (a));
    }

inline unsigned char I (double x, double y)
    {
    return (char)((x * x + y * y) * 100.0);
    }








