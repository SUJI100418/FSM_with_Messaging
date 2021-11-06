#include <fstream>
#include <time.h>

#include "Locations.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

#include "Kakarot.h"
#include "Vegeta.h"
#include "Frieza.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  Kakarot* Goku = new Kakarot(ent_Kakarot);
  
  Vegeta* Vegy = new Vegeta(ent_Vegeta);

  Frieza* Free = new Frieza(ent_Frieza);


  EntityMgr->RegisterEntity(Goku);
  EntityMgr->RegisterEntity(Vegy);
  EntityMgr->RegisterEntity(Free);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
	Goku->Update();
	Vegy->Update();
	Free->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    //Sleep(800);
  }

  delete Goku;
  delete Vegy;
  delete Free;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






