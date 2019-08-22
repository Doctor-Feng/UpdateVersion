
// UpdateVersionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpdateVersion.h"
#include "UpdateVersionDlg.h"
#include "afxdialogex.h"
#include "DlgSetting.h"

#include <urlmon.h>                 //Needed for the URLDownloadToFile() function
#pragma comment(lib, "urlmon.lib")  //Needed for the URLDownloadToFile() function
using namespace std;

CString IniFilePath="D:\\Program Files\\config.ini";   //  使用绝对路径


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUpdateVersionDlg 对话框




CUpdateVersionDlg::CUpdateVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateVersionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
}

BEGIN_MESSAGE_MAP(CUpdateVersionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CUpdateVersionDlg::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CUpdateVersionDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CUpdateVersionDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, &CUpdateVersionDlg::OnBnClickedButtonReplace)
END_MESSAGE_MAP()


// CUpdateVersionDlg 消息处理程序

BOOL CUpdateVersionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// [8/17/2019 fdh]  设置list的字体
	static   CFont   font1;  
	font1.CreatePointFont(150, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC_TIP)->SetFont(&font1);
	GetDlgItem(IDC_LIST_FILE)->SetFont(&font1);
	font1.Detach();
	font1.CreatePointFont(150, _T("黑体"));
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_EXIT)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_UPDATE)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_REPLACE)->SetFont(&font1);

	// TODO: 在此添加额外的初始化代码
	//打开一个网址
	CString info;
	bool read = ReadHtml("http://fengdh.cn/shared",info);
	if(read)
	{
		//如果读取到了数据
		//a href="update-1.2.26.6680.exe"
		//std::regex pattern("a\ href=\"update-[0-9]{1}\.[0-9][1]\.[1-9]{2}\.[0-9]{4}\.exe\"");
		std::regex pattern("a\ href=\"upgrade-[0-9]{1}.[0-9]{1}.[0-9]{2}.[0-9]{4}.exe\"");
		std::vector<CString> results;
		CString tempResult;
		bool success = GetDataFromHtml(info,pattern,results);
		if(success)
		{
			for (std::vector<CString>::iterator it = results.begin(); it != results.end(); ++it)
			{
				tempResult = *it;
				//截取文件名
				CString Filename;
				AfxExtractSubString(Filename,tempResult,1,'=');
				Filename = Filename.Trim("\"");
				m_listFile.AddString(Filename);
			}
		}
		else
		{
			AfxMessageBox("未找到匹配文件");
		}
	}
	else
	{
		AfxMessageBox("网页数据读取失败");
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpdateVersionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpdateVersionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpdateVersionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUpdateVersionDlg::OnBnClickedButtonDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel;
	m_listFile.GetCurSel();
	sel = m_listFile.GetCurSel();
	if (sel < 0)
	{
		AfxMessageBox("你未选中任何文件");
		return;
	}
	else
	{
		CString strTmp;
		m_listFile.GetText(sel,strTmp); //得到当前选择的字符串
		CString url_file;

		char cMissionPath[200];

		GetPrivateProfileString("参数","服务器地址","http://fengdh.cn/shared",cMissionPath,200,IniFilePath);
		CString s_MissionPath;
		s_MissionPath.Format("%s",cMissionPath);
		//url_file.Format("http://fengdh.cn/shared/%s",strTmp);
		url_file.Format("%s%s",s_MissionPath,strTmp);

		GetPrivateProfileString("参数","保存路径","D:\\",cMissionPath,200,IniFilePath);
		s_MissionPath.Format("%s",cMissionPath);
	
		CString s_SavePath;
		s_SavePath.Format("%s\\%s",cMissionPath,strTmp);

		//Convert the string to a LPCSTR type so we can use it in the URLDownloadToFile() function
		LPCSTR lpcURL = url_file;

		//string destination = "C:\\Users\\15076\\Desktop\\2222.gif";
		//Convert the string to a LPCSTR type so we can use it in the URLDownloadToFile() function
		//LPCSTR lpcDestination = destination.c_str();
		//HRESULT hr = URLDownloadToFile( NULL, lpcURL, lpcDestination, 0, NULL );
		HRESULT hr = URLDownloadToFile( NULL, lpcURL, s_SavePath, 0, NULL );
	}
	
}

void CUpdateVersionDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_QUIT,0,0);//最常用
}


void CUpdateVersionDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgSetting dlg;
	dlg.DoModal();

}
;

void CUpdateVersionDlg::OnBnClickedButtonReplace()
{
	// TODO: 更新版本
	int sel;
	m_listFile.GetCurSel();
	sel = m_listFile.GetCurSel();
	if (sel < 0)
	{
		AfxMessageBox("你未选中任何文件");
		return;
	}
	CString strTmp;
	m_listFile.GetText(sel,strTmp); //得到当前选择的字符串
	CString url_file;

	char cMissionPath[200];
	CString s_MissionPath;

	GetPrivateProfileString("参数","保存路径","D:\\",cMissionPath,200,IniFilePath);
	s_MissionPath.Format("%s",cMissionPath);

	CString s_SavePath;
	s_SavePath.Format("%s\\%s",cMissionPath,strTmp);

	//Convert the string to a LPCSTR type so we can use it in the URLDownloadToFile() function
	LPCSTR lpcURL = s_SavePath;

	ShellExecute( GetSafeHwnd(), "open", lpcURL, NULL, NULL, 1 );

}
