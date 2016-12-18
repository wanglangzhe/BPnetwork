// HDNUM_CHANGE.cpp : implementation file
//

#include "stdafx.h"
#include "id.h"
#include "HDNUM_CHANGE.h"
#include "afxdialogex.h"


// CHDNUM_CHANGE dialog

IMPLEMENT_DYNAMIC(CHDNUM_CHANGE, CDialogEx)

CHDNUM_CHANGE::CHDNUM_CHANGE(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HDNUM_CHANGE, pParent)
	, input_hdnum(0)
{

}

CHDNUM_CHANGE::~CHDNUM_CHANGE()
{
}

void CHDNUM_CHANGE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_hdnum);
	DDV_MinMaxInt(pDX, input_hdnum, 3, 10);
}


BEGIN_MESSAGE_MAP(CHDNUM_CHANGE, CDialogEx)
END_MESSAGE_MAP()


// CHDNUM_CHANGE message handlers
