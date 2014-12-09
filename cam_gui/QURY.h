#ifndef __QURY_H__
#define __QURY_H__
#include "wx/wxprec.h"
#include <wx/dateevt.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

#include "wx/grid.h"
#include "wx/headerctrl.h"
#include "wx/generic/gridctrl.h"
#include "wx/generic/grideditors.h"
#include "database.h"
class QURYFRAM : public wxDialog
{
public:
	QURYFRAM(wxWindow *parent, const wxDateTime& dt, int dtpStyle);

	//wxDateTime GetDate() const { return m_datePicker->GetValue(); }
	~QURYFRAM();
private:
	void OnDateChange(wxDateEvent& event);
	void OnTimeChange(wxDateEvent& event);
	void OnQRUY(wxCommandEvent& event);
	void OnCOPY(wxCommandEvent& event);
	void _wxFB_ONleftclick( wxGridEvent& event ){ ONleftclick( event ); }
	virtual void ONleftclick( wxGridEvent& event )
	{
		//wxMessageBox(_("hello"));
		wxMenu menu;

		menu.Append(wxID_ANY, _("&About"));
		menu.Append(wxID_ANY, _("To be &deleted"));
		menu.AppendCheckItem(wxID_ANY, _("To be &checked"));
		menu.Append(wxID_ANY, _("To be &greyed"),
			_("This menu item should be initially greyed out"));
		menu.AppendSeparator();
		menu.Append(wxID_ANY, _("E&xit"));
		PopupMenu(&menu);
	}
	wxDatePickerCtrlBase *m_datePicker;
	wxDatePickerCtrlBase *m_datePicker1;
	wxStaticText *m_dateText;
	wxSizer *sizerTop;

	wxTimePickerCtrlBase* m_timePicker;
	wxTimePickerCtrlBase* m_timePicker1;
	wxStaticText* m_timeText;
	wxGrid	*m_grid1;
	DECLARE_EVENT_TABLE()
};
#endif
