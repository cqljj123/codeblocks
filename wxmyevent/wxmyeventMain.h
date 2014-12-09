/***************************************************************
 * Name:      wxmyeventMain.h
 * Purpose:   Defines Application Frame
 * Author:    liu (cqljj123)
 * Created:   2014-12-02
 * Copyright: liu (www.liujianjun.com)
 * License:
 **************************************************************/

#ifndef WXMYEVENTMAIN_H
#define WXMYEVENTMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxmyeventApp.h"

class wxmyeventFrame: public wxFrame
{
    public:
        wxmyeventFrame(wxFrame *frame, const wxString& title);
        ~wxmyeventFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXMYEVENTMAIN_H
