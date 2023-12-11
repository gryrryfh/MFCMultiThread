
// MyView.cpp : CMyView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "My.h"
#endif

#include "MyDoc.h"
#include "MyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FINDMAX, &CMyView::OnFindmax)
	ON_MESSAGE(WM_MAX, &CMyView::OnMaxFound)
END_MESSAGE_MAP()

// CMyView 생성/소멸

CMyView::CMyView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyView 그리기

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(30,30, pDoc->m_str);
}


// CMyView 인쇄

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMyView 진단

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView 메시지 처리기



UINT MyThread(LPVOID pParam);
UINT MyThread(LPVOID pParam)
{
  	SData * pData = (SData*)pParam;
	for (int i = 0; i < 5; i++) { // 배열 크기 조정
		pData->sum += pData->array[i];
	}

  	::PostMessage(pData->NotifyWindow, WM_MAX, 0, 0);
	return 0;
}

void CMyView::OnFindmax()
{
	data.array[0]=1;
	data.array[1]=5;
	data.array[2]=2;
	data.array[3]=4;
	data.array[4]=3;
	data.sum=0;
	data.NotifyWindow = m_hWnd;
	AfxBeginThread(MyThread, &data);
}
LRESULT CMyView::OnMaxFound(WPARAM wParam, LPARAM lParam)
{
	CMyDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString msg;
	msg.Format(L"Max of the array = %d", data.sum);
	pDoc->m_str = msg;
	TerminateThread(Thread, 0);
	Invalidate();
	return 0L;
}
