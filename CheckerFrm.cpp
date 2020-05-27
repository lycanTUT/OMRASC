///-----------------------------------------------------------------
///
/// @file      CheckerFrm.cpp
/// @author    Miguel Asido
/// Created:   16/12/2018 5:32:16 PM
/// @section   DESCRIPTION
///            CheckerFrm class implementation
///
///------------------------------------------------------------------

#include "CheckerFrm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std; 

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// CheckerFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(CheckerFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(CheckerFrm::OnClose)
	EVT_BUTTON(ID_SAVE_BUTTON,CheckerFrm::Save_ButtonClick)
	EVT_BUTTON(ID_GETAK,CheckerFrm::GetAKClick)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER1,CheckerFrm::WxSlider1Scroll)
	
	EVT_TEXT(ID_IDNUM,CheckerFrm::IDnumUpdated)
	EVT_BUTTON(ID_BUTTONSCORE,CheckerFrm::ButtonScoreClick)
	EVT_BUTTON(ID_UPLOADA,CheckerFrm::UploadASClick)
	EVT_BUTTON(ID_UPLOADAK,CheckerFrm::UploadAKClick)
END_EVENT_TABLE()
////Event Table End

CheckerFrm::CheckerFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
    AK_image=false;
    AS_image=false;

  CreateGUIControls();
}

CheckerFrm::~CheckerFrm()
{
}

void CheckerFrm::CreateGUIControls()
{
  //Do not add custom code between
  //GUI Items Creation Start and GUI Items Creation End
  //wxDev-C++ designer will remove them.
  //Add the custom code before or after the blocks
  ////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	Save_Button = new wxButton(this, ID_SAVE_BUTTON, _("Save"), wxPoint(380, 225), wxSize(75, 25), 0, wxDefaultValidator, _("Save_Button"));

	GetAK = new wxButton(this, ID_GETAK, _("Get Answer Key"), wxPoint(211, 282), wxSize(100, 25), 0, wxDefaultValidator, _("GetAK"));
	GetAK->SetFont(wxFont(7, wxSWISS, wxNORMAL, wxNORMAL, false));

	WxStaticText5 = new wxStaticText(this, ID_WXSTATICTEXT5, _("Threshold"), wxPoint(380, 284), wxDefaultSize, 0, _("WxStaticText5"));

	WxSlider1 = new wxSlider(this, ID_WXSLIDER1, 0, 0, 10, wxPoint(340, 308), wxSize(150, 30), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, _("WxSlider1"));
	WxSlider1->SetRange(0,10);
	WxSlider1->SetValue(0);

	dlgAK_browse =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, _("SCORE"), wxPoint(400, 149), wxDefaultSize, 0, _("WxStaticText4"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("ID NUMBER"), wxPoint(385, 80), wxDefaultSize, 0, _("WxStaticText3"));

	score = new wxTextCtrl(this, ID_SCORE, _(""), wxPoint(355, 170), wxSize(130, 30), 0, wxDefaultValidator, _("score"));

	IDnum = new wxTextCtrl(this, ID_IDNUM, _(""), wxPoint(355, 105), wxSize(130, 30), 0, wxDefaultValidator, _("IDnum"));

	ButtonScore = new wxButton(this, ID_BUTTONSCORE, _("Get Score"), wxPoint(690, 280), wxSize(100, 25), 0, wxDefaultValidator, _("ButtonScore"));
	ButtonScore->SetFont(wxFont(7, wxSWISS, wxNORMAL, wxNORMAL, false, _("Arial Narrow")));

	UploadAS = new wxButton(this, ID_UPLOADA, _("Upload Answer Sheet"), wxPoint(530, 280), wxSize(100, 25), 0, wxDefaultValidator, _("UploadAS"));
	UploadAS->SetFont(wxFont(7, wxSWISS, wxNORMAL, wxNORMAL, false, _("Arial")));

	UploadAK = new wxButton(this, ID_UPLOADAK, _("Upload Answer Key"), wxPoint(50, 280), wxSize(100, 25), 0, wxDefaultValidator, _("UploadAK"));
	UploadAK->SetFont(wxFont(7, wxSWISS, wxNORMAL, wxNORMAL, false, _("Arial")));

	AS_Bitmap = new wxStaticBitmap(this, ID_AS_BITMAP, wxNullBitmap, wxPoint(500, 30), wxSize(320, 240) );

	AK_Bitmap = new wxStaticBitmap(this, ID_AK_BITMAP, wxNullBitmap, wxPoint(20, 30), wxSize(320, 240) );

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Answer Sheet:"), wxPoint(505, 10), wxDefaultSize, 0, _("WxStaticText2"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Answer Key:"), wxPoint(25, 10), wxDefaultSize, 0, _("WxStaticText1"));

	SetTitle(_("Answer Sheet Checker"));
	SetIcon(wxNullIcon);
	SetSize(6,5,857,385);
	Center();
	
  ////GUI Items Creation End
}
    wxImage AS_frame;
    wxImage AK_frame;
    char choices[] = {'A','B','C','D','E'};
    char AnswerKey[] = {'A','B','C','D','E','A','B','C','D','E'};
    char Answers[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void CheckerFrm::OnClose(wxCloseEvent& event)
{
  Destroy();
}

/*
 * IDnumUpdated
 */
void CheckerFrm::IDnumUpdated(wxCommandEvent& event)
{
	// insert your code here
}

void Gray(wxImage &img){
    int width = img.GetWidth();
    int height = img.GetHeight();
    
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            int r = img.GetRed(x,y);
            int g = img.GetGreen(x,y);
            int b = img.GetBlue(x,y);
            int gray = (r*306 + g*601 + b*117)/1024;
            img.SetRGB(x,y,gray,gray,gray); 
        }
    }  
}

void Thresh(wxImage &img, int thresh){
    int width = img.GetWidth();
    int height = img.GetHeight();

    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            
            if (img.GetRed(x,y) < thresh){
                img.SetRGB(x,y,0,0,0);    
            }
            else{
                img.SetRGB(x,y,255,255,255); 
            }
        }
    } 
} 

void gaussian(wxImage &img){
    int width = img.GetWidth(); 
    int height = img.GetHeight();  
    wxImage temp;
    temp.wxImage::Create(width, height);
    int kernel[3][3] ={ {159,252,159},
                        {252,400,252},
                        {159,252,159},};
    for (int y = 1; y < height-1; y++) {
        for (int x = 1; x < width-1; x++) {
            int gauss = 0;
            for(int ver = -1; ver <= 1; ver++){
                for (int hor = -1; hor <= 1; hor++){
                    gauss += (img.GetRed(x+hor,y+ver)*kernel[ver+1][hor+1])/2048;      
                }   
            }            
           temp.SetRGB(x, y, gauss, gauss, gauss);      
        }
    }
    img = temp;
}

void resizing (wxImage &img){
    int h = img.GetHeight();
    int w = img.GetWidth();
    if (h != 240 && w != 320) 
    {
        img = img.Scale(320, 240);
    }
}

void DrawRect (wxImage &img, int startX, int endX, int startY, int endY, int R, int G, int B){
    for (int x = startX; x <= endX; x++){
        img.SetRGB(x, startY, R, G, B);    
        img.SetRGB(x, endY, R, G, B);
    }
    for (int y = startY; y <= endY; y++){
        img.SetRGB(startX, y, R, G, B);    
        img.SetRGB(endX, y, R, G, B);
    }
}

int item (wxImage &img, int startX, int endX, int startY, int endY){
    int pixVal = 0;
    for (int x = startX; x <= endX; x++){
        for (int y = startY; y <= endY; y++){
            pixVal += img.GetRed(x,y)/255;
        }
    }
    return pixVal;    
}
void GetChoice(wxImage img, char *sheet){
    for (int items = 0; items <= 9; items++) {
        int numShaded = 0;
		for (int choice = 0; choice <= 4; choice++) {
			int answer = item(img, 190 + 3 + (20*choice), 200 - 3 + (20*choice), 30 + 3 + (20*items), 40 - 3 + (20*items));
			if (answer < 20) {
                sheet[items] = choices[choice];
                numShaded++;
		    }
	   }
	   if (numShaded != 1){
            sheet[items] = ' ';    
        }
    }
}

int GetScore(wxImage img){
    int score = 0;
    for (int quest = 0; quest < 10; quest++){
        if (Answers[quest] == AnswerKey[quest]){
            score++;
        }
    } 
    return score;
}

int GetIDnum(wxImage img){
    bool IDshaded;
    int IDnum = 0;
    int IDnumShaded;
    for (int IDdigit = 0; IDdigit <= 5; IDdigit++) {
		IDnumShaded = 0;
		for (int IDval = 0; IDval <= 9; IDval++) {				
		int digit = item(img, 30 + 3 + (20*IDdigit), 40 - 3 + (20*IDdigit), 30 + 3 + (20*IDval), 40 - 3 + (20*IDval));
			if (digit < 20) {
				IDnum += IDval * pow(10, 5 - IDdigit);
				IDnumShaded++;
			}
		}
		if (IDnumShaded == 1) {
			IDshaded = true;
		}
		else {
			IDshaded = false;
		}
    }
    if (IDshaded){
        return IDnum;
    }
    else {
        return 0;
    }
}

void MorphDilate (wxImage &img){
    int width = img.GetWidth();
    int height = img.GetHeight();
    wxImage temp = img;    
    for (int x = 1; x < width - 1; x++){
        for (int y = 1; y < height - 1; y++){
            int count = 0;
            
            for (int hor = -1; hor <= 1; hor++){
                for (int ver = -1; ver <= 1; ver++){
                    if (img.GetRed(x + hor, y + ver) == 255){
                        count++;
                    }
                }   
            }
            
            if (count > 7){
                temp.SetRGB(x,y,255,255,255);   
            }
            else{
                temp.SetRGB(x,y,0,0,0);
            }
        }   
    }
    img = temp;
}

void MorphErode (wxImage &img){
    int width = img.GetWidth();
    int height = img.GetHeight();
    wxImage temp = img;    
    for (int x = 1; x < width - 1; x++){
        for (int y = 1; y < height - 1; y++){
            int count = 0;
            
            for (int hor = -1; hor <= 1; hor++){
                for (int ver = -1; ver <= 1; ver++){
                    if (img.GetRed(x + hor, y + ver) == 0){
                        count++;
                    }
                }   
            }
            
            if (count > 7){
                temp.SetRGB(x,y,0,0,0);   
            }
            else{
                temp.SetRGB(x,y,255,255,255);
            }
        }   
    }
    
}

void recordGrade(int newID, int newscore){
    ifstream oldFile;
    ofstream newFile;
    char c;
    
    oldFile.open("Grades.csv");
	newFile.open("Grades_temp.csv");

	while (oldFile.get(c))
	{
		newFile << c;
	}

	newFile << endl << newID << "," << newscore;

	oldFile.close();
	newFile.close();
	remove("Grades.csv");
	rename("Grades_temp.csv", "Grades.csv");
}

/*
 * UploadAKClick
 */
void CheckerFrm::UploadAKClick(wxCommandEvent& event)
{
  dlgAK_browse -> ShowModal();
    if (dlgAK_browse -> GetPath().IsEmpty())
    {
        return;
    }
    
    AK_image = AK_pic.LoadFile(dlgAK_browse->GetPath(), wxBITMAP_TYPE_ANY);
    resizing(AK_pic);
    Gray(AK_pic);
    gaussian(AK_pic);
    AK_Bitmap -> SetBitmap(AK_pic);
}

/*
 * UploadASClick
 */
void CheckerFrm::UploadASClick(wxCommandEvent& event)
{
	dlgAK_browse -> ShowModal();
    if (dlgAK_browse -> GetPath().IsEmpty())
    {
        return;
    }  
    
    AS_image = AS_pic.LoadFile(dlgAK_browse->GetPath(), wxBITMAP_TYPE_ANY);

    resizing(AS_pic);
    Gray(AS_pic);
    gaussian(AS_pic);
    AS_Bitmap -> SetBitmap(AS_pic);
}

/*
 * WxSlider1Scroll
 */
void CheckerFrm::WxSlider1Scroll(wxScrollEvent& event)
{
    WxSlider1->SetRange(0,255);
    int threshold = WxSlider1->GetValue();
    if (AS_image){
        AS_frame = AS_pic;
        Thresh(AS_frame, threshold);
        DrawRect(AS_frame, 0, 319, 0, 239, 255, 255, 255);
        MorphErode(AS_frame);
        MorphDilate(AS_frame);
        MorphDilate(AS_frame);
        MorphErode(AS_frame);
        AS_Bitmap -> SetBitmap(AS_frame);
    }
    if (AK_image){
        AK_frame = AK_pic;
        Thresh(AK_frame, threshold);
        DrawRect(AK_frame, 0, 319, 0, 239, 255, 255, 255);
        MorphErode(AK_frame);
        MorphDilate(AK_frame);
        MorphDilate(AK_frame);
        MorphErode(AK_frame);
        AK_Bitmap -> SetBitmap(AK_frame);
    }
}

/*
 * GetAKClick
 */
void CheckerFrm::GetAKClick(wxCommandEvent& event)
{
    if (AS_image && AK_image){
	   GetChoice(AK_frame, AnswerKey);
	   AK_Bitmap -> SetBitmap(AK_frame);
    }   
}
int newID;
int newScore;
/*
 * ButtonScoreClick
 */
void CheckerFrm::ButtonScoreClick(wxCommandEvent& event)
{
    if (AS_image && AK_image){
        newID = GetIDnum(AS_frame);
        AS_Bitmap -> SetBitmap(AS_frame);
        IDnum -> SetValue(wxString::Format(wxT("%d"), newID));
    
        GetChoice(AS_frame, Answers);
        newScore = GetScore(AS_frame);
	    score -> SetValue(wxString::Format(wxT("%d"), newScore));
    }
}

/*
 * Save_ButtonClick
 */
void CheckerFrm::Save_ButtonClick(wxCommandEvent& event)
{
    if (AS_image && AK_image){
	   recordGrade(newID, newScore);
    } 

}
