#include "Includes\\MyLib.h"

int main ()
    {
    CreateMyWindow ();           //

    pictures_t pictures;         //
    LoadPictures (pictures);     //

    array_t <dyn, button_t> buttons (0);  //
    SetButtons (buttons, pictures);       //

    int buttonPressed = NothingPressed;   //

    txBegin (); //

    while (!Exit ())
        {
        DrawBackground (pictures);      //

        DoOperationsWithButtons (buttons, &buttonPressed);  //

        txSleep (1);
        }

    txEnd ();

    DeletePictures (pictures);

    _txExit = true;
    return 0;
    }











