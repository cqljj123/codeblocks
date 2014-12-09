#include "QURY.h"
#include <wx/statline.h>
#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"
#include "wx/aboutdlg.h"
#include "wx/clipbrd.h"
#include <vector>
#include <map>


enum{
	QURYIDMY=6005,
	QURYIDCOY
};
void quryfromdatabase(const char*sqlvalue,std::vector<std::map<wxString,wxString>> &quryout)
{
	quryout.clear();
	char  buf[200];
	getcwd(buf,199);
	sqlitedbdef(db);
	wxString path;
	path.Printf("%s\\data\\database.db",buf);
	int result = sqlite3_open(path.c_str(), &db );
	IFSQLITE_OK_DONE(result,db);/*打开数据库*/
	sqlitstmtdef(stmtC);/*定义执行语句*/
	sqlitepreparedef(result,db,sqlvalue,&stmtC);	 /*准备结构*/
	int j = 0;
	while(sqlite3_step(stmtC)==SQLITE_ROW)
	{
		std::map<wxString,wxString> quryout1;
		quryout1["time"]= (char *)sqlite3_column_text(stmtC,0);
		quryout1["gq"] = (char*)sqlite3_column_text(stmtC,1);
		quryout1["yq"] =  (char*)sqlite3_column_text(stmtC,2);
		quryout1["wd"] = (char*)sqlite3_column_text(stmtC,3);
		quryout1["sd"] = (char*)sqlite3_column_text(stmtC,4);
		quryout1["ynd"] = (char*)sqlite3_column_text(stmtC,5);
		quryout.push_back(quryout1);

	}
}

BEGIN_EVENT_TABLE(QURYFRAM, wxDialog)
	EVT_BUTTON(QURYIDMY,QURYFRAM::OnQRUY)
	EVT_BUTTON(QURYIDCOY,QURYFRAM::OnCOPY)
	EVT_GRID_CELL_RIGHT_CLICK( QURYFRAM::_wxFB_ONleftclick )
	END_EVENT_TABLE()

	QURYFRAM::QURYFRAM(wxWindow *parent, const wxDateTime& dt, int dtpStyle)
	: wxDialog(parent, wxID_ANY, wxString(_("查询实验数据")))
{
	m_datePicker = new wxDatePickerCtrl(this, wxID_ANY, dt,
		wxDefaultPosition, wxDefaultSize,
		dtpStyle);
	m_datePicker1 = new wxDatePickerCtrl(this, wxID_ANY, dt,
		wxDefaultPosition, wxDefaultSize,
		dtpStyle);
	m_timePicker = new wxTimePickerCtrl(this, wxID_ANY);
	m_timePicker1 = new wxTimePickerCtrl(this, wxID_ANY);
	m_datePicker->SetRange(wxDateTime(1, wxDateTime::Jan, 1900),wxDefaultDateTime);

	//m_dateText = new wxStaticText(this, wxID_ANY,dt.IsValid() ? dt.FormatISODate(): wxString());

	const wxSizerFlags flags = wxSizerFlags().Centre().Border();
	wxFlexGridSizer* const sizerMain = new wxFlexGridSizer(3);

	sizerMain->Add(new wxStaticText(this, wxID_ANY, "开始时间:"), flags);
	sizerMain->Add(m_datePicker, flags);
	sizerMain->Add(m_timePicker,flags);
	sizerMain->Add(new wxStaticText(this, wxID_ANY, "截止时间:"), flags);
	sizerMain->Add(m_datePicker1, flags);
	sizerMain->Add(m_timePicker1,flags);
	sizerMain->Add(new wxStaticText(this, wxID_ANY, ""),flags);

	sizerMain->Add(new wxButton(this,QURYIDMY,_("查询")), flags);
	sizerMain->Add(new wxButton(this,QURYIDCOY,_("复制")), flags);

	sizerTop = new wxBoxSizer(wxVERTICAL);

	m_grid1 = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid1->CreateGrid( 15, 6);
	m_grid1->EnableEditing( false );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );

	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( true );
	m_grid1->SetColLabelSize( 30 );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	// Rows
	m_grid1->EnableDragRowSize( true );
	m_grid1->SetRowLabelSize( wxGRID_AUTOSIZE );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	// Label Appearance
	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_grid1->SetColLabelValue(0,_("时间"));
	m_grid1->SetColLabelValue(1,_("光强"));
	m_grid1->SetColLabelValue(2,_("压强"));
	m_grid1->SetColLabelValue(3,_("温度"));
	m_grid1->SetColLabelValue(4,_("湿度"));
	m_grid1->SetColLabelValue(5,_("氧浓度"));
	sizerTop->Add(sizerMain, flags);
	sizerTop->Add(new wxStaticLine(this, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizerTop->Add(m_grid1);//,0, wxALL, 5 );
	SetSizerAndFit(sizerTop,false);
}
void QURYFRAM::OnQRUY(wxCommandEvent& WXUNUSED(event))
{
	wxString st1,st2;
	st1.Printf("%s %s",this->m_datePicker->GetValue().FormatISODate(),this->m_timePicker->GetValue().FormatISOTime());
	st2.Printf("%s %s",this->m_datePicker1->GetValue().FormatISODate(),this->m_timePicker1->GetValue().FormatISOTime());

	wxString operstring;
	operstring.Printf("select time,gq,yq,wd,sd,ynd from data where time>'%s' and time < '%s'",st1,st2);
	std::vector<std::map<wxString,wxString>> quryout;
	quryfromdatabase(operstring.c_str(),quryout);
	while(m_grid1->GetRows()>0){
		m_grid1->DeleteRows(0,1,false);
	}
	for(int i = 0;i<quryout.size();++i)
	{
		m_grid1->InsertRows(0,1,true);
		m_grid1->SetCellValue(quryout[i]["time"],0,0);
		m_grid1->SetCellValue(quryout[i]["gq"],0,1);
		m_grid1->SetCellValue(quryout[i]["yq"],0,2);
		m_grid1->SetCellValue(quryout[i]["wd"],0,3);
		m_grid1->SetCellValue(quryout[i]["sd"],0,4);
		m_grid1->SetCellValue(quryout[i]["ynd"],0,5);
	}
	//m_grid1->Refresh();
}
void QURYFRAM::OnCOPY(wxCommandEvent& WXUNUSED(event))
{
	wxString st;
	if (wxTheClipboard->Open())
	{
		//if (wxTheClipboard->IsSupported( wxDF_UNICODETEXT ))
		//{
		wxTheClipboard->Clear();
		wxTextDataObject *data = new wxTextDataObject;
		wxString copydata;
		int i=0,j=0;
		for(i=0;i<this->m_grid1->GetCols();++i)
		{
			copydata += m_grid1->GetColLabelValue(i);
			if(i == this->m_grid1->GetCols() -1) break;
			copydata += _("\t");
		}
		copydata += "\r\n";
		for(i=0;i<this->m_grid1->GetRows();++i)
		{
			wxString data;
			j = 0;
			data = m_grid1->GetCellValue(i,j);
			if(data.length()<1) break;
			data += "\t";
			for(j = 1; j<this->m_grid1->GetCols();++j)
			{
				data += m_grid1->GetCellValue(i,j);
				if(j == this->m_grid1->GetCols() -1) break;
				data += "\t";
			}
			data += "\r\n";
			copydata += data;

		}
		data->SetText(copydata);
		wxTheClipboard->SetData(data);
		//}
		wxTheClipboard->Close();
	}
}
QURYFRAM::~QURYFRAM()
{
	Close(true);
}
