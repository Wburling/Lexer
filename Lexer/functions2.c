#include "functions.h"

int tokenCount = 0;
char *Keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
char *Operator[] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"}; // got to readd all operators and then make a double operators char array;
char singleOperator[] = {'.', '<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '=', '!'};
char *doubleOperator[] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
char Numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool isNum(char s)
{
    for (int i = 0; i < 10; i++)
    {
        if (s == Numbers[i])
        {
            return true;
        }
    }
    return false;
}
bool isKeyword(char *s)
{
    for (int i = 0; i < 37; i++)
    {
        if (strcmp(s, Keywords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isOperator(char *s)
{
    for (int i = 0; i < 27; i++)
    {
        if (strcmp(s, Operator[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isSingleOperator(char s)
{
    for (int i = 0; i < 18; i++)
    {
        if (s == singleOperator[i])
        {
            return true;
        }
    }
    return false;
}
bool isDoubleOperator(char *s)
{
    for (int i = 0; i < 10; i++)
    {
        if (s == doubleOperator[i])
            return true;
    }
    return false;
}
bool isString(char s)
{
    if (s == '\"')
    {
        return true;
    }
    return false;
}

char **separateIntoTokens(char *s)
{
    int start = 0;
    int cases = 0;
    char **array = malloc(sizeof(char *) * strlen(s));
    for (int end = 0; end < strlen(s); end++)
    {
        /*
        We always have to check if it is a special case.. our last if statement is our normal tokenizer. If its a special case make cases variable - 1;
        */

        // Basic finding space, new line, EOF, etc token
        if (s[end] == ' ' || s[end] == '\n' || s[end] == '\0' ||end == strlen(s) - 1 || isSingleOperator(s[end]) || isString(s[end]))
        {
           
            if (s[end] == '.' && isNum(s[end + 1]))
            {
                end++;
                continue;
            }
            if (end == strlen(s) - 1)
                cases = 1;
            
            if (isString(s[end]))
                cases = -1;
            array[tokenCount] = malloc(sizeof(char) * 2048);
            for (int i = 0; i < end - start + cases; i++)
            {
                array[tokenCount][i] = s[start + i];
            }
             
            if ((array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0') && array[tokenCount][0] != '\n')
                tokenCount++;
           
            cases = 0;
            start = end + 1;
        }
        // if it is a special string
        if (isString(s[end]))
        {
            start = end;
            end++;
            for (int i = end; i < strlen(s); i++)
            {
                if (s[i] == '\"')
                {
                    if (s[i] + 1 == ' ')
                        end = i + 1;
                    else
                        end = i;
                    array[tokenCount] = malloc(sizeof(char) * 2048);
                    for (int j = 0; j < end - start + 1; j++)
                    {
                        array[tokenCount][j] = s[start + j];
                    }
                    if ((array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0') && array[tokenCount][0] != '\n')
                        tokenCount++;
                    break;
                }
            }
            start = end + 1;
            continue;
        }
        // if it is an operator such as ; or *
        if (isSingleOperator(s[end]) && isSingleOperator(s[end + 1]) == false)
        {
          
            for (int i = 0; i < 18; i++)
            {
                if (s[end] == singleOperator[i])
                {
                    array[tokenCount] = malloc(sizeof(char) * 2048);
                    array[tokenCount][0] = s[end];
                    tokenCount++;
                    break;
                }
            }
            start = end + 1;
            continue;
        }
        if (isSingleOperator(s[end]) && isSingleOperator(s[end + 1]) == true)
        {
            bool doublePassed = false;
            // if it is a comment
            //printf("made it to the double operator Loop\n");
            if (s[end] == '/' && s[end + 1] == '*')
            {
                start--;
                // if its a comment
                for (int t = start; EOF; t++)
                {
                   
                    if (s[t] == '*' && s[t + 1] == '/')
                    {
                        t++; 
                        end = t + 1; // + 1 
                         
                        
                        for (int i = 0; i < end-start; i++)
                        {
                            array[tokenCount][i] = s[start + i];
                        }
                        tokenCount++;
                        start = end + 1; 
                        end++;
                        break;
                    }
                }
                continue;
                // if its a normal double operator
            }
            for (int i = 0; i < 10; i++)
            {
                // printf("%.*s == ", 2, s + start - 1);
                // printf("%s\n", doubleOperator[i]);
                if (strncmp(s + start - 1, doubleOperator[i], 2) == 0)
                {
                    // printf("HIT: %.*s\n", 2, s + start - 1);
                    array[tokenCount] = malloc(sizeof(char) * 2048);
                    array[tokenCount][0] = s[end];
                    array[tokenCount][1] = s[end + 1];
                    tokenCount++;
                    doublePassed = true;
                    if(isSingleOperator(s[end + 2])) {
                        start+=1;
                        end+=1;
                    }
                    else {
                    start++;
                    end++;
                    }
                    break;
                }
            }
            if (doublePassed == false)
            {
                array[tokenCount] = malloc(sizeof(char) * 2048);
                array[tokenCount][0] = s[end];
                tokenCount++;
                array[tokenCount] = malloc(sizeof(char) * 2048);
                array[tokenCount][0] = s[end + 1];
                tokenCount++;
                if (s[end + 1] == ' ')
                {
                    start += 2;
                    end += 2;
                }
                else
                {
                    start += 1;
                    end += 1;
                }
                continue;
            }
            // start++;
            // end++;
            continue;
        }
    }
    return array;
}

void sort(char **s)
{
    for (int i = 0; i < tokenCount; i++)
    {
        if (isKeyword(s[i]))
        {
            strcat(s[i], " (keyword)");
        }
        else if (isOperator(s[i]))
        {
            strcat(s[i], " (operator)");
        }
        else if (s[i][0] == '/' && s[i][1] == '*')
        {
            strcat(s[i], " (comment)");
        }
        else if (s[i][0] == '\"')
        {
            strcat(s[i], " (string)");
        }
        else if (isNum(s[i][0]))
        {
            strcat(s[i], " (numeric literal)");
        }
        else if(s[i][0] == '\'') {
            strcat(s[i], " (character literal)");
        }
        else
        {
            strcat(s[i], " (identifier)");
        }
    }
}

void display(char **s, FILE *file)
{
    for (int i = 0; i < tokenCount; i++)
    { // this is a test loop to display all the tokens
        //fprintf(stdout, "%s\n", s[i]);
        fprintf(file, "%s\n", s[i]);
    }
}