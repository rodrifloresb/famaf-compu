/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "character.h"

void array_dump(CharacterList array) {
  for (alignment_t alignment=good; alignment<CHARACTER_ALIGNMENTS; ++alignment) {
    for (charttype_t charttype=physical; charttype < CHARACTER_TYPES; ++charttype) {
      Character character = array[charttype][alignment];

      char *str_alignment = (character.alignment == good) ? "Good" : "Evil";
      char *str_alive = (character.alive) ? "Yes" : "Nope";

      fprintf(stdout,
              "Character '%s': Life=%u/100, Strength=%u/10, Agility=%u/10, "
              "alignment='%s', Alive='%s'\n",
              NAMES[character.name], character.life, character.strength,
              character.agility, str_alignment, str_alive);
    }
  }
}

float array_alive_mean_life(CharacterList array) {
    float promedio_life = 0;
    unsigned int pjdead = 0;

    for (charttype_t i = 0; i < CHARACTER_TYPES; i++)
    {
      promedio_life = promedio_life + array[i][evil].life + array[i][good].life;
      
      if (!array[i][evil].alive)
      {
        ++pjdead;
      }

      if (!array[i][good].alive)
      {
        ++pjdead;
      }
    }

    promedio_life = promedio_life / ((CHARACTER_TYPES * CHARACTER_ALIGNMENTS) - pjdead);
      
    return promedio_life;
}

unsigned int array_from_file(CharacterList array, const char *filepath) {
  FILE *file = NULL;

  // check if file exists
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  // read the file
  unsigned int readed = 0;
  while (!feof(file) && readed < CHARACTER_COUNT) {
    charttype_t charttype;
    alignment_t alignment;

    char s_charttype, s_alignment;
    int res=fscanf(file, "[%c %c] " , &s_charttype, &s_alignment);
    if (res != 2) {
        fprintf(stderr, "Error reading type and alignment.\n");
        exit(EXIT_FAILURE);
    }

    if (s_charttype == 'a')
    {
      charttype = agile;
    }

    if (s_charttype == 'p')
    {
      charttype = physical;
    }
    
    if (s_charttype == 't')
    {
      charttype = tank;
    }
    
    if (s_charttype == 'm')
    {
      charttype = magic;
    }

    if (s_alignment == 'g')
    {
      alignment = good;
    }
    
    if (s_alignment == 'e')
    {
      alignment = evil;
    }
    

    // Reads the name and obtains an name_t value
    name_t name = read_character_name(file);

    Character character = character_from_file_line(file, name, alignment);

    array[charttype][alignment] = character;

    ++readed;
  }
  /* COMPLETAR SI ES NECESARIO CON ALGUNA VERIFICACIÓN FINAL */

  // close the file
  fclose(file);

  return readed;
}
