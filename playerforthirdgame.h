#ifndef _PLAYERFORTHIRDGAME_H_
#define _PLAYERFORTHIRDGAME_H_

class Player
{
    public:
        Player(WINDOW * thirdgwin,int y,int x,char c);
        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        void display();
        int gety();
        int getx();
    
    private:
        int xloc, yloc, xMax,yMax;
        char character;
        WINDOW * curwin;
};

Player::Player(WINDOW * thirdgwin,int y,int x, char c)
{
    curwin=thirdgwin;
    yloc=y;
    xloc=x;
    getmaxyx(curwin,yMax,xMax);
    keypad(curwin,true);
    character=c;
}

int Player::gety()
{
    return yloc;
}

int Player::getx()
{
    return xloc;
}

void Player::mvup()
{
    mvwaddch(curwin,yloc,xloc,' ');
    yloc--;
    if(yloc<1)
        yloc=1;
}

void Player::mvdown()
{
    mvwaddch(curwin,yloc,xloc,' ');
    yloc++;
    if (yloc>yMax-2)
        yloc=yMax-2;
}

void Player::mvleft()
{
    mvwaddch(curwin,yloc,xloc,' ');
    xloc--;
    if(xloc<1)
        xloc=1;
}

void Player::mvright()
{
    mvwaddch(curwin,yloc,xloc,' ');
    xloc++;
    if(xloc>xMax-2)
        xloc=xMax-2;
}

void Player::display()
{
    mvwaddch(curwin,yloc,xloc,character);
}

#endif