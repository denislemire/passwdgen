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

#include <fstream>
#include <stdlib.h>
#include "../config.h"
#include "password.h"

password::password ()
{
  minLength = 0;
  maxLength = 0;
  pwdType = 0;
  whichHand = 0;
  isPronounceable = false;
}

password::password (int a, int b)
{
  pwdType = a;
  whichHand = 0;
  isPronounceable = false;
}

password::password (int a, int b, int c)
{
  minLength = b;
  maxLength = c;

  pwdType = a;
  whichHand = 0;
  isPronounceable = false;
}

void password::type (int a)
{
  pwdType = a;
}

void password::length (int a)
{
  minLength = a;
  maxLength = a;
}

void password::length (int a, int b)
{
  minLength = a;
  maxLength = b;
}

void password::hand (int a)
{
  whichHand = a;
}

void password::pronounceable (bool a)
{
  isPronounceable = a;
}

char *password::generate ()
{
  char randChar;
  short passwdLength;
  short counter[2];
  passwd = new char[passwdLength + 1];

  seedRandom ();

  if (minLength == maxLength) {
    passwdLength = maxLength;
  } else {
    passwdLength = (rand()%(maxLength - minLength + 1) + minLength);
  }

  if (passwdLength < 1) {
    lengthErr ();
  }

  for (counter[0]=0; counter[0]<=passwdLength; counter[0]++) {
    do {
      do {
        randChar = getASCII ();
      } while (checkHand (randChar, counter) != 1);
    } while (checkPronounce (randChar, counter) != 1);
    passwd[counter[0]] = randChar;
  }
  passwd[passwdLength] = '\0';

  return (passwd);
}

ostream &operator << (ostream &os, password &a)
{
  os << a.passwd;
  return os;
}

void password::lengthErr () noexcept(false)
{
  pwdgenerr z ("password length must be a minimum of 1.", 1);
  throw z;
}

void password::seedRandom () noexcept(false)
{
  char randomSeed[4];
  ifstream devRandom;
 
  devRandom.open ("/dev/random");
  if (devRandom.fail()) {
    pwdgenerr z ("unable to open /dev/random.", 2);
    throw z;
  }
 
  devRandom >> randomSeed[0] >> randomSeed[1]
            >> randomSeed[2] >> randomSeed[3];
 
  devRandom.close ();
  srand (randomSeed[0]<<24|randomSeed[1]<<16|randomSeed[2]<<8|randomSeed[3]);
}

char password::getASCII ()
{
  char lowerCase[27] = "abcdefghijklmnopqrstuvwxyz";
  char upperCase[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char numeric[11] = "1234567890";
  char printAble[19] = "!@#$%^&*-_=+,<.>/?";
  short tmpVar;

  switch (pwdType) {
    case 1: // Lowercase alphabetic
    return (lowerCase[rand()%26]);

    case 2: // Uppercase alphabetic
    return (upperCase[rand()%26]);

    case 3: // Mixed case alphabetic
    tmpVar = rand()%52;
    if (tmpVar > 25) {
      return (upperCase[tmpVar - 26]);
    } else {
      return (lowerCase[tmpVar]);
    }

    case 4: // Numeric
    return (numeric[rand()%10]);

    case 5: // Lowercase alphanumeric
    tmpVar = rand()%36;
    if (tmpVar > 9) {
      return (lowerCase[tmpVar - 10]);
    } else {
      return (numeric[tmpVar]);
    }

    case 6: // Uppercase alphanumeric
    tmpVar = rand()%36;
    if (tmpVar > 9) {
      return (upperCase[tmpVar - 10]);
    } else {
      return (numeric[tmpVar]);
    }

    case 7: // Mixed case alphanumeric
    tmpVar = rand()%62;
    if (tmpVar > 9) {
      if (tmpVar > 35) {
        return (upperCase[tmpVar - 36]); 
      } else {
        return (lowerCase[tmpVar - 10]);
      }
    } else {
      return (numeric[tmpVar]);
    }

    case 8: // Misc characters only
    return (printAble[rand()%18]);

    case 9: // Lowercase alphabetic and misc
    tmpVar = rand()%44;
    if (tmpVar > 17) {
      return (lowerCase[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 10: // Uppercase alphabetic and misc
    tmpVar = rand()%44;
    if (tmpVar > 17) {
      return (upperCase[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 11: // Mixed case alphabetic and misc
    tmpVar = rand()%62;
    if (tmpVar > 17) {
      if (tmpVar > 43) {
        return (upperCase[tmpVar - 44]); 
      } else {
        return (lowerCase[tmpVar - 18]);
      }
    } else {
      return (printAble[tmpVar]);
    }

    case 12: // Numeric and printable
    tmpVar = rand()%28;
    if (tmpVar > 17) {
      return (numeric[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 13: // Lowercase alphanumeric and misc
    tmpVar = rand()%54;
    if (tmpVar > 17) {
      if (tmpVar > 27) {
        return (lowerCase[tmpVar - 28]);
      } else {
        return (numeric[tmpVar - 18]);
      }
    } else {
      return (printAble[tmpVar]);
    }

    case 14: // Uppercase alphanumeric and misc
    tmpVar = rand()%54;
    if (tmpVar > 17) {
      if (tmpVar > 27) {
        return (upperCase[tmpVar - 28]);
      } else {
        return (numeric[tmpVar - 18]);
      }
    } else {
      return (printAble[tmpVar]);
    }

    case 15: // Mixed case alphanumeric and misc
    tmpVar = rand()%80;
    if (tmpVar > 17) {
      if (tmpVar > 27) {
        if (tmpVar > 53) {
          return (upperCase[tmpVar - 54]);
        } else {
          return (lowerCase[tmpVar - 28]);
        }
      } else {
        return (numeric[tmpVar - 18]);
      }
    } else {
      return (printAble[tmpVar]);
    }
  }

  return ('\0');
}

int password::checkHand (char randChar, short *counter)
{
  char leftKeys[43] = "!#$%123456@ABCDEFGQRSTVWXZabcdefgqrstvwxz^";
  char rightKeys[41] = "&*+,_./0789<=>?HIJKLMNOPUYhijklmnopuy[]-";

  switch (whichHand) {
    case 0: // both hands
      return (1);
      break;

    case 1: // left hand
      if (pwdType == 0) return (1);
        for (counter[1]=0; counter[1]<=40; counter[1]++) {
          if (randChar == leftKeys[counter[1]]) {
            return (1); 
          }
        }
        return (0);
      break;

    case 2: // right hand
      if (pwdType == 0) return (1);
        for (counter[1]=0; counter[1]<=38; counter[1]++) {
          if (randChar == rightKeys[counter[1]]) {
            return (1); 
          }
        }
        return (0);
      break;

    case 3: // alternating hands
      if (pwdType == 0) return (1);
      
      if (counter[0]%2) { // Even, right char. Odd, left char.
        for (counter[1]=0; counter[1]<=38; counter[1]++) {
          if (randChar == rightKeys[counter[1]]) {
            return (1); 
          }
        }
      } else {
        for (counter[1]=0; counter[1]<=38; counter[1]++) {
          if (randChar == leftKeys[counter[1]]) {
            return (1); 
          }
        }
      }
      break;
  }
  return (0);
}

int password::checkPronounce (char randChar, short *counter) 
{
  char consonants[41] = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
  char vowels[13] = "AEIOUYaeiouy";

  if (isPronounceable) {
      if (pwdType == 0) return (1);
      if (counter[0]%2) { // Even, vowel. Odd, consenant.
        for (counter[1]=0; counter[1]<=10; counter[1]++) {
          if (randChar == vowels[counter[1]]) {
            return (1);
          }
        }
      } else {
        for (counter[1]=0; counter[1]<=38; counter[1]++) {
          if (randChar == consonants[counter[1]]) {
            return (1); 
          }
        }
      }
  } else {
	return (1);
  }

  return (0);

}

password::~password ()
{
  delete[] passwd;
  passwd = nullptr;
}
