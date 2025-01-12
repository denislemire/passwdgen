//
//  Copyright (C) 2025 Denis Lemire <denis@lemire.name>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//                                                                              


#include <iostream>
using namespace std;

#include "pwdgenerr.h"

#define LOWERCASE_ALPHA 1
#define UPPERCASE_ALPHA 2
#define NUMERIC 4
#define MISC 8

#define BOTH 0
#define LEFT 1
#define RIGHT 2
#define ALTERNATE 3

class password
{
  public:
    password ();
    password (int type, int length);
    password (int type, int min, int max);
    ~password ();
    void type (int type);
    void length (int length);
    void length (int min, int max);
    void hand (int hand); 
    void pronounceable (bool pronounce);
    char *generate ();
    friend ostream &operator << (ostream &os, password &a);

  protected:
    void lengthErr () noexcept(false);
    void seedRandom () noexcept(false); 
    char getASCII ();
    int checkHand (char randChar, short *counter);
    int checkPronounce (char randChar, short *counter);
    int minLength, maxLength, pwdType, whichHand;
    bool isPronounceable;
    char *passwd = nullptr;
};
