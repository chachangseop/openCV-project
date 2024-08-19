
// ColorImageAlpha1View.cpp: CColorImageAlpha1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageAlpha1.h"
#endif

#include "ColorImageAlpha1Doc.h"
#include "ColorImageAlpha1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageAlpha1View

IMPLEMENT_DYNCREATE(CColorImageAlpha1View, CView)

BEGIN_MESSAGE_MAP(CColorImageAlpha1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImageAlpha1View::OnEqualImage)
	ON_COMMAND(IDM_GRAYSCALE_IMAGE, &CColorImageAlpha1View::OnGrayscaleImage)
	ON_COMMAND(IDM_ADDBR_IMAGE, &CColorImageAlpha1View::OnAddbrImage)
	ON_COMMAND(IDM_CHANGE_SATUR, &CColorImageAlpha1View::OnChangeSatur)
	ON_COMMAND(IDM_PICKORANGE_IMAGE, &CColorImageAlpha1View::OnPickorangeImage)
	ON_COMMAND(IDM_REVERS_IMAGE, &CColorImageAlpha1View::OnReversImage)
	ON_COMMAND(IDM_RRREVERS_IMAGE, &CColorImageAlpha1View::OnRrreversImage)
	ON_COMMAND(IDM_AND_IMAGE, &CColorImageAlpha1View::OnAndImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CColorImageAlpha1View::OnGammaImage)
	ON_COMMAND(IDM_ZOOMO_IMAGE, &CColorImageAlpha1View::OnZoomoImage)
	ON_COMMAND(IDM_ZOOMI_IMAGE, &CColorImageAlpha1View::OnZoomiImage)
	ON_COMMAND(IDM_ROTATE_IMAGE, &CColorImageAlpha1View::OnRotateImage)
	ON_COMMAND(IDM_MIRRORLR_IMAGE, &CColorImageAlpha1View::OnMirrorlrImage)
	ON_COMMAND(IDM_MIRRORHL_IMAGE, &CColorImageAlpha1View::OnMirrorhlImage)
	ON_COMMAND(IDM_TRANS_IMAGE, &CColorImageAlpha1View::OnTransImage)
	ON_COMMAND(IDM_HISTOST_IMAGE, &CColorImageAlpha1View::OnHistostImage)
	ON_COMMAND(IDM_ANDIN_IMAGE, &CColorImageAlpha1View::OnAndinImage)
	ON_COMMAND(IDM_HISTOEQ_IMAGE, &CColorImageAlpha1View::OnHistoeqImage)
	ON_COMMAND(IDM_AMBOSS_IMAGE, &CColorImageAlpha1View::OnAmbossImage)
	ON_COMMAND(IDM_EMBOSS_HSI, &CColorImageAlpha1View::OnEmbossHsi)
	ON_COMMAND(IDM_BLUR_IMAGE, &CColorImageAlpha1View::OnBlurImage)
	ON_COMMAND(IDM_SHARPN_IMAGE, &CColorImageAlpha1View::OnSharpnImage)
	ON_COMMAND(IDM_SHARPH_IMAGE, &CColorImageAlpha1View::OnSharphImage)
	ON_COMMAND(IDM_SHARPL_IMAGE, &CColorImageAlpha1View::OnSharplImage)
	ON_COMMAND(IDM_USHA_IMAGE, &CColorImageAlpha1View::OnUshaImage)
	ON_COMMAND(IDM_CHA_IMAGE, &CColorImageAlpha1View::OnChaImage)
	ON_COMMAND(IDM_ROBERTSA_IMAGE, &CColorImageAlpha1View::OnRobertsaImage)
	ON_COMMAND(IDM_ROBERTSB_IMAGE, &CColorImageAlpha1View::OnRobertsbImage)
	ON_COMMAND(IDM_ROBERTSAB_IMAGE, &CColorImageAlpha1View::OnRobertsabImage)
	ON_COMMAND(IDM_SOBELA_IMAGE, &CColorImageAlpha1View::OnSobelaImage)
	ON_COMMAND(IDM_SOBELB_IMAGE, &CColorImageAlpha1View::OnSobelbImage)
	ON_COMMAND(IDM_SOBELAB_IMAGE, &CColorImageAlpha1View::OnSobelabImage)
	ON_COMMAND(IDM_PREWITTA_IMAGE, &CColorImageAlpha1View::OnPrewittaImage)
	ON_COMMAND(IDM_PREWITTB_IMAGE, &CColorImageAlpha1View::OnPrewittbImage)
	ON_COMMAND(IDM_PREWITTAB_IMAGE, &CColorImageAlpha1View::OnPrewittabImage)
	ON_COMMAND(IDM_LAPLAMA_IMAGE, &CColorImageAlpha1View::OnLaplamaImage)
	ON_COMMAND(IDM_LAPLAMB_IMAGE, &CColorImageAlpha1View::OnLaplambImage)
	ON_COMMAND(IDM_LAPLAMAB_IMAGE, &CColorImageAlpha1View::OnLaplamabImage)
	ON_COMMAND(IDM_LOG_IMAGE, &CColorImageAlpha1View::OnLogImage)
	ON_COMMAND(IDM_DOG_IMAGE, &CColorImageAlpha1View::OnDogImage)
END_MESSAGE_MAP()

// CColorImageAlpha1View 생성/소멸

CColorImageAlpha1View::CColorImageAlpha1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageAlpha1View::~CColorImageAlpha1View()
{
}

BOOL CColorImageAlpha1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageAlpha1View 그리기

void CColorImageAlpha1View::OnDraw(CDC* pDC)
{
	//CColorImageAlpha1Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//int R, G, B;
	//for (int i = 0; i < pDoc->m_inH; i++)
	//	for (int k = 0; k < pDoc->m_inW; k++)
	//	{
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
	//	}
	//for (int i = 0; i < pDoc->m_outH; i++)
	//	for (int k = 0; k < pDoc->m_outW; k++)
	//	{
	//		R = pDoc->m_outImageR[i][k];
	//		G = pDoc->m_outImageG[i][k];
	//		B = pDoc->m_outImageB[i][k];
	//		pDC->SetPixel(pDoc->m_inW + k + 5, i + 5, RGB(R, G, B));
	//	}
	






	// ///////////////////
	// /*** 성능 계선 ***/
	///////////////////
	///////////////////
	///* ** 더블 버퍼링 ***/
	///////////////////
	//CColorImageAlpha1Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	///////////////////////
	///// 성능 개선을 위한 더블 버퍼링 
	//////////////////////
	//int i, k;
	//unsigned char R, G, B;
	//// 메모리 DC 선언
	//CDC memDC;
	//CBitmap* pOldBitmap, bitmap;

	//// 화면 DC와 호환되는 메모리 DC 객체를 생성
	//memDC.CreateCompatibleDC(pDC);

	//// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	//bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	//pOldBitmap = memDC.SelectObject(&bitmap);
	//memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	//// 메모리 DC에 그리기
	//for (i = 0; i < pDoc->m_inH; i++) {
	//	for (k = 0; k < pDoc->m_inW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		memDC.SetPixel(k, i, RGB(R, G, B));
	//	}
	//}
	//// 메모리 DC를 화면 DC에 고속 복사
	//pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	//memDC.SelectObject(pOldBitmap);
	//memDC.DeleteDC();
	//bitmap.DeleteObject();

	/////////////////////

	//// 화면 DC와 호환되는 메모리 DC 객체를 생성
	//memDC.CreateCompatibleDC(pDC);

	//// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	//bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	//pOldBitmap = memDC.SelectObject(&bitmap);
	//memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	//// 메모리 DC에 그리기
	//for (i = 0; i < pDoc->m_outH; i++) {
	//	for (k = 0; k < pDoc->m_outW; k++) {
	//		R = pDoc->m_outImageR[i][k];
	//		G = pDoc->m_outImageG[i][k];
	//		B = pDoc->m_outImageB[i][k];
	//		memDC.SetPixel(k, i, RGB(R, G, B));
	//	}
	//}
	//// 메모리 DC를 화면 DC에 고속 복사
	//pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	//memDC.SelectObject(pOldBitmap);
	//memDC.DeleteDC();
	//bitmap.DeleteObject();







	// ///////////////////
	/// ** 성능 계선  크기**
	///////////////////
	///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800; //필요시 실 모니터 또는 화면 해상도 에 다라 조절
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; //기본
	if (inH > MAXSIZE || inW > MAXSIZE) {
		//hop으로 계산
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);
		
		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}



	// 메모리 DC에 그리기

	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i*hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; //기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		//hop으로 계산
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}





	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	
}


// CColorImageAlpha1View 인쇄

BOOL CColorImageAlpha1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageAlpha1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageAlpha1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageAlpha1View 진단

#ifdef _DEBUG
void CColorImageAlpha1View::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageAlpha1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageAlpha1Doc* CColorImageAlpha1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageAlpha1Doc)));
	return (CColorImageAlpha1Doc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageAlpha1View 메시지 처리기


void CColorImageAlpha1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnGrayscaleImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayscaleImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAddbrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddbrImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnChangeSatur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSatur();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnPickorangeImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPickorangeImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnReversImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReversImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRrreversImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRrreversImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnZoomoImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomoImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnZoomiImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomiImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRotateImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotateImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnMirrorlrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorlrImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnMirrorhlImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorhlImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnTransImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnTransImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnHistostImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistostImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAndinImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndinImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnHistoeqImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoeqImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAmbossImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAmbossImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEmbossHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsi();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnBlurImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharpnImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpnImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharphImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharphImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharplImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharplImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnUshaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUshaImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnChaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChaImage();
	Invalidate(TRUE);
}



void CColorImageAlpha1View::OnRobertsaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobertsaImage();
	Invalidate(TRUE);
}

void CColorImageAlpha1View::OnRobertsbImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobertsbImage();
	Invalidate(TRUE);
}

void CColorImageAlpha1View::OnRobertsabImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobertsabImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSobelaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSobelaImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSobelbImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSobelbImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSobelabImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSobelabImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnPrewittaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPrewittaImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnPrewittbImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPrewittbImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnPrewittabImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPrewittabImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnLaplamaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplamaImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnLaplambImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplambImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnLaplamabImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplamabImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLogImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDogImage();
	Invalidate(TRUE);
}
