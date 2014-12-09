/***************************************************************
 * Name:      textwx7Main.h
 * Purpose:   Defines Application Frame
 * Author:    liu (cqljj123)
 * Created:   2014-11-18
 * Copyright: liu (www.liujianjun.com)
 * License:
 **************************************************************/

#ifndef TEXTWX7MAIN_H
#define TEXTWX7MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "textwx7App.h"


#include <wx/button.h>
#include <wx/statline.h>
class textwx7Dialog: public wxDialog
{
    public:
        textwx7Dialog(wxDialog *dlg, const wxString& title);
        ~textwx7Dialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // TEXTWX7MAIN_H
