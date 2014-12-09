#ifndef __DETECTED_H__
#define __DETECTED_H__
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/frame.h>

#include  "database.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DETECTEDFRAM
///////////////////////////////////////////////////////////////////////////////
class DETECTEDFRAM : public wxDialog 
{
private:

protected:
	wxStaticText* m_staticText1;
	wxSlider* m_slider1;
	wxChoice* m_choice1;
	wxButton* m_button1;
	wxGrid* m_grid1;
	wxTimer m_timer1;
	wxStaticText * slidervalueshow;
	int ifstop; /*if start detected */
	/*start or stop detected*/
	void startbotn(wxCommandEvent& vt); 
	/*timer event*/
	void onTimer(wxTimerEvent& event);
	/*slider event*/
	void onSlider(wxCommandEvent & event);
public:
	/*create function*/
	DETECTEDFRAM( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	/*destroy function*/
	~DETECTEDFRAM();
	DECLARE_EVENT_TABLE()
};



#endif