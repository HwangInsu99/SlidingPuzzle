
// SlidingPuzzleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SlidingPuzzle.h"
#include "SlidingPuzzleDlg.h"
#include "afxdialogex.h"
#include "Puzzle.h"
#include "QuadPuzzle.h"
#include "Twinkle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CSlidingPuzzleDlg 대화 상자



CSlidingPuzzleDlg::CSlidingPuzzleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLIDINGPUZZLE_DIALOG, pParent)
{//초기화선언
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	puzzle = new Puzzle();
	quadPuzzle = new QuadPuzzle();
	twinkle = new Twinkle();
	triple = TRUE; // 3X3퍼즐일 시 TRUE
	quadra = FALSE; // 4X4퍼즐일 시 TRUE
	twink = FALSE; // 반짝이는 이펙트가 출력될때 TRUE
	completed = FALSE; // 퍼즐완성시 TRUE
	count = 0; // 반짝이는 이펙트출력의 시간조절에 사용
	moveCount = 0;
	origin.Load(L"images\\Completed.jpg");
}

void CSlidingPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSlidingPuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(tripleP_Button, &CSlidingPuzzleDlg::OnClickedTriplepButton)
	ON_BN_CLICKED(quadraP_Button, &CSlidingPuzzleDlg::OnClickedQuadrapButton)
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CSlidingPuzzleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// 참조한 클래스의 이미지로딩
	puzzle->LoadImage();
	puzzle->Shuffle();
	quadPuzzle->LoadImage();
	quadPuzzle->Shuffle();
	twinkle->LoadImage();
	//타이머설정
	SetTimer(1, 3000, nullptr);
	SetTimer(2, 100, nullptr);

	return TRUE; 
}

void CSlidingPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CSlidingPuzzleDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	CBitmap* pOldBitmap, bmp;
	

	MemDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	origin.Draw(MemDC, 500, 20, 250, 250); //원본그림
	// 3X3과 4X4 퍼즐을 확인하고 그린다
	if (triple)
		puzzle->Draw(MemDC);
	else if (quadPuzzle)
		quadPuzzle->Draw(MemDC);

	str.Format(L"이동 횟수: %d", moveCount);
	MemDC.TextOutW(250, 30, str);

	// 퍼즐 완성시 타이머를 멈추고 대화상자를 띄움
	if (completed)
	{
		KillTimer(1);
		KillTimer(2);
		twink = FALSE;
		twinkle->count = 0;
		MessageBoxW(TEXT("Congratulations"));
	}

	if (twink)
	{
		twinkle->Draw(MemDC);
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
	bmp.DeleteObject();

	CDialogEx::OnPaint();
		
}

HCURSOR CSlidingPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSlidingPuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//마우스 클릭이 퍼즐내에서 실행됬는지 확인
	//3X3
	if (triple && point.x >= puzzle->startX && point.x <= puzzle->startX + 300 && point.y >= puzzle->startY && point.y < puzzle->startY + 300)
	{
		//클릭된 좌표가 퍼즐의 어느위치인지 계산
		int i = (int)(point.y - puzzle->startY) / 100;
		int j = (int)(point.x - puzzle->startX) / 100;
		//퍼즐에 전달 후 이동했을 시 이동횟수를 1추가함
		if (puzzle->Change(i, j))
			moveCount++;
		//퍼즐이 완성됬는지 확인
		completed = puzzle->Check();
		Invalidate();
	}
	//4X4
	else if (quadra && point.x >= puzzle->startX && point.x <= puzzle->startX + 300 && point.y >= puzzle->startY && point.y < puzzle->startY + 300)
	{
		int i = (int)(point.y - quadPuzzle->startY) / 75;
		int j = (int)(point.x - quadPuzzle->startX) / 75;
		if (quadPuzzle->Change(i, j))
			moveCount++;
		completed = quadPuzzle->Check();
		Invalidate();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

//해당버튼클릭시 3X3퍼즐로 초기화 후 변경
void CSlidingPuzzleDlg::OnClickedTriplepButton()
{
	triple = TRUE;
	quadra = FALSE;
	puzzle->Shuffle();
	completed = FALSE;
	moveCount = 0;
	SetTimer(1, 3000, nullptr);
	Invalidate();
}
//해당버튼클릭시 4X4퍼즐로 초기화 후 변경
void CSlidingPuzzleDlg::OnClickedQuadrapButton()
{
	triple = FALSE;
	quadra = TRUE;
	quadPuzzle->Shuffle();
	completed = FALSE;
	moveCount = 0;
	SetTimer(1, 3000, nullptr);
	Invalidate();
}

//반짝이는 이펙트를 일정시간마다 랜덤한위치에 만든다
void CSlidingPuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1 && !completed)
	{
		count = 0;
		twink = TRUE;
		twinkle->RandomPoint();
		SetTimer(2, 100, nullptr);
	}
	else if (nIDEvent == 2 && !completed)
	{
		if (count >= 5)
		{
			twink = FALSE;
			twinkle->count = 0;
			KillTimer(2);
			Invalidate();
		}
		else
		{
			twinkle->Tick();
			count++;
			Invalidate();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

//창크기고정
void CSlidingPuzzleDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(800, 500);
	lpMMI->ptMaxTrackSize = CPoint(800, 500);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CSlidingPuzzleDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
