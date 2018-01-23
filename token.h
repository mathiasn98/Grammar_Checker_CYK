#ifndef TOKEN_H
#define TOKEN_H
#include "boolean.h"
// Deklarasi Type
typedef char Kata [256];

typedef struct 
{
    Kata Start;
    Kata GoTo;
} Production;

typedef struct
{
    Production Array [200];
    int Neff;
} ArrayProduction;

typedef struct
{
    Kata Ka;
    char To;
} Token;

typedef struct
{
    Token Array [100];
    int Neff;
} ArrayOfToken;

typedef struct
{
    char Token;
    int Line;
}TokenLine;

typedef struct
{
    TokenLine Array [200];
    int Neff;
} ArrayOfString;

typedef struct
{
    Kata Array [15];
    int Neff;
} ArrayOfKata;

typedef struct
{
    ArrayOfKata Array [256][256];
    int Neff;
} MatriksCYK;

// Deklarasi Fungsi dan Prosedur
void CreateEmpty(ArrayProduction *T);
void ReadCNF(ArrayProduction *T);
boolean IsSama(Kata x1, Kata x2);
void BacaListToken(ArrayOfToken *T);
char StringToToken(Kata X, ArrayOfToken TabToken);
void BacaString (ArrayOfString *TabString, ArrayOfToken TabToken);
void SetUkuranMatriks (MatriksCYK *Mat, int Neff);
void HasilTabelParser (ArrayProduction TabProducion, Kata X, ArrayOfKata *Hasil);
void RunCYK (ArrayOfString TabString,ArrayProduction TabProduction);


#endif