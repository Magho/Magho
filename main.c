#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include<conio.h>
#include<windows.h>
#include "functions.h"

int main()
{
    //srand(time(NULL));
    system("color 0c");

    view();
    printf("\t \t \t\t \t\t \t        main manue \n\n");
    printf("\t \t \t\t \t\t \t        1-start the game\n\n");
    printf("\t \t \t\t \t\t \t        2-Load the last game\n\n");
    printf("\t \t \t\t \t\t \t        3-show scores\n\n");
    printf("\t \t \t\t \t\t \t        4- How to play the game\n\n");
    printf("\t \t \t\t \t\t \t        To save the game enter s at any time\n\n");            // game view function
    int mainChoice;

    while(1)
    {

        //<-------------------------------------------------Validation of choosing from main menu ----------------------------------------->
        printf("\t \t \t\t \t\t \t\t");
        while (scanf("%d",&mainChoice)!=1)
        {
            fflush(stdin);
            printf("\n\t \t \t\t \t\t \t        please choose a number from 1 to 4\n");
            printf("\t \t \t\t \t\t \t\t");
        }
        fflush(stdin);
        if (mainChoice==1||mainChoice==2||mainChoice==3||mainChoice==4)
        {
            break;
        }
        else if (mainChoice!=1&&mainChoice!=2&&mainChoice!=3&&mainChoice!=3)
        {
            printf("\n\t \t \t\t \t\t \t        please choose a number from 1 to 4\n");
        }
    }
    // <-------------------------------------------------case of  playing the game --------------------------------------------->

    if (mainChoice==1)
    {
        while (1)
        {

            //<-------------------------------------------------Validation of choosing dimension ----------------------------------------->

            printf("\n\t \t \t\t \t\t \t        please dimensions must be between 3 and 30\n");
            printf("\t \t \t\t \t\t \t\t");
            while (scanf("%d %d",&nRows,&mColoms)   !=  2 )
            {
                while(getchar() != '\n');
                printf("\n\t \t \t\t \t\t \t        please dimensions must be between 3 and 30\n");

                printf("\t \t \t\t \t\t \t\t");
            }
            fflush(stdin);


            if ((nRows<3||nRows>30)||(mColoms<3||mColoms>30))
            {
                printf("\n\t \t \t\t \t\t \t        the dimensions are not acceptable please enter it again\n");
            }
            else break;

            //<-------------------------------------------------Validation of choosing dimension ------------------------------------------------->

            //<-------------------------------------------------Declaring arrays of the main game------------------------------------------------->
        }
        int i,j;
        int mineSweeper1[nRows][mColoms],mineSweeper4[nRows][mColoms];
        char mineSweeper2[nRows][mColoms],mineSweeper3[nRows][mColoms];

        for (i=0; i<nRows; i++)
        {
            for(j=0; j<mColoms; j++)
            {
                mineSweeper1[i][j]=0;
            }
        }

        for (i=0; i<nRows; i++)
        {
            for(j=0; j<mColoms; j++)
            {
                mineSweeper2[i][j]=' ';
            }
        }

        for (i=0; i<nRows; i++)
        {
            for(j=0; j<mColoms; j++)
            {
                mineSweeper3[i][j]='X';
            }
        }

        for (i=0; i<nRows; i++)
        {
            for(j=0; j<mColoms; j++)
            {
                mineSweeper4[i][j]=0;
            }
        }

        printarray(mineSweeper3);

        //<-------------------------------------------------   state first time   ------------------------------------------------->

        time_t timeAtStart;
        time(&timeAtStart);
        struct tm*firstTime = localtime(&timeAtStart);

        firstSecond = firstTime->tm_sec;
        firstMinute = firstTime->tm_min;
        firstHour = firstTime->tm_hour;
        flag100=1;

        //<-------------------------------------------------   state first time   ------------------------------------------------->
        numberOfMines =((nRows*mColoms)/10)+1;
        numberOfFlags=numberOfMines;
        int arrayOfMines[numberOfMines][2];                     //arrayOfMines contain place of mines;
        int question =0;
        int h;
        while (flag)
        {
            int a, b;
            char actionChoice;
            //<--------------------------------------Validation on choosing cells-----------------------------------------------

            printf("\n\t \t \t\t \t\t \t        enter an action\n");
            printf("\n\t \t \t\t \t\t \t        1- enter O for open a cell\n");
            printf("\n\t \t \t\t \t\t \t        2- enter F to flag a cell\n");
            printf("\n\t \t \t\t \t\t \t        3- enter Q to question a cell\n");
            printf("\n\t \t \t\t \t\t \t        4- enter U for unflag or unquestion a cell\n");
            printf("\t \t \t\t \t\t \t\t");

            while (1)
            {
                printf("\t \t \t\t \t\t \t\t");

                while (scanf("%c",&actionChoice)   !=  1 )
                {
                    actionChoice = toupper(actionChoice);
                    while(getchar() != '\n');
                    printf("\n\t \t \t\t \t\t \t        Please choose a character from above\n");
                    printf("\t \t \t\t \t\t \t\t");
                }
                actionChoice = toupper(actionChoice);
                fflush(stdin);
                if (actionChoice!='O'&&actionChoice!='F'&&actionChoice!='Q'&&actionChoice!='U'&&actionChoice!='S')
                {
                    printf("\n\t \t \t\t \t\t \t        Please choose a character from above\n");
                }
                else break;
            }

            if (actionChoice=='S')
            {

                if (firstmove==1)
                {
                    printf("\n\t \t \t\t \t\t \tyou canot save the game now");
                    continue;
                }
                saveTheGame(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,arrayOfMines);
            }

            printf("\n\t \t \t\t \t\t \t        enter a cell\n");
            while (1)
            {
                printf("\t \t \t\t \t\t \t\t");

                while (scanf("%d %d",&a,&b)   !=  2 )
                {
                    while(getchar() != '\n');
                    printf("\n\t \t \t\t \t\t \t        please  must be a number between %d and %d\n",nRows,mColoms);
                    printf("\t \t \t\t \t\t \t\t");
                }
                fflush(stdin);
                if (a>nRows||a>mColoms||b>nRows||b>mColoms)
                {
                    printf("\n\t \t \t\t \t\t \t        please  must be a number between %d and %d\n",nRows,mColoms);
                }
                else break;
            }
            enterCases(actionChoice,mineSweeper1,mineSweeper2,mineSweeper3,mineSweeper4,arrayOfMines,a,b);
        }
    }

    // <-------------------------------------------------case of  playing the game --------------------------------------------->


    // <-------------------------------------------------case of showing score--------------------------------------------->

    if (mainChoice==2)
    {
        pthread_cancel(timeThread1);
        firstmove=0;
        int i,score1,duplicate,flag12=1;
        FILE *file = fopen("load.txt","r");
        int number;

        fscanf(file,"%i",&number);                  //get number of people played before

        typedef struct
        {
            char name[100];
            int numberOfMines;
            int nRows;
            int mColoms;
            int flag100;
            int flag;
            int seconds;
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
        for (i=0; i<number; i++)
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
                    fscanf(file, "%d ", &temp3);
                    winners[i].mineSweeper2[j][k] = temp3;
                }
            }
            for (j=0; j<winners[i].nRows; j++)
            {
                for (k=0; k<winners[i].mColoms; k++)
                {
                    int temp3;
                    fscanf(file, "%d ", &temp3);
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

        for (i=0; i<number; i++)
        {
            printf("\t \t \t\t \t\t \t%d.%s\t\n",i+1,winners[i].name);
        }

        printf("\n\t \t \t\t \t\t \tenter the name of the game to load :\n");      //asking the user for name
        printf("\t \t \t\t \t\t \t\t");
        char name[100];
        scanf("%s",name);
        fflush(stdin);
        strupr(name);

        while(flag12)
        {

            for (i=0; i<number; i++)
            {
                if (!stricmp(name,winners[i].name))
                {
                    flag12=0;
                    duplicate=i;
                    break;
                }
            }
            if (flag12)
            {

                printf("\n\t \t \t\t \t\t \tThere is no game saved with this name please choose a name from above\n");      //asking the user for name
                printf("\t \t \t\t \t\t \t\t");
                scanf("%s",name);
                fflush(stdin);
                strupr(name);
            }
        }
        printf("\n");

        numberOfMines=winners[duplicate].numberOfMines;
        nRows=winners[duplicate].nRows;
        mColoms=winners[duplicate].mColoms;
        flag100=winners[duplicate].flag100;
        flag=winners[duplicate].flag;
        seconds=winners[duplicate].seconds;
        flag3=winners[duplicate].flag3;
        flag1=winners[duplicate].flag1;
        flag2=winners[duplicate].flag2;
        flag4=winners[duplicate].flag4;
        flag300=winners[duplicate].flag300;
        flagoo=winners[duplicate].flagoo;
        numOfQuestions=winners[duplicate].numOfQuestions;
        numberOfFlags=winners[duplicate].numberOfFlags;
        numberOfMovements=winners[duplicate].numberOfMovements;

        int mineSweeper1[nRows][mColoms];
        char mineSweeper2[nRows][mColoms];
        char mineSweeper3[nRows][mColoms];
        int mineSweeper4[nRows][mColoms];
        int arrayOfMines[numberOfMines][2];

        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                mineSweeper1[j][k]=winners[duplicate].mineSweeper1[j][k];
            }
        }

        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                mineSweeper2[j][k]=winners[duplicate].mineSweeper2[j][k];
            }
        }

        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                mineSweeper3[j][k]=winners[duplicate].mineSweeper3[j][k];
            }
        }

        for (j=0; j<nRows; j++)
        {
            for (k=0; k<mColoms; k++)
            {
                mineSweeper4[j][k]=winners[duplicate].mineSweeper4[j][k];
            }
        }

        for (k=0; k<numberOfMines; k++)
        {
            arrayOfMines[k][0]=winners[duplicate].arrayOfMines[k][0];
            arrayOfMines[k][1]=winners[duplicate].arrayOfMines[k][1];
        }


        time_t timeAtStart;
        time(&timeAtStart);
        struct tm*firstTime = localtime(&timeAtStart);

        firstSecond = firstTime->tm_sec;
        firstMinute = firstTime->tm_min;
        firstHour = firstTime->tm_hour;
        flag100=1;

        if (firstmove==1)
        {

            numberOfMines =((nRows*mColoms)/10)+1;
            numberOfFlags=numberOfMines;
        }

        openedGrid(mineSweeper1,mineSweeper2);

        fclose(file);

        printarray(mineSweeper3);
        pthread_create(&timeThread1,NULL,timeThread,mineSweeper3);

        printarrayint(mineSweeper1);

while (flag)
        {
            int a, b;
            char actionChoice;
            //<--------------------------------------Validation on choosing cells-----------------------------------------------

            printf("\n\t \t \t\t \t\t \t        enter an action\n");
            printf("\n\t \t \t\t \t\t \t        1- enter O for open a cell\n");
            printf("\n\t \t \t\t \t\t \t        2- enter F to flag a cell\n");
            printf("\n\t \t \t\t \t\t \t        3- enter Q to question a cell\n");
            printf("\n\t \t \t\t \t\t \t        4- enter U for unflag or unquestion a cell\n");
            printf("\t \t \t\t \t\t \t\t");

            while (1)
            {
                printf("\t \t \t\t \t\t \t\t");

                while (scanf("%c",&actionChoice)   !=  1 )
                {
                    actionChoice = toupper(actionChoice);
                    while(getchar() != '\n');
                    printf("\n\t \t \t\t \t\t \t        Please choose a character from above\n");
                    printf("\t \t \t\t \t\t \t\t");
                }
                actionChoice = toupper(actionChoice);
                fflush(stdin);
                if (actionChoice!='O'&&actionChoice!='F'&&actionChoice!='Q'&&actionChoice!='U'&&actionChoice!='S')
                {
                    printf("\n\t \t \t\t \t\t \t        Please choose a character from above\n");
                }
                else break;
            }

            if (actionChoice=='S')
            {

                if (firstmove==1)
                {
                    printf("\n\t \t \t\t \t\t \tyou canot save the game now");
                    continue;
                }
                saveTheGame(mineSweeper1,mineSweeper2,mineSweeper3, mineSweeper4,arrayOfMines);
            }

            printf("\n\t \t \t\t \t\t \t        enter a cell\n");
            while (1)
            {
                printf("\t \t \t\t \t\t \t\t");

                while (scanf("%d %d",&a,&b)   !=  2 )
                {
                    while(getchar() != '\n');
                    printf("\n\t \t \t\t \t\t \t        please  must be a number between %d and %d\n",nRows,mColoms);
                    printf("\t \t \t\t \t\t \t\t");
                }
                fflush(stdin);
                if (a>nRows||a>mColoms||b>nRows||b>mColoms)
                {
                    printf("\n\t \t \t\t \t\t \t        please  must be a number between %d and %d\n",nRows,mColoms);
                }
                else break;
            }
            enterCases(actionChoice,mineSweeper1,mineSweeper2,mineSweeper3,mineSweeper4,arrayOfMines,a,b);
        }

    }
    if (mainChoice==3)
    {
        int j,i,h,flag=0,duplicate;
        FILE *file = fopen("score.txt","r");
        int number;

        fscanf(file,"%i",&number);      //get number of people played before
        number+=1;
        typedef struct
        {
            char name[100];
            int grade ;
        } score;

        score winners[number];
        for (i=0; i<number-1; i++)
        {
            fscanf(file,"%s",winners[i].name);
            fscanf(file," %i",&winners[i].grade);
        }

        for (i=0; i<number-1; i++)
        {
            printf("\n\t \t \t\t \t\t \t%d.%s\t",i+1,winners[i].name);
            printf("\n\t \t \t\t \t\t \t%d\n",winners[i].grade);
        }

        if  (number==1)printf("\n\t \t \t\t \t\t \t        there is no score yet\n");

        fclose(file);

        printf("\n\t \t \t\t \t\t \tpress enter to return to main menu\n");
        getchar();
        system("cls");
        main();
    }
    // <-------------------------------------------------case of showing score--------------------------------------------->
    // <-------------------------------------------------case of how to play the game--------------------------------------------->

    if (mainChoice==4)
    {
        system("cls");

        HANDLE mohamed = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;
        GetConsoleScreenBufferInfo(mohamed,&consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
        SetConsoleTextAttribute(mohamed, 02);

        printf("\n\t \t \t\t \t\t \t        When the game start there are four options for the user to choose from:\n\t \t \t\t \t\t \t\t 1-Start the game.\n\t \t \t\t \t\t\t \t 2-Load games.\n\t \t \t\t\t \t\t \t 3-Show scores.\n\t \t \t\t \t\t \t\t 4-How to play this game?\n");
        printf("\n\t \t \t\t \t\t \t        Case of 1:\n\n\t \t \t\t \t\t \t \tHere the user have to input the dimensions of the rectangle between 3:30 then choosing a cell and an action to be performed on it:\n\t \t \t\t \t\t \t ");
        printf("\t\"O\": to open the cell.\n\t \t \t\t \t\t \t \t\"F\": to flag the cell then he couldn’t open the cell until he unflag it.\n\t \t \t\t \t\t \t \t\"Q\": if the player doesn’t sure if the cell contain a mine or not.\n\t \t \t\t \t\t \t \t\"S\":To save the game");
        printf("\n\t \t \t\t \t\t \t\t\"U\": to remove a flag or question from a cell.\n\t \t \t\t \t\t \t\t Then the player keep playing until he win or lose.\n");
        printf("\n\n\t \t \t\t \t\t \t        Case of 2:\n\n");
        printf("\t\t \t \t\t \t\t \tThen all saved games is printed for the player to choose a game to load.\n");
        printf("\n\t \t \t\t \t\t \t        Case of 3:\n");
        printf("\n\t \t \t\t \t\t \t        The scores for all player played the game is printed on the screen ranked from the highest score to the lowest one.\n");
        SetConsoleTextAttribute(mohamed, saved_attributes);

        printf("\n\t \t \t\t \t\t \tpress enter to return to main menu\n");
        getchar();
        system("cls");
        main();
    }
    // <-------------------------------------------------case of show how to play the game--------------------------------------------->

    return 0;
}

