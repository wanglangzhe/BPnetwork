// myIdentify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "id.h"
#include "myIdentify.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>


// myIdentify �Ի���

IMPLEMENT_DYNAMIC(myIdentify, CDialog)

myIdentify::myIdentify(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_IDENTIFY, pParent)
{
	
}

BOOL myIdentify::OnInitDialog()
{
	//MessageBox(L"init ! ");

	SetCursor(LoadCursor(NULL, IDC_CROSS)); // �������Ϊʮ��

	p0 = CPoint(-1, -1);
	pm = CPoint(0, 0);
	onDraw = false;

	m_bLButtonDown = FALSE; // ������������Ϊ��
	m_bErase = FALSE; // ����Ҫ����Ϊ��


	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // ������ɫ���߱�
	pLinePen = new CPen(PS_SOLID, 55, RGB(255, 0, 0)); // ������ɫ��ֱ�߱�

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


	CDialog::OnOK();//��һ�����رմ���  
	DestroyWindow();//�ڶ���,�ͷ���Դ
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


// myIdentify ��Ϣ�������


void myIdentify::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CDC* pDC = &dc; // ��ȡDC
	CPen pen, *pOldPen; // ����ʶ����ָ��
						// ����10��λ�����ɫʵ�ıʣ�
	pen.CreatePen(PS_SOLID, 20, RGB(0, 255, 0));
	pOldPen = pDC->SelectObject(&pen); // ѡ����ɫ��
	pDC->Rectangle(0, 0, 320, 320); // ������
	pDC->SelectObject(pOldPen); // ѡ����ɫ��
	pen.DeleteObject(); // ɾ����ɫ������
						// ���������ؿ�ĺ�ɫ���߱ʣ�
												//pen.CreatePen(PS_DASH, 0, RGB(255, 0, 0));
												//pOldPen = pDC->SelectObject(&pen); // ѡ���ɫ��
												//pDC->MoveTo(10, 10); pDC->LineTo(100, 100); // ��ֱ��
												//pDC->SelectObject(pOldPen); // ѡ����ɫ��
												//delete &pen; // ɾ���ʶ���
	ReleaseDC(pDC); // �ͷ�DC

}


void myIdentify::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture(); // ������겶��
	m_bLButtonDown = TRUE; // ������������Ϊ��
	onDraw = true;
	p0 = point; // ����ֱ�ߵ����
	pm = p0; // ��ֱ�ߵ��յ�������

	CDialog::OnLButtonDown(nFlags, point);
}


void myIdentify::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	onDraw = false;

	ReleaseCapture(); // �ͷ���겶��
	
	CDialog::OnLButtonUp(nFlags, point);
}


void myIdentify::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	if (onDraw && p0 != point && point.x < 320 && point.y < 320) { // ����������Ϊ�棨�϶���ͼ��
		CDC* pDC = GetDC(); // ��ȡ�豸������
		pDC->SelectObject(pLinePen); // ѡȡ��ɫ���߱�
		//pDC->SetROP2(R2_XORPEN); // ����Ϊ����ͼ��ʽ
		//pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ
									 //pDC->SelectStockObject(NULL_BRUSH); // ѡ���ˢ
									 // ���ڶ�̬�����ͼ�Σ�����Ρ���Բ�ȣ�
		
		pDC->MoveTo(p0); pDC->LineTo(point); // ������ֱ��
		
		ReleaseDC(pDC); // �ͷ��豸������
	}
	p0 = point; // �������յ�

	CDialog::OnMouseMove(nFlags, point);
}

/////////////////////////���ã�����

bool SaveBitmapToFile(CBitmap* bitmap, LPWSTR lpFileName)
{
	HBITMAP hBitmap;    // Ϊ�ղŵ���Ļλͼ���  
	HDC hDC; //�豸������    
	int iBits; //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���    
	WORD wBitCount; //λͼ��ÿ��������ռ�ֽ���    
	DWORD dwPaletteSize = 0, //�����ɫ���С  
		dwBmBitsSize,  //λͼ�������ֽڴ�С     
		dwDIBSize,   //λͼ�ļ���С  
		dwWritten;  //д���ļ��ֽ���  
	BITMAP Bitmap; //λͼ���Խṹ    
	BITMAPFILEHEADER bmfHdr; //λͼ�ļ�ͷ�ṹ    
	BITMAPINFOHEADER bi; //λͼ��Ϣͷ�ṹ      
	LPBITMAPINFOHEADER lpbi; //ָ��λͼ��Ϣͷ�ṹ    
	HANDLE fh,   //�����ļ�  
		hDib,    //�����ڴ���  
		hPal,   //��ɫ����  
		hOldPal = NULL;

	//����λͼ�ļ�ÿ��������ռ�ֽ���    
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

	//�����ɫ���С    
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ    
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

	//Ϊλͼ���ݷ����ڴ�    
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	// �����ɫ��         
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//   ��ȡ�õ�ɫ�����µ�����ֵ    
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	//�ָ���ɫ��       
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	
	//����λͼ�ļ�              
	fh = CreateFile(lpFileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	//   ����λͼ�ļ�ͷ    
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

	//   д��λͼ�ļ�ͷ    
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	//   д��λͼ�ļ���������    
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize,
		&dwWritten, NULL);

	//���            
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return TRUE;
}


void myIdentify::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	mdc.CreateCompatibleDC(pDC); // �������ݵ��ڴ�DC
	bmp.DeleteObject();
	bmp.CreateCompatibleBitmap(pDC, w, h); // ��������CBitmap����
	CBitmap *pOldBmp = mdc.SelectObject(&bmp); // ��λͼѡ���ڴ�DC
											   // ��ָ������Ļ���δ���DC���е�λͼ��
	mdc.BitBlt(0, 0, w, h, pDC, 0, 0, SRCCOPY);
	mdc.SelectObject(pOldBmp);

	SaveBitmapToFile(&bmp, L"test.bmp");

	BITMAP bm;
	bmp.GetBitmap(&bm);

	int size = bm.bmHeight * bm.bmWidthBytes;//height*widthBytes; 
	BYTE *lpBits = new BYTE[size];
	bmp.GetBitmapBits(size, lpBits);//�õ�RGB����

	int height = bm.bmHeight, width = bm.bmWidth, widthBytes = bm.bmWidthBytes;

	bool *lpGray = new bool[height*width];

	int RR, GG, BB;

	for (int i = 0; i<height; i++)

		for (int j = 0; j<width; j++)

		{

			BB = lpBits[i*widthBytes + j * 4];

			GG = lpBits[i*widthBytes + j * 4 + 1];

			RR = lpBits[i*widthBytes + j * 4 + 2];

			lpGray[i*width + j] = (RR == 255 && GG == 0 && BB == 0);//ת��Ϊ�Ҷ�
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
