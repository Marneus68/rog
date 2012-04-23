#include "R.h"

int main (int argc, char const* argv[])
{
    rog::Rgame *theGame = rog::Rgame::Initialize(GAME_NAME);
    
    theGame->Run();
    
    return 0;
}
