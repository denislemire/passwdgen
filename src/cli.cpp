//
//  Copyright (C) 2000 Denis Lemire <denis@lemire.com>
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
#include <strstream>
#include <config.h>

#ifdef HAVE_GETOPT_H
  #include <getopt.h>
#else
  #include <mygetopt.h>
#endif

#include "../class/password.h"

void instructUser ();
void displayHelp ();
void displayVersion ();
int parseCmdLine (int argc, char **argv, password *a, int *quietOput);

void instructUser ()
{
  cout << "passwdgen: You must specificy one or more of the `-Aa1@\' options\n"
       << "Try `passwdgen --help\' for more information.\n";
}

void displayHelp ()
{
  cout << "`passwdgen\' generates random passwords based on your criteria.\n\n"
       << "Usage: passwdgen [OPTIONS]...\n\n"
       << "password options:\n"
       << "  -a, --lowercase\tinclude lowercase alphabetical characters\n"
       << "  -A, --uppercase\tinclude uppercase alphabetical characters\n"
       << "  -1, --numeric\t\tinclude numerical characters\n"
       << "  -@, --misc\t\tinclude misc characters (insane)\n"
       << "  -p, --pronounceable\tgenerate pronounceable passwords\n"
       << "  -l, --lefthand\tinclude only left hand characters\n"
       << "  -r, --righthand\tinclude only right hand characters\n"
       << "      --alternate\talternate between left and right hand characters\n"
       << "      --length=LENGTH\tspecify a fixed password length (4 min, 20 max)\n"
       << "      --min=LENGTH\tminimum password length (4 min, 20 max, 6 default)\n"
       << "      --max=LENGTH\tmaximum password length (4 min, 20 max, 8 default)\n\n"
       << "other options:\n"
       << "  -q, --quiet\t\toutput password only, no verbosity\n"
       << "      --version\t\tdisplay version information and exit\n"
       << "      --help\t\tdisplay this help and exit\n\n"
       << "Report bugs to <denis@lemire.com>.\n";
}

void displayVersion ()
{
  cout << PACKAGE << ' ' << VERSION << '\n';
}

int parseCmdLine (int argc, char **argv, password *a, int *quietOutput)
{
  int option, option_index;
  int passwdType = 0, minLength = 6, maxLength = 8;
  strstream s;

  static struct option const long_options[] = {
    {"lowercase", no_argument, 0, 'a'},
    {"uppercase", no_argument, 0, 'A'},
    {"numeric", no_argument, 0, '1'},
    {"misc", no_argument, 0, '@'},
    {"lefthand", no_argument, 0, 'l'},
    {"righthand", no_argument, 0, 'r'},
    {"alternate", no_argument, 0, 'b'},
    {"pronounceable", no_argument, 0, 'p'},
    {"length", required_argument, 0, 'f'},
    {"min", required_argument, 0, 'm'},
    {"max", required_argument, 0, 'M'},
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"quiet", no_argument, 0, 'q'},
    {NULL, 0, NULL, 0}
  };

  if (argc == 1) {
    instructUser ();
    return (-1);
  }

  do {
    option_index = 0;
    option = getopt_long (argc, argv, "aA1@frbpq", long_options, &option_index);

    switch (option) {
      case 'a': passwdType = passwdType + 1; break;
      case 'A': passwdType = passwdType + 2; break;
      case '1': passwdType = passwdType + 4; break;
      case '@': passwdType = passwdType + 8; break;
      case 'f': s << optarg; s >> minLength; maxLength = minLength ; break;
      case 'm': s << optarg; s >> minLength; break;
      case 'M': s << optarg; s >> maxLength; break;
      case 'l': a->hand (LEFT); break;
      case 'r': a->hand (RIGHT); break;
      case 'b': a->hand (ALTERNATE); break;
      case 'p': a->pronounceable (true); break;
      case 'q': *quietOutput = 1; break;
      case 'v': displayVersion (); exit(0); break;
      case 'h': displayHelp (); exit(0); break;

      case '?':
        cout << "Try `passwdgen --help\' for more information.\n";
        exit (3);
        break;
    }
  } while (option != -1);

  if (passwdType == 0) {
    instructUser ();
    return (-1);
  } else {
    a->type (passwdType);
    a->length (minLength, maxLength);
    return (0);
  }
}
