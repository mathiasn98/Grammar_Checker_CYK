#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void CreateEmpty(ArrayProduction *T)
// Untuk Membuat Array kosong 
{
    (*T).Neff=0;
}

void ReadCNF(ArrayProduction *T)
// Prosedur untuk membaca CNF yang terdapat pada file external CNF.txt
{
    // Kamus Lokal
    FILE * pita;
    char CC,CP;
    int iProduction,iArray;
    boolean BagianGoTo;

    // Algoritma
    iProduction=0;
    iArray=0;
    BagianGoTo=false;
    pita = fopen("CNF.txt","r");
    while (fscanf(pita,"%c",&CC)!=EOF)
    {
        if((CP=='-')&&(CC=='>'))
        {
            BagianGoTo=true;
            iProduction=0;
        }
        else if (CC=='|')
        {
            BagianGoTo=true;
            iProduction=0;
            iArray++;
            strcpy((((*T).Array[iArray]).Start),(((*T).Array[iArray-1]).Start));
        }
        else if (CC=='\n')
        {
            BagianGoTo=false;
            iArray++;
            iProduction=0;
        }
        else if (CC!='-')
        {
            if (CC!=' ')
            {
                if (!BagianGoTo)
                {
                    ((*T).Array[iArray]).Start[iProduction]=CC;
                    iProduction++;
                }
                else if (BagianGoTo)
                {
                    ((*T).Array[iArray]).GoTo[iProduction]=CC;
                    iProduction++;
                }
            }
        }
        CP=CC;
    }
    (*T).Neff=iArray;
}

boolean IsSama(Kata x1, Kata x2)
// Mengembalikan True jika kata x1 sama dengan kata x2
{
    // Kamus Lokal
    int p1,p2,i;
	char kata1,kata2;
    boolean cek;

    // Algoritma
    p1=strlen(x1);
	p2=strlen(x2);
    cek=true;
    if (p1==p2)
    {
        i=0;
        while ((cek)&&i<p1)
        {
        	kata1=x1[i];
        	kata2=x2[i];
            if (kata1!=kata2)
            {
                cek=false;
            }
            i++;
        }
    }
    else
    {
        cek=false;
    }
    return cek;
}

void BacaListToken(ArrayOfToken *T)
// Prosedur untuk membaca file external yang berisi karakter dan keytoken.
{
    // Kamus Lokal
    FILE * pita;
    char CC;
    boolean InToken;
    int iKata,iArray;

    //Algoritma
    InToken=false;
    iKata=0;
    iArray=0;
    pita = fopen("token.txt","r");
    while (fscanf(pita,"%c",&CC)!=EOF)
    {
        if (CC==' ')
        {
            (*T).Array[iArray].Ka[iKata]='\0';
            InToken=true;
        }
        else if (CC=='\n')
        {
            iKata=0;
            iArray++;
        }
        else
        {
            if (!InToken)
            {
                (*T).Array[iArray].Ka[iKata]=CC;
                iKata++;
            }
            else
            {
                (*T).Array[iArray].To=CC;
                InToken=false;
            }
        }
    }
    (*T).Neff=iArray;
}

char StringToToken (Kata X, ArrayOfToken TabToken)
// Mengembalikan char yang merepresentasi kata X
{
    // Kamus Lokal
    int i;
    boolean found;
    // Algoritma
    found=false;
    i=0;
    while ((i<TabToken.Neff)&&(!found))
    {
        if (IsSama(X,TabToken.Array[i].Ka))
        {
            found=true;
        }
        else
        {
            i++;
        }
    }
    if (found)
    {
        return (TabToken.Array[i].To);
    }
    else
    {
        return ('#');
    }
}


void BacaString (ArrayOfString *TabString, ArrayOfToken TabToken)
// Prosedur untuk membaca file external menjadi array of token
{
    // Kamus Lokal
    FILE *pita;
    char CC,CL;
    int iSTemp,iTabString,line;
    Kata STemp;
    // Algoritma
    pita = fopen("string.txt","r");
    iSTemp=0;
    iTabString=0;
    line=1;
    while (fscanf(pita,"%c",&CC)!=EOF)
    {
        CL=tolower(CC);
        if ((CL!=' ')&&(CL!='\n'))
        {
            STemp[iSTemp]=CL;
            iSTemp++;
        }
        else 
        {
            if (iSTemp!=0)
            {
                STemp[iSTemp]='\0';
                (*TabString).Array[iTabString].Token=StringToToken(STemp,TabToken);
                (*TabString).Array[iTabString].Line=line;
                iTabString++;
                iSTemp=0;
            }
            if (CC=='\n')
            {
                line++;
            }
        }
    }
    (*TabString).Neff=iTabString;
}

void SetUkuranMatriks (MatriksCYK *Mat, int Neff)
{
    // Kamus Lokal
    int i,j;
    // Algoritma
    (*Mat).Neff=Neff;
    for (i=0;i<Neff;i++)
    {
        for (j=0;j<Neff;j++);
        {
            (*Mat).Array[i][j].Neff=0;
        }
    }
}


void HasilTabelParser (ArrayProduction TabProducion, Kata X, ArrayOfKata *Hasil)
// Mengembalikan Hasil yang merupakan kata Start dari kata X
{
    // Kamus lokal
    int i,ineff;
    // Algoritma
    i=0;
    ineff=(*Hasil).Neff;
    while ((i<TabProducion.Neff))
    {
        if (IsSama(X,TabProducion.Array[i].GoTo))
        {
            strcpy((*Hasil).Array[ineff],(TabProducion.Array[i].Start));
            ineff++;
        }
        i++;
    }
    (*Hasil).Neff=ineff;
}
void RunCYK (ArrayOfString TabString, ArrayProduction TabProduction)
{
    // Kamus Lokal
    static MatriksCYK Mat;
    static Kata KToken,Hasil;
    int i,j,k,l,m,n,o;
    int barissalah;
    boolean languageAccepted;
    // Algoritma
    SetUkuranMatriks(&Mat,TabString.Neff);
    for (i=0;i<TabString.Neff;i++)
    {
        for (j=0;j<(TabString.Neff-i);j++)
        {
            if (i==0)
            {
                KToken[0]=TabString.Array[j].Token;
                KToken[1]='\0';
                HasilTabelParser(TabProduction,KToken,&(Mat.Array[i][j]));
            }
            else
            {
                l=0;
                m=i+j;
                for(k=(i-1);k>=0;k--)
                {
                    for (n=0;n<Mat.Array[k][j].Neff;n++)
                    {
                        for (o=0;o<Mat.Array[l][m].Neff;o++)
                        {
                            KToken[0]='\0';
                            strcpy(KToken,(Mat.Array[k][j].Array[n]));
                            strcat(KToken,(Mat.Array[l][m].Array[o]));
                            HasilTabelParser(TabProduction,KToken,&(Mat.Array[i][j]));
                        }
                    }
                    l++;
                    m--;
                }
            }
        }
    }
    for (i=(Mat.Neff-1);i>=0;i--)
    {
        for (j=0;j<Mat.Neff-i;j++)
        {
            for (k=0;k<Mat.Array[i][j].Neff;k++)
            {
                printf("%s",Mat.Array[i][j].Array[k]);
            }
            printf(" ");
        }
        printf("\n");
    }

    printf("\n" );
    languageAccepted = false;
    i = 0;
    while((!languageAccepted) && (i <Mat.Array[(Mat.Neff-1)][0].Neff))
    {
        if(!strcmp(Mat.Array[(Mat.Neff-1)][0].Array[i],"<S>"))
        {
            languageAccepted = true;
        }
        i++;
    }

    if(languageAccepted)
    {
        printf("Language Accepted !\n");
    }
    else
    {
        printf("SYNTAX ERROR ! \n");
        i=Mat.Neff;
        boolean notempty = false;
        while ((!notempty) && (i>=0))
        {
            j=0;
            while ((j<=(Mat.Neff-i))&&(!notempty))
            {
                if (strlen(Mat.Array[i][j].Array[0])!=0)
                {
                    notempty=true;
                }
                else
                {
                    j++;
                }
            }
            if (!notempty)
            {
                i--;
            }
        }
        barissalah=TabString.Array[i].Line;
        printf("Baris yang menyebabkan salah adalah %d",barissalah);
    }
    
}