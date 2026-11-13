#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Keywords */
char keywords[][10] ={"int","float","char","if","else","while","for","return","void","double"};

/* Operators */
char operators[] ={'+','-','*','/','=','>','<','%','!','&','|'};

/* Braces */
char braces[] ={'(',')','{','}','[',']'};

/* Check Keyword */
int isKeyword(char s[])
{
    for(int i=0;i<10;i++)
    {
        if(strcmp(s,keywords[i])==0)
            return 1;
    }
    return 0;
}

/* Check Integer */
int isInteger(char s[])
{
    if(s[0]=='\0')
    return 0;

    for(int i=0;s[i]!='\0';i++)
    {
        if(!isdigit((unsigned char)s[i]))
        return 0;
    }

    return 1;
}

/* Check Float */
int isFloat(char s[])
{
    int dot=0;

    if(s[0]=='\0')
    return 0;

    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]=='.')
        dot++;
        else if(!isdigit((unsigned char)s[i]))
        return 0;
    }

    if(dot!=1)
        return 0;

    if(s[0]=='.' || s[strlen(s)-1]=='.')
        return 0;

    return 1;
}

/* Check Identifier */
int isIdentifier(char s[])
{
    if(!(isalpha((unsigned char)s[0]) || s[0]=='_'))
    return 0;

    for(int i=1;s[i]!='\0';i++)
    {
        if(!(isalnum((unsigned char)s[i]) || s[i]=='_'))
        return 0;
    }

    return 1;
}

/* Check Invalid Identifier */
int isInvalidIdentifier(char s[])
{
    if(isdigit((unsigned char)s[0]))
    {
        for(int i=1;s[i]!='\0';i++)
        {
            if(isalpha((unsigned char)s[i]) || s[i]=='_')
            return 1;
        }
    }

    return 0;
}

/* Check Character Constant */
int isCharConstant(char s[])
{
    return strlen(s)==3 && s[0]=='\'' && s[2]=='\'';
}

/* Check String Constant */
int isStringConstant(char s[])
{
    int len=strlen(s);

    return (len>=2 && s[0]=='"' && s[len-1]=='"');
}

/* Check Operator */
int isOperator(char ch)
{
    for(int i=0;i<11;i++)
    {
        if(ch==operators[i])
        return 1;
    }

    return 0;
}

/* Check Brace */
int isBrace(char ch)
{
    for(int i=0;i<6;i++)
    {
        if(ch==braces[i])
        return 1;
    }

    return 0;
}

/* Classify Token */
void classify(char token[])
{
    if(isKeyword(token))
        printf("%s --> Keyword\n",token);

    else if(isInteger(token))
        printf("%s --> Integer Constant\n",token);

    else if(isFloat(token))
        printf("%s --> Floating Constant\n",token);

    else if(isCharConstant(token))
        printf("%s --> Character Constant\n",token);

    else if(isStringConstant(token))
        printf("%s --> String Constant\n",token);

    else if(isInvalidIdentifier(token))
        printf("%s --> ERROR : Invalid Identifier\n",token);

    else if(isIdentifier(token))
        printf("%s --> Identifier\n",token);

    else
        printf("%s --> ERROR : Invalid Token\n",token);
}

/* Main Function */
int main()
{
    FILE *fp = fopen("input.txt","r");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    int ch;
    char buffer[256];
    int i = 0;

    while((ch = fgetc(fp)) != EOF)
    {
        /* Read String Constant */
        if(ch == '"')
        {
            if(i != 0)
            {
                buffer[i] = '\0';
                classify(buffer);
                i = 0;
            }

            buffer[i++] = ch;

            int closed = 0;

            while((ch = fgetc(fp)) != EOF)
            {
                if(ch == '"')
                {
                    buffer[i++] = ch;
                    closed = 1;
                    break;
                }

                if(ch == '\n' || ch==' ')
                    break;

                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if(closed)
            {
                classify(buffer);
            }
            else
            {
                printf("%s --> ERROR : Unterminated String Constant\n", buffer);
            }

            i = 0;
            continue;
        }

        /* Read Character Constant */
        else if(ch == '\'')
        {
            if(i != 0)
            {
                buffer[i] = '\0';
                classify(buffer);
                i = 0;
            }

            buffer[i++] = ch;

            int closed = 0;

            while((ch = fgetc(fp)) != EOF)
            {
                if(ch == '\'')
                {
                    buffer[i++] = ch;
                    closed = 1;
                    break;
                }

                if(ch == '\n')
                    break;

                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if(closed)
            {
                classify(buffer);
            }
            else
            {
                printf("%s --> ERROR : Unterminated Character Constant\n", buffer);
            }

            i = 0;
            continue;
        }

        /* Build Identifier / Number */
        else if(isalnum(ch) || ch=='_' || ch=='.')
        {
            buffer[i++] = ch;
        }

        else
        {
            if(i != 0)
            {
                buffer[i] = '\0';
                classify(buffer);
                i = 0;
            }

            if(isOperator(ch))
            {
                printf("%c --> Operator\n", ch);
            }
            else if(isBrace(ch))
            {
                printf("%c --> Brace\n", ch);
            }
            else if(ch==';' || ch==',')
            {
                printf("%c --> Separator\n", ch);
            }
            else if(!isspace(ch))
            {
                printf("%c --> ERROR : Invalid Character\n", ch);
            }
        }
    }
    // if(i != 0)
    // {
    //     buffer[i] = '\0';
    //     classify(buffer);
    // }
    fclose(fp);

    return 0;
}