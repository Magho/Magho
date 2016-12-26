#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include<conio.h>
#include<windows.h>
#include"score.h"

int firstmove = 1;
int numberOfMines;
int nRows,mColoms;
int firstSecond ;
int firstMinute ;
int firstHour ;
int flag100=0,flag=1;
int seconds=0;
int flag3=1;
int flag1=0,flag2=0,flag4=1,flag300=1;
int flagoo=0;
int numOfQuestions=0,numberOfFlags,numberOfMovements=0;
pthread_t timeThread1;

// <------------------------------------------------- Counting a second --------------------------------------------->

void timeThread2(int milliseconds)
{

    int milli=clock()*1000/CLOCKS_PER_SEC;
    int fine =milli+milliseconds;

    do
    {

        milli=clock()*1000/CLOCKS_PER_SEC;
    }

    while (milli<=fine);
}

// <------------------------------------------------- Counting a second --------------------------------------------->


// <------------------------------------------------- print the array using threads --------------------------------->

void timeThread(char mineSweeper[][mColoms])
{

    int i=0;

    while (1)
    {
        timeThread2(1000);
        i++;
        pthread_testcancel();
        if (i%60==0)
        {
            printarray(mineSweeper);
        }
    }
}

// <------------------------------------------------- print the array using threads --------------------------------->


// <------------------------------------------------- for first play in the game ------------------------------------>

void firstmovework(int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int a,int b,int arrayOfMines[][2],int numberOfMines)
{
    int c,d;
    int i=0;
    while (i<numberOfMines )            // distributing mines using rand function
    {
        c=rand()%nRows;
        d=rand()%mColoms;

        if (c==a-1&&d==b-1)
        {
            continue;
        }

        int found = 0;
        int k;

        for (k =0 ; k < numberOfMines ; k++)
        {
            if (c == arrayOfMines[k][0] && d == arrayOfMines[k][1])  // if the cell already has a mine break
            {
                found = 1;
                break;
            }
        }
        if (found)continue;

        arrayOfMines[i][0]=c;
        arrayOfMines[i][1]=d;
        mineSweeper2[c][d]='M';

        i++;
    }

    int t =0;
    for (t ; t < numberOfMines ; t++)
    {

        c = arrayOfMines[t][0];
        d = arrayOfMines[t][1];
        int k = c -1;
        int k_fin = c+1;
        if (k < 0)k++;
        if (k_fin >= nRows)k_fin--;
        int j_fin = d + 1;
        if ( j_fin >= mColoms)j_fin--;

        for (k ; k <= k_fin; k++)
        {
            int j = d-1;
            if (j < 0)j++;
            for ( j ; j <= j_fin ; j++)
            {
                if ( (k != c || j != d)&& mineSweeper2[k][j] != 'M')      //distributing numbers around mines
                {
                    mineSweeper1[k][j]++;
                }
            }
        }
    }

}

// <------------------------------------------------- for first play in the game ------------------------------------>

// <------------------------------------------------- auto open function -------------------------------------------->

void autoOpen(int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int a,int b)
{

    int count1 =0;
    int c=a-1;
    int d=b-1;
    int k = c -1;
    int k_fin = c+1;
    if (k < 0)k++;
    if (k_fin >= nRows)k_fin--;
    int j_fin = d + 1;
    if ( j_fin >= mColoms)j_fin--;


    for (k ; k <= k_fin; k++)
    {
        int j = d-1;
        if (j < 0)j++;
        for ( j ; j <= j_fin ; j++)
        {
            if (mineSweeper3[k][j]=='F')count1++;     //counting flags around the cell
        }
    }

    if (count1>=mineSweeper1[a-1][b-1]&&mineSweeper1[a-1][b-1]!=0)
    {
        flag300=1;
        int c=a-1;
        int d=b-1;
        int k = c -1;
        int k_fin = c+1;
        if (k < 0)k++;
        if (k_fin >= nRows)k_fin--;
        int j_fin = d + 1;
        if ( j_fin >= mColoms)j_fin--;

        for (k ; k <= k_fin; k++)
        {
            int j = d-1;
            if (j < 0)j++;
            for ( j ; j <= j_fin ; j++)
            {
                if (mineSweeper3[k][j]!='F'&&mineSweeper2[k][j]==' '&&mineSweeper4[k][j]==0&&mineSweeper1[k][j]==0) //the cell is not opened and not flaged
                {
                    mineSweeper4[k][j]=1;
                    recursion(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,k+1,j+1);
                    mineSweeper3[k][j]=' ';                  //the cell is empty
                }
                else if (mineSweeper3[k][j]!='F'&&mineSweeper4[k][j]==0&&mineSweeper2[k][j]==' '&&mineSweeper1[k][j]!=0)//the cell has no flag and closed
                {
                    mineSweeper4[k][j]=1;
                    mineSweeper3[k][j]=mineSweeper1[k][j]+48;          //case the cell has a number
                }

                else if (mineSweeper3[k][j]!='F'&&mineSweeper2[k][j]=='M')   //the cell has no flag and has a mine
                {
                    mineSweeper4[k][j]=1;
                    flagoo==1;
                    lose (mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,k+1,j+1);
                }
            }
        }
    }
    else
    {

        flag300=0;
        printf("\n\t\t \t \t\t \t\t \tThe cell is already opened\n");
    }
}

// <------------------------------------------------- auto open function -------------------------------------------->


// <-------------------------------------------------  open function ------------------------------------------------>


void open (int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int a,int b)
{
    int i,j;

    if (mineSweeper4[a-1][b-1]==1)autoOpen(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b);

    else if (mineSweeper1[a-1][b-1]==0&&mineSweeper2[a-1][b-1]!='M')
    {
        mineSweeper3[a-1][b-1] = mineSweeper2[a-1][b-1];        //case the cell is empty
        mineSweeper4[a-1][b-1]=1;
        flag300=1;
        recursion(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b);

    }

    else
    {
        flag300=1;
        mineSweeper3[a-1][b-1] = mineSweeper1[a-1][b-1]+48;     //case the cell has a number
        mineSweeper4[a-1][b-1]=1;
    }
}

// <-------------------------------------------------  open function ------------------------------------------------>

// <-------------------------------------------------  recursion function ------------------------------------------------>

void recursion(int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int c,int d)
{

    c--;
    d--;
    int k = c -1;
    int k_fin = c+1;
    if (k < 0)k++;
    if (k_fin >= nRows)k_fin--;
    int j_fin = d + 1;
    if ( j_fin >= mColoms)j_fin--;

    for (k ; k <= k_fin; k++)
    {
        int j = d-1;
        if (j < 0)j++;
        for ( j ; j <= j_fin ; j++)
        {
            if (k!=c||j!=d)
            {

                if (mineSweeper2[k][j]==' '&&mineSweeper1[k][j]==0 && mineSweeper4[k][j] != 1)
                {
                    mineSweeper3[k][j]= ' ';  //case that the cell is empty
                    mineSweeper4[k][j]=1;
                    recursion(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,k+1,j+1);
                }
                else if (mineSweeper2[k][j]==' '&&mineSweeper1[k][j]!=0&& mineSweeper4[k][j] != 1)
                {
                    mineSweeper3[k][j]= mineSweeper1[k][j]+48;   //case that the cell has a number
                    mineSweeper4[k][j] = 1;
                }
            }
        }
    }
}

// <-------------------------------------------------  recursion function ------------------------------------------------>


// <-------------------------------------------------  print array int --------------------------------------------------->


void printarrayint(int mineSweeper[nRows][mColoms])
{
    int i,j;
    printf("\t");
    for (i=0; i<mColoms; i++)
    {
        printf("%d\t",i+1);             //print coloms numbers to the file
    }

    printf("\n");
    for (i=0; i<nRows; i++)
    {
        printf("\n%d\t",i+1);                   //print rows numbers to the file

        for(j=0; j<mColoms; j++)
        {
            printf("%d\t",mineSweeper[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// <-------------------------------------------------  print array int --------------------------------------------------->


// <-------------------------------------------------  print array char -------------------------------------------------->

void printarray(char mineSweeper[nRows][mColoms])
{
    int i,j;
    int timeInMinutes=0;
    int timeInSeconds=0;
    if (flag100==1)
    {

        // <-------------------------------------------------  read time before print -------------------------------------------->
        time_t timeAtEnd;
        time(&timeAtEnd);
        struct tm*firstTime = localtime(&timeAtEnd);

        int lastSecond = firstTime->tm_sec;
        int lastMinute = firstTime->tm_min;
        int lastHour = firstTime->tm_hour;

        int hours = (lastHour - firstHour)*3600;
        int minutes = (lastMinute-firstMinute)*60;
        seconds += (lastSecond-firstSecond)+minutes+hours;

        timeInMinutes = seconds /60;
        timeInSeconds = seconds%60;
        printf("\t \t \t\t \t\t \t        Time In Minutes : %d\t Time In Seconds :%d \t Flags possible : %d \n",timeInMinutes,timeInSeconds,numberOfFlags);
        printf("\t \t \t\t \t\t \t        number of movements: %d\t number of used flags: %d\t number of Qmarks: %d\n\n",numberOfMovements,numberOfMines-numberOfFlags,numOfQuestions);


        // <-------------------------------------------------  read time before print -------------------------------------------->

    }
    system("cls");
    view();

    printf("\t \t \t\t \t\t \t        Time In Minutes : %d\t Time In Seconds :%d \t Flags possible : %d \n",timeInMinutes,timeInSeconds,numberOfFlags);
    printf("\t \t \t\t \t\t \t        number of movements: %d\t number of used flags: %d\t number of Qmarks: %d\n\n",numberOfMovements,numberOfMines-numberOfFlags,numOfQuestions);


    printf("\t \t \t\t \t\t \t        \t");
    for (i=0; i<mColoms; i++)
    {
        printf("%d\t",i+1);                     //print coloms numbers to the file
    }
    printf("\n");

    for (i=0; i<nRows; i++)
    {
        printf("\n\t \t \t\t \t\t \t        %d\t",i+1);         //print rows numbers to the file

        for(j=0; j<mColoms; j++)
        {
            printf("%c\t",mineSweeper[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


// <-------------------------------------------------  print array char -------------------------------------------------->


// <-------------------------------------------------  winning code  ----------------------------------------------------->

void win(int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int a,int b,int arrayOfMines[][2],int numberOfMines)
{
    int i,j,h;
    flag3=1;
    for (j=0; j<nRows; j++)
    {
        for (h=0; h<mColoms; h++)
        {
            flag4=1;
            for (i=0; i<numberOfMines; i++)
            {
                if (j==arrayOfMines[i][0]&&h==arrayOfMines[i][1])   //check that the cells of mines are not opened
                {
                    flag4=0;
                    break;
                }
            }
            if(flag4==1)
            {
                if (mineSweeper4[j][h]==1)
                {
                    flag2=1;
                }

                else
                {
                    flag2=0;
                    flag3=0;
                    break;
                }
            }
        }
        if (flag3==0)break;
    }

    if ( flag2==1)
    {
        for (i=0; i<numberOfMines; i++)                            //check that other cells are opened
        {
            mineSweeper3[arrayOfMines[i][0]][arrayOfMines[i][1]]='F';
        }

        printarray(mineSweeper3);
        printf("\n\t \t \t\t \t\t \tYou did it!   You wined the game\n\n\n");
        pthread_cancel(timeThread1);
        int score1  = ((pow(nRows,4)*pow(mColoms,4))/(seconds*numberOfMovements));


        // <-------------------------------------------------  getting scores from file -------------------------------------------------->

        int j,i,h,flag12=0,duplicate;
        FILE *file = fopen("score.txt","r");
        int number;

        fscanf(file,"%i",&number);                  //get number of people played before
        number+=1;
        typedef struct
        {
            char name[100];
            int grade ;
        } score;

        score winners[number];                      //get scores from the score file
        for (i=0; i<number-1; i++)
        {
            fscanf(file,"%s",winners[i].name);
            fscanf(file," %i",&winners[i].grade);
        }

        winners[number-1].grade=score1;
        char yourname[100];
        printf("\n\t \t \t\t \t\t \tenter your name :\n");      //asking the user for name
        printf("\t \t \t\t \t\t \t\t");
        scanf("%s",winners[number-1].name);
        fflush(stdin);
        strupr(winners[number-1].name);
        strcpy(yourname,winners[number-1].name);

        for (i=0; i<number-1; i++)
        {
            if (!stricmp(winners[number-1].name,winners[i].name))
            {
                flag12=1;
                duplicate=i;
                break;
            }
            else flag12=0;
        }

        //checking that the name was not used before

        while (flag12==1)
        {
            printf("\\t \t \t\t \t\t \tThe name is already used if you want to save as a new player enter \"N\" \n\t \t \t\t \t\t \tif yo want to add this score to the old one enter\"Y\" ");
            char x;
            printf("\t \t \t\t \t\t \t\t");
            scanf("%c",&x);
            fflush(stdin);
            x=toupper(x);
            if  (x=='N')//change the repeated name
            {
                printf("\n\t \t \t\t \t\t \tEnter your name again :\n");
                printf("\t \t \t\t \t\t \t\t");
                scanf("%s",winners[number-1].name);
                fflush(stdin);
                strupr(winners[number-1].name);
                strcpy(yourname,winners[number-1].name);
                for (i=0; i<number-1; i++)
                {
                    if (!stricmp(winners[number-1].name,winners[i].name))
                    {
                        flag12=1;
                        break;
                        duplicate=i;
                    }
                    else flag12=0;
                }
            }

            else if (x=='Y')//add score to the last one
            {
                winners[duplicate].grade+=winners[number-1].grade;
                number--;
                flag12=0;
            }
        }

        // sort the scores in a structure

        for (j=0; j<number-1; j++)
        {
            for (i=0; i<number-1; i++)
            {
                if (winners[i].grade<winners[i+1].grade)
                {
                    int temp1;

                    temp1=winners[i].grade;
                    winners[i].grade=winners[i+1].grade;
                    winners[i+1].grade=temp1;

                    char temp2[100];
                    strcpy(temp2,winners[i].name);
                    strcpy(winners[i].name,winners[i+1].name);
                    strcpy(winners[i+1].name,temp2);
                }
            }
        }

        printf("\n");

        //print scores for the player

        for (i=0; i<number; i++)
        {
            if (!strcmp(winners[i].name,yourname))
            {

                HANDLE mohamed = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
                WORD saved_attributes;
                GetConsoleScreenBufferInfo(mohamed,&consoleInfo);
                saved_attributes = consoleInfo.wAttributes;
                SetConsoleTextAttribute(mohamed, 249);


                printf("\t \t \t\t \t\t \t%d.%s\t",i+1,winners[i].name);    // the name of the current winner
                printf("\t \t \t\t \t\t \t%d\t\t\t\t\t\t\t\t\t\n",winners[i].grade);

                SetConsoleTextAttribute(mohamed, saved_attributes);

            }
            else
            {
                printf("\t \t \t\t \t\t \t%d.%s\t",i+1,winners[i].name);
                printf("\t\t\t\t\t\t\t%d\n",winners[i].grade);
            }
        }

        fclose(file);
        FILE *file2 = fopen("score.txt","w");
        fprintf(file2,"%d",number);
        fputs("\n",file);
        for (i=0; i<number; i++)
        {
            fprintf(file2,"%s %d",winners[i].name,winners[i].grade);       //print arranged scores to the score file
        }
        fclose(file2);
        flag=0;
    }

    // <-------------------------------------------------  getting scores from file -------------------------------------------------->
}
// <-------------------------------------------------   win function ------------------------------------------------------------->

// <-------------------------------------------------   lose function ------------------------------------------------------------>

void lose (int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int a,int b)
{
    int i,j;

    for (i=0; i<nRows; i++)
    {
        for(j=0; j<mColoms; j++)
        {
            if (mineSweeper2[i][j]=='M'&&mineSweeper3[i][j]=='F')            //right flags
            {

                mineSweeper3[i][j]='*';
            }

            else if (mineSweeper3[i][j]=='F'&&mineSweeper2[i][j]!='M')      //wrong flags
            {

                mineSweeper3[i][j]='-';
            }

            else if (mineSweeper2[i][j]=='M'&&mineSweeper3[i][j]!='F')       //mines that he did not open
            {

                mineSweeper3[i][j]='M';
            }
        }
    }

    mineSweeper3[a-1][b-1]='!';      //the cell that made the player lose
    printf(" You are a big loser\n\n");
    printarray(mineSweeper3);
    printf(" You are a big loser\n\n");
    flag =0;
}
// <-------------------------------------------------   lose function ------------------------------------------------------------>

void openedGrid(int mineSweeper1[][mColoms],char mineSweeper2[][mColoms])
{

    FILE *opened = fopen("Opened Grid.txt","w");

    int i,j;
    fprintf(opened,"\t");
    for (i=0; i<mColoms; i++)
    {
        fprintf(opened,"%d",i+1);      //print colums  numbers to the file
        fprintf(opened,"\t");

    }
    fprintf(opened,"\n");

    for (i=0; i<nRows; i++)
    {
        fprintf(opened,"\n");
        fprintf(opened,"%d",i+1);              //print rows numbers to the file
        fprintf(opened,"\t");

        for(j=0; j<mColoms; j++)
        {
            fprintf(opened,"%d",mineSweeper1[i][j]);
            fprintf(opened,"\t");
        }
        fprintf(opened,"\n");
    }

    fprintf(opened,"\n");
    fprintf(opened,"\n");
    fprintf(opened,"\n");


    fprintf(opened,"\t");
    for (i=0; i<mColoms; i++)
    {
        fprintf(opened,"%d",i+1);                       //print colums  numbers to the file
        fprintf(opened,"\t");

    }

    for (i=0; i<nRows; i++)
    {
        fprintf(opened,"\n");
        fprintf(opened,"%d",i+1);                       //print rows numbers to the file
        for(j=0; j<mColoms; j++)
        {
            fprintf(opened,"\t");
            fprintf(opened,"%c",mineSweeper2[i][j]);
        }
        fprintf(opened,"\n");
    }
    fprintf(opened,"\n");
    fclose(opened);
}


void saveTheGame (int Minesweeper1[nRows][mColoms],char Minesweeper2[nRows][mColoms],char Minesweeper3[nRows][mColoms],int Minesweeper4[nRows][mColoms],int arrayOfMines[numberOfMines][2])
{
    pthread_cancel(timeThread1);
    int i,score1,duplicate,flag12;
    FILE *file = fopen("load.txt","r");
    int number;

    fscanf(file,"%i",&number);                  //get number of people played before
    number+=1;

    typedef struct
    {
        char name[100];
        int numberOfMines;
        int nRows;
        int mColoms;
        int flag100;
        int flag;
        int seconds ;
        int flag3;
        int flag1;
        int flag2;
        int flag4;
        int flag300;
        int flagoo;
        int numOfQuestions;
        int numberOfFlags;
        int numberOfMovements;
        int mineSweeper1[30][30];
        char mineSweeper2[30][30];
        char mineSweeper3[30][30];
        int mineSweeper4[30][30];
        int arrayOfMines[100][2];

    } load;

    int j,k;
    load winners[number];                      //get scores from the score file
    for (i=0; i<number-1; i++)
    {
        fscanf(file,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",winners[i].name,&winners[i].numberOfMines,&winners[i].nRows,&winners[i].mColoms,&winners[i].flag100,&winners[i].flag,&winners[i].seconds,&winners[i].flag3,&winners[i].flag1,&winners[i].flag2,&winners[i].flag4,&winners[i].flag300,&winners[i].flagoo,&winners[i].numOfQuestions,&winners[i].numberOfFlags,&winners[i].numberOfMovements);

        for (j=0; j<winners[i].nRows; j++)
        {
            for (k=0; k<winners[i].mColoms; k++)
            {
                fscanf(file,"%d ",&winners[i].mineSweeper1[j][k]);
            }
        }
        for (j=0; j<winners[i].nRows; j++)
        {
            for (k=0; k<winners[i].mColoms; k++)
            {
                int temp3;
                fscanf(file , "%d " , &temp3);
                winners[i].mineSweeper2[j][k] = temp3;
            }
        }
        for (j=0; j<winners[i].nRows; j++)
        {
            for (k=0; k<winners[i].mColoms; k++)
            {
                int temp3;
                fscanf(file , "%d " , &temp3);
                winners[i].mineSweeper3[j][k] = temp3;
            }
        }
        for (j=0; j<winners[i].nRows; j++)
        {
            for (k=0; k<winners[i].mColoms; k++)
            {
                fscanf(file,"%d ",&winners[i].mineSweeper4[j][k]);
            }
        }

        for (k=0; k<winners[i].numberOfMines; k++)
        {
            fscanf(file,"%d ",&winners[i].arrayOfMines[k][0]);
            fscanf(file,"%d ",&winners[i].arrayOfMines[k][1]);
        }
    }


    printf("\n\t \t \t\t \t\t \tenter your name :\n");      //asking the user for name
    printf("\t \t \t\t \t\t \t\t");
    scanf("%s",winners[number-1].name);
    fflush(stdin);
    strupr(winners[number-1].name);

    winners[number-1].numberOfMines=numberOfMines;
    winners[number-1].nRows=nRows;
    winners[number-1].mColoms=mColoms;
    winners[number-1].flag100=flag100;
    winners[number-1].flag=flag;
    winners[number-1].seconds=seconds;
    winners[number-1].flag3=flag3;
    winners[number-1].flag1=flag1;
    winners[number-1].flag2=flag2;
    winners[number-1].flag4=flag4;
    winners[number-1].flag300=flag300;
    winners[number-1].flagoo=flagoo;
    winners[number-1].numOfQuestions=numOfQuestions;
    winners[number-1].numberOfFlags=numberOfFlags;
    winners[number-1].numberOfMovements=numberOfMovements;

    for (j=0; j<nRows; j++)
    {
        for (k=0; k<mColoms; k++)
        {
            winners[number-1].mineSweeper1[j][k]=Minesweeper1[j][k];
        }
    }

    for (j=0; j<nRows; j++)
    {
        for (k=0; k<mColoms; k++)
        {
            winners[number-1].mineSweeper2[j][k]=Minesweeper2[j][k];
        }
    }

    for (j=0; j<nRows; j++)
    {
        for (k=0; k<mColoms; k++)
        {
            winners[number-1].mineSweeper3[j][k]=Minesweeper3[j][k];
        }
    }

    for (j=0; j<nRows; j++)
    {
        for (k=0; k<mColoms; k++)
        {
            winners[number-1].mineSweeper4[j][k]=Minesweeper4[j][k];
        }
    }

    for (k=0; k<numberOfMines; k++)
    {
        winners[number-1].arrayOfMines[k][0]=arrayOfMines[k][0];
        winners[number-1].arrayOfMines[k][1]=arrayOfMines[k][1];
    }


    for (i=0; i<number-1; i++)
    {
        if (!stricmp(winners[number-1].name,winners[i].name))
        {
            flag12=1;
            duplicate=i;
            break;
        }
        else flag12=0;
    }

    //checking that the name was not used before

    while (flag12==1)
    {
        printf("\\t \t \t\t \t\t \tThe name is already used if you want to save as a new player enter \"N\" \n\t \t \t\t \t\t \tif yo want to add this score to the old one enter\"Y\" ");
        char x;
        printf("\t \t \t\t \t\t \t\t");
        scanf("%c",&x);
        fflush(stdin);
        x=toupper(x);
        if  (x=='N')//change the repeated name
        {
            printf("\n\t \t \t\t \t\t \tEnter your name again :\n");
            printf("\t \t \t\t \t\t \t\t");
            scanf("%s",winners[number-1].name);
            fflush(stdin);
            strupr(winners[number-1].name);
            for (i=0; i<number-1; i++)
            {
                if (!stricmp(winners[number-1].name,winners[i].name))
                {
                    flag12=1;
                    break;
                    duplicate=i;
                }
                else flag12=0;
            }
        }

        else if (x=='Y')//add score to the last one
        {

            winners[duplicate].numberOfMines=numberOfMines;
            winners[duplicate].nRows=nRows;
            winners[duplicate].mColoms=mColoms;
            winners[duplicate].flag100=flag100;
            winners[duplicate].flag=flag;
            winners[number-1].seconds=seconds;
            winners[duplicate].flag3=flag3;
            winners[duplicate].flag1=flag1;
            winners[duplicate].flag2=flag2;
            winners[duplicate].flag4=flag4;
            winners[duplicate].flag300=flag300;
            winners[duplicate].flagoo=flagoo;
            winners[duplicate].numOfQuestions=numOfQuestions;
            winners[duplicate].numberOfFlags=numberOfFlags;
            winners[duplicate].numberOfMovements=numberOfMovements;



            for (j=0; j<nRows; j++)
            {
                for (k=0; k<mColoms; k++)
                {
                    winners[duplicate].mineSweeper1[j][k]=Minesweeper1[j][k];
                }
            }

            for (j=0; j<nRows; j++)
            {
                for (k=0; k<mColoms; k++)
                {
                    winners[duplicate].mineSweeper2[j][k]=Minesweeper2[j][k];
                }
            }

            for (j=0; j<nRows; j++)
            {
                for (k=0; k<mColoms; k++)
                {
                    winners[duplicate].mineSweeper3[j][k]=Minesweeper3[j][k];
                }
            }

            for (j=0; j<nRows; j++)
            {
                for (k=0; k<mColoms; k++)
                {
                    winners[duplicate].mineSweeper4[j][k]=Minesweeper4[j][k];
                }
            }

            for (k=0; k<numberOfMines; k++)
            {
                winners[duplicate].arrayOfMines[k][0]=arrayOfMines[k][0];
                winners[duplicate].arrayOfMines[k][1]=arrayOfMines[k][1];
            }


            number--;
            flag12=0;
        }
    }

    printf("\n");

    fclose(file);
    FILE *file2 = fopen("load.txt","w");
    fprintf(file2,"%d",number);
    fputs("\n",file);
    for (i=0; i<number; i++)
    {
        fprintf(file,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",winners[i].name,winners[i].numberOfMines,winners[i].nRows,winners[i].mColoms,winners[i].flag100,winners[i].flag,winners[i].seconds,winners[i].flag3,winners[i].flag1,winners[i].flag2,winners[i].flag4,winners[i].flag300,winners[i].flagoo,winners[i].numOfQuestions,winners[i].numberOfFlags,winners[i].numberOfMovements);

        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                fprintf(file,"%d ",winners[i].mineSweeper1[j][k]);
            }
        }
        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                fprintf(file,"%d ",winners[i].mineSweeper2[j][k]);
            }
        }
        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                fprintf(file,"%d ",winners[i].mineSweeper3[j][k]);
            }
        }
        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                fprintf(file,"%d ",winners[i].mineSweeper4[j][k]);
            }
        }

        for (k=0; k<numberOfMines; k++)
        {
            fprintf(file,"%d ",winners[i].arrayOfMines[k][0]);
            fprintf(file,"%d ",winners[i].arrayOfMines[k][1]);
        }
    }

    fclose(file2);
    flag=1;
    printarray(Minesweeper3);
    pthread_create(&timeThread1,NULL,timeThread,Minesweeper3);

    //system("cls");
    // to end the game
}

void enterCases (int actionChoice,int mineSweeper1[][mColoms],char mineSweeper2[][mColoms],char mineSweeper3[][mColoms],int mineSweeper4[][mColoms],int arrayOfMines[][2],int a,int b)
{

    switch (actionChoice)
    {

    case 'O':

        //<-------------------------------------------------  Open Case   ------------------------------------------------->
        pthread_cancel(timeThread1);
        pthread_create(&timeThread1,NULL,timeThread,mineSweeper3);
        //distributing mines in first move using firstmovework function;
        if (firstmove)
        {
            firstmovework(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b,arrayOfMines,numberOfMines);
            openedGrid(mineSweeper1,mineSweeper2);
        }
        firstmove = 0;

        //using lose function if a mine opened;
        if ((mineSweeper2[a-1][b-1]=='M'&&mineSweeper3[a-1][b-1]!='F')||(flagoo==1&&mineSweeper3[a-1][b-1]!='F'))  lose(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b);


        else if (mineSweeper3[a-1][b-1]=='F')printf("\n\t \t \t\t \t\t \t        The cell is flaged if you want to open it remove the flag first");

        else
        {
            open(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b);
            if (flagoo==0&&flag300==1)
            {
                numberOfMovements+=1;
                printarray(mineSweeper3);
                printf("\n");
            }
        }

        //use win game function if all mines was flaged or the are the rest only;
        win(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,a,b,arrayOfMines,numberOfMines);

        break;

    //<-------------------------------------------------  Open Case   ------------------------------------------------->

    //<-------------------------------------------------  flag Case   ------------------------------------------------->


    case 'F':

        pthread_cancel(timeThread1);
        pthread_create(&timeThread1,NULL,timeThread,mineSweeper3);
        if (mineSweeper3[a-1][b-1]=='F')printf("\n\t \t \t\t \t\t \t        The Cell is already Flaged");

        else if (numberOfFlags==0) printf("\n\t \t \t\t \t\t \t        You have already used all possible flags");

        else if (mineSweeper4[a-1][b-1]==0&&numberOfFlags!=0)
        {
            mineSweeper3[a-1][b-1]='F';
            numberOfFlags-=1;
            numberOfMovements+=1;
            printarray(mineSweeper3);
            printf("\n");
        }

        else if (mineSweeper4[a-1][b-1]==1) printf("\n\t \t \t\t \t\t \t        The cell is opened You cannot flag it\n");

        break;

    //<-------------------------------------------------  flag Case   ------------------------------------------------->


    //<-------------------------------------------------  Question Case   ------------------------------------------------->

    case 'Q':
        pthread_cancel(timeThread1);
        pthread_create(&timeThread1,NULL,timeThread,mineSweeper3);

        if (mineSweeper3[a-1][b-1]=='Q')printf("\n\t \t \t\t \t\t \t        The Cell is already Questioned");
        else if (mineSweeper4[a-1][b-1]==0)
        {
            mineSweeper3[a-1][b-1]='Q';
            numberOfMovements+=1;
            numOfQuestions+=1;
            printarray(mineSweeper3);
            printf("\n");
        }
        else if (mineSweeper4[a-1][b-1]==1)printf("\n\t \t \t\t \t\t \t        The cell is opened You cannot Question it\n");
        break;
    //<-------------------------------------------------  Question Case   ------------------------------------------------->

    //<------------------------------------------------- erase flag or questions Case ------------------------------------->

    case 'U':
        pthread_cancel(timeThread1);
        pthread_create(&timeThread1,NULL,timeThread,mineSweeper3);

        if ((mineSweeper3[a-1][b-1]=='Q'||mineSweeper3[a-1][b-1]=='F')&&mineSweeper4[a-1][b-1]==0)
        {
            if (mineSweeper3[a-1][b-1]=='F')numberOfFlags+=1;
            else numOfQuestions-=1;
            mineSweeper3[a-1][b-1]='X';
            numberOfMovements+=1;
            printarray(mineSweeper3);
            printf("\n");
        }
        else if (mineSweeper3[a-1][b-1]!='Q'&&mineSweeper3[a-1][b-1]!='F') printf("\n\t \t \t\t \t\t \t        The cell isnot Flaged or Questioned yet\n");

        else printf("\n\t \t \t\t \t\t \t        The cell is opened You cannot do this a ction to it\n");
        printf("\n");

        break;

    case 'S':

        if (firstmove==1){

            printf("\n\t \t \t\t \t\t \tyou canot save the game now");
            break;
        }
        saveTheGame(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,arrayOfMines);
        break;
        //<------------------------------------------------- erase flag or questions Case ------------------------------------->
    }

}

void view (){


    printf("\n\t \t \t\t \t\t \t                          \t         **                        ");
    printf("\n\t \t \t\t \t\t \t          **          **  \t        **            ********");
    printf("\n\t \t \t\t \t\t \t         ****        **** \t      |*|             **********");
    printf("\n\t \t \t\t \t\t \t        ******      ******\t      |*|            ******  ****");
    printf("\n\t \t \t\t \t\t \t        ******************\t    *******         ******    ****");
    printf("\n\t \t \t\t \t\t \t        ******************\t   **********        ******    ");
    printf("\n\t \t \t\t \t\t \t        ****  ******  ****\t **************       ******");
    printf("\n\t \t \t\t \t\t \t        ****   ****   ****\t****************       ******");
    printf("\n\t \t \t\t \t\t \t        ****    **    ****\t****************        ******");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t****************         *******");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t****************          *******");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t **************    ****    *******   ");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t  ************     *****  *******");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t   **********       ***********");
    printf("\n\t \t \t\t \t\t \t        ****          ****\t     *******         *********");
    printf("\n\t \t \t\t \t\t \t        __________________________________________________________\n\n\n");


}
