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
#include "cli.h"

int main (int argc, char **argv)
{
  password a;
  int quietOutput = 0;

  try
  {
    if (parseCmdLine (argc, argv, &a, &quietOutput) != 0) return -1;
    a.generate ();
  }
    
  catch (pwdgenerr err)
  {
    cerr << "Error: " << *err.message () << '\n';
    return err.value ();
  }

  switch (quietOutput) {
    case 0: cout << "Your password is: " << a << '\n'; break;
    case 1: cout << a << '\n'; break;
  }

  return 0;
}
