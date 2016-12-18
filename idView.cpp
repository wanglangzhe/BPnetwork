
// idView.cpp : CidView ���ʵ��
//

#include "stdafx.h"
#include "bp.h"
#include "myIdentify.h"
#include "XOR.h"
#include "HDNUM_CHANGE.h"
#include <iostream>
#include <string>

#pragma warning(disable : 4996) 

bp::bp *bpNetwork;

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "id.h"
#endif

#include "idDoc.h"
#include "idView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CidView

IMPLEMENT_DYNCREATE(CidView, CView)

BEGIN_MESSAGE_MAP(CidView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CidView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_STUDY, &CidView::OnStudy)
	ON_COMMAND(ID_TESTNETWORK, &CidView::OnTestnetwork)
	ON_COMMAND(ID_SAVENETWORK, &CidView::OnSavenetwork)
	ON_COMMAND(ID_LOADNETWORK, &CidView::OnLoadnetwork)
	ON_COMMAND(ID_IDENTIFY, &CidView::OnIdentify)
	ON_COMMAND(ID_XOR, &CidView::OnXor)
	ON_COMMAND(ID_HDNUM_CHANGE, &CidView::OnHdnumChange)
	ON_COMMAND(ID_TEST, &CidView::OnTest)
END_MESSAGE_MAP()

// CidView ����/����

CidView::CidView()
{
	//MessageBox(L"start");
	// TODO: �ڴ˴���ӹ������
	bpNetwork = new bp::bp();
}

CidView::~CidView()
{
	delete bpNetwork;
}

BOOL CidView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CidView ����

void CidView::OnDraw(CDC* /*pDC*/)
{
	CidDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CidView ��ӡ


void CidView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CidView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CidView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CidView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CidView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CidView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CidView ���

#ifdef _DEBUG
void CidView::AssertValid() const
{
	CView::AssertValid();
}

void CidView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CidDoc* CidView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CidDoc)));
	return (CidDoc*)m_pDocument;
}
#endif //_DEBUG


// CidView ��Ϣ�������

float databinding[][4] = {
	
	{0, 1, 0, 1 },
	{0, 0, 1, 0},	
	{1, 0, 0, 1},
	{1, 1, 1, 0},

	{ 1, 1, 1, 0 },
	{ 1, 0, 0, 1 },
	{ 0, 1, 0, 1 },
	{ 0, 0, 1, 0 },
	/*
	{0, 0, 1, 0},
	{ 1, 0, 0, 1 },
	{ 0, 1, 0, 1 },
	{ 1, 1, 0, 1 }
	*/
};



void CidView::OnStudy()
{		
	//����˴������������ѧϰ
	// TODO: �ڴ���������������
	//MessageBox(L"here!");

	AllocConsole();                     // �򿪿���̨��Դ
	freopen("CONOUT$", "w+t", stdout);// ����д
	freopen("CONIN$", "r+t", stdin);  // �����
	printf("Hello World\n");          // д����
	//char ch = getchar();                // ������
	
	std::vector<bp::Data> data;
	
	for (int i = 0; i < 8; ++i) {
		int now = data.size();
		data.push_back(bp::Data());
		data[now].input.push_back(databinding[i][0]);
		data[now].input.push_back(databinding[i][1]);
		data[now].output.push_back(databinding[i][2]);
		data[now].output.push_back(databinding[i][3]);
	}
	

	//bp::washData("C:\\Users\\Administrator\\Desktop\\BPnetwork-master\\", data);
	
	bpNetwork->getData(data);
	//bpNetwork->train();
	bpNetwork->tranInit();

	RECT rect;
	GetClientRect(&rect);
	int iW = rect.right, iH = rect.bottom;
	int dx, dy; 
	int r = 10;
	dx = max(1, iW / (bpNetwork->getLayer()));

	CDC* pDC = GetDC(); // ��ȡDC
	CPen pen, *pOldPen; // ����ʶ����ָ��

	for (int tim = 0; tim < ITERS * 10; ++tim) {

		if (0) {
			reverse(data.begin(), data.end());	//����ѵ��
			bpNetwork->getData(data);
		}

		RECT rect;
		GetClientRect(&rect);
		pDC->FillSolidRect(&rect, RGB(255, 255, 255));
		
		std::cout << tim << std::endl;
		
		bool flag = bpNetwork->tranAset(1); //3 - tim * 2.0 / 1000

		int x = 0, y = 0, layer = bpNetwork->getLayer();
		for (int lay = 1; lay < layer; ++lay) {

			x += dx; y = 0;
			dy = max(1, iH / (1 + bpNetwork->nodeOfLay(lay)));
						
			for (int i = 0; i < bpNetwork->nodeOfLay(lay); ++i) {

				double tt = bpNetwork->getB(lay, i); r = (0.2 + ABS(tt)) * 10 + 1;
				CBrush brush(RGB(tt < 0 ? 255 : 0, tt >= 0 ? 255 : 0, 10)), *pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);

				y += dy;
				pDC->Ellipse(x - r, y - r, x + r, y + r);

				pDC->SelectObject(pOldBrush);
				brush.DeleteObject();
			}

			if (lay + 1 < layer) {
				
				int y1, y2, dy2;
				dy2 = iH / (1 + bpNetwork->nodeOfLay(lay + 1));
				y1 = 0;
				for (int i = 0; i < bpNetwork->nodeOfLay(lay); ++i) {
					y2 = 0; y1 += dy;
					for (int j = 0; j < bpNetwork->nodeOfLay(lay + 1); ++j) {
						y2 += dy2;

						double tt = bpNetwork->getW(lay, i, j);
						pen.CreatePen(PS_SOLID, 1 + 1.5 * tt, RGB(tt < 0 ? 255 : 0, tt >= 0 ? 255 : 0, ABS(tt) < 1e-4 ? 255: 10));
						pOldPen = pDC->SelectObject(&pen); // ѡ����ɫ��

						int vx = dx, vy = y2 - y1;
						pDC->MoveTo(x + 0.1 * vx, y1 + 0.1 * vy);
						pDC->LineTo(x + 0.9 * vx, y1 + 0.9 * vy);

						pDC->SelectObject(pOldPen); // ѡ����ɫ��
						pen.DeleteObject(); // ɾ����ɫ������
					}
				}				
			}
		}
		if (flag) break;
	}

	ReleaseDC(pDC); // �ͷ�DC

					/*
					for (int tim = 0; tim < 40; ++tim) {
					int x, y;
					std::cin >> x >> y;
					std::vector <float> test(2), ans;
					test[0] = x; test[1] = y;
					ans = bpNetwork->foreCast(test);
					std::cout << ans[0] << ' ' << ans[1] << std::endl;
					}
					*/
	
	MessageBox(L"train finish");
	
	//FreeConsole();                      // �ͷſ���̨��Դ

	//
}


void CidView::OnTestnetwork()
{
	// TODO: �ڴ���������������

	AllocConsole();                     // �򿪿���̨��Դ
	freopen("CONOUT$", "w+t", stdout);// ����д
	freopen("CONIN$", "r+t", stdin);  // �����
	printf("Hello World\n");          // д����

	bp::testData("D:\\work\\VS\\id\\dataset\\digits\\testDigits\\", bpNetwork);

	

	FreeConsole();
}


void CidView::OnSavenetwork()
{
	// TODO: �ڴ���������������
	if (!bpNetwork->store()) MessageBox(L"���籣��ʧ��");
	else MessageBox(L"���籣��ɹ�");
}


void CidView::OnLoadnetwork()
{
	// TODO: �ڴ���������������
	if (!bpNetwork->load()) MessageBox(L"�����ȡʧ��");
	else MessageBox(L"�����ȡ�ɹ�");
}


void CidView::OnIdentify()
{
	// TODO: �ڴ���������������
	myIdentify dlg;
	if (dlg.DoModal() == IDOK) {
		//MessageBox(L"ʶ���������");
	}
	else {
		assert(0);
	}
}

std::wstring getstr(float x)
{
	std::wstring s;
	char ch[40] = {0};
	sprintf(ch, "%f", x);
	for (int i = 0; i < strlen(ch); i++)
		s += ch[i];
	return s;
}

void CidView::OnXor()
{
	// TODO: Add your command handler code here
	CXOR dlg;
	int x = 0, y = 0;
	dlg.xor_insert_A = x;
	dlg.xor_insert_B = y;
	if (dlg.DoModal() == IDOK)
	{
		x = dlg.xor_insert_A;
		y = dlg.xor_insert_B;
		std::vector <float> test(2), ans;
		test[0] = x; test[1] = y;
		ans = bpNetwork->foreCast(test);
		std::wstring ans0 = getstr(ans[0]);
		std::wstring ans1 = getstr(ans[1]);
		std::wstring a = L"��Ϊ0�ļ���Ϊ" + ans0 + L"\r\n��Ϊ1�ļ���Ϊ" + ans1;
		LPCWSTR str = a.c_str();
		MessageBox(str);
	}
		
}


void CidView::OnHdnumChange()
{
	// TODO: Add your command handler code here
	bpNetwork->set_hdnum(0);
	CHDNUM_CHANGE dlg;
	if (dlg.DoModal() == IDOK)
	{
		bpNetwork->set_hdnum(dlg.input_hdnum);
	}
}


void CidView::OnTest()
{
	// TODO: Add your command handler code here
	CXOR dlg;
	int x = 0, y = 0;
	dlg.xor_insert_A = x;
	dlg.xor_insert_B = y;
	if (dlg.DoModal() == IDOK)
	{
		x = dlg.xor_insert_A;
		y = dlg.xor_insert_B;
		std::vector <float> test(2), ans;
		test[0] = x; test[1] = y;
		ans = bpNetwork->foreCast(test);
		std::wstring ans0 = getstr(ans[0]);
		std::wstring ans1 = getstr(ans[1]);
		std::wstring a = L"��Ϊ0�ļ���Ϊ" + ans0 + L"\r\n��Ϊ1�ļ���Ϊ" + ans1;
		LPCWSTR str = a.c_str();
		MessageBox(str);
	}

}
