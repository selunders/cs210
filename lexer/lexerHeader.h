/* ccxLexer.c
 *
 * Header file for ccxLexer.c
 * 
 * 
 * This header contains all the information for...
 *  
 *-------------------------------------------------------------------------------------
 */

// List of CCX keywords
char *keywordArr[35] = {
    "accessor",
    "and",
    "array",
    "bool",
    "case",
    "character",
    "constant",
    "else",
    "elsif",
    "end",
    "exit",
    "float",
    "func",
    "if",
    "ifc",
    "in",
    "integer",
    "is",
    "mutator",
    "natural",
    "null",
    "of",
    "or",
    "others",
    "out",
    "pkg",
    "positive",
    "proc",
    "ptr",
    "range",
    "subtype",
    "then",
    "type",
    "when",
    "while"};

// List of CCX operators
char operatorArr[22] = {
    '.',
    '<',
    '>',
    '(',
    ')',
    '+',
    '-',
    '*',
    '/',
    //tokenIn: string
    '|',
    '&',
    ';',
    ',',
    ':',
    '=',
    '[',
    ']',
    '{',
    '}',
    '$',
    '!',
    '@'};

// Arrays for checking for double operators
char longOpStartArr[9] = {':', '.', '<', '>', '*', '!', '=', '{', '}'};
char longOpEndArr[6] = {'=', '.', '<', '>', '*', ':'};
char *longOpArr[12] = {
    ":=",
    "..",
    "<<",
    ">>",
    "<>",
    "<=",
    ">=",
    "**",
    "!=",
    "=>",
    "{:",
    "}:"};

char c;             // Used to store most recent character
int lexIndex = 0;   // Store location in lexemeIn array
char lexemeIn[256]; // Stores current lexeme being identified

void getNextChar(FILE *filePointer) // Grabs the next char from the file stream
{
    c = fgetc(filePointer); // Get next char
    lexemeIn[lexIndex] = c; // Store char in lexemeIn array
    lexIndex++;             // Increment location index
}

void lexClear() // Used to clear the lexeme array
{
    lexIndex = 0; // Reset location index
    int i = 0;
    while (i < 256) // Set array to null values
    {
        lexemeIn[i] = '\0';
        i++;
    }
}

int isCharInArr(char charIn, char arr[], int arrlen) // Check if a character is in an array
{
    int i = 0;
    while (i < arrlen)
    {
        if (charIn == arr[i])
            return 1;
        else
            i++;
    }
    return 0;
}

int isKeyword(char *strIn) // Checks if a string is a valid keyword
{
    int i = 0;
    while (i < 35)
    {
        if (strcmp(keywordArr[i], strIn) == 0)
            return 1;
        else
            i++;
    }
    return 0;
}

int isDoubleOp(char *strIn) // Checks if a string is a valid 2 char operator
{
    int i = 0;
    while (i < 12)
    {
        if (strcmp(longOpArr[i], strIn) == 0)
            return 1;
        else
            i++;
    }
    return 0;
}

int isLowerAlpha(char charIn) // Checks if lowercase letter
{
    if ((charIn >= 'a') && (charIn <= 'z'))
        return 1;
    else
        return 0;
}

int isUpperAlpha(char charIn) // Checks if uppercase letter
{
    if ((charIn >= 'A') && (charIn <= 'Z'))
    {
        return 1;
    }
    else
        return 0;
}

int isAlpha(char charIn) // Checks if charIn is a letter
{
    if (isLowerAlpha(charIn) || isUpperAlpha(charIn))
        return 1;
    else
        return 0;
}

int isNumericLiteral(char charIn) // Checks if charIn is valid for a numeric literal
{
    if (((charIn >= '0') && (charIn <= '9')) || (charIn == '.') || isUpperAlpha(charIn) || isLowerAlpha(charIn) || (charIn == '-') || (charIn == '.' || charIn == '#'))
        return 1;
    else
        return 0;
}

int isIdentifierChar(char charIn) // Checks if charIn is valid for an identifier
{
    if (((charIn >= '0') && (charIn <= '9')) || isAlpha(charIn) || (charIn == '_'))
        return 1;
    else
        return 0;
}

int isSpace(char charIn) // Checks if charIn is white space
{
    if ((charIn == ' ') || (charIn == '\t') || (charIn == '\n') || (charIn == '\v') || (charIn == '\f') || (charIn == '\r'))
        return 1;
    else
        return 0;
}

void putBackChar(FILE *filePointer) // Puts the last character read back into the file stream to be read again
{
    ungetc(lexemeIn[lexIndex - 1], filePointer); // Put last character back
    lexemeIn[lexIndex - 1] = '\0';               // Set the last character in array to \0
    lexIndex -= 1;                               // Decrement the location index
}

void mainSwitch(FILE *filePointer) // This is the main function for checking lexemes
{
    getNextChar(filePointer); // Grab the first character
    if (c == EOF)             // Check for end of file
        return;
    int lexemeCase;                    // Stores the number for the lexeme case
    if (lexemeIn[lexIndex - 1] == '/') // This could be a comment
        lexemeCase = 0;
    else if (lexemeIn[lexIndex - 1] == '"') // This is a string
        lexemeCase = 1;
    else if (lexemeIn[lexIndex - 1] == 39) // This is a character literal
        lexemeCase = 2;
    else if (isCharInArr(lexemeIn[lexIndex - 1], operatorArr, 22)) // This is an operator
        lexemeCase = 3;
    else if ((lexemeIn[lexIndex - 1] >= '0') && (lexemeIn[lexIndex - 1] <= '9')) // This is the start of a numeric literal
        lexemeCase = 4;
    else if (isAlpha(lexemeIn[lexIndex - 1])) // This is either a keyword or anidentifier
        lexemeCase = 5;
    else // This is an UNKNOWN lexeme
        lexemeCase = -1;

    // Now that we know where to start, put the case into the switch statement
    switch (lexemeCase) // Main switch statement
    {
    case 0: // Comments
        getNextChar(filePointer);
        if (lexemeIn[lexIndex - 1] == '*') // If yes, then this is the start of a comment '/*'
        {
            printf("%c%c", lexemeIn[lexIndex - 2], lexemeIn[lexIndex - 1]);
            do
            {
                getNextChar(filePointer);
                printf("%c", lexemeIn[lexIndex - 1]);
            } while (!((lexemeIn[lexIndex - 1] == '/') && (lexemeIn[lexIndex - 2] == '*'))); // Print char by char until comment closes with */
            printf(" (comment)\n");
        }
        lexClear();
        break;

    case 1:                                   // Strings
        printf("%c", lexemeIn[lexIndex - 1]); // Print "
        do
        {
            getNextChar(filePointer);
            printf("%c", lexemeIn[lexIndex - 1]); // Print char by char until string closes with "
        } while ((lexemeIn[lexIndex - 1] != '"'));
        printf(" (string)\n");
        lexClear();
        break;

    case 2:                                   // Chars
        printf("%c", lexemeIn[lexIndex - 1]); // Print '
        do
        {
            getNextChar(filePointer);
            printf("%c", lexemeIn[lexIndex - 1]); // Print char by char until char closes with '
        } while ((lexemeIn[lexIndex - 1] != 39));
        printf(" (character literal)\n");
        lexClear();
        break;

    case 3:                                                         // Operators
        if (isCharInArr(lexemeIn[lexIndex - 1], longOpStartArr, 9)) // Is char a valid first char of a 2 char operator
        {
            getNextChar(filePointer);                                 // Get the next character
            if (isCharInArr(lexemeIn[lexIndex - 1], longOpEndArr, 6)) // Is it a valid end for a 2 char operator
            {
                if (isDoubleOp(lexemeIn))                // Check if the whole thing is a valid double operator (Prevents things like !: or :: from printing as an operator)
                    printf("%s (operator)\n", lexemeIn); // Print double operator if valid
                else                                     // Put back the second char if not valid, then print the first char
                {
                    putBackChar(filePointer);
                    printf("%c (operator)\n", lexemeIn[lexIndex - 1]);
                }
            }
            else // Put back the invalid end
            {
                putBackChar(filePointer);
                printf("%c (operator)\n", lexemeIn[lexIndex - 1]); // Print the single operator
            }
        }
        else // Print the single operator
            printf("%c (operator)\n", lexemeIn[lexIndex - 1]);
        lexClear();
        break;

    case 4: // Numeric Literals
        do
        {
            getNextChar(filePointer);
        } while (isNumericLiteral(lexemeIn[lexIndex - 1])); // Get characters until you reach something that isn't part of a numeric literal
        putBackChar(filePointer);                           // Puts that back since it went one too far
        printf("%s (numeric literal)\n", lexemeIn);         // Print numeric literal
        lexClear();
        break;

    case 5: // Keywords & Identifiers
        // printf("Checking for Keywords\n");
        do
        {
            getNextChar(filePointer);
        } while (isAlpha(lexemeIn[lexIndex - 1])); // Look for char that isn't a letter
        if (!(isIdentifierChar(lexemeIn[lexIndex - 1])))
        {                                           // If the character isn't for an identifier
            putBackChar(filePointer);               // Put the char back
            if (isKeyword(lexemeIn))                // If the lexeme is a keyword
                printf("%s (keyword)\n", lexemeIn); // Print it
            else
            {
                printf("%s (identifier)\n", lexemeIn); // Else it's an identifier
            }
        }
        else
        {
            do
            {
                getNextChar(filePointer);
            } while (isIdentifierChar(lexemeIn[lexIndex - 1])); // Continue grabbing chars until you hit something that's not valid for an identifier
            putBackChar(filePointer);                           // Put back that char, as it went one too far
            printf("%s (identifier)\n", lexemeIn);
        }
        lexClear();
        break;

        // case 10: // Used for debugging
        //     printf("LexemeIndex: %i\nFull lexemeIn:\n%s\nlexIndex-1: %c\n", lexIndex, lexemeIn, lexemeIn[lexIndex - 1]);
        //     lexClear();
        //     break;

    default:                       // Shouldn't come up for valid '.ccx' or '.cci' files
        if (!(isSpace(*lexemeIn))) // Keeps white space from appearing as an UNKNOWN lexeme
        {
            printf("%s (UNKOWN)\n", lexemeIn);
            c = EOF; // Terminate program if there's an UNKOWN lexeme
        }
        lexClear();
        break;
    }
}