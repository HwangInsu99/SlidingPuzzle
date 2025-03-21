
// SlidingPuzzleDlg.h: 헤더 파일
//

#pragma once
class Puzzle;
class QuadPuzzle;
class Twinkle;


// CSlidingPuzzleDlg 대화 상자
class CSlidingPuzzleDlg : public CDialogEx
{
// 생성입니다.
public:
	CSlidingPuzzleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CSlidingPuzzleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLIDINGPUZZLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int count;
	int moveCount;
	CString str;
	Puzzle *puzzle;
	QuadPuzzle* quadPuzzle;
	Twinkle* twinkle;
	BOOL triple;
	BOOL quadra;
	BOOL twink;
	BOOL completed;
	CImage origin;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedTriplepButton();
	afx_msg void OnClickedQuadrapButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
