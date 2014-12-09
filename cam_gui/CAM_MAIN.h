#ifndef __CAM_MAIN_H__
#define __CAM_MAIN_H__
#include "wx/wxprec.h"
#include "QURY.h"
#include "DETECTED.h"
//#include "panelfram.h"
// Define a new frame type: this is going to be our main frame
class CAM_MAINRAM : public wxFrame
{
public:
    // ctor(s)
    CAM_MAINRAM(const wxString& title);
	//wxPanel * m_panel;
    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void DETECTEDWIND(wxCommandEvent& event);
	void QURYDATA(wxCommandEvent& event);
	QURYFRAM *dlg;
	DETECTEDFRAM *dfr;
	//PANELFRAM *  MYPANELFRAM;
	~CAM_MAINRAM()
	{
		Close();
	}

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------


#endif