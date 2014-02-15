//author: Trevor Sherrard
//project: SortME

  

#include "RobotSerial.h"
#include <fstream>

/**
* \fn RobotSerial::send(unsigned char NumToSend)
* \brief sends an usigned char over serial to the arduino. 
*  for people tracking, a 'l' or 'r' will be sent depending on the persons x value.
*  for block sorting a char containing the number will be sent. (see main.cpp)
* \param charToSend the char that will be sent to the arduino
*/
void RobotSerial::send(char charToSend)
{
    std::ofstream ofs ("/dev/ttyACM0", std::ofstream::out);
    ofs << charToSend;
    ofs.close();
}
