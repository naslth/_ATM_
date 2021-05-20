#include "../include/showScreen.h"
#include "../include/mysupplib.h"


void setConsoleScreen(int width, int height)
{
    setConsoleScreenBufferSize(width,height);

    setConsoleSize(width,height);

    SetConsoleTitle(TEXT("The ATM - BANKING SYSTEM"));
}



int showDisplayAndChooseOpt(int x, int y)
{
    int Color[] = {7,7,7,7}; // white color
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-14,y/2-11);
    setColor(Color[0]);
    std::cout << "The ATM - BANKING SYSTEM !!!";
    int tempY = y/2-9;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            gotoXY(x/2-15 + j, tempY);
            std::cout << "-";
        }
        tempY++;
        if (i != 3)
        {
            for(int j=tempY; j<tempY+3; j++)
            {
                gotoXY(x/2-15, j);
                std::cout << "|";
                gotoXY(x/2-15 + 29, j);
                std::cout << "|";
            }
        }
        tempY+=3;
    }
    while(true)
    {
        tempY=y/2-7;
        for(int i=1; i<=3; i++)
        {
            gotoXY(x/2-14,tempY);
            setColor(Color[i]);
            if(i==1)
                std::cout << " 1.  Sign up for an account";
            else if(i==2)
                std::cout << " 2.  Log in to account";
            else if(i==3)
                std::cout << " 3.  Exit";
            tempY+=4;
        }

        key=_getch();

        if(key==72&&(counter>=2&&counter<=3))
            counter--;
        if(key==80&&(counter>=1&&counter<=2))
            counter++;
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }

        for(int i=1; i<=3; i++)
        {
            if(counter==i)
                Color[i]=12; // red color
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
}



int showMenuAndChooseOpt(int x, int y)
{
    int Color[] = {7,7,7,7,7,7,7,7};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-15,y/2-12);
    setColor(Color[0]);
    std::cout << "-----------------MENU-----------------";
    int tempY = y/2-11;
    for (int i = 0; i < 8; i++)
    {
        if(i!=0)
        {
            for (int j = 0; j < 38; j++)
            {
                gotoXY(x/2-15 + j, tempY);
                std::cout << "-";
            }
            tempY++;
        }
        if (i != 7)
        {
            for(int j=tempY; j<tempY+2; j++)
            {
                gotoXY(x/2-15, j);
                std::cout << "|";
                gotoXY(x/2-15 + 29, j);
                std::cout << "|";
            }
        }
        tempY+=2;
    }
    while(true)
    {
        tempY=y/2-10;
        for(int i=1; i<=7; i++)
        {
            gotoXY(x/2-14,tempY);
            setColor(Color[i]);
            if(i==1)
                std::cout << "    1.   Transaction history";
            else if(i==2)
                std::cout << "    2.   Check your balance";
            else if(i==3)
                std::cout << "    3.   Deposit";
            else if(i==4)
                std::cout << "    4.   Withdraw";
            else if(i==5)
                std::cout << "    5.   Transfer";
            else if(i==6)
                std::cout << "    6.   Change Password";
            else if(i==7)
                std::cout << "    7.   Log out";
            tempY+=3;
        }

        key=_getch();

        if(key==72&&(counter>=2&&counter<=7))
            counter--;
        if(key==80&&(counter>=1&&counter<=6))
            counter++;
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }

        for(int i=1; i<=7; i++)
        {
            if(counter==i)
                Color[i]=12;
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
}



int showOptAndChoose(int x,int y,int caseOpt)
{
    int Color[] = {7,7};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-14,y/2-11);
    setColor(Color[0]);
    std::cout << "Please choose an option";
    int tempY = y/2-9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            gotoXY(x/2-15 + j, tempY);
            std::cout << "-";
        }
        tempY++;
        if (i != 2)
        {
            for(int j=tempY; j<tempY+3; j++)
            {
                gotoXY(x/2-15, j);
                std::cout << "|";
                gotoXY(x/2-15 + 34, j);
                std::cout << "|";
            }
        }
        tempY=tempY+3;
    }
    while(true)
    {

        gotoXY(x/2-14,y/2-7);
        setColor(Color[1]);
        if(caseOpt==1)
            std::cout << " 1.  Check transaction history";
        else if(caseOpt==2)
            std::cout << " 1.   Check balance";
        else if(caseOpt==3)
            std::cout << " 1.   Deposit";
        else if(caseOpt==4)
            std::cout << " 1.   Withdraw";
        else if(caseOpt==5)
            std::cout << " 1.   Tranfer";
        else if(caseOpt==6)
            std::cout << " 1.   Change password";
        else if(caseOpt==7)
            std::cout << " 1.   Log out";

        gotoXY(x/2-14,y/2-3);
        setColor(Color[2]);
        std::cout << " 2.   Return";

        key=_getch();

        if(key==72&&(counter==2))
            counter--;
        if(key==80&&(counter==1))
            counter++;
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }

        for(int i=1; i<=2; i++)
        {
            if(counter==i)
                Color[i]=12;
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
}

