#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_grade(string text);

int main(void)
{
    string text = get_string("Text: ");
    int grade = get_grade(text);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    // compute the number of letters present in the text
    int countLetters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            countLetters++;
        }
    }
    return countLetters;
}

int count_words(string text)
{
    // compute the number of word present in the text
    int countWords = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            countWords++;
        }
    }

    return countWords;
}

int count_sentences(string text)
{
    // compute the number of sentences in the text
    int countSentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (c == '.' || c == '!' || c == '?')
        {
            countSentences++;
        }
    }
    
    return countSentences;
}


int get_grade(string text)
{
    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);

    float L_COEFF = 0.0588;
    float S_COEFF = 0.296;
    float COLEMAN_CONST = 15.8;
    float L = 0.0;
    float S = 0.0;

    if (words != 0)
    {
        L = (float) letters / words * 100;
        S = (float) sentences / words * 100;
    }

    float index = (L_COEFF * L) - (S_COEFF * S) - COLEMAN_CONST;

    return (int) round(index);
}