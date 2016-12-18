#pragma once
#include "afxwin.h"


// CXOR dialog

class CXOR : public CDialogEx
{
	DECLARE_DYNAMIC(CXOR)

public:
	CXOR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CXOR();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int xor_insert_A;
	int xor_insert_B;

	CButton xor_ok;
	CButton xor_cancel;
	
	afx_msg void OnEnChangeA();
	afx_msg void OnXor();
};
