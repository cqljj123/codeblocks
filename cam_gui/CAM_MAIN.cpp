#include "CAM_MAIN.h"
#include "wx/image.h"
#include "wx/imagpng.h"
#include "wx/wxhtml.h"
#include "wx/statline.h"

/*
	define id
*/
enum
{
	MYWXID_DETECT = 6000,
	MYWXID_QURY
};

// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(CAM_MAINRAM, wxFrame)
   //EVT_MENU(wxID_ABOUT, CAM_MAINRAM::OnAbout)
   EVT_MENU(wxID_EXIT,  CAM_MAINRAM::OnQuit)
   EVT_BUTTON(MYWXID_DETECT,  CAM_MAINRAM::DETECTEDWIND)
   EVT_BUTTON(MYWXID_QURY,  CAM_MAINRAM::QURYDATA)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------
// frame constructor
CAM_MAINRAM::CAM_MAINRAM(const wxString& title)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    //SetIcon(wxICON(sample));

    // create a menu bar
    wxMenu *menuFile = new wxMenu;
	wxMenu *menuHelp = new wxMenu;
	wxPanel *m_panel = new wxPanel(this,-1);
	menuHelp->Append(wxID_HELP,_("&帮助"));
	menuHelp->Append(wxID_ABOUT,_("&关于"));
    menuFile->Append(wxID_EXIT,_("&退出"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&文件"));
	menuBar->Append(menuHelp, _("&帮助"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
	wxBoxSizer *topsizer, *buSizer;
    wxHtmlWindow *html;
	topsizer = new wxBoxSizer(wxVERTICAL);
	buSizer = new wxBoxSizer(wxHORIZONTAL);

    html = new wxHtmlWindow(m_panel, wxID_ANY, wxDefaultPosition, /*wxDefaultSize*/wxSize(400, 200), wxHW_SCROLLBAR_NEVER,"tis");
    html -> SetBorders(0);
    html -> LoadPage(_("data/about.htm"));
    html -> SetSize(html -> GetInternalRepresentation() -> GetWidth(),
                    html -> GetInternalRepresentation() -> GetHeight());
    topsizer -> Add(html, 1, wxALL, 10);
    topsizer -> Add(new wxStaticLine(m_panel, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	topsizer -> Add(buSizer);
    wxButton *bu1 = new wxButton(m_panel, MYWXID_DETECT, _("测量"));
	wxButton *bu2 = new wxButton(m_panel, MYWXID_QURY, _("查询"));
    bu1 -> SetDefault();
	bu2->SetDefault();
    buSizer -> Add(bu1, 0, wxALL | wxALIGN_LEFT, 15);
	buSizer -> Add(bu2, 0, wxALL | wxALIGN_RIGHT, 15);
    m_panel->SetSizer(topsizer);
    topsizer -> Fit(this);

	createdatabase();
	dfr = new DETECTEDFRAM(this,wxID_ANY,_("测量"));
	dlg = new QURYFRAM(this, wxDateTime::Today(), wxDP_DEFAULT);
}

// event handlers
void CAM_MAINRAM::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void CAM_MAINRAM::DETECTEDWIND(wxCommandEvent& WXUNUSED(event))
{
	dfr->Hide();
	dfr->Show(true);
}
void CAM_MAINRAM::QURYDATA(wxCommandEvent& WXUNUSED(event))
{

	dlg->Show(true);

}
