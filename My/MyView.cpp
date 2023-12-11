
// MyView.cpp : CMyView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FINDMAX, &CMyView::OnFindmax)
	ON_MESSAGE(WM_MAX, &CMyView::OnMaxFound)
END_MESSAGE_MAP()

// CMyView ����/�Ҹ�

CMyView::CMyView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMyView �׸���

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(30,30, pDoc->m_str);
}


// CMyView �μ�

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMyView ����

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView �޽��� ó����



UINT MyThread(LPVOID pParam);
UINT MyThread(LPVOID pParam)
{
  	SData * pData = (SData*)pParam;
	for (int i = 0; i < 5; i++) { // �迭 ũ�� ����
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
