#include <wx/gbsizer.h>
#include "wx/wxprec.h"
#include "DETECTED.h"
#include "comm.h"
#include "wx/statline.h"
#include <map>
#include <cctype>
//std::map<wxString,double>
//#include "wx/hashmap.h"
#define POS(r, c)        wxGBPosition(r,c)
#define SPAN(r, c)       wxGBSpan(r,c)
///////////////////////////////////////////////////////////////////////////
class lexstr
{
public:
	char *pstr;
	int pos;
	int maxlen;
	lexstr(char *pp,int len)
	{
		pstr = pp;
		pos = 0;
		maxlen = len;
	}
	char next()
	{
		if(pos>=maxlen) return '\0';
		++pos;
		return pstr[pos];
	}
	char cur()
	{
		if(pos>=maxlen) return '\0';
		return pstr[pos];
	}
	void back()
	{
		if(pos>0) pos--;
	}

};
int savetodatabase(const char * savesql)
{
	char  buf[200];
	getcwd(buf,199);
	sqlitedbdef(db);
	wxString path;
	path.Printf("%s\\data\\database.db",buf);
	int result = sqlite3_open(path.c_str(), &db );
	IFSQLITE_OK_DONE(result,db);/*打开数据库*/
	sqlitstmtdef(stmtC);/*定义执行语句*/
	sqlitepreparedef(result,db,savesql,&stmtC);	 /*准备结构*/
	result = sqlite3_step(stmtC); /*执行*/
	if(result != SQLITE_DONE)
	{
		return result;
	}
	//wxMessageBox("create");
	return SQLITE_OK;


}

/*解析字符串获得数值*/
void parservalue(string & str,std::map<string,string>& values)
{
	lexstr mylex(&str[0],str.length());
	string vstr,dstr;
	while(mylex.cur()!='\0')
	{
		switch (mylex.cur())
		{
		case '=':
			{
				dstr.clear();
				char tpc = mylex.next();
				while(tpc != '\0' &&tpc != '\r' && tpc != '\n' && tpc != ' ')
				{
					dstr.push_back(tpc);
					tpc = mylex.next();
				}
				values[vstr] = dstr;
			}
			break;
		case '\r':
			{
				mylex.next();
			}
			break;
		case '\n':
			{
				mylex.next();
			}
			break;
		case ' ':
			{
				mylex.next();
			}
			break;

		default:
			{
				vstr.clear();
				char tpc = mylex.cur();
				while(tpc != '=' && tpc != '\0' &&tpc != '\r' && tpc != '\n' && tpc != ' ')
				{
					vstr.push_back(tpc);
					tpc = mylex.next();
				}
			}
			break;
		}

	}


}

enum{

	myboten1 = 6006,
	mytimerid,
	MYSLIDER
};

BEGIN_EVENT_TABLE(DETECTEDFRAM, wxDialog)
	//EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_BUTTON(myboten1,  DETECTEDFRAM::startbotn)
	EVT_TIMER(mytimerid,DETECTEDFRAM::onTimer)
	EVT_SLIDER(MYSLIDER,DETECTEDFRAM::onSlider)
	END_EVENT_TABLE()
	static void getlocaltime(wxString & st);

void getcomvalue(string & tp1)
{
	MYCOMM comm1;
	comm1.open("com5");
	comm1.set();
	string ab ;
	ab=string("1234");
	comm1.write(ab);
	Sleep(2000);
	comm1.showread(tp1);
}
/*按时间调度传感器并显示到表格*/
std::map<string,string> detectvalues;
void DETECTEDFRAM::onTimer(wxTimerEvent& event)
{
	wxString time1;
	getlocaltime(time1);
	this->m_grid1->InsertRows(0,1);

	string tp1;
	getcomvalue(tp1);
	parservalue(tp1,detectvalues);
	this->m_grid1->DeleteRows(4,1);
	this->m_grid1->SetCellValue(time1,0,0);
	this->m_grid1->SetCellValue(detectvalues["G"],0,1);
	this->m_grid1->SetCellValue(detectvalues["P"],0,2);
	this->m_grid1->SetCellValue(detectvalues["T1"],0,3);
	this->m_grid1->SetCellValue(detectvalues["H"],0,4);
	this->m_grid1->SetCellValue(detectvalues["O"],0,5);
	//this->m_grid1->SetCellValue(detectvalues["T2"],0,6);
	wxString savesql;
	savesql.Printf("insert into data(time,wd,gq,yq,sd,ynd)values('%s','%s','%s','%s','%s','%s')",time1.c_str(),
		detectvalues["T1"].c_str(),detectvalues["G"].c_str()
		,detectvalues["P"].c_str(),detectvalues["H"].c_str(),
		detectvalues["O"].c_str());
	savetodatabase(savesql.c_str());

}
void DETECTEDFRAM::onSlider(wxCommandEvent & event)
{
	wxString showvalue;
	showvalue.Printf("%d%%",m_slider1->GetValue());
	slidervalueshow->SetLabel(showvalue);
}
static void getlocaltime(wxString & st)
{

	time_t t;
	struct tm p;
	t=time(NULL);/*获取从1970年1月1日零时到现在的秒数，保存到变量t中*/
	p=*localtime(&t); /*变量t的值转换为实际日期时间的表示格式*/
	st.Printf(_("%d-%02d-%02d %02d:%02d:%02d"),(1900+p.tm_year), (1+p.tm_mon),p.tm_mday,p.tm_hour, p.tm_min, p.tm_sec);

}
void DETECTEDFRAM::startbotn(wxCommandEvent & WXUNUSED(event))
{

	//static int ifstop=0;
	wxArrayString xians;
	xians.push_back(_("开始"));
	xians.push_back(_("停止"));
	this->ifstop= this->ifstop==1?0:1;
	this->m_choice1->GetSelection();
	wxString st;
	if(ifstop)
	{

		st.Printf(_("启动测试,运行平率为:%d 分钟"),this->m_choice1->GetSelection()+1);//,this->m_timer1->GetInterval());
		wxMessageBox(st);
		m_timer1.Start(60000*(this->m_choice1->GetSelection()+1));
		m_button1->SetLabel(xians[ifstop]);
	}
	else
	{
		st.Printf(_("停止测试"));//,this->m_timer1->GetInterval());
		wxMessageBox(st);
		if(m_timer1.IsRunning()) m_timer1.Stop();
		m_button1->SetLabel(xians[ifstop]);
	}
}



DETECTEDFRAM::DETECTEDFRAM( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) :
	wxDialog(parent/*(wxFrame *)NULL*/, wxID_ANY, title),m_timer1(this,mytimerid)
{
	this->ifstop = 0;
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	//this->m_timer1 = new wxTimer(wxID_ANY);
	wxGridBagSizer* gSizer1;
	gSizer1 = new wxGridBagSizer();
	wxPanel *m_panel = new wxPanel(this,-1);
	m_staticText1 = new wxStaticText( m_panel, wxID_ANY, _("光强"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_staticText1,
		POS(0,0), SPAN(1, 1),
		wxALIGN_CENTER | wxALL, 5);

	m_slider1 = new wxSlider( m_panel, MYSLIDER, 50, 0, 100, wxDefaultPosition, wxSize(300,-1), wxSL_HORIZONTAL );
	gSizer1->Add( m_slider1,     POS(0,1), SPAN(1, 3),
		wxALIGN_LEFT | wxALL, 5);
	slidervalueshow = new wxStaticText( m_panel, wxID_ANY, _("50%"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( slidervalueshow,
		POS(0,4), SPAN(1, 1),
		wxALIGN_CENTER | wxALL, 5);

	gSizer1->Add( new wxStaticText( m_panel, wxID_ANY, _("测量频率"), wxDefaultPosition, wxDefaultSize, 0 ),
		POS(1,0), SPAN(1, 1),
		wxALIGN_CENTER | wxALL, 5);

	wxArrayString m_choice1Choices;
	m_choice1Choices.Add(_("1分钟"));
	m_choice1Choices.Add(_("2分钟"));
	m_choice1Choices.Add(_("3分钟"));
	m_choice1Choices.Add(_("4分钟"));
	m_choice1 = new wxChoice( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	//wxMessageBox( m_choice1->Select(1));

	m_choice1->SetSelection( 0 );
	gSizer1->Add( m_choice1,
		POS(1,1), SPAN(1, 1),
		wxALIGN_CENTER | wxALL, 5);

	m_button1 = new wxButton( m_panel, myboten1, _("开始"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button1,
		POS(1,2), SPAN(1, 1),
		wxALIGN_RIGHT | wxALL, 5);



	bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );
	m_grid1 = new wxGrid( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	// Grid
	m_grid1->CreateGrid( 6, 6 );
	m_grid1->EnableEditing( false );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );

	// Columns
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( true );
	m_grid1->SetColLabelSize( wxGRID_AUTOSIZE );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	//m_grid1->SetColSize(0,wxGRID_AUTOSIZE);

	// Rows
	m_grid1->EnableDragRowSize( true );
	m_grid1->SetRowLabelSize( 0 );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance
	m_grid1->SetColLabelValue(0,_("时间"));
	m_grid1->SetColLabelValue(1,_("光强"));
	m_grid1->SetColLabelValue(2,_("压强"));
	m_grid1->SetColLabelValue(3,_("温度"));
	m_grid1->SetColLabelValue(4,_("湿度"));
	m_grid1->SetColLabelValue(5,_("氧浓度"));
	//m_grid1->SetColLabelValue(6,_("温度2"));
	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer1->Add(new wxStaticLine(m_panel, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	bSizer1->Add( m_grid1, 0, wxALL, 5 );
	m_panel->SetSizer( bSizer1 );
	//this->Layout();
	//this->Centre( wxBOTH );
	m_panel->Centre( wxBOTH );
	bSizer1 -> Fit(this);
}

DETECTEDFRAM::~DETECTEDFRAM()
{
	Close(true);
}
