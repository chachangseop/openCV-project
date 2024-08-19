
// ColorImageAlpha1View.h: CColorImageAlpha1View 클래스의 인터페이스
//

#pragma once


class CColorImageAlpha1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageAlpha1View() noexcept;
	DECLARE_DYNCREATE(CColorImageAlpha1View)

// 특성입니다.
public:
	CColorImageAlpha1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CColorImageAlpha1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayscaleImage();
	afx_msg void OnAddbrImage();
	afx_msg void OnChangeSatur();
	afx_msg void OnPickorangeImage();
	afx_msg void OnReversImage();
	afx_msg void OnRrreversImage();
	afx_msg void OnAndImage();
	afx_msg void OnGammaImage();
	afx_msg void OnZoomoImage();
	afx_msg void OnZoomiImage();
	afx_msg void OnRotateImage();
	afx_msg void OnMirrorlrImage();
	afx_msg void OnMirrorhlImage();
	afx_msg void OnTransImage();
	afx_msg void OnHistostImage();
	afx_msg void OnAndinImage();
	afx_msg void OnHistoeqImage();
	afx_msg void OnAmbossImage();
	afx_msg void OnEmbossHsi();
	afx_msg void OnBlurImage();
	afx_msg void OnSharpnImage();
	afx_msg void OnSharphImage();
	afx_msg void OnSharplImage();
	afx_msg void OnUshaImage();
	afx_msg void OnChaImage();
	afx_msg void OnRobertsaImage();
	afx_msg void OnRobertsbImage();
	afx_msg void OnRobertsabImage();
	afx_msg void OnSobelaImage();
	afx_msg void OnSobelbImage();
	afx_msg void OnSobelabImage();
	afx_msg void OnPrewittaImage();
	afx_msg void OnPrewittbImage();
	afx_msg void OnPrewittabImage();
	afx_msg void OnLaplamaImage();
	afx_msg void OnLaplambImage();
	afx_msg void OnLaplamabImage();
	afx_msg void OnLogImage();
	afx_msg void OnDogImage();
};

#ifndef _DEBUG  // ColorImageAlpha1View.cpp의 디버그 버전
inline CColorImageAlpha1Doc* CColorImageAlpha1View::GetDocument() const
   { return reinterpret_cast<CColorImageAlpha1Doc*>(m_pDocument); }
#endif

