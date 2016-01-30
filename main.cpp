#include "MyLib.h"

template <template <typename, int> class Type, int Sz>
bool Main (array_t <Type, button_t, Sz> & buttons);

int main ()
    {
    CreateMyWindow (Window, true);

    array_t <stt, button_t, 10> buttons;
    SetButtons (buttons);

    Main (buttons);

    _txExit = true;
    return 0;
    }

template <template <typename, int> class Type, int Sz>
bool Main (array_t <Type, button_t, Sz> & buttons)
    {
    txBegin ();

    while (true)
        {
        Clear ();

        DoOperationsWithButtons (buttons);

        txSleep (1);
        }

    txEnd ();

    return true;
    }













