// myIdentify.cpp : 实现文件
//

#include "stdafx.h"
#include "id.h"
#include "myIdentify.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>


// myIdentify 对话框

IMPLEMENT_DYNAMIC(myIdentify, CDialog)

myIdentify::myIdentify(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_IDENTIFY, pParent)
{
	
}

BOOL myIdentify::OnInitDialog()
{
	//MessageBox(L"init ! ");

	SetCursor(LoadCursor(NULL, IDC_CROSS)); // 设置鼠标为十字

	p0 = CPoint(-1, -1);
	pm = CPoint(0, 0);
	onDraw = false;

	m_bLButtonDown = FALSE; // 设左鼠标键按下为假
	m_bErase = FALSE; // 设需要擦除为假


	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // 创建灰色点线笔
	pLinePen = new CPen(PS_SOLID, 55, RGB(255, 0, 0)); // 创建红色的直线笔

	return true;
	CRect temprect(0, 0, 400 * 4 / 3, 400 );
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	return true;
}

void myIdentify::OnOK()
{
	save(); 
	int ans = bp::testAdata("", bpNetwork);
	CString str;
	str.Format(_T("%d"), ans);
	MessageBox(str);


	CDialog::OnOK();//第一步，关闭窗口  
	DestroyWindow();//第二步,释放资源
}

myIdentify::~myIdentify()
{
	delete pGrayPen;
	delete pLinePen;
}

void myIdentify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(myIdentify, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// myIdentify 消息处理程序


void myIdentify::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

	CDC* pDC = &dc; // 获取DC
	CPen pen, *pOldPen; // 定义笔对象和指针
						// 创建10单位宽的绿色实心笔：
	pen.CreatePen(PS_SOLID, 20, RGB(0, 255, 0));
	pOldPen = pDC->SelectObject(&pen); // 选入绿色笔
	pDC->Rectangle(0, 0, 320, 320); // 画矩形
	pDC->SelectObject(pOldPen); // 选出绿色笔
	pen.DeleteObject(); // 删除绿色笔内容
						// 创建单像素宽的红色虚线笔：
												//pen.CreatePen(PS_DASH, 0, RGB(255, 0, 0));
												//pOldPen = pDC->SelectObject(&pen); // 选入红色笔
												//pDC->MoveTo(10, 10); pDC->LineTo(100, 100); // 画直线
												//pDC->SelectObject(pOldPen); // 选出红色笔
												//delete &pen; // 删除笔对象
	ReleaseDC(pDC); // 释放DC

}


void myIdentify::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture(); // 设置鼠标捕获
	m_bLButtonDown = TRUE; // 设左鼠标键按下为真
	onDraw = true;
	p0 = point; // 保存直线的起点
	pm = p0; // 让直线的终点等于起点

	CDialog::OnLButtonDown(nFlags, point);
}


void myIdentify::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	onDraw = false;

	ReleaseCapture(); // 释放鼠标捕获
	
	CDialog::OnLButtonUp(nFlags, point);
}


void myIdentify::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	if (onDraw && p0 != point && point.x < 320 && point.y < 320) { // 左鼠标键按下为真（拖动画图）
		CDC* pDC = GetDC(); // 获取设备上下文
		pDC->SelectObject(pLinePen); // 选取灰色点线笔
		//pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
		//pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
									 //pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
									 // 用于动态画封闭图形（如矩形、椭圆等）
		
		pDC->MoveTo(p0); pDC->LineTo(point); // 绘制新直线
		
		ReleaseDC(pDC); // 释放设备上下文
	}
	p0 = point; // 更新老终点

	CDialog::OnMouseMove(nFlags, point);
}

/////////////////////////借用！！！

bool SaveBitmapToFile(CBitmap* bitmap, LPWSTR lpFileName)
{
	HBITMAP hBitmap;    // 为刚才的屏幕位图句柄  
	HDC hDC; //设备描述表    
	int iBits; //当前显示分辨率下每个像素所占字节数    
	WORD wBitCount; //位图中每个像素所占字节数    
	DWORD dwPaletteSize = 0, //定义调色板大小  
		dwBmBitsSize,  //位图中像素字节大小     
		dwDIBSize,   //位图文件大小  
		dwWritten;  //写入文件字节数  
	BITMAP Bitmap; //位图属性结构    
	BITMAPFILEHEADER bmfHdr; //位图文件头结构    
	BITMAPINFOHEADER bi; //位图信息头结构      
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构    
	HANDLE fh,   //定义文件  
		hDib,    //分配内存句柄  
		hPal,   //调色板句柄  
		hOldPal = NULL;

	//计算位图文件每个像素所占字节数    
	hBitmap = (HBITMAP)*bitmap;
	hDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);

	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else if (iBits <= 32)
		wBitCount = 32;

	//计算调色板大小    
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//设置位图信息头结构    
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存    
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	// 处理调色板         
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//   获取该调色板下新的像素值    
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	//恢复调色板       
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	
	//创建位图文件              
	fh = CreateFile(lpFileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	//   设置位图文件头    
	bmfHdr.bfType = 0x4D42;     //   "BM"    
	dwDIBSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)
		+ (DWORD)sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize;

	//   写入位图文件头    
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	//   写入位图文件其余内容    
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize,
		&dwWritten, NULL);

	//清除            
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return TRUE;
}


void myIdentify::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//save bmp
	save();

	CDialog::OnRButtonUp(nFlags, point);
}

void myIdentify::save() 
{
	int tim[32][32] = { 0 };
	std::ofstream os("col.txt");

	int w = 320, h = 320;
	CBitmap bmp;
	CDC *pDC = GetDC();
	CDC mdc;
	mdc.CreateCompatibleDC(pDC); // 创建兼容的内存DC
	bmp.DeleteObject();
	bmp.CreateCompatibleBitmap(pDC, w, h); // 创建兼容CBitmap对象
	CBitmap *pOldBmp = mdc.SelectObject(&bmp); // 将位图选入内存DC
											   // 将指定的屏幕矩形传入DC（中的位图）
	mdc.BitBlt(0, 0, w, h, pDC, 0, 0, SRCCOPY);
	mdc.SelectObject(pOldBmp);

	SaveBitmapToFile(&bmp, L"test.bmp");

	BITMAP bm;
	bmp.GetBitmap(&bm);

	int size = bm.bmHeight * bm.bmWidthBytes;//height*widthBytes; 
	BYTE *lpBits = new BYTE[size];
	bmp.GetBitmapBits(size, lpBits);//得到RGB数据

	int height = bm.bmHeight, width = bm.bmWidth, widthBytes = bm.bmWidthBytes;

	bool *lpGray = new bool[height*width];

	int RR, GG, BB;

	for (int i = 0; i<height; i++)

		for (int j = 0; j<width; j++)

		{

			BB = lpBits[i*widthBytes + j * 4];

			GG = lpBits[i*widthBytes + j * 4 + 1];

			RR = lpBits[i*widthBytes + j * 4 + 2];

			lpGray[i*width + j] = (RR == 255 && GG == 0 && BB == 0);//转化为灰度
			if (RR == 255 && GG == 0 && BB == 0) ++tim[i / 10][j / 10];
			//os << i << ' ' << j << ' ' << R << ' ' << G << ' ' << B << std::endl;
		}


	for (int i = 0; i < 32; ++i) {
		//continue;
		for (int j = 0; j < 32; ++j) os << (tim[i][j] >= 50);
		os << std::endl;
	}

	os.close();

	delete[]lpBits;

	delete[]lpGray;

}
