#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,

  Msg_WannaBattle,
  Msg_FriezaCome,
  Msg_TimeToRevenge,
  Msg_Yes,
  Msg_No,
  Msg_YouWin,
  Msg_FriezaFaint
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_WannaBattle:

	  return "Hey, You wanna Battle with me?";

  case Msg_FriezaCome:

	  return "Vegeta! Come here quickly! Freezer is coming!";

  case Msg_TimeToRevenge:
	  
	  return "I'M BACK! TIME TO REVENGE, GOKU!";

  case Msg_Yes:

	  return "Let's do this.";

  case Msg_No:

	  return "I don't want it.";

  case Msg_YouWin:

	  return "You Win...";

  case Msg_FriezaFaint:

	  return "<<--Frieza Faint-->>";

  default:

    return "Not recognized!";
  }
}

#endif