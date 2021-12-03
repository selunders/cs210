/* ccxLexer.c
 *
 * CS 210.Wilder.........Seth Lunders
 * 9/27/2020 ............lund4272@vandals.uidaho.edu
 *
 * The purpose of the program is to seperate and classify the lexemes of a 'ccx' or 'cci' file 
 * 
 * Overall the program works by comparing characters and lexemes taken in to valid CCX character and lexeme lists
 *-------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h> // for strcmp
#include "lexerHeader.h"

int main(int argc, char *argv[])
{
   // -- Check for the correct number of arguments --
   if (argc > 2)
   {
      printf("Too many arguments supplied.\n");
      return 0;
   }
   else if (argc < 2)
   {
      printf("Error: No file given.\n");
      return 0;
   }

   // -- Open the file --
   FILE *fp = fopen(argv[1], "r");

   // -- Return if could not open file --
   if (fp == NULL)
   {
      printf("Could not open file.\n");
      return 0;
   }

   // -- Main loop through program --
   
   while (c != EOF) { // Run until you hit the end of the file
      mainSwitch(fp); // Runs the switch statement that classifies lexemes
   }

   // -- Close file and exit --
   fclose(fp);
   return 0;
}