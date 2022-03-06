/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#include "ExKeyPressCatcher.h"
#include "OdaCommon.h"
#include "IfcExamplesCommon.h"
#ifdef ODA_UNIXOS
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#endif //ODA_UNIXOS

#ifdef ODA_WINDOWS
bool windowsEscapeKeyCatcher()
{
  if (GetAsyncKeyState(VK_ESCAPE)) 
  {
    odPrintConsoleString(L"\nCompose process interrupted\n");
    system("Pause");
    return true;
  }
  return false;
}
#endif // ODA_WINDOWS

#ifdef ODA_UNIXOS

struct termios orig_termios;

void reset_terminal_mode()
{
  tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
  struct termios new_termios;

  tcgetattr(0, &orig_termios);
  memcpy(&new_termios, &orig_termios, sizeof(new_termios));

  atexit(reset_terminal_mode);
  cfmakeraw(&new_termios);
  tcsetattr(0, TCSANOW, &new_termios);
  }

int getch()
{
  int r;
  unsigned char c;
  if ((r = read(0, &c, sizeof(c))) < 0) {
    return r;
  }
  else {
    return c;
  }
}

bool unixPressKeyCatcher()
{
  struct timeval tv = { 0L, 0L };
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

#endif // ODA_UNIXOS

KeyPressCatcher::KeyPressCatcher()
{
#ifdef ODA_WINDOWS
  m_interruptCallback = &windowsEscapeKeyCatcher;
#endif // ODA_WINDOWS
#ifdef ODA_UNIXOS
  set_conio_terminal_mode();
  m_interruptCallback = &unixPressKeyCatcher;
#endif // ODA_UNIXOS
}
KeyPressCatcher::~KeyPressCatcher()
{
#ifdef ODA_UNIXOS
  (void)getch();
#endif // ODA_UNIXOS
}

InterruptFunction KeyPressCatcher::getInterruptCallback()
{
  return m_interruptCallback;
}
