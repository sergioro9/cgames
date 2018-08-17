/* ------------------------------------
 *               PLAYER.H
 * ------------------------------------
 * A basic implementation of a top-down
 * style player. Not optimized or feat-
 * ture rich, but easy to understand.
 * ------------------------------------
 * @author Austin Fishbaugh
 * https://github.com/austinfishbaugh/Tutorials/blob/master/Tutorial%208/player.h
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
  public:
    Player(WINDOW * win, int y, int x, char c);

    void mvup();
    void mvdown();
    void mvleft();
    void mvright();
    int  getmv();
    void display();

  private:
    int xLoc, yLoc, xMax, yMax;
    char character;
    WINDOW * curwin;
};

Player::Player(WINDOW * win, int y, int x, char c)
{
  curwin = win;
  yLoc = y;
  xLoc = x;
  getmaxyx(curwin, yMax, xMax);
  keypad(curwin, true);
  character = c;
}

void Player::mvup()
{
  mvwaddch(curwin, yLoc, xLoc, '.');
  yLoc -= 1;
  if(yLoc < 1)
    yLoc = 1;
}

void Player::mvdown()
{
  mvwaddch(curwin, yLoc, xLoc, '.');
  yLoc += 1;
  if(yLoc > yMax-1)
    yLoc = yMax-1;
}

void Player::mvleft()
{
  mvwaddch(curwin, yLoc, xLoc, '.');
  xLoc -= 1;
  if(xLoc < 1)
    xLoc = 1;
}

void Player::mvright()
{
  mvwaddch(curwin, yLoc, xLoc, '.');
  xLoc += 1;
  if(xLoc > xMax-1)
    xLoc = xMax-1;
}

int Player::getmv()
{
  int choice = wgetch(curwin);
  switch(choice)
  {
    case KEY_UP:
      mvup();
      break;
    case KEY_DOWN:
      mvdown();
      break;
    case KEY_LEFT:
      mvleft();
      break;
    case KEY_RIGHT:
      mvright();
      break;
    default:
      break;
  }
  return choice;
}

void Player::display()
{
  mvwaddch(curwin, yLoc, xLoc, character);
}

#endif
