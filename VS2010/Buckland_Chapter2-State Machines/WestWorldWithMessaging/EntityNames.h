#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Kakarot,

  ent_Vegeta,

  ent_Frieza

};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 

  case ent_Kakarot:

	  return "Kakarot";
	
  case ent_Vegeta:

	  return "Vegeta";

  case ent_Frieza:

	  return "Frieza";

  default:

    return "UNKNOWN!";
  }
}

#endif