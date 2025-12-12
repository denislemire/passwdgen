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
#include <random>
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
  minLength = b;
  maxLength = b;
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

  seedRandom ();

  if (minLength > maxLength) {
    lengthErr ("minimum length must not exceed maximum length.");
  }

  if (minLength == maxLength) {
    passwdLength = maxLength;
  } else {
    passwdLength = secureRandom(maxLength - minLength + 1) + minLength;
  }

  if (passwdLength < 1) {
    lengthErr ("password length must be a minimum of 1.");
  }

  passwd = new char[passwdLength + 1];

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

void password::lengthErr (const char *str) noexcept(false)
{
  pwdgenerr z (str, 1);
  throw z;
}

void password::seedRandom () noexcept(false)
{
  // This function is kept for compatibility but no longer needed
  // as we now use secureRandom() which uses std::random_device
}

// Secure random number generator using std::random_device (CSPRNG)
// Cross-platform: uses OS CSPRNG (/dev/urandom on Unix, CryptGenRandom on Windows, etc.)
static int secureRandom(int max) noexcept(false)
{
  if (max <= 0) {
    pwdgenerr z ("invalid random range.", 2);
    throw z;
  }
  
  static std::random_device rd;
  std::uniform_int_distribution<int> dist(0, max - 1);
  return dist(rd);
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
    return (lowerCase[secureRandom(26)]);

    case 2: // Uppercase alphabetic
    return (upperCase[secureRandom(26)]);

    case 3: // Mixed case alphabetic
    tmpVar = secureRandom(52);
    if (tmpVar > 25) {
      return (upperCase[tmpVar - 26]);
    } else {
      return (lowerCase[tmpVar]);
    }

    case 4: // Numeric
    return (numeric[secureRandom(10)]);

    case 5: // Lowercase alphanumeric
    tmpVar = secureRandom(36);
    if (tmpVar > 9) {
      return (lowerCase[tmpVar - 10]);
    } else {
      return (numeric[tmpVar]);
    }

    case 6: // Uppercase alphanumeric
    tmpVar = secureRandom(36);
    if (tmpVar > 9) {
      return (upperCase[tmpVar - 10]);
    } else {
      return (numeric[tmpVar]);
    }

    case 7: // Mixed case alphanumeric
    tmpVar = secureRandom(62);
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
    return (printAble[secureRandom(18)]);

    case 9: // Lowercase alphabetic and misc
    tmpVar = secureRandom(44);
    if (tmpVar > 17) {
      return (lowerCase[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 10: // Uppercase alphabetic and misc
    tmpVar = secureRandom(44);
    if (tmpVar > 17) {
      return (upperCase[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 11: // Mixed case alphabetic and misc
    tmpVar = secureRandom(62);
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
    tmpVar = secureRandom(28);
    if (tmpVar > 17) {
      return (numeric[tmpVar - 18]);
    } else {
      return (printAble[tmpVar]);
    }

    case 13: // Lowercase alphanumeric and misc
    tmpVar = secureRandom(54);
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
    tmpVar = secureRandom(54);
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
    tmpVar = secureRandom(80);
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
