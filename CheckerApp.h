//---------------------------------------------------------------------------
//
// Name:        CheckerApp.h
// Author:      Miguel Asido
// Created:     16/12/2018 5:32:16 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __CHECKERFRMApp_h__
#define __CHECKERFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class CheckerFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
