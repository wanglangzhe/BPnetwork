
// idView.h : CidView ��Ľӿ�
//

#pragma once


class CidView : public CView
{
protected: // �������л�����
	CidView();
	DECLARE_DYNCREATE(CidView)

// ����
public:
	CidDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CidView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStudy();
	afx_msg void OnTestnetwork();
	afx_msg void OnSavenetwork();
	afx_msg void OnLoadnetwork();
	afx_msg void OnIdentify();
	afx_msg void OnXor();
};

#ifndef _DEBUG  // idView.cpp �еĵ��԰汾
inline CidDoc* CidView::GetDocument() const
   { return reinterpret_cast<CidDoc*>(m_pDocument); }
#endif

