///-----------------------------------------------------------------
///
/// @file      CheckerFrm.h
/// @author    Miguel Asido
/// Created:   16/12/2018 5:32:16 PM
/// @section   DESCRIPTION
///            CheckerFrm class declaration
///
///------------------------------------------------------------------

#ifndef __CHECKERFRM_H__
#define __CHECKERFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/slider.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
////Header Include End

////Dialog Style Start
#undef CheckerFrm_STYLE
#define CheckerFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class CheckerFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		CheckerFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Checker"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = CheckerFrm_STYLE);
		virtual ~CheckerFrm();
		void UploadAKClick(wxCommandEvent& event);
		void UploadASClick(wxCommandEvent& event);
		void ButtonScoreClick(wxCommandEvent& event);
		void edit_scoreUpdated(wxCommandEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxButton3Click(wxCommandEvent& event);
		void WxButton4Click(wxCommandEvent& event);
		void ButtonGrayscaleClick(wxCommandEvent& event);
		void ButtonBinarizeClick(wxCommandEvent& event);
		void ButtonGaussianClick(wxCommandEvent& event);
		void WxSlider1Scroll(wxScrollEvent& event);
		void ButtonCombineClick(wxCommandEvent& event);
		void GetAKClick(wxCommandEvent& event);
		void IDnumUpdated(wxCommandEvent& event);
		void WxButton1Click0(wxCommandEvent& event);
		void Save_ButtonClick(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *Save_Button;
		wxButton *GetAK;
		wxStaticText *WxStaticText5;
		wxSlider *WxSlider1;
		wxFileDialog *dlgAK_browse;
		wxStaticText *WxStaticText4;
		wxStaticText *WxStaticText3;
		wxTextCtrl *score;
		wxTextCtrl *IDnum;
		wxButton *ButtonScore;
		wxButton *UploadAS;
		wxButton *UploadAK;
		wxStaticBitmap *AS_Bitmap;
		wxStaticBitmap *AK_Bitmap;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_SAVE_BUTTON = 1018,
			ID_GETAK = 1017,
			ID_WXSTATICTEXT5 = 1015,
			ID_WXSLIDER1 = 1014,
			ID_WXSTATICTEXT4 = 1013,
			ID_WXSTATICTEXT3 = 1012,
			ID_SCORE = 1009,
			ID_IDNUM = 1008,
			ID_BUTTONSCORE = 1007,
			ID_UPLOADA = 1006,
			ID_UPLOADAK = 1005,
			ID_AS_BITMAP = 1004,
			ID_AK_BITMAP = 1003,
			ID_WXSTATICTEXT2 = 1002,
			ID_WXSTATICTEXT1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		wxImage AK_pic;
        wxImage AS_pic;
        wxImage AS_ID_pic;
        wxImage AK_combined;
        wxImage AS_combined;
        wxImage ASK_combined;
        
        bool AK_image;
        bool AS_image;

};


void greyscale(wxImage &img);
void binarization(wxImage &img);
void gaussian(wxImage &img);
void resizing (wxImage &img);

wxImage combineAK(wxImage AK, wxImage AS);
wxImage combineAS(wxImage AK, wxImage AS);
wxImage combineASK(wxImage AK, wxImage AS);
int GetScore(wxImage img, wxImage repeat);
int GetIDProcess(wxImage img, int MarkerStartCol);

int repeating(wxImage img);
int countMarkers(wxImage img);

#endif
