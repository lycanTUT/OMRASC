//---------------------------------------------------------------------------
//
// Name:        CheckerApp.cpp
// Author:      Miguel Asido
// Created:     16/12/2018 5:32:16 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "CheckerApp.h"
#include "CheckerFrm.h"

IMPLEMENT_APP(CheckerFrmApp)

bool CheckerFrmApp::OnInit()
{
    CheckerFrm* frame = new CheckerFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int CheckerFrmApp::OnExit()
{
	return 0;
}
