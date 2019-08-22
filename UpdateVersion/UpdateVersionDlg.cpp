
// UpdateVersionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpdateVersion.h"
#include "UpdateVersionDlg.h"
#include "afxdialogex.h"
#include "DlgSetting.h"

#include <urlmon.h>                 //Needed for the URLDownloadToFile() function
#pragma comment(lib, "urlmon.lib")  //Needed for the URLDownloadToFile() function
using namespace std;

CString IniFilePath="D:\\Program Files\\config.ini";   //  ʹ�þ���·��


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUpdateVersionDlg �Ի���




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


// CUpdateVersionDlg ��Ϣ�������

BOOL CUpdateVersionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// [8/17/2019 fdh]  ����list������
	static   CFont   font1;  
	font1.CreatePointFont(150, _T("΢���ź�"));
	GetDlgItem(IDC_STATIC_TIP)->SetFont(&font1);
	GetDlgItem(IDC_LIST_FILE)->SetFont(&font1);
	font1.Detach();
	font1.CreatePointFont(150, _T("����"));
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_EXIT)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_UPDATE)->SetFont(&font1);
	GetDlgItem(IDC_BUTTON_REPLACE)->SetFont(&font1);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��һ����ַ
	CString info;
	bool read = ReadHtml("http://fengdh.cn/shared",info);
	if(read)
	{
		//�����ȡ��������
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
				//��ȡ�ļ���
				CString Filename;
				AfxExtractSubString(Filename,tempResult,1,'=');
				Filename = Filename.Trim("\"");
				m_listFile.AddString(Filename);
			}
		}
		else
		{
			AfxMessageBox("δ�ҵ�ƥ���ļ�");
		}
	}
	else
	{
		AfxMessageBox("��ҳ���ݶ�ȡʧ��");
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpdateVersionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUpdateVersionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUpdateVersionDlg::OnBnClickedButtonDownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel;
	m_listFile.GetCurSel();
	sel = m_listFile.GetCurSel();
	if (sel < 0)
	{
		AfxMessageBox("��δѡ���κ��ļ�");
		return;
	}
	else
	{
		CString strTmp;
		m_listFile.GetText(sel,strTmp); //�õ���ǰѡ����ַ���
		CString url_file;

		char cMissionPath[200];

		GetPrivateProfileString("����","��������ַ","http://fengdh.cn/shared",cMissionPath,200,IniFilePath);
		CString s_MissionPath;
		s_MissionPath.Format("%s",cMissionPath);
		//url_file.Format("http://fengdh.cn/shared/%s",strTmp);
		url_file.Format("%s%s",s_MissionPath,strTmp);

		GetPrivateProfileString("����","����·��","D:\\",cMissionPath,200,IniFilePath);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostMessage(WM_QUIT,0,0);//���
}


void CUpdateVersionDlg::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgSetting dlg;
	dlg.DoModal();

}
;

void CUpdateVersionDlg::OnBnClickedButtonReplace()
{
	// TODO: ���°汾
	int sel;
	m_listFile.GetCurSel();
	sel = m_listFile.GetCurSel();
	if (sel < 0)
	{
		AfxMessageBox("��δѡ���κ��ļ�");
		return;
	}
	CString strTmp;
	m_listFile.GetText(sel,strTmp); //�õ���ǰѡ����ַ���
	CString url_file;

	char cMissionPath[200];
	CString s_MissionPath;

	GetPrivateProfileString("����","����·��","D:\\",cMissionPath,200,IniFilePath);
	s_MissionPath.Format("%s",cMissionPath);

	CString s_SavePath;
	s_SavePath.Format("%s\\%s",cMissionPath,strTmp);

	//Convert the string to a LPCSTR type so we can use it in the URLDownloadToFile() function
	LPCSTR lpcURL = s_SavePath;

	ShellExecute( GetSafeHwnd(), "open", lpcURL, NULL, NULL, 1 );

}
