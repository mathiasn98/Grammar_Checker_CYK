/* TUGAS BESAR 2 TBFO
MATHIAS NOVIANTO 13516021
ALVIN LIMASSA 13516039 */
#include <stdio.h>
#include "token.h"

int main ()
{
    // Kamus Loal
    int i;
    static ArrayOfToken ArrayT;
    static ArrayOfString ArrayS;
    static ArrayProduction ArrayP;
    // Algoritma
    CreateEmpty(&ArrayP);
    ReadCNF(&ArrayP);
    BacaListToken(&ArrayT);
    BacaString(&ArrayS,ArrayT);
    for (i=0;i<ArrayS.Neff;i++)
    {
        printf("%c ",ArrayS.Array[i].Token);
    }
    printf("\n");
    RunCYK(ArrayS,ArrayP);
    
}