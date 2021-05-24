#include "../include/showScreen.h"


void setConsoleScreen(int width, int height)
{
    setConsoleScreenBufferSize(width,height);

    setConsoleSize(width,height);

    SetConsoleTitle(TEXT("The ATM - BANKING SYSTEM"));
}



int showDisplayAndChooseOpt(int x, int y)
{
    int Color[] = {AQUA,AQUA,AQUA,AQUA};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    setColor(AQUA);
    gotoXY(x/2-45,y/2-15);
    std::cout << "    _  _____  __  __         ___              _    _               ___            _               ";
    gotoXY(x/2-45,y/2-14);
    std::cout << "   /_\\|_   _||  \\/  |  ___  | _ ) __ _  _ _  | |__(_) _ _   __ _  / __| _  _  ___| |_  ___  _ __  ";
    gotoXY(x/2-45,y/2-13);
    std::cout << "  / _ \\ | |  | |\\/| | |___| | _ \\/ _` || ` \\ | / /| || ` \\ / _` | \\__ \\| || |(_-<|  _|/ -_)| `  \\ ";
    gotoXY(x/2-45,y/2-12);
    std::cout << " /_/ \\_\\|_|  |_|  |_|       |___/\\__,_||_||_||_\\_\\|_||_||_|\\__, | |___/ \\_, |/__/ \\__|\\___||_|_|_|";
    gotoXY(x/2-45,y/2-11);
    std::cout << "                                                           |___/        |__/                      ";
    int tempY = y/2-8;
// Vẽ box
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
        tempY=y/2-6;
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
                Color[i]=RED; // chuyển dòng đang chọn thành màu đỏ
            else
                Color[i]=AQUA;
        }
    }
    setColor(WHITE);
    ShowCur(true);
    return answer;
}



int showMenuAndChooseOpt(int x, int y)
{
    int Color[] = {AQUA,AQUA,AQUA,AQUA,AQUA,AQUA,AQUA,AQUA,AQUA};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    setColor(AQUA);
    gotoXY(x/2-5,y/2-16);
    std::cout << "     __         ";
    gotoXY(x/2-5,y/2-15);
    std::cout << "|\\/||_ |\\ ||  | ";
    gotoXY(x/2-5,y/2-14);
    std::cout << "|  ||__| \\|\\__/ ";
    int tempY = y/2-12;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 38; j++)
        {
            gotoXY(x/2-15 + j, tempY);
            std::cout << "-";
        }
        tempY++;
        if (i != 8)
        {
            for(int j=tempY; j<tempY+2; j++)
            {
                gotoXY(x/2-15, j);
                std::cout << "|";
                gotoXY(x/2-15 + 37, j);
                std::cout << "|";
            }
        }
        tempY+=2;
    }
    while(true)
    {
        tempY=y/2-11;
        for(int i=1; i<=8; i++)
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
                std::cout << "    6.   Change password";
            else if(i==7)
                std::cout << "    7.   Log out";
            else if(i==8)
                std::cout << "    8.   Open music option";
            tempY+=3;
        }

        key=_getch();

        if(key==72&&(counter>=2&&counter<=8))
            counter--;
        if(key==80&&(counter>=1&&counter<=7))
            counter++;
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }

        for(int i=1; i<=8; i++)
        {
            if(counter==i)
                Color[i]=RED;
            else
                Color[i]=AQUA;
        }
    }
    setColor(WHITE);
    ShowCur(true);
    return answer;
}



int showOptAndChoose(int x,int y,int caseOpt)
{
    int Color[] = {AQUA,AQUA,AQUA};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    setColor(AQUA);
    gotoXY(x/2-13,y/2-12);
    std::cout << " __                                       ";
    gotoXY(x/2-13,y/2-11);
    std::cout << "/  |_  _  _  _ _    _  _    _  _ |_. _  _  ";
    gotoXY(x/2-13,y/2-10);
    std::cout << "\\__| )(_)(_)_)(-`  (_|| )  (_)|_)|_|(_)| ) ";
    gotoXY(x/2-13,y/2-9);
    std::cout << "                              |            ";
    int tempY = y/2-7;
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

        gotoXY(x/2-14,y/2-5);
        setColor(Color[1]);
        if(caseOpt==1)
            std::cout << " 1.   Check transaction history";
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

        gotoXY(x/2-14,y/2-1);
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
                Color[i]=RED;
            else
                Color[i]=AQUA;
        }
    }
    setColor(WHITE);
    ShowCur(true);
    return answer;
}

void showMusicAndChooseOpt(int x, int y)
{
    int Color[] = {AQUA,AQUA,AQUA,AQUA,AQUA};
    int counter=1;
    char key;
    ShowCur(false);
    setColor(AQUA);
    gotoXY(x/2-10,y/2-14);
    std::cout << "|\\/|    _. _   _  _ |_. _  _  ";
    gotoXY(x/2-10,y/2-13);
    std::cout << "|  ||_|_)|(_  (_)|_)|_|(_)| ) ";
    gotoXY(x/2-10,y/2-12);
    std::cout << "                 |            ";
    int tempY = y/2-9;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 42; j++)
        {
            gotoXY(x/2-15 + j, tempY);
            std::cout << "-";
        }
        tempY++;
        if (i != 4)
        {
            for(int j=tempY; j<tempY+3; j++)
            {
                gotoXY(x/2-15, j);
                std::cout << "|";
                gotoXY(x/2-15 + 41, j);
                std::cout << "|";
            }
        }
        tempY+=3;
    }
    while(true)
    {
        tempY=y/2-7;
        for(int i=1; i<=4; i++)
        {
            gotoXY(x/2-14,tempY);
            setColor(Color[i]);
            if(i==1)
                std::cout << " 1. Disfigure - Blank";
            else if(i==2)
                std::cout << " 2. Electro-Light - Symbolism";
            else if(i==3)
                std::cout << " 3. Different Heaven & EH!DE - My Heart";
            else if(i==4)
                std::cout << " 4. Turn music off";
            tempY+=4;
        }

        key=_getch();

        if(key==72&&(counter>=2&&counter<=4))
            counter--;
        if(key==80&&(counter>=1&&counter<=3))
            counter++;
        if(key=='\r')
        {
            system("cls");
            break;
        }

        for(int i=1; i<=4; i++)
        {
            if(counter==i)
            {
                Color[i]=RED;
                if(i==4)
                {
                    PlaySound(NULL,NULL,SND_ASYNC | SND_LOOP);
                }
                else
                {
                    std::string tempOpt=std::to_string(i);
                    std::string temp = "music\\soundtrack"+tempOpt+".wav";
                    const char* s=temp.c_str();
                    PlaySound(s,NULL,SND_ASYNC | SND_LOOP);
                }
            }
            else
            {
                Color[i]=AQUA;
            }
        }
    }
    setColor(WHITE);
    ShowCur(true);
}
