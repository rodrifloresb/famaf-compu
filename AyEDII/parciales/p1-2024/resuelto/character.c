/*
  @file character.c
  @brief Implements character structure and methods
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

static const int AMOUNT_OF_ATTRIBUTES=3;

// Converts a name_t value into a string for visualization or comparation.
char* NAMES[]={[alice]="Alice", 
               [mario]="Mario", 
               [lenny]="Lenny",
               [eliza]="Eliza",
               [eddie]="Eddie",
               [frank]="Frank",
               [nadia]="Nadia",
               [oscar]="Oscar",
               [bella]="Bella",
               [yoshi]="Yoshi"};

Character character_from_file_line(FILE *file, name_t name, alignment_t alignment) {

  // placeholders
  unsigned int life;
  unsigned int strength;
  unsigned int agility;
  
  int res = fscanf(file, EXPECTED_ATTRIBUTE_FORMAT, &life, &strength ,&agility);
  
  if (res != AMOUNT_OF_ATTRIBUTES) {
      fprintf(stderr, "Error terna habilidad.\n");
      exit(EXIT_FAILURE);
  }

  if (strength == 0)
  {
      fprintf(stderr, "La fuerza no puede ser 0.\n");
      exit(EXIT_FAILURE);
  }

  if (strength > 10) // no encuentro la tecla O
  {
      fprintf(stderr, "La fuerza no puede ser mas de 10.\n");
      exit(EXIT_FAILURE);
  }
  
  
  if (agility == 0)
  {
      fprintf(stderr, "La agilidad no puede ser 0.\n");
      exit(EXIT_FAILURE);
  }

  if (agility > 10) // no encuentro la tecla O
  {
      fprintf(stderr, "La agilidad no puede ser mas de 10.\n");
      exit(EXIT_FAILURE);
  }

  if (life > 100)
  {
      fprintf(stderr, "La vida no puede ser mas de 100.\n");
      exit(EXIT_FAILURE);
  }

  Character character;

  character.name = name;
  character.alignment = alignment;
  character.alive = true;
  character.life = life;
  character.strength = strength;
  character.agility = agility;

  if (character.life == 0u)
  {
    character.alive = false;
  }
  

  return character;
}

name_t read_character_name(FILE *file) {
  char str_name[CHARACTER_NAME_LENGTH];


  for (int i=0; i<CHARACTER_NAME_LENGTH; i++) {
    int res = fscanf(file, "%c", &str_name[i]);
    if (res != 1) {
      fprintf(stderr, "Bad character name.");
      exit(EXIT_FAILURE);
    }
  }
  str_name[CHARACTER_NAME_LENGTH] = '\0';
  printf("read_character_name: str_name -> '%s'\n", str_name);
  name_t name=alice;
  while (strcmp(NAMES[name], str_name)!=0 && name < CHARACTER_COUNT) {
    name++;
  }
  if (name == CHARACTER_COUNT) {
      fprintf(stderr, "Character name unknown.");
      exit(EXIT_FAILURE);
  }
  return name;
}
