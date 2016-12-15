#pragma once
#include "bp.h"

// myIdentify 对话框

extern bp::bp *bpNetwork;

class myIdentify : public CDialog
{
	DECLARE_DYNAMIC(myIdentify)

public:
	myIdentify(CWnd* pParent = NULL);   // 标准构造函数

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	virtual ~myIdentify();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IDENTIFY };
#endif
	BOOL m_bLButtonDown, // 判断是否按下左鼠标键
		m_bErase; // 是否需要擦除图形

	CPoint p0, pm;
	bool onDraw;
	CPen *pGrayPen, *pLinePen;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void save() ;
};
