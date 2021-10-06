//*************************
//*** EV3 Main Function ***
//*************************
#include "EV3_Thread.h"
#include "EV3_LCDDisplay.h"
#include "EV3_Sensor_InfraRed.h"
#include "..\Navigator.h"
using namespace ev3_c_api;

//Value of sensor reading is between 0 - 100, this method gets the reading and converts it into a cstring that can be displayed
void GetIRProximityString(char output[], unsigned char input)
{
    output[0] = input / 100 + '0';
    input = input % 100;
    output[1] = input / 10 + '0';
    input = input % 10;
    output[2] = input + '0';
    output[3] = '\0';
    return;
}

int EV3_main()
{
    /*Navigator driver(Vec(2.0f, 0.0f));
    while (!driver.isAtDestination())
        driver.moveToDestination();*/

    char readingOut[4];
    unsigned char readingIn = GetProximity(E_Port_1);
    GetIRProximityString(readingOut, readingIn);//Takes 'readingOut' and modifies it to be the value 'readingIn'

    Draw_Text(20, 20, E_Font_Normal, false, readingOut);
    EV3_Sleep(3000);
    return 0;
}
