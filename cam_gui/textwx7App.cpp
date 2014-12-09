/***************************************************************
 * Name:      textwx7App.cpp
 * Purpose:   Code for Application Class
 * Author:    liu (cqljj123)
 * Created:   2014-11-18
 * Copyright: liu (www.liujianjun.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "textwx7App.h"
#include "textwx7Main.h"

IMPLEMENT_APP(textwx7App);

bool textwx7App::OnInit()
{
    
    textwx7Dialog* dlg = new textwx7Dialog(0L, _("wxWidgets Application Template"));
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
