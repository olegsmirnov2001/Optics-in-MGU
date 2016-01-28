#include "TXLib.h"
#include "MyLib.h"

int main ()
    {
    CreateMyWindow ();

    int Sz1 = 0, Sz2 = 0;
    scanf ("%d %d\n", &Sz1, &Sz2);

    matrix_t <int> matr (Sz1, Sz2);

    for (int number1 = 0; number1 < Sz1; number1++)
        {
        for (int number2 = 0; number2 < Sz2; number2++)
            scanf ("%d ", matr [number1][number2]);

        scanf ("\n");
        }

    PrintfMatrix (matr);

    //_txExit = true;
    return 0;
    }













