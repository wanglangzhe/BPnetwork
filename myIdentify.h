#pragma once
#include "bp.h"

// myIdentify �Ի���

extern bp::bp *bpNetwork;

class myIdentify : public CDialog
{
	DECLARE_DYNAMIC(myIdentify)

public:
	myIdentify(CWnd* pParent = NULL);   // ��׼���캯��

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	virtual ~myIdentify();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IDENTIFY };
#endif
	BOOL m_bLButtonDown, // �ж��Ƿ���������
		m_bErase; // �Ƿ���Ҫ����ͼ��

	CPoint p0, pm;
	bool onDraw;
	CPen *pGrayPen, *pLinePen;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void save() ;
};
