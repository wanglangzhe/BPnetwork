
// idView.cpp : CidView 类的实现
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

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CidView 构造/析构

CidView::CidView()
{
	//MessageBox(L"start");
	// TODO: 在此处添加构造代码
	bpNetwork = new bp::bp();
}

CidView::~CidView()
{
	delete bpNetwork;
}

BOOL CidView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CidView 绘制

void CidView::OnDraw(CDC* /*pDC*/)
{
	CidDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CidView 打印


void CidView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CidView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CidView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CidView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CidView 诊断

#ifdef _DEBUG
void CidView::AssertValid() const
{
	CView::AssertValid();
}

void CidView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CidDoc* CidView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CidDoc)));
	return (CidDoc*)m_pDocument;
}
#endif //_DEBUG


// CidView 消息处理程序

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
	//点击此处进行神经网络的学习
	// TODO: 在此添加命令处理程序代码
	//MessageBox(L"here!");

	AllocConsole();                     // 打开控制台资源
	freopen("CONOUT$", "w+t", stdout);// 申请写
	freopen("CONIN$", "r+t", stdin);  // 申请读
	printf("Hello World\n");          // 写数据
	//char ch = getchar();                // 读数据
	
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

	CDC* pDC = GetDC(); // 获取DC
	CPen pen, *pOldPen; // 定义笔对象和指针

	for (int tim = 0; tim < ITERS * 10; ++tim) {

		if (0) {
			reverse(data.begin(), data.end());	//反向训练
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
						pOldPen = pDC->SelectObject(&pen); // 选入绿色笔

						int vx = dx, vy = y2 - y1;
						pDC->MoveTo(x + 0.1 * vx, y1 + 0.1 * vy);
						pDC->LineTo(x + 0.9 * vx, y1 + 0.9 * vy);

						pDC->SelectObject(pOldPen); // 选出绿色笔
						pen.DeleteObject(); // 删除绿色笔内容
					}
				}				
			}
		}
		if (flag) break;
	}

	ReleaseDC(pDC); // 释放DC

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
	
	//FreeConsole();                      // 释放控制台资源

	//
}


void CidView::OnTestnetwork()
{
	// TODO: 在此添加命令处理程序代码

	AllocConsole();                     // 打开控制台资源
	freopen("CONOUT$", "w+t", stdout);// 申请写
	freopen("CONIN$", "r+t", stdin);  // 申请读
	printf("Hello World\n");          // 写数据

	bp::testData("D:\\work\\VS\\id\\dataset\\digits\\testDigits\\", bpNetwork);

	

	FreeConsole();
}


void CidView::OnSavenetwork()
{
	// TODO: 在此添加命令处理程序代码
	if (!bpNetwork->store()) MessageBox(L"网络保存失败");
	else MessageBox(L"网络保存成功");
}


void CidView::OnLoadnetwork()
{
	// TODO: 在此添加命令处理程序代码
	if (!bpNetwork->load()) MessageBox(L"网络读取失败");
	else MessageBox(L"网络读取成功");
}


void CidView::OnIdentify()
{
	// TODO: 在此添加命令处理程序代码
	myIdentify dlg;
	if (dlg.DoModal() == IDOK) {
		//MessageBox(L"识别输入完毕");
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
		std::wstring a = L"答案为0的几率为" + ans0 + L"\r\n答案为1的几率为" + ans1;
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
		std::wstring a = L"答案为0的几率为" + ans0 + L"\r\n答案为1的几率为" + ans1;
		LPCWSTR str = a.c_str();
		MessageBox(str);
	}

}
