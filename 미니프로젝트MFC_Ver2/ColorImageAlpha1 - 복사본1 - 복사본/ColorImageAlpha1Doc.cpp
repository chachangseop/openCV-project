
// ColorImageAlpha1Doc.cpp: CColorImageAlpha1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageAlpha1.h"
#endif

#include "ColorImageAlpha1Doc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "CConstant1Dlg.h"
#include "Constant2Dlg.h"
#include "Constant3Dlg.h"
#include "Constant4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageAlpha1Doc

IMPLEMENT_DYNCREATE(CColorImageAlpha1Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageAlpha1Doc, CDocument)
END_MESSAGE_MAP()


// CColorImageAlpha1Doc 생성/소멸

CColorImageAlpha1Doc::CColorImageAlpha1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageAlpha1Doc::~CColorImageAlpha1Doc()
{
}

BOOL CColorImageAlpha1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageAlpha1Doc serialization

void CColorImageAlpha1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageAlpha1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageAlpha1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageAlpha1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageAlpha1Doc 진단

#ifdef _DEBUG
void CColorImageAlpha1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageAlpha1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageAlpha1Doc 명령


BOOL CColorImageAlpha1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// 기존 메모리 해제 
	if (m_inImageR != NULL) {
		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;



	}
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage image;
	image.Load(lpszPathName);
	//중요 입력영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	//메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage 의 객체값   > 메모리
	COLORREF  px;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++){
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}
	return TRUE;
}


unsigned char** CColorImageAlpha1Doc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];
	return memory;

	
}
double** CColorImageAlpha1Doc::OnMalloc2D_double(int h, int w)
{
	double** memory;
	memory = new double * [h];
	for (int i = 0; i < h; i++)
		memory[i] = new double [w];
	return memory;
}

template <typename T>
void CColorImageAlpha1Doc::OnFree2D(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}



void CColorImageAlpha1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);


	CDocument::OnCloseDocument();
}

void CColorImageAlpha1Doc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

}

void CColorImageAlpha1Doc::OnEqualImage()
{

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);



	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}




void CColorImageAlpha1Doc::OnGrayscaleImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
		
		}
	}
}


BOOL CColorImageAlpha1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outH, m_outW, 32);

	unsigned char R, G, B;
	COLORREF px;
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
		{
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);
	

	return TRUE;
}


void CColorImageAlpha1Doc::OnAddbrImage()
{

	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			/*if (m_inImageR[i][k] + value > 255,
				m_inImageG[i][k] + value > 255,
				m_inImageB[i][k] + value > 255)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 255;
			else if (m_inImageR[i][k] + value < 0,
				     m_inImageG[i][k] + value < 0,
				     m_inImageB[i][k] + value < 0)
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = 0;*/
			/*if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;
			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;
			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;
				
			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;
			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;
			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;
				     
			else
				m_outImageR[i][k] = m_inImageR[i][k] + value;
			    m_outImageG[i][k] = m_inImageG[i][k] + value;
			    m_outImageB[i][k] = m_inImageB[i][k] + value;*/
			if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] + value;
			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] + value;
			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] + value;
			
		}
	}
}


void CColorImageAlpha1Doc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);



	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			//HIS 모델값
			//H(색상):0~360
			//s(채도):0.0~1.0
			//I(명도): 0~255
			//RGB-->HSI
			double H, S, I;
			double R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];


			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];
			//채도S 흐리게
			S = S - 0.2;
			if (S < 0)
				S = 0.0;
			//HSI -->RGB
			unsigned char* rgb = HSI2RGB2(H, S, I);
			H = rgb[0]; G = rgb[1]; B = rgb[2];
			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;



			/*m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];*/
		}
	}
}


double* CColorImageAlpha1Doc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
	
}


//unsigned char** CColorImageAlpha1Doc::HSI2RGB(double H, double S, double I)
//{
//	// TODO: 여기에 구현 코드 추가.
//	double R, G, B;
//	unsigned char* RGB = new unsigned char[3];
//	double angle1, angle2, scale;
//
//	if (I == 0.0) { // Black
//		RGB[0] = 0;
//		RGB[1] = 0;
//		RGB[2] = 0;
//		return RGB;
//	}
//
//	if (H <= 0.0) H += 360.0f;
//
//	scale = 3.0 * I;
//	if (H <= 120.0)
//	{
//		angle1 = H * 0.017453293;
//		angle2 = (60.0 - H) * 0.017453293;
//		B = (1.0 - S) / 3.0f;
//		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
//		G = 1.0 - R - B;
//		B *= scale;
//		R *= scale;
//		G *= scale;
//	}
//
//
//	else if ((H > 120.0) && (H <= 240.0)) {
//		H -= 120.0;
//		angle1 = H * 0.017453293;
//
//		angle2 = (60.0 - H) * 0.017453293;
//		R = (1.0 - S) / 3.0;
//		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
//		B = 1.0 - R - G;
//		R *= scale;
//		G *= scale;
//		B *= scale;
//	}
//	else {
//		H -= 240.0;
//		angle1 = H * 0.017453293;
//		angle2 = (60.0 - H) * 0.017453293;
//		G = (1.0f - S) / 3.0;
//		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
//		R = 1.0 - G - B;
//
//		R *= scale;
//		G *= scale;
//		B *= scale;
//	}
//
//	RGB[0] = (unsigned char)R;
//	RGB[1] = (unsigned char)G;
//	RGB[2] = (unsigned char)B;
//	return RGB;
//}

unsigned char* CColorImageAlpha1Doc::HSI2RGB2(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}



void CColorImageAlpha1Doc::OnPickorangeImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);



	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			//HIS 모델값
			//H(색상):0~360
			//s(채도):0.0~1.0
			//I(명도): 0~255
			//RGB-->HSI
			double H, S, I;
			double R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];


			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];
			

			// 오랜지 추출 (H:8~20)
			if (8 <= H && H <= 20)
			{


				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else
			{
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;

			}
		}
	}
}




void CColorImageAlpha1Doc::OnReversImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double avg;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;

		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_outImageR[i][k] >= 128)
			    m_outImageR[i][k] =255;
			if (m_outImageG[i][k] >= 128)
				m_outImageG[i][k] = 255;
			if (m_outImageB[i][k] >= 128)
				m_outImageB[i][k] = 255;
			
		}
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_outImageR[i][k] < 128)
				m_outImageR[i][k] = 0;
			if (m_outImageG[i][k] < 128)
				m_outImageG[i][k] = 0;
			if (m_outImageB[i][k] < 128)
				m_outImageB[i][k] = 0;



		}
	}
}


void CColorImageAlpha1Doc::OnRrreversImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);



	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] =255 - m_inImageR[i][k];
			m_outImageG[i][k] =255 - m_inImageG[i][k];
			m_outImageB[i][k] =255 - m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnAndImage()
{

	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	unsigned char value = dlg.m_constant;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k] & value;
			m_outImageG[i][k] = m_inImageG[i][k] & value;
			m_outImageB[i][k] = m_inImageB[i][k] & value;
		}
	}
}


void CColorImageAlpha1Doc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return
		//기존 메모리 해지
		OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double value = dlg.m_constant1;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = pow((double)m_inImageR[i][k] / 255, value) * 255;
			m_outImageG[i][k] = pow((double)m_inImageG[i][k] / 255, value) * 255;
			m_outImageB[i][k] = pow((double)m_inImageB[i][k] / 255, value) * 255;

		}
	}
}


void CColorImageAlpha1Doc::OnZoomoImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		int scale = dlg.m_constant;
		//기존 메모리 해지
		OnFreeOutImage();
		//출력 이미지 크기
		m_outH = (int)(m_inH / scale);
		m_outW = (int)(m_inW / scale);
		//메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// 출력 이미지 영상 처리 <핵심 알고리즘>

		unsigned char value = dlg.m_constant;
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				m_outImageR[i][k] = m_inImageR[(int)(i * scale)][(int)(k * scale)];
				m_outImageG[i][k] = m_inImageG[(int)(i * scale)][(int)(k * scale)];
				m_outImageB[i][k] = m_inImageB[(int)(i * scale)][(int)(k * scale)];

			}
		}
	}
}


void CColorImageAlpha1Doc::OnZoomiImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		int scale = dlg.m_constant;
		//기존 메모리 해지
		OnFreeOutImage();
		//출력 이미지 크기
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		//메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// 출력 이미지 영상 처리 <핵심 알고리즘>

		unsigned char value = dlg.m_constant;
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)(k / scale)];
				m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)(k / scale)];
				m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)(k / scale)];

			}
		}
	}
}


void CColorImageAlpha1Doc::OnRotateImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant4Dlg dlg;
	if (dlg.DoModal() == IDOK) {
		
		//기존 메모리 해지
		OnFreeOutImage();
		//출력 이미지 크기
		m_outH = m_inH;
		m_outW = m_inW;
		//메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int degree = dlg.m_constant4;
		double radian = -degree * 3.141592 / 180.0;
		int cx = m_inH / 2;
		int cy = m_inW / 2;
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				int xd = i;
				int yd = k;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				    m_outImageG[xd][yd] = m_inImageG[xs][ys];
				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				    m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}


void CColorImageAlpha1Doc::OnMirrorlrImage()
{

	// TODO: 여기에 구현 코드 추가.
	
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int mk = m_inW - 1 - k;
			m_outImageR[i][k] = m_inImageR[i][mk];
			m_outImageG[i][k] = m_inImageG[i][mk];
			m_outImageB[i][k] = m_inImageB[i][mk];
		}
	}
}


void CColorImageAlpha1Doc::OnMirrorhlImage()
{
	// TODO: 여기에 구현 코드 추가.

	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int mi = m_inH - 1 - i;
			m_outImageR[i][k] = m_inImageR[mi][k];
			m_outImageG[i][k] = m_inImageG[mi][k];
			m_outImageB[i][k] = m_inImageB[mi][k];
		}
	}
}


void CColorImageAlpha1Doc::OnTransImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() == IDOK) {
		double tx = dlg.m_constant3;
		CConstant2Dlg dlg;
		if (dlg.DoModal() == IDOK) {
			double ty = dlg.m_constant2;
			//기존 메모리 해지
			OnFreeOutImage();
			//출력 이미지 크기
			m_outH = m_inH;
			m_outW = m_inW;
			//메모리 할당
			m_outImageR = OnMalloc2D(m_outH, m_outW);
			m_outImageG = OnMalloc2D(m_outH, m_outW);
			m_outImageB = OnMalloc2D(m_outH, m_outW);

			// 출력 이미지 영상 처리 <핵심 알고리즘>
			for (int i = 0; i < m_inH - tx; i++) {
				for (int k = 0; k < m_inW - ty; k++) {
					m_outImageR[(int)(i + tx)][(int)(k + ty)] = m_inImageR[i][k];
					m_outImageG[(int)(i + tx)][(int)(k + ty)] = m_inImageG[i][k];
					m_outImageB[(int)(i + tx)][(int)(k + ty)] = m_inImageB[i][k];

				}
			}
		}
	}
}


void CColorImageAlpha1Doc::OnHistostImage()
{

	// TODO: 여기에 구현 코드 추가.

	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int high[3], low[3];
	high[0] = m_inImageR[0][0];
	high[1] = m_inImageG[0][0];
	high[2] = m_inImageB[0][0];
	low[0] = m_inImageR[0][0];
	low[1] = m_inImageG[0][0];
	low[2] = m_inImageB[0][0];
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] < low[0])
				low[0] = m_inImageR[i][k];
			if (m_inImageG[i][k] < low[1])
				low[1] = m_inImageG[i][k];
			if (m_inImageB[i][k] < low[2])
				low[2] = m_inImageB[i][k];


			if (m_inImageR[i][k] > high[0])
				high[0] = m_inImageR[i][k];
			if (m_inImageG[i][k] > high[1])
				high[1] = m_inImageG[i][k];
			if (m_inImageB[i][k] > high[2])
				high[2] = m_inImageB[i][k];
		}
	}
	int old[3], neew[3];
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			old[0] = m_inImageR[i][k];
			old[1] = m_inImageG[i][k];
			old[2] = m_inImageB[i][k];
			neew[0] = (int)((double)(old[0] - low[0]) / (double)(high[0] - low[0]) * 255.0);
			if (neew[0] > 255)
				neew[0] = 255;
			if (neew[0] < 0)
				neew[0] = 0;
			m_outImageR[i][k] = neew[0];
			neew[1] = (int)((double)(old[1] - low[1]) / (double)(high[1] - low[1]) * 255.0);
			if (neew[1] > 255)
				neew[1] = 255;
			if (neew[1] < 0)
				neew[1] = 0;
			m_outImageG[i][k] = neew[1];
			neew[2] = (int)((double)(old[2] - low[2]) / (double)(high[2] - low[2]) * 255.0);
			if (neew[2] > 255)
				neew[2] = 255;
			if (neew[2] < 0)
				neew[2] = 0;
			m_outImageB[i][k] = neew[2];
		}
	}
}


void CColorImageAlpha1Doc::OnAndinImage()
{
	// TODO: 여기에 구현 코드 추가.

	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int high[3], low[3];
	high[0] = m_inImageR[0][0];
	high[1] = m_inImageG[0][0];
	high[2] = m_inImageB[0][0];
	low[0] = m_inImageR[0][0];
	low[1] = m_inImageG[0][0];
	low[2] = m_inImageB[0][0];
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] < low[0])
				low[0] = m_inImageR[i][k];
			if (m_inImageG[i][k] < low[1])
				low[1] = m_inImageG[i][k];
			if (m_inImageB[i][k] < low[2])
				low[2] = m_inImageB[i][k];


			if (m_inImageR[i][k] > high[0])
				high[0] = m_inImageR[i][k];
			if (m_inImageG[i][k] > high[1])
				high[1] = m_inImageG[i][k];
			if (m_inImageB[i][k] > high[2])
				high[2] = m_inImageB[i][k];
		}
	}
	high[0] -= 50, high[1] -= 50, high[2] -= 50;
	low[0] += 50, low[1] += 50, low[2] += 50;
	int old[3], neew[3];
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			old[0] = m_inImageR[i][k];
			old[1] = m_inImageG[i][k];
			old[2] = m_inImageB[i][k];
			neew[0] = (int)((double)(old[0] - low[0]) / (double)(high[0] - low[0]) * 255.0);
			if (neew[0] > 255)
				neew[0] = 255;
			if (neew[0] < 0)
				neew[0] = 0;
			m_outImageR[i][k] = neew[0];
			neew[1] = (int)((double)(old[1] - low[1]) / (double)(high[1] - low[1]) * 255.0);
			if (neew[1] > 255)
				neew[1] = 255;
			if (neew[1] < 0)
				neew[1] = 0;
			m_outImageG[i][k] = neew[1];
			neew[2] = (int)((double)(old[2] - low[2]) / (double)(high[2] - low[2]) * 255.0);
			if (neew[2] > 255)
				neew[2] = 255;
			if (neew[2] < 0)
				neew[2] = 0;
			m_outImageB[i][k] = neew[2];
		}
	}
}


void CColorImageAlpha1Doc::OnHistoeqImage()
{
	// TODO: 여기에 구현 코드 추가.

	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int histoR[256] = { 0 };//{0} 나머지 값도 0으로 초기화 
	int histoG[256] = { 0 };//{0} 나머지 값도 0으로 초기화 
	int histoB[256] = { 0 };//{0} 나머지 값도 0으로 초기화 

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	}
	//2단계 : 히스토그램 누적합 sumHisto[i]
	int sumHistoR[256] = { 0 };//{0} 나머지 값도 0으로 초기화 
	int sumHistoG[256] = { 0 };
	int sumHistoB[256] = { 0 };
	sumHistoR[0] = histoR[0];
	sumHistoG[0] = histoG[0];
	sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++)
	{
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];

	}

	//3단계 : 정규화된 히스토그램 생성 normalHisto=sumHisto*(1.0/(inH*inW))*255.0;
	double normalHistoR[256] = { 1.0 };
	double normalHistoG[256] = { 1.0 };
	double normalHistoB[256] = { 1.0 };

	for (int i = 0; i < 256; i++)
	{
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;


	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = (unsigned char)normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalHistoB[m_inImageB[i][k]];
		}
	}
}


void CColorImageAlpha1Doc::OnAmbossImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,0.0,0.0},
		{ 0.0,0.0,0.0},
		{ 0.0,0.0,1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}
	//후처리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}





void CColorImageAlpha1Doc::OnEmbossHsi()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,0.0,0.0},
		{ 0.0,0.0,0.0},
		{ 0.0,0.0,1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	///////// RGB 모델 --> HSI 모델 ///////////////

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}
	//후처리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			tmpInImageI[i][k] += 127.0;
		}



	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}




	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);

	OnFree2D(tmpInImageH, m_inH + 2);
	OnFree2D(tmpInImageS, m_inH + 2);
	OnFree2D(tmpInImageI, m_inH + 2);



	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnBlurImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}
	
	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharpnImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 0. ,-1. , 0.},
		{ -1., 5., -1.},
		{ 0. ,-1. , 0.}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}
	//후처리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharphImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);


	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ -1. / 9,-1. / 9,-1. / 9},
		{ -1. / 9, 8. / 9,-1. / 9},
		{ -1. / 9,-1. / 9,-1. / 9}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}
	


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharplImage()
{
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {

		// TODO: 여기에 구현 코드 추가.
		//기존 메모리 해지
		OnFreeOutImage();
		//출력 이미지 크기
		m_outH = m_inH;
		m_outW = m_inW;
		//메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		const int MSIZE = 3;
		double mask[MSIZE][MSIZE] = {//엠보싱 마스크
			{ 1. / 9,1. / 9,1. / 9},
			{ 1. / 9,1. / 9,1. / 9},
			{ 1. / 9,1. / 9,1. / 9}
		};
		//임시 메모리 할당
		double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
		tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
		tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
		tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
		tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
		tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
		tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

		//임시 메모리 초기화
		for (int i = 0; i < m_inH + 2; i++) {
			for (int k = 0; k < m_inW + 2; k++) {
				tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
			}
		}

		//입력메모리 임시입력메모리
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {

				tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
				tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
				tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
			}


		//회선연산
		double S;
		double hx;
		int val = (int)dlg.m_constant;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0;
				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageR[i + m][k + n] * mask[m][n];
				tmpOutImageR[i][k] = S;
				hx = val * m_inImageR[i][k] - S * (val - 1);
				tmpOutImageR[i][k] = hx;
				S = 0;
				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageG[i + m][k + n] * mask[m][n];
				tmpOutImageG[i][k] = S;
				hx = val * m_inImageG[i][k] - S * (val - 1);
				tmpOutImageG[i][k] = hx;
				S = 0;
				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageB[i + m][k + n] * mask[m][n];
				tmpOutImageB[i][k] = S;
				hx = val * m_inImageB[i][k] - S * (val - 1);
				tmpOutImageB[i][k] = hx;

			}
		}

		//임시 출력 영상--> 출력영상
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
			}
		}

		//임시 메모리 해제
		OnFree2D(tmpInImageR, m_inH + 2);
		OnFree2D(tmpInImageG, m_inH + 2);
		OnFree2D(tmpInImageB, m_inH + 2);
		OnFree2D(tmpOutImageR, m_outH);
		OnFree2D(tmpOutImageG, m_outH);
		OnFree2D(tmpOutImageB, m_outH);
	}
}

double CColorImageAlpha1Doc::OndoublePlus(double x)
{
	if (x >= 0)
		return x;
	else
		return -x;
	return 0.0;
}

void CColorImageAlpha1Doc::OnUshaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					if (OndoublePlus(tmpInImageR[i + 1][k + 1] - tmpInImageR[i + m][k + n] >= S))
						//블록의 가운데 값 빼기 주변 픽셀 값의 절대 값
						//fabs 라이브러리에 있는 절대값함수
						S = OndoublePlus(tmpInImageR[i + 1][k + 1] - tmpInImageR[i + m][k + n]);
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					if (OndoublePlus(tmpInImageG[i + 1][k + 1] - tmpInImageG[i + m][k + n] >= S))
						//블록의 가운데 값 빼기 주변 픽셀 값의 절대 값
						//fabs 라이브러리에 있는 절대값함수
						S = OndoublePlus(tmpInImageG[i + 1][k + 1] - tmpInImageG[i + m][k + n]);
			tmpOutImageG[i][k] = S;

			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					if (OndoublePlus(tmpInImageB[i + 1][k + 1] - tmpInImageB[i + m][k + n] >= S))
						//블록의 가운데 값 빼기 주변 픽셀 값의 절대 값
						//fabs 라이브러리에 있는 절대값함수
						S = OndoublePlus(tmpInImageB[i + 1][k + 1] - tmpInImageB[i + m][k + n]);
			tmpOutImageB[i][k] = S;

		}
	}
	//후처리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}




void CColorImageAlpha1Doc::OnChaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 4;
	double mask[MSIZE] = {//엠보싱 마스크
		0.0,1.0,2.0,3.0
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			mask[0] = OndoublePlus(tmpInImageR[i][k] - tmpInImageR[i + 2][k + 2]);
			mask[1] = OndoublePlus(tmpInImageR[i][k + 1] - tmpInImageR[i + 2][k + 1]);
			mask[2] = OndoublePlus(tmpInImageR[i][k + 2] - tmpInImageR[i + 2][k]);
			mask[3] = OndoublePlus(tmpInImageR[i + 1][k + 2] - tmpInImageR[i + 1][k]);
			for (int m = 0; m < MSIZE; m++) {
				if (mask[m] >= S)S = mask[m];
			}
			tmpOutImageR[i][k] = S;

			S = 0;
			mask[0] = OndoublePlus(tmpInImageG[i][k] - tmpInImageG[i + 2][k + 2]);
			mask[1] = OndoublePlus(tmpInImageG[i][k + 1] - tmpInImageG[i + 2][k + 1]);
			mask[2] = OndoublePlus(tmpInImageG[i][k + 2] - tmpInImageG[i + 2][k]);
			mask[3] = OndoublePlus(tmpInImageG[i + 1][k + 2] - tmpInImageG[i + 1][k]);
			for (int m = 0; m < MSIZE; m++) {
				if (mask[m] >= S)S = mask[m];
			}
			tmpOutImageG[i][k] = S;

			S = 0;
			mask[0] = OndoublePlus(tmpInImageB[i][k] - tmpInImageB[i + 2][k + 2]);
			mask[1] = OndoublePlus(tmpInImageB[i][k + 1] - tmpInImageB[i + 2][k + 1]);
			mask[2] = OndoublePlus(tmpInImageB[i][k + 2] - tmpInImageB[i + 2][k]);
			mask[3] = OndoublePlus(tmpInImageB[i + 1][k + 2] - tmpInImageB[i + 1][k]);
			for (int m = 0; m < MSIZE; m++) {
				if (mask[m] >= S)S = mask[m];
			}
			tmpOutImageB[i][k] = S;

		}
	}
	//후처리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnRobertsaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,0.0,0.0},
		{ 0.0,1.0,0.0},
		{ 0.0,0.0,0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}
	


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}

void CColorImageAlpha1Doc::OnRobertsbImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 0.0,0.0,-1.0},
		{ 0.0,1.0, 0.0},
		{ 0.0,0.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnRobertsabImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,0.0,-1.0},
		{ 0.0,2.0, 0.0},
		{ 0.0,0.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSobelaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,-2.0,-1.0},
	    { 0.0, 0.0, 0.0},
	    { 1.0, 2.0, 1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSobelbImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 1.0,0.0,-1.0},
		{ 2.0,0.0,-2.0},
		{ 1.0,0.0,-1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSobelabImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 0.0,-2.0,-2.0},
		{ 2.0, 0.0,-2.0},
		{ 2.0, 2.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnPrewittaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,-1.0,-1.0},
	    { 0.0, 0.0, 0.0},
	    { 1.0, 1.0, 1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnPrewittbImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnPrewittabImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 0.0,-1.0,-2.0},
		{ 1.0, 0.0,-1.0},
		{ 2.0, 1.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnLaplamaImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 0.0,-1.0, 0.0},
		{-1.0, 4.0,-1.0},
		{ 0.0,-1.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnLaplambImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{ 1.0, 1.0,1.0},
		{ 1.0,-8.0,1.0},
		{ 1.0, 1.0,1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnLaplamabImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
		{-1.0,-1.0,-1.0},
		{-1.0, 8.0,-1.0},
		{-1.0,-1.0,-1.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnLogImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 5;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
	   { 0.0, 0.0,-1.0, 0.0, 0.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   {-1.0,-2.0,16.0,-2.0,-1.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   { 0.0, 0.0,-1.0, 0.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	tmpInImageG = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	tmpInImageB = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 4; i++) {
		for (int k = 0; k < m_inW + 4; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 4);
	OnFree2D(tmpInImageG, m_inH + 4);
	OnFree2D(tmpInImageB, m_inH + 4);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnDogImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해지
	OnFreeOutImage();
	//출력 이미지 크기
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int MSIZE = 7;
	double mask[MSIZE][MSIZE] = {//엠보싱 마스크
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0,16.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0}
	};
	//임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 6, m_inW + 6);
	tmpInImageG = OnMalloc2D_double(m_inH + 6, m_inW + 6);
	tmpInImageB = OnMalloc2D_double(m_inH + 6, m_inW + 6);
	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	//임시 메모리 초기화
	for (int i = 0; i < m_inH + 6; i++) {
		for (int k = 0; k < m_inW + 6; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	//입력메모리 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {

			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}


	//회선연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;
			S = 0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;

		}
	}



	//임시 출력 영상--> 출력영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	//임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 6);
	OnFree2D(tmpInImageG, m_inH + 6);
	OnFree2D(tmpInImageB, m_inH + 6);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}
