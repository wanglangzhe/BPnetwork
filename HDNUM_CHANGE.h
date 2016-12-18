#pragma once


// CHDNUM_CHANGE dialog

class CHDNUM_CHANGE : public CDialogEx
{
	DECLARE_DYNAMIC(CHDNUM_CHANGE)

public:
	CHDNUM_CHANGE(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHDNUM_CHANGE();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int input_hdnum;
};
