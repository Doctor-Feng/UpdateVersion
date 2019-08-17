
// UpdateVersionDlg.h : ͷ�ļ�
//
#include <regex>
#include <string>
#include <afxinet.h>
#include "afxwin.h"
using namespace std;

#pragma once

// CUpdateVersionDlg �Ի���
class CUpdateVersionDlg : public CDialogEx
{
// ����
public:
	CUpdateVersionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPDATEVERSION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDownload();

	afx_msg bool ReadHtml(CString url,CString& info)
	{
		CInternetSession c;
		CHttpFile * p = NULL;
		//p=(CHttpFile*)c.OpenURL("http://fengdh.cn/shared");//��һ��URL
		p=(CHttpFile*)c.OpenURL(url);
		CString str;
		//CString info;
		while(p->ReadString(str))   //��ȡ��ҳ���� 
			info+=str;
		if(info.IsEmpty())
			return false;
		else
			return true;
	}

	afx_msg bool GetDataFromHtml(const char *html, regex patterns,std::vector<CString> &results)
	{
		//regex pattern("a\ href=\"\\d.gif\"");
		//std::vector<CString> results;
		std::smatch match;
		std::string html_data = html;
		while (std::regex_search(html_data, match, patterns))
		{
			results.push_back(match[0].str().c_str());
			html_data = match.suffix();
		}

		if(results.size()>0)
			return true;
		else
			return false;
	}

	CListBox m_listFile;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonSet();
};
