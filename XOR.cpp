// XOR.cpp : implementation file
//

#include "stdafx.h"
#include "id.h"
#include "XOR.h"
#include "afxdialogex.h"


// CXOR dialog

IMPLEMENT_DYNAMIC(CXOR, CDialogEx)

CXOR::CXOR(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XOR, pParent)
	, xor_insert_A(0)
	, xor_insert_B(0)
{

}

CXOR::~CXOR()
{
}

void CXOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, INSERT_A, xor_insert_A);
	DDX_Text(pDX, INSERT_B, xor_insert_B);
	DDX_Control(pDX, IDOK, xor_ok);
	DDX_Control(pDX, IDCANCEL, xor_cancel);
	DDV_MinMaxInt(pDX, xor_insert_A, 0, 1);
	DDV_MinMaxInt(pDX, xor_insert_B, 0, 1);
}


BEGIN_MESSAGE_MAP(CXOR, CDialogEx)
	ON_EN_CHANGE(INSERT_A, &CXOR::OnEnChangeA)
	ON_COMMAND(ID_XOR, &CXOR::OnXor)
END_MESSAGE_MAP()


// CXOR message handlers


void CXOR::OnEnChangeA()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CXOR::OnXor()
{
	// TODO: Add your command handler code here

}
