/***************************************************************
 * Name:      wxmyeventApp.cpp
 * Purpose:   Code for Application Class
 * Author:    liu (cqljj123)
 * Created:   2014-12-02
 * Copyright: liu (www.liujianjun.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxmyeventApp.h"
#include "wxmyeventMain.h"

IMPLEMENT_APP(wxmyeventApp);

bool wxmyeventApp::OnInit()
{
    wxmyeventFrame* frame = new wxmyeventFrame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
