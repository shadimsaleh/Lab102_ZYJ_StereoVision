/********************************************************************
	���� :	2012/10/28
	�ļ� :	.\StereoVision\StereoVision\StereoVisionDlg.cpp
	���� :	StereoVisionDlg
	���� :	��� chenyusiyuan AT 126 DOT com
	
	���� :	�����Ӿ����Գ������ʵ�ִ���
*********************************************************************/

#include "stdafx.h"

/***
 *	����ڴ�й©
 */
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
//////////////////////////////////////////////////////////////////////////

#include "StereoVision.h"
#include "StereoVisionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CStereoVisionDlg dialog

CStereoVisionDlg::CStereoVisionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStereoVisionDlg::IDD, pParent)
	, m_lfCamID(0)
	, m_riCamID(0)
	, m_nCamCount(0)
	, m_nImageWidth(0)
	, m_nImageHeight(0)
	, m_nImageChannels(0)
	, m_ProcMethod(0)
	, m_ObjectWidth(0)
	, m_ObjectHeight(0)
	, m_ObjectDistance(0)
	, m_ObjectDisparity(0)
	, m_nCornerSize_X(0)
	, m_nCornerSize_Y(0)
	, m_nSquareSize(0)
	, m_nBoards(0)
	, m_pCheck(NULL)
	, m_nID_RAD(0)
	, m_nMinDisp(0)
	, m_nMaxDisp(0)
	, m_nSADWinSiz(0)
	, m_nTextThres(0)
	, m_nDisp12MaxDiff(-1)
	, m_nPreFiltCap(0)
	, m_nUniqRatio(0)
	, m_nSpeckRange(0)
	, m_nSpeckWinSiz(0)
	, m_nDelayTime(0)
	, m_bFullDP(FALSE)
	, m_bSaveFrame(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CStereoVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_nCornerSize_X, 0, 50);
	DDV_MinMaxInt(pDX, m_nCornerSize_Y, 0, 50);
	DDV_MinMaxInt(pDX, m_nBoards, 0, 100);
	DDV_MinMaxInt(pDX, m_nMinDisp, -64, 16);
	DDV_MinMaxInt(pDX, m_nMaxDisp, 0, 240);
	DDV_MinMaxInt(pDX, m_nSADWinSiz, 0, 21);
	DDV_MinMaxInt(pDX, m_nTextThres, 0, 50);
	DDV_MinMaxInt(pDX, m_nDisp12MaxDiff, -1, 16);
	DDV_MinMaxInt(pDX, m_nPreFiltCap, 0, 100);
	DDV_MinMaxInt(pDX, m_nUniqRatio, 0, 50);
	DDV_MinMaxInt(pDX, m_nSpeckRange, 0, 64);
	DDV_MinMaxInt(pDX, m_nSpeckWinSiz, 0, 200);
	DDV_MinMaxInt(pDX, m_nDelayTime, 0, 99);
	DDX_Control(pDX, IDC_CBN1CamList, m_CBNCamList);
	DDX_Control(pDX, IDC_CBN2MethodList, m_CBNMethodList);
	DDX_Control(pDX, IDC_SPIN_minDisp, m_spinMinDisp);
	DDX_Control(pDX, IDC_SPIN_maxDisp, m_spinMaxDisp);
	DDX_Control(pDX, IDC_SPIN_SADWinSiz, m_spinSADWinSiz);
	DDX_Control(pDX, IDC_SPIN_textThres, m_spinTextThres);
	DDX_Control(pDX, IDC_SPIN_disp12MaxDiff, m_spinDisp12MaxDiff);
	DDX_Control(pDX, IDC_SPIN_preFiltCap, m_spinPreFiltCap);
	DDX_Control(pDX, IDC_SPIN_uniqRatio, m_spinUniqRatio);
	DDX_Control(pDX, IDC_SPIN_speckRange, m_spinSpeckRange);
	DDX_Control(pDX, IDC_SPIN_speckWinSiz, m_spinSpeckWinSiz);
	DDX_Control(pDX, IDC_CBN_Resolution, m_CBNResolution);
	DDX_Check(pDX, IDC_CHK_fullDP, m_bFullDP);
	DDX_Check(pDX, IDC_CHK_SaveAsVideo, m_bSaveFrame);
	DDX_Text(pDX, IDC_EDIT_DelayTime, m_nDelayTime);
	DDX_Text(pDX, IDC_EDIT_speckWinSiz, m_nSpeckWinSiz);
	DDX_Text(pDX, IDC_EDIT_speckRange, m_nSpeckRange);
	DDX_Text(pDX, IDC_EDIT_uniqRatio, m_nUniqRatio);
	DDX_Text(pDX, IDC_EDIT_preFiltCap, m_nPreFiltCap);
	DDX_Text(pDX, IDC_e5LfObjSpan, m_ObjectWidth);
	DDX_Text(pDX, IDC_e6ObjPRLX, m_ObjectHeight);
	DDX_Text(pDX, IDC_e7ObjDist, m_ObjectDistance);
	DDX_Text(pDX, IDC_e8ObjSize, m_ObjectDisparity);
	DDX_Text(pDX, IDC_BoardWidth, m_nCornerSize_X);
	DDX_Text(pDX, IDC_BoardHeight, m_nCornerSize_Y);
	DDX_Text(pDX, IDC_SquareSize, m_nSquareSize);
	DDX_Text(pDX, IDC_EDIT_minDisp, m_nMinDisp);
	DDX_Text(pDX, IDC_nBoards, m_nBoards);
	DDX_Text(pDX, IDC_EDIT_maxDisp, m_nMaxDisp);
	DDX_Text(pDX, IDC_EDIT_SADWinSiz, m_nSADWinSiz);
	DDX_Text(pDX, IDC_EDIT_textThres, m_nTextThres);
	DDX_Text(pDX, IDC_EDIT_disp12MaxDiff, m_nDisp12MaxDiff);
}


BEGIN_MESSAGE_MAP(CStereoVisionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CStereoVisionDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BN1RunCam, &CStereoVisionDlg::OnBnClkRunCam)
	ON_BN_CLICKED(IDC_BN2StopCam, &CStereoVisionDlg::OnBnClkStopCam)
	ON_BN_CLICKED(IDC_RAD_BM, &CStereoVisionDlg::OnBnClkRad_BM)
	ON_BN_CLICKED(IDC_RAD_SGBM, &CStereoVisionDlg::OnBnClkRad_SGBM)
	ON_BN_CLICKED(IDC_BN_CompDisp, &CStereoVisionDlg::OnBnClk_DoCompDisp)
	ON_BN_CLICKED(IDC_BN_StopDispComp, &CStereoVisionDlg::OnBnClk_StopDispComp)
	ON_BN_CLICKED(IDC_BN2StereoCalib, &CStereoVisionDlg::OnBnClk_DoCameraCalib)
	ON_BN_CLICKED(IDC_BN_ExitCameraCalib, &CStereoVisionDlg::OnBnClk_ExitCameraCalib)
	ON_BN_CLICKED(IDC_BN_StereoDefParam, &CStereoVisionDlg::OnBnClkDefaultStereoParam)
	ON_BN_CLICKED(IDC_BN_DefaultCamCalibParam, &CStereoVisionDlg::OnBnClkDefaultCamCalibParam)
	ON_CBN_SELCHANGE(IDC_CBN1CamList, &CStereoVisionDlg::OnCbnSelchgCbn1Camlist)
	ON_CBN_SELCHANGE(IDC_CBN2MethodList, &CStereoVisionDlg::OnCbnSelchgCbn2Methodlist)
	ON_CBN_SELCHANGE(IDC_CBN_Resolution, &CStereoVisionDlg::OnCbnSelchangeCbnResolution)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_maxDisp, &CStereoVisionDlg::OnDeltaposSpin_MaxDisp)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SADWinSiz, &CStereoVisionDlg::OnDeltaposSpin_SADWinSiz)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_speckRange, &CStereoVisionDlg::OnDeltaposSpin_SpeckRange)
	ON_BN_CLICKED(IDC_RAD_CalibFromCam, &CStereoVisionDlg::OnBnClickedRadCalibfromcam)
	ON_BN_CLICKED(IDC_RAD_DispFromCam, &CStereoVisionDlg::OnBnClickedRadDispfromcam)
END_MESSAGE_MAP()


// CStereoVisionDlg message handlers

/*----------------------------
 * ���� : ��ʼ���Ի���
 *----------------------------
 * ���� : CStereoVisionDlg::OnInitDialog
 * ���� : virtual protected 
 * ���� : BOOL
 *
 */
BOOL CStereoVisionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//////////////////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here
	
	// ��ȡ������·��
	m_workDir = F_GetAppExecPath();

	// Ĭ��ͼ������Ϊ��ʾԭʼͼ��
	m_ProcMethod = SHOW_ORIGINAL_FRAME;

	// ��ȡ����ͷ��Ŀ
	m_nCamCount = CCameraDS::CameraCount();
	if( m_nCamCount < 1 )
	{
		AfxMessageBox(_T("���������1������ͷ��"));
		//return -1;
	}

	// ����Ͽ�CamList���������ͷ���Ƶ��ַ���
	char camera_name[1024];
	char istr[25];
	CString camstr;
	for(int i=0; i < m_nCamCount; i++)
	{  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );

		sprintf_s(istr, " # %d", i);
		strcat_s( camera_name, istr );  
		camstr = camera_name;
		if(retval >0)
			m_CBNCamList.AddString(camstr);
		else
			AfxMessageBox(_T("���ܻ�ȡ����ͷ������"));
	}
	camstr.ReleaseBuffer();

	// ����Ͽ�MethodList����Ӹ���֡���������ַ���
	m_CBNMethodList.AddString(_T("��ʾԭʼ����"));
	m_CBNMethodList.AddString(_T("Canny��Ե���"));
	m_CBNMethodList.AddString(_T("ֱ��ͼ����"));
	m_CBNMethodList.AddString(_T("ɫ�ʿռ�任"));
	m_CBNMethodList.SetCurSel(0);

	// ʹһϵ�а�ťʧЧ
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( FALSE );			// ��������ͷʧЧ
	GetDlgItem( IDC_BN2StopCam )->EnableWindow( FALSE );		// ֹͣ����ͷʧЧ
	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);		// ֹͣ�Ӳ����ʧЧ
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);	// �����Ӳ�ͼ����ʧЧ
	
	// ��ʼ��˫Ŀƥ������ؼ�����
	CheckRadioButton(IDC_RAD_BOUGUET, IDC_RAD_HARTLEY, IDC_RAD_BOUGUET);				// Ĭ��ʹ��BOUGUET����˫ĿУ��
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);								// Ĭ��ʹ�� BM �㷨�����Ӳ�
	CheckRadioButton(IDC_RAD_DispFromCam, IDC_RAD_DispFromImg, IDC_RAD_DispFromCam);	// Ĭ�ϴ��������ȡͼ��
	CheckRadioButton(IDC_RAD_ToHSV, IDC_RAD_ToXYZ, IDC_RAD_ToHSV);						// Ĭ��ͼ���ʽת��Ϊ HSV ��ʽ
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_StereoRectify);								// Ĭ��ִ��˫ĿУ��
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ProjTo3D);			// Ĭ��ִ��˫Ŀ���
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowFullDisp);		// Ĭ��ִ��˫Ŀ���
	m_pCheck->SetCheck(1);
	m_pCheck = NULL;

	m_nMaxDisp = 0;
	m_nSADWinSiz =0;
	m_nPreFiltCap =0;
	m_nSpeckRange = 0;
	m_nDelayTime = 5;
	m_spinMinDisp.SetRange(-64, 16);
	m_spinMaxDisp.SetRange(0, 240);
	m_spinSADWinSiz.SetRange(0, 21);
	m_spinTextThres.SetRange(0, 50);
	m_spinDisp12MaxDiff.SetRange(-1, 36);
	m_spinPreFiltCap.SetRange(0, 100);
	m_spinUniqRatio.SetRange(0, 50);
	m_spinSpeckRange.SetRange(0, 64);
	m_spinSpeckWinSiz.SetRange(0, 200);

	UpdateData( FALSE );

	// ��ʼ��ͼ����ʾ�ؼ���ͼ��
	CRect rect;
	GetDlgItem(IDC_PicLfCam) ->GetClientRect( &rect );
	m_lfImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicRiCam) ->GetClientRect( &rect );
	m_riImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicSynImg) ->GetClientRect( &rect );
	m_disparity = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*----------------------------
 * ���� : OnSysCommand
 *----------------------------
 * ���� : CStereoVisionDlg::OnSysCommand
 * ���� : protected 
 * ���� : void
 *
 * ���� : UINT nID
 * ���� : LPARAM lParam
 */
void CStereoVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


/*----------------------------
 * ���� : OnPaint
 *----------------------------
 * ���� : CStereoVisionDlg::OnPaint
 * ���� : protected 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();						// �ػ�Ի���
		CDialog::UpdateWindow();				// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
		if (!m_lfImage.empty())
		{
			F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );		// �ػ�ͼƬ����
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );		// �ػ�ͼƬ����
			F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );	// �ػ�ͼƬ����
		}
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
/*----------------------------
 * ���� : OnQueryDragIcon
 *----------------------------
 * ���� : CStereoVisionDlg::OnQueryDragIcon
 * ���� : protected 
 * ���� : HCURSOR
 *
 */
HCURSOR CStereoVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*----------------------------
 * ���� : ѡ������ͷ�����˵���Ӧ
 *----------------------------
 * ���� : CStereoVisionDlg::OnCbnSelchgCbn1Camlist
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnCbnSelchgCbn1Camlist()
{
	// TODO: Add your control notification handler code here

	// ȷ����������ͷ��Ӧ���豸��ţ���Ӧ�����˵�ѡ�������ţ�
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD1LfCam, IDC_RAD2RiCam);
	if (m_nID_RAD == IDC_RAD1LfCam)
	{
		m_lfCamID = m_CBNCamList.GetCurSel();
	} 
	else
	{
		m_riCamID = m_CBNCamList.GetCurSel();
	}

	// ʹ��������ͷ��ť��Ч
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( TRUE );
	
	return;
}


/*----------------------------
 * ���� : ѡ������ͷ�ֱ���
 *----------------------------
 * ���� : CStereoVisionDlg::OnCbnSelchangeCbnResolution
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnCbnSelchangeCbnResolution()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_CBNResolution.GetCurSel();
	switch (index)
	{
	case 0:
		m_nImageWidth = 640;
		m_nImageHeight = 480;
		break;
	case 1:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
		break;
	case 2:
		m_nImageWidth = 320;
		m_nImageHeight = 240;
		break;
	default:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
	}

	m_nImageChannels = 3;
}


/*----------------------------
 * ���� : ��������ͷ
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkRunCam
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkRunCam()
{
	// TODO: Add your control notification handler code here
	if (m_nImageWidth * m_nImageHeight * m_nImageChannels <= 0)
	{
		AfxMessageBox(_T("��ѡ������ͷ����ķֱ��ʣ�")); 
		return;
	}
	if (m_nCamCount >= 1)
	{
		//�򿪵�һ������ͷ
		//if( ! lfCam.OpenCamera(m_riCamID, false, m_nImageWidth, m_nImageHeight) ) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
		//if ( !lfCam.open("rtsp://192.168.4.66:554/profile2/media.smp") )
		if (!lfCam.open(m_lfCamID))
		{
			AfxMessageBox(_T("��������ͷʧ��."));
			return;
		}
		lfCam.set(CV_CAP_PROP_FRAME_WIDTH,  m_nImageWidth);
		lfCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	}
	if (m_nCamCount >= 1)
	{
		if (m_lfCamID == m_riCamID)
		{
			//AfxMessageBox(_T("��������ͷ���豸��Ų�����ͬ��"));
			//return;
		}
		//�򿪵ڶ�������ͷ
		//if( ! riCam.OpenCamera(m_lfCamID, false, m_nImageWidth, m_nImageHeight) ) 
		//if ( !riCam.open("rtsp://192.168.4.100:554/profile2/media.smp") )
		if (!riCam.open(m_riCamID))
		{
			AfxMessageBox(_T("��������ͷʧ��."));
			return;
		}
		riCam.set(CV_CAP_PROP_FRAME_WIDTH,  m_nImageWidth);
		riCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);

		GetDlgItem( IDC_BN_CompDisp )->EnableWindow( TRUE );
	}
	
	// ʹ���ְ�ť��Ч
	GetDlgItem( IDC_BN2StopCam )->EnableWindow( TRUE );
	GetDlgItem( IDC_BN2StereoCalib)->EnableWindow( TRUE );
	// ʹ���ְ�ťʧЧ
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( FALSE );
	GetDlgItem( IDC_CBN1CamList )->EnableWindow( FALSE );
	GetDlgItem( IDC_CBN_Resolution )->EnableWindow( FALSE );
	GetDlgItem( IDCANCEL )->EnableWindow(FALSE);

	// ��������ͷ����ʾʵʱ����
	DoShowOrigFrame();

	//// ����OpenCV�����Ա���Ӧ�����¼�
	//namedWindow("1");
	//resizeWindow("1",1,1);
	//HWND hLfWnd = (HWND) cvGetWindowHandle("1");
	//HWND hLfParent = ::GetParent(hLfWnd);
	//HWND hwnd1=::FindWindow(_T("CStereoVisionDlg"),_T("StereoVision"));
	//::SetParent(hLfWnd, hwnd1);
	//::ShowWindow(hLfWnd, SW_MINIMIZE);

	return;
}


/*----------------------------
 * ���� : ��ʱ����Ӧ
 *		 ��Ҫ���� û��˫Ŀ�����˫Ŀƥ�����ʱ ��������ʾ�ʹ������
 *----------------------------
 * ���� : CStereoVisionDlg::OnTimer
 * ���� : private 
 * ���� : void
 *
 * ���� : UINT_PTR nIDEvent
 */
void CStereoVisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//snowchange 0712
	if (lfCam.isOpened())
	{
		Mat lfFrame;
		//Mat lfFrameold;
		lfCam >> lfFrame;
		//lfFrame.create(lfFrameold.rows, lfFrameold.cols, CV_8UC3);
		/*int  i,i3=0;
		int isize = lfFrameold.cols*lfFrameold.rows;
		for (i = isize*2; i < isize*3; i++)
		{
			lfFrame.data[i3] = lfFrameold.data[i];
			lfFrame.data[i3+1] = lfFrameold.data[i];
			lfFrame.data[i3+2] = lfFrameold.data[i];
			i3 += 3;
		}*/

		if (m_ProcMethod == SHOW_ORIGINAL_FRAME)
		{
			F_ShowImage(lfFrame, m_lfImage, IDC_PicLfCam);
		} 
		else
		{
			DoFrameProc(lfFrame, lfFrame);
			F_ShowImage(lfFrame, m_lfImage, IDC_PicLfCam);
		}
	}
	if (riCam.isOpened())
	{
		Mat riFrame;
		//Mat riFrameold;

		riCam >> riFrame;
		/*riFrame.create(riFrameold.rows, riFrameold.cols, CV_8UC3);
		int  i, i3 = 0;
		int isize = riFrameold.cols*riFrameold.rows;
		for (i = isize * 2; i < isize * 3; i++)
		{
			riFrame.data[i3] = riFrameold.data[i];
			riFrame.data[i3 + 1] = riFrameold.data[i];
			riFrame.data[i3 + 2] = riFrameold.data[i];
			i3 += 3;
		}
*/
		if (m_ProcMethod == SHOW_ORIGINAL_FRAME)
		{
			F_ShowImage(riFrame, m_riImage, IDC_PicRiCam);
		} 
		else
		{
			DoFrameProc(riFrame, riFrame);
			F_ShowImage(riFrame, m_riImage, IDC_PicRiCam);
		}
	}
	CDialog::OnTimer(nIDEvent);
}


/*----------------------------
 * ���� : �ر�����ͷ
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkStopCam
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkStopCam()
{
	// TODO: Add your control notification handler code here
	if (lfCam.isOpened())
	{
		GetDlgItem( IDC_BN2StopCam )->EnableWindow( FALSE );
		KillTimer(1);

		// ��ͼ����������
		m_lfImage = Scalar(0);
		F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );
		lfCam.release();
		if (riCam.isOpened())
		{
			m_riImage = Scalar(0);
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );
			riCam.release();
		}

		// ʹ��������ͷ��ť������ͷѡ���б���Ч
		GetDlgItem( IDC_BN1RunCam )->EnableWindow( TRUE );
		GetDlgItem( IDC_CBN1CamList )->EnableWindow( TRUE );
		GetDlgItem( IDC_CBN_Resolution )->EnableWindow( TRUE );
		GetDlgItem( IDCANCEL )->EnableWindow(TRUE);
		GetDlgItem( IDC_BN2StereoCalib)->EnableWindow( FALSE );
		GetDlgItem( IDC_BN_CompDisp )->EnableWindow( FALSE );
	}
	return;
}


/*----------------------------
 * ���� : ֡�����������˵�ѡ����Ӧ��
 *		 �޸�֡�����־ֵ
 *----------------------------
 * ���� : CStereoVisionDlg::OnCbnSelchgCbn2Methodlist
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnCbnSelchgCbn2Methodlist()
{
	// TODO: Add your control notification handler code here
	m_ProcMethod = m_CBNMethodList.GetCurSel();
}


/*----------------------------
 * ���� : �������ļ��Ի���ѡ�񵥸������ļ�
 *----------------------------
 * ���� : CStereoVisionDlg::DoSelectFiles
 * ���� : private 
 * ���� : selectedFiles	ѡ����ļ���·������
 *
 * ���� : lpszDefExt			[in]	�ļ�Ĭ�ϸ�ʽ
 * ���� : dwFlags			[in]	�Ի���ѡ��
 * ���� : lpszFilter			[in]	�ļ���ʽ��������
 * ���� : lpstrTitle			[in]	�Ի������
 * ���� : lpstrInitialDir	[in]	�Ի���ĳ�ʼ·��
 */
vector<CStringA> CStereoVisionDlg::DoSelectFiles(
	LPCTSTR	lpszDefExt,
	DWORD	dwFlags,
	LPCTSTR	lpszFilter,
	LPCWSTR	lpstrTitle,
	LPCWSTR	lpstrInitialDir )
{
	vector<CStringA> selectedFiles;
	POSITION filePosition;
	DWORD MAXFILE = 4000;  
	TCHAR* pc = new TCHAR[MAXFILE];  

	CFileDialog dlg( TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL );	
	
	dlg.m_ofn.nMaxFile = MAXFILE; 
	dlg.m_ofn.lpstrFile = pc;   
	dlg.m_ofn.lpstrFile[0] = NULL; 
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if( dlg.DoModal() == IDOK )
	{
		filePosition = dlg.GetStartPosition();
		while(filePosition != NULL)   
		{   
			CStringA path;
			path = dlg.GetNextPathName(filePosition);
			selectedFiles.push_back( path );  
		}  
	}

	delete []pc;
	return selectedFiles;
}


/*----------------------------
 * ���� : ��������ͷ�����Ĭ�ϲ���
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkDefaultCamCalibParam
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkDefaultCamCalibParam()
{
	// TODO: Add your control notification handler code here
	m_nCornerSize_X = 9;
	m_nCornerSize_Y = 6;
	m_nBoards = 20;
	m_nSquareSize = 26.0f;
	UpdateData(FALSE);

	CheckRadioButton(IDC_RAD_CalibFromCam, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromCam);
	CheckRadioButton(IDC_RAD_Load1CamCalibResult, IDC_RAD_StereoCalib, IDC_RAD_Calib1CamFirst);

	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowCalibResult);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK1FPP);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK1FPP2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK2UIG);
	m_pCheck->SetCheck(0);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK2UIG2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK3FAR);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK3FAR2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK4ZTD);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK4SFL);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK5FI);
	m_pCheck->SetCheck(0);
	m_pCheck = NULL;

	return;
}


/*----------------------------
 * ���� : ȷ���������������ѡ��
 *----------------------------
 * ���� : CStereoVisionDlg::DoParseOptionsOfCameraCalib
 * ���� : private 
 * ���� : void
 *
 * ���� : opt	[i/o]	���������ѡ��
 */
void CStereoVisionDlg::DoParseOptionsOfCameraCalib(OptionCameraCalib& opt)
{
	// ����ͷ���������ʼ��
	opt.squareSize = 30.0f;
	opt.flagCameraCalib = CV_CALIB_FIX_K3;
	opt.flagStereoCalib = 0;
	opt.numberFrameSkip = 30;
	opt.doStereoCalib = true;

	UINT nCheckIDs[9] = { IDC_CHK1FPP, IDC_CHK2UIG, IDC_CHK3FAR, IDC_CHK4ZTD,
		IDC_CHK1FPP2, IDC_CHK2UIG2, IDC_CHK3FAR2, IDC_CHK4SFL, IDC_CHK5FI };
	int nFlagDefs1[4] = { CV_CALIB_FIX_PRINCIPAL_POINT, CV_CALIB_USE_INTRINSIC_GUESS,
		CV_CALIB_FIX_ASPECT_RATIO, CV_CALIB_ZERO_TANGENT_DIST };
	int nFlagDefs2[5] = { CV_CALIB_FIX_PRINCIPAL_POINT, CV_CALIB_USE_INTRINSIC_GUESS,
		CV_CALIB_FIX_ASPECT_RATIO, CV_CALIB_SAME_FOCAL_LENGTH, CV_CALIB_FIX_INTRINSIC };

	// ����MFC��������̲����趨
	UpdateData(TRUE);
	opt.cornerSize.width = m_nCornerSize_X; 	// ���̽ǵ��� (nx, ny)
	opt.cornerSize.height = m_nCornerSize_Y;
	opt.numberBoards = m_nBoards;				// ������̴���
	opt.squareSize = m_nSquareSize; 			// ���̷����С

	// ȷ�����̽ǵ��������ݵĻ�ȡ��ʽ
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ReadCornerData);
	opt.loadConerDatas = m_pCheck->GetCheck() > 0;	

	// ȷ��������ͼ����Դ������ͷ or ����ͼƬ��
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_CalibFromCam, IDC_RAD_CalibFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_CalibFromImg;
	if(opt.readLocalImage)		// ���ӱ���ͼƬ���룬����֡������Ϊ 5 ֡
		opt.numberFrameSkip = 5;

	// ȷ��˫Ŀ����Ĵ���
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_Load1CamCalibResult, IDC_RAD_StereoCalib);
	opt.calibOrder = m_nID_RAD == IDC_RAD_Load1CamCalibResult ? CALIB_LOAD_CAMERA_PARAMS : 
		m_nID_RAD == IDC_RAD_Calib1CamFirst ? CALIB_SINGLE_CAMERA_FIRST : 
		m_nID_RAD == IDC_RAD_StereoCalib ? CALIB_STEREO_CAMERAS_DIRECTLY : 	CALIB_SINGLE_CAMERA_FIRST;	
	//if (m_nCamCount == 1)	//����ͷֻ��һ��ʱ�����ܽ���˫Ŀ����
	if (false)
	{
		opt.doStereoCalib = false;
		opt.calibOrder = CALIB_SINGLE_CAMERA_FIRST;
		m_pCheck = (CButton*)GetDlgItem(IDC_RAD_Calib1CamFirst);
		m_pCheck->SetCheck(1);
		GetDlgItem(IDC_RAD_StereoCalib)->EnableWindow(FALSE);
	}

	// ȷ��˫ĿУ���㷨
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BOUGUET, IDC_RAD_HARTLEY);
	opt.rectifyMethod = m_nID_RAD == IDC_RAD_BOUGUET ? StereoCalib::RECTIFY_BOUGUET : StereoCalib::RECTIFY_HARTLEY;

	// ���붨�����������
	int i;
	for (i=0; i<4; i++)
	{
		m_pCheck = (CButton*)GetDlgItem(nCheckIDs[i]);
		if(m_pCheck->GetCheck())
			opt.flagCameraCalib |= nFlagDefs1[i];
	}
	for (i=4; i<9; i++)
	{
		m_pCheck = (CButton*)GetDlgItem(nCheckIDs[i]);
		if(m_pCheck->GetCheck())
			opt.flagStereoCalib |= nFlagDefs2[i-4];
	}

	UpdateData(TRUE);
}

//void getimage(VideoCapture riCam, Mat* riFrame)
//{
//	Mat riFrameold;
//
//	riCam >> riFrameold;
//	riFrame->create(riFrameold.rows, riFrameold.cols, CV_8UC3);
//	int  i, i3 = 0;
//	int isize = riFrameold.cols*riFrameold.rows;
//	for (i = isize * 2; i < isize * 3; i++)
//	{
//		riFrame->data[i3] = riFrameold.data[i];
//		riFrame->data[i3 + 1] = riFrameold.data[i];
//		riFrame->data[i3 + 2] = riFrameold.data[i];
//		i3 += 3;
//	}
//}
/*----------------------------
 * ���� : ˫Ŀ���� ��ť��Ӧ
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClk_DoCameraCalib
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClk_DoCameraCalib()
{

	//Jacqueszhu 14/07/2015
	//lfCam.set(CV_CAP_PROP_FRAME_WIDTH, m_nImageWidth);
	//lfCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	//riCam.set(CV_CAP_PROP_FRAME_WIDTH, m_nImageWidth);
	//riCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	// TODO: Add your control notification handler code here
	KillTimer(1);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	GetDlgItem(IDC_CBN2MethodList)->EnableWindow(FALSE);

	// ���̼�������ʼ��
	int nFoundBoard = 0, nFrame = 0;
	vector<CStringA> img0Files, img1Files;
	const char* img0_file = NULL, *img1_file = NULL;
	//Jacqueszhu 14/07/2015
	cv::Mat frame0, frame1 , img0, img1;

	cv::Size imageSize;

	StereoCalib::CornerDatas cornerDatas;
	StereoCalib::StereoParams stereoParams;
	StereoCalib::RemapMatrixs remapMatrixs;
	OptionCameraCalib optCalib;

	//ȷ���������������ѡ��
	DoParseOptionsOfCameraCalib(optCalib);

	try
	{
		////////////////////////////////////////////////////////////////////////
		// ����������̽ǵ�
		// *** �ӱ����ļ�����ǵ���������
		const char* cornerFile = "CornerData.yml";
		if (optCalib.loadConerDatas)		
		{
			if ( m_stereoCalibrator.loadCornerData(cornerFile, cornerDatas) )
			{
				AfxMessageBox(_T("�Ѷ���ǵ���������"));
			}
			else
			{
				LPCTSTR errMsg = _T("�ǵ��������ݶ���ʧ�ܣ�\n  --ȷ�ϵ�ǰ�ļ����а��� CornerData.yml �ļ��� \n ����\n  --ִ�����̽ǵ��⡣");
				throw errMsg;
			}
		} 
		// *** ������ͷ�򱾵�ͼƬ������̽ǵ�
		else		
		{
			// ��ѡ��ӱ���ͼƬ���붨��ͼ�����ȵ����Ի���ѡ��ͼƬ�ļ�
			if(optCalib.readLocalImage)
			{
				img0Files = DoSelectFiles(
					_T("*.bmp"), 
					OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
					_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
					_T("ѡ������ͼ�ļ�"),
					_T("Imgs\\Left"));
				img1Files = DoSelectFiles(
					_T("*.bmp"), 
					OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
					_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
					_T("ѡ������ͼ�ļ�"),
					_T("Imgs\\Right"));

				if( img0Files.empty() )	// �ж��Ƿ���ͼƬ
				{
					LPCTSTR errMsg = _T("û��ѡ����Ч��ͼ���ļ���������ѡ��!");
					throw errMsg;
				}

				img0_file = img0Files[ 0 ];
				img0 = cvLoadImage(img0_file);
				imageSize = img0.size();

				if (false == img1Files.empty())
				{
					optCalib.numberBoards = MIN(optCalib.numberBoards, MIN(img0Files.size(), img1Files.size()));
				}
				else
				{
					optCalib.doStereoCalib = false;
					optCalib.numberBoards = MIN(optCalib.numberBoards, img0Files.size());
				}
			} 
			else
			{
				//snowchange 0712
				
				lfCam >> img0;
				cv::resize(img0, img0, Size(m_nImageWidth, m_nImageHeight), 0, 0,1);
				//getimage(lfCam, &img0);
				imageSize = img0.size();
			}

			////////////////////////////////////////////////////////////////////////
			// ��ʼ���ǵ����ݼ�
			m_stereoCalibrator.initCornerData(optCalib.numberBoards, imageSize, optCalib.cornerSize, optCalib.squareSize, cornerDatas);
			
			// �����˳���������갴ť
			GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(TRUE);

			// ��ʼ���ǵ�
			MSG msg;
			while(nFoundBoard < optCalib.numberBoards)
			{
				// MFC ������Ϣ����
				if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
				{ 
					if(msg.message == WM_QUIT) 
					{ 
						LPCTSTR errMsg = _T("�ֶ��˳�˫Ŀ�궨!");
						throw errMsg; 
					}	

					//// ��Ҫ #include "Strsafe.h"
					//TCHAR info[50];
					//StringCbPrintf( info, sizeof(info), _T("��Ϣ��� = %d\n"), msg.message );
					//OutputDebugString(info);

					::TranslateMessage(&msg); 
					::DispatchMessage(&msg);
				}

				// ����ͼ��
				if(optCalib.readLocalImage)	// �ӱ���ͼƬ
				{
					img0_file = img0Files[ nFoundBoard ];
					frame0 = cvLoadImage(img0_file);
					if (optCalib.doStereoCalib)
					{
						img1_file = img1Files[ nFoundBoard ];
						frame1 = cvLoadImage(img1_file);
					}
				} 
				else	// ������ͷ
				{
					//snowchange 0712
					//frame0.create(Size(m_nImageWidth,m_nImageHeight),CV_8UC3);

					//Jacqueszhu 14/07/2015					
					lfCam >> frame0;			
					cv::resize(frame0, frame0, Size(m_nImageWidth, m_nImageHeight), 0.0, 0.0, 1);
					/*Mat frame0old;
					lfCam >> frame0old;
					
					frame0.create(frame0old.rows, frame0old.cols, CV_8UC3);
					int  i, i3 = 0;
					int isize = frame0old.cols*frame0old.rows;
					uchar* pchar = frame0old.data + 2*isize;
					for (i = 0; i < 76800; i++)
					{
						frame0.data[i3] = *pchar;
						frame0.data[i3 + 1] = *pchar;
						frame0.data[i3 + 2] = *pchar;
						i3 += 3;
						pchar++;
					}*/
					//getimage(lfCam, &frame0);
					if (optCalib.doStereoCalib)
					{
						//Jacqueszhu 14/07/2015						
						riCam >> frame1;
						cv::resize(frame1, frame1, Size(m_nImageWidth, m_nImageHeight), 0.0, 0.0,1);
					}
						//getimage(riCam, &frame1);
				}				
				if ( frame0.empty())	break;
				if (optCalib.doStereoCalib)
				{
					if ( frame1.empty())	break;
				}

				// ����ͼ��
				img0 = frame0.clone();
				if (optCalib.doStereoCalib) img1 = frame1.clone();

				// ���ǵ�
				if ( m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard) )
				{
					if (nFrame++ > optCalib.numberFrameSkip)
					{
						//������ͼ
						if (optCalib.readLocalImage == false)
						{
							CStringA imgName( m_workDir );
							imgName.AppendFormat("Images\\left%03d.jpg",nFoundBoard);
							string imgname = imgName.GetBuffer(0);
							imwrite(imgname, frame0);

							if (optCalib.doStereoCalib) 
							{
								imgName = m_workDir;
								imgName.AppendFormat("Images\\right%03d.jpg",nFoundBoard);
								imgname = imgName.GetBuffer(0);
								imwrite(imgname, frame1);
							}
						}

						nFoundBoard++; 
						nFrame = 0;
					}

					if (nFoundBoard > 0 && nFrame < 5)
					{
						//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
						bitwise_not(img0, img0);
						if (optCalib.doStereoCalib) bitwise_not(img1, img1);
					}
				} // --End "if ( m_stereoCalibrator.detectCorners )"

				// ��ʾ��⵽�Ľǵ�
				F_ShowImage( img0, m_lfImage, IDC_PicLfCam );
				if (optCalib.doStereoCalib) F_ShowImage( img1, m_riImage, IDC_PicRiCam ); 
			} // --End "while(nFoundBoard < optCalib.numberBoards) "
			
			if (nFoundBoard < 4)
			{
				LPCTSTR errMsg = _T("���ɹ�������ͼ����С��4�����˳�˫Ŀ�궨!");
				throw errMsg;
			}
			else if (nFoundBoard != optCalib.numberBoards)
			{
				optCalib.numberBoards = nFoundBoard;
				m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
			}

			// ����ǵ���������
			m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);

			AfxMessageBox(_T("���̽ǵ������"));
		} // --End "if (optCalib.loadConerDatas)"
		// �ѻ�ȡ�ǵ���������

		// �����˳���������갴ť
		GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);

		////////////////////////////////////////////////////////////////////////
		// �Ƿ�����ѱ궨�õ�����ͷ�ڲΣ�
		if (optCalib.calibOrder == CALIB_LOAD_CAMERA_PARAMS)
		{		
			if (0 == m_stereoCalibrator.loadCameraParams("leftCamera.yml", stereoParams.cameraParams1))
			{
				LPCTSTR errMsg = _T("��������ͷ�ڲ�ʧ�ܣ��Ҳ��� leftCamera.yml �ļ�!");
				throw errMsg;
			}
			
			if (optCalib.doStereoCalib) 
			{
				if (0 == m_stereoCalibrator.loadCameraParams("rightCamera.yml", stereoParams.cameraParams2))
				{
					LPCTSTR errMsg = _T("��������ͷ�ڲ�ʧ�ܣ��Ҳ��� rightCamera.yml �ļ�!");
					throw errMsg;
				}
			}

			// ��ʾ�Ѷ����ѱ궨�õ�����ͷ�ڲ�
			AfxMessageBox(_T("�Ѷ���궨�õ�����ͷ�ڲ�"));
		}	

		// ��������ͷ�궨
		if (optCalib.doStereoCalib)	// ˫Ŀ�궨��У��
		{
			stereoParams.cameraParams1.flags = optCalib.flagCameraCalib;
			stereoParams.cameraParams2.flags = optCalib.flagCameraCalib;
			stereoParams.flags = optCalib.flagStereoCalib;
			bool needCalibSingleCamera = (CALIB_SINGLE_CAMERA_FIRST == optCalib.calibOrder);
			m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, needCalibSingleCamera);

			// ����궨���
			double avgErr = 0;
			m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
			char info[50];
			sprintf_s( info, "�궨��� = %7.4g", avgErr );
			CString ss;
			ss = info;
			AfxMessageBox(ss);

			// ִ��˫ĿУ��
			m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);

			AfxMessageBox(_T("�����˫ĿУ��"));

			// ��������ͷ�������	
			m_stereoCalibrator.saveCalibrationDatas("calib_paras.xml"/*����Ϊ�ɱ��������ļ�ȷ��*/, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);

			AfxMessageBox(_T("�ѱ��涨�����"));

		} 
		else // ��Ŀ�궨
		{
			StereoCalib::CameraParams cameraParams;
			cameraParams.flags = optCalib.flagCameraCalib;

			// ִ�е�Ŀ����
			m_stereoCalibrator.calibrateSingleCamera(cornerDatas, cameraParams);
			m_stereoCalibrator.saveCameraParams(cameraParams);

			// ����궨���
			double avgErr = 0;
			m_stereoCalibrator.getCameraCalibrateError(cornerDatas.objectPoints, cornerDatas.imagePoints1, cameraParams, avgErr);
			char info[50];
			sprintf_s( info, "�ѱ��涨��������궨��� = %7.4g", avgErr );
			CString ss;
			ss = info;
			AfxMessageBox(ss);

			// ִ�е�ĿУ��
			m_stereoCalibrator.rectifySingleCamera(cameraParams, remapMatrixs);

		}

		//////////////////////////////////////////////////////////////////////////
		// ��ʾ�궨Ч��
		{
			// �����˳���������갴ť
			GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(TRUE);

			MSG msg;
			while (true)
			{
				// MFC ������Ϣ����
				if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
				{ 
					if(msg.message == WM_QUIT) 
					{ 
						break; 
					}	
					::TranslateMessage(&msg); 
					::DispatchMessage(&msg);
				}

				// ����ͼ��
				lfCam >> frame0;
				if (optCalib.doStereoCalib) 
					riCam >> frame1;			
				if ( frame0.empty())	break;
				if (optCalib.doStereoCalib)
				{
					if ( frame1.empty())	break;
				}

				// ����ͼ��
				img0 = frame0.clone();
				if (optCalib.doStereoCalib) 
					img1 = frame1.clone();

				// У��ͼ��
				UpdateData(FALSE);
				m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowCalibResult);
				bool showCalibrated = m_pCheck->GetCheck() > 0;
				if ( showCalibrated )
					m_stereoCalibrator.remapImage(img0, img1, img0, img1, remapMatrixs);

				// ��ʾУ��Ч��
				F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
				if (optCalib.doStereoCalib) 
					F_ShowImage(img1, m_riImage, IDC_PicRiCam);
			}
		}

	}
	//////////////////////////////////////////////////////////////////////////
	// ������Ϣ����
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}

	// �����˳���������갴ť
	GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////	
	if(lfCam.isOpened() || riCam.isOpened())
	{
		// ����������ָ�˫Ŀ���갴ť
		GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBN2MethodList)->EnableWindow(TRUE);

		// �ָ�������ʾ
		DoShowOrigFrame();		
	}

	return;
}


/*----------------------------------
 * ���� :	ֹͣ�ǵ��� ��ť��Ӧ
 *----------------------------------
 * ���� :	CStereoVisionDlg::OnBnClk_StopDetectCorners
 * ���� :	private 
 * ���� :	void
 *
 */
void CStereoVisionDlg::OnBnClk_ExitCameraCalib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����˳���Ϣ
	::PostMessage(this->m_hWnd, WM_QUIT, 0, 0);
	// ����ֹͣ�ǵ��ⰴť
	GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);
}


/*----------------------------
 * ���� : ȷ������ƥ������ѡ��
 *----------------------------
 * ���� : CStereoVisionDlg::DoParseOptionsOfStereoMatch
 * ���� : private 
 * ���� : void
 *
 * ���� : opt	[i/o]	����ƥ��ѡ��
 */
void CStereoVisionDlg::DoParseOptionsOfStereoMatch(OptionStereoMatch& opt)
{
	// ȷ�ϼ����Ӳ���㷨
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	opt.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
	// ȷ��������ͼ����Դ������ͷ or ����ͼƬ��
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_DispFromCam, IDC_RAD_DispFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_DispFromImg;
	// ȷ���Ƿ�ִ��˫ĿУ��
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_StereoRectify);
	opt.useStereoRectify = m_pCheck->GetCheck() > 0;
	// ȷ���Ƿ񱣴�ƥ����
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_SaveAsVideo);
	opt.saveResults = m_pCheck->GetCheck() > 0;
	// ȷ���Ƿ���ʱ��ʾƥ��Ч��
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_DelayProc);
	opt.delayEachFrame = m_pCheck->GetCheck() > 0;
	if (opt.readLocalImage)
	{
		opt.delayEachFrame = true;
		m_pCheck->SetCheck(1);
	}
	// ȷ���Ƿ�������ά����
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ProjTo3D);
	opt.generatePointCloud = m_pCheck->GetCheck() > 0;
	// ȷ���Ƿ���ʾ��ɫ�Ӳ�ͼ
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowFullDisp);
	opt.showColorDisparity = m_pCheck->GetCheck() > 0;
}


/*----------------------------
 * ���� : ���� BM �����״̬����
 *----------------------------
 * ���� : CStereoVisionDlg::DoUpdateStateBM
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::DoUpdateStateBM()
{
	UpdateData(TRUE);
	m_stereoMatcher.m_BM.state->preFilterCap = m_nPreFiltCap;
	m_stereoMatcher.m_BM.state->SADWindowSize = m_nSADWinSiz;
	m_stereoMatcher.m_BM.state->minDisparity = m_nMinDisp;
	m_stereoMatcher.m_BM.state->numberOfDisparities = m_nMaxDisp;
	m_stereoMatcher.m_BM.state->textureThreshold = m_nTextThres;
	m_stereoMatcher.m_BM.state->uniquenessRatio = m_nUniqRatio;
	m_stereoMatcher.m_BM.state->speckleWindowSize = m_nSpeckWinSiz;
	m_stereoMatcher.m_BM.state->speckleRange = m_nSpeckRange;

}


/*----------------------------
 * ���� : ���� SGBM �����״̬����
 *----------------------------
 * ���� : CStereoVisionDlg::DoUpdateStateSGBM
 * ���� : private 
 * ���� : void
 *
 * ���� : imgChannels	[in]	ͼ��ͨ����
 */
void CStereoVisionDlg::DoUpdateStateSGBM(int imgChannels)
{
	UpdateData(TRUE);
	m_stereoMatcher.m_SGBM.preFilterCap = m_nPreFiltCap;
	m_stereoMatcher.m_SGBM.SADWindowSize = m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.P1 =  8 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.P2 = 32 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.minDisparity = m_nMinDisp;
	m_stereoMatcher.m_SGBM.numberOfDisparities = m_nMaxDisp;
	m_stereoMatcher.m_SGBM.uniquenessRatio = m_nUniqRatio;
	m_stereoMatcher.m_SGBM.speckleWindowSize = m_nSpeckWinSiz;
	m_stereoMatcher.m_SGBM.speckleRange = m_nSpeckRange;
	m_stereoMatcher.m_SGBM.fullDP = m_bFullDP;
}


/*----------------------------
 * ���� : �����Ӳ� ��ť��Ӧ
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClk_DoCompDisp
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClk_DoCompDisp()
{
	// TODO: Add your control notification handler code here 
	
	// ��ͣ��ʾ����ͷ����Ĳ���
	KillTimer(1);			

	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_BM)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_SGBM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StopCam)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	GetDlgItem(IDC_CBN2MethodList)->EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////
	// ������ʼ��
	UpdateData(TRUE);
	if (m_nMaxDisp==0)
	{
		AfxMessageBox(_T("��������ƥ���㷨����"));
		return;
	}

	OptionStereoMatch optMatch;
	CStringA xmlPath;			// �����������ļ�
	vector<CStringA> imgFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgFiles2;	
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;

	cv::Mat img1, img2, img1p, img2p, disp, disp8u, pointCloud;
	LPCTSTR errMsg;

	try 
	{
		//////////////////////////////////////////////////////////////////////////
		// ��������е�����ƥ��ѡ������
		DoParseOptionsOfStereoMatch( optMatch );

		//////////////////////////////////////////////////////////////////////////
		// ѡ��/Ԥ��ͼ������� or ����ͼƬ��
		if (optMatch.readLocalImage)
		{
			// ѡ������ͼ
			imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);
			// ѡ������ͼ
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
				errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
				throw errMsg;
			}

			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename);
			img2 = imread(img2_filename);
		} 
		else
		{
			lfCam >> img1;
			//Jacqueszhu 14/07/2015
			cv::resize(img1, img1, Size(m_nImageWidth, m_nImageHeight), 0, 0, 1);
			riCam >> img2;
			cv::resize(img2, img2, Size(m_nImageWidth, m_nImageHeight), 0, 0, 1);
		}

		//////////////////////////////////////////////////////////////////////////
		// ��ȡ˫ĿУ���任����
		if( optMatch.useStereoRectify )
		{
			// ������ͷ��������ļ�
			vector<CStringA> xmlFiles;
			xmlFiles = DoSelectFiles(
				_T("*.xml"), 
				OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
				_T("XML/YML file (*.xml; *.yml) |*.xml; *.yml | All Files (*.*) |*.*||"), 
				_T("ѡ������ͷ��������ļ�"),
				m_workDir
				);
			if( xmlFiles.empty() )	
			{
				errMsg = _T("û��ѡ����Ч������ͷ��������ļ�!");			
				throw errMsg;
			}
			xmlPath = xmlFiles[0];			// ��ȡxml�ļ�·��
			xml_filename = xmlPath;

			// ��������ͷ�������
			switch (m_stereoMatcher.init(img1.cols, img1.rows, xml_filename))
			{
			case 0:
			case -99:
				errMsg = _T("��ȡ����ͷ��������ļ�ʧ�ܣ�������ѡ��!");			
				throw errMsg;
			case -1:
				errMsg = _T("���������ͼ��ߴ��뵱ǰ���õ�ͼ��ߴ粻һ�£�������ѡ��!");			
				throw errMsg;
			case -2:
				if (optMatch.generatePointCloud)
				{
					optMatch.generatePointCloud = false;
					errMsg = _T("�����ļ���Ӧ��У���������� BOUGUET �������޷�������ά����!");			
					throw errMsg;
				}
				break;
			}

		}	
		else
			m_stereoMatcher.init(img1.cols, img1.rows, "");

		//////////////////////////////////////////////////////////////////////////
		// ��ʼ����ͼ���Ӳ�
		m_stereoMatcher.m_BM.state->disp12MaxDiff = m_nDisp12MaxDiff;
		m_stereoMatcher.m_SGBM.disp12MaxDiff = m_nDisp12MaxDiff;

		int frameCount = 0;	//ͼ�����
		PointCloudAnalyzer pointCloudAnalyzer;
		clock_t tStart = clock();
		MSG msg;

		while(true)
		{
			// MFC ������Ϣ����
			if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
			{ 
				if(msg.message == WM_QUIT) 
				{ 
					break; 
				}	
				::TranslateMessage(&msg); 
				::DispatchMessage(&msg);
			}

			// ����ͼ��
			if (optMatch.readLocalImage)
			{
				if (frameCount >= MIN(imgFiles1.size(), imgFiles2.size()))
					break;
				img1_filename = imgFiles1[frameCount];
				img2_filename = imgFiles2[frameCount];
				img1 = imread(img1_filename, 1);
				img2 = imread(img2_filename, 1);
				if(img1.empty() || img2.empty()) break;
				frameCount++;
			} 
			else
			{
				lfCam >> img1;
				//Jacqueszhu 14/07/2015
				cv::resize(img1, img1, Size(m_nImageWidth, m_nImageHeight), 0, 0, 1);
				riCam >> img2;
				cv::resize(img2, img2, Size(m_nImageWidth, m_nImageHeight), 0, 0, 1);
				if(img1.empty()) break;
			}

			// Ԥ����
			if (m_ProcMethod)
			{
				DoFrameProc(img1, img1);
				DoFrameProc(img2, img2);
			}

			// ִ��˫Ŀƥ��
			if (optMatch.stereoMethod == STEREO_BM)
			{
				DoUpdateStateBM();
				m_stereoMatcher.bmMatch(img1, img2, disp, img1p, img2p);
			} 
			else if (optMatch.stereoMethod == STEREO_SGBM)
			{
				DoUpdateStateSGBM(img1.channels());
				m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			}

			// �����Ⱦ�����������ߣ��Աȶ� �ж�׼ ���
			for( j = 0; j < img1p.rows; j += 32 )		
			{
				line( img1p, cvPoint(0,j),	cvPoint(img1p.cols,j), CV_RGB(0,255,0)); 
				line( img2p, cvPoint(0,j),	cvPoint(img2p.cols,j), CV_RGB(0,255,0)); 
			}

			// ���������ͷ��������壿
			if ( optMatch.generatePointCloud )
			{
				m_stereoMatcher.getPointClouds(disp, pointCloud);

				vector<PointCloudAnalyzer::ObjectInfo> objectInfos;
				pointCloudAnalyzer.detectNearObject(img1p, pointCloud, objectInfos);

				if (!objectInfos.empty() && (clock()-tStart) > 500)
				{
					tStart = clock();
					double fl = m_stereoMatcher.m_FL;
					m_ObjectDistance = objectInfos[0].distance; m_ObjectDistance = (int)(m_ObjectDistance * 10000) / 10000.;
					m_ObjectHeight = objectInfos[0].boundRect.height * objectInfos[0].distance / fl; m_ObjectHeight = (int)(m_ObjectHeight * 10000) / 10000.;
					m_ObjectWidth = objectInfos[0].boundRect.width * objectInfos[0].distance / fl; m_ObjectWidth = (int)(m_ObjectWidth * 10000) / 10000.;
					UpdateData(FALSE);
				}
			}

			// ��ʾ��ɫ���Ӳ�ͼ��
			if( optMatch.showColorDisparity )
			{
				m_stereoMatcher.getDisparityImage(disp, disp8u, true);
			}
			else
			{
				m_stereoMatcher.getDisparityImage(disp, disp8u, false);
			}	

			// ������MFC������ʾ
			F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
			F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
			F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );	

			// ���滭����Ӳ�ͼ��
			if( optMatch.saveResults )
				F_Saveframe( img1, img2, disp);

			if( optMatch.delayEachFrame )
				Sleep(m_nDelayTime * 1000);

		}

		// �������һ֡����ͼ��ĵ�������
		if ( optMatch.generatePointCloud )
		{
			m_stereoMatcher.savePointClouds(pointCloud, "points.txt");
		}

		// ��ͼ����������
		m_disparity = Scalar(0);
		F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );

		// �ͷ��ڴ�
		xmlPath.ReleaseBuffer();
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}

	GetDlgItem(IDC_RAD_BM)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_SGBM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN2StopCam)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
	GetDlgItem(IDC_CBN2MethodList)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);

	// ������ʾʵʱ����
	DoShowOrigFrame();
	return;
}


/*----------------------------
 * ���� : ֹͣ�����Ӳ����������ʾ
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClk_StopDispComp
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClk_StopDispComp()
{
	// TODO: Add your control notification handler code here

	// �����˳���Ϣ
	::PostMessage(this->m_hWnd, WM_QUIT, 0, 0);
	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);

	if (lfCam.isOpened() || riCam.isOpened())
	{
		// ���ò��ְ�ť
		GetDlgItem(IDC_BN2StopCam)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_BM)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_SGBM)->EnableWindow(TRUE);
	}

	return;
}


/*----------------------------
 * ���� : ����˫Ŀƥ���㷨��Ĭ�ϲ���
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkDefaultStereoParam
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkDefaultStereoParam()
{
	// TODO: Add your control notification handler code here
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 64;
		m_nSADWinSiz = 19;
		m_nTextThres = 10;
		m_nDisp12MaxDiff = -1;
		m_nPreFiltCap = 31;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
		UpdateData(FALSE);
	} 
	else if(m_nID_RAD == IDC_RAD_SGBM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 64;
		m_nSADWinSiz = 7;
		m_nDisp12MaxDiff = -1;
		m_nPreFiltCap = 63;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
		m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
		m_pCheck->SetCheck(0);
		UpdateData(FALSE);
	}
}


/*----------------------------
 * ���� : �����е�˫Ŀƥ���������
 *----------------------------
 * ���� : CStereoVisionDlg::DoClearParamsOfStereoMatch
 * ���� : private 
 * ���� : void
 *
 * ���� : void
 */
void CStereoVisionDlg::DoClearParamsOfStereoMatch(void)
{
	m_nMinDisp = 0;	
	m_nMaxDisp = 0;
	m_nSADWinSiz = 0;
	m_nTextThres = 0;
	m_nDisp12MaxDiff = -1;
	m_nPreFiltCap = 0;
	m_nUniqRatio = 0;
	m_nSpeckRange = 0;
	m_nSpeckWinSiz = 0;
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
	m_pCheck->SetCheck(0);
	UpdateData(FALSE);
	return;
}


/*----------------------------
 * ���� : ���ѡ�� BM �㷨�����в������㣬ʹ����ؿؼ�
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkRad_BM
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkRad_BM()
{
	// TODO: Add your control notification handler code here
	DoClearParamsOfStereoMatch();
	m_spinPreFiltCap.SetRange(0, 31);
	GetDlgItem(IDC_EDIT_minDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_maxDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SADWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_textThres)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_preFiltCap)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_uniqRatio)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckRange)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_fullDP)->EnableWindow(FALSE);
}


/*----------------------------
 * ���� : ���ѡ�� SGBM �㷨�����в������㣬ʹ����ؿؼ�
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClkRad_SGBM
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClkRad_SGBM()
{
	// TODO: Add your control notification handler code here
	DoClearParamsOfStereoMatch();
	m_spinPreFiltCap.SetRange(0, 100);
	GetDlgItem(IDC_EDIT_minDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_maxDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SADWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_textThres)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_preFiltCap)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_uniqRatio)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckRange)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_fullDP)->EnableWindow(TRUE);
}


/*----------------------------
 * ���� : ��������Ӳ�ֵ����ת��ť  ��Ӧ����
 *----------------------------
 * ���� : CStereoVisionDlg::OnDeltaposSpin_MaxDisp
 * ���� : private 
 * ���� : void
 *
 * ���� : NMHDR * pNMHDR
 * ���� : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_MaxDisp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	m_nMaxDisp += (int)pNMUpDown->iDelta * 16;
	if(m_nMaxDisp<16) 
		m_nMaxDisp = 16;
	if(m_nMaxDisp>240)
		m_nMaxDisp = 240;

	UpdateData(FALSE);
}


/*----------------------------
 * ���� : ����SAD���ڴ�С����ת��ť  ��Ӧ����
 *----------------------------
 * ���� : CStereoVisionDlg::OnDeltaposSpin_SADWinSiz
 * ���� : private 
 * ���� : void
 *
 * ���� : NMHDR * pNMHDR
 * ���� : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_SADWinSiz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		UpdateData(TRUE);
		m_nSADWinSiz += (int)pNMUpDown->iDelta * 2; 
		if(m_nSADWinSiz % 2 == 0)
			m_nSADWinSiz += 1;
		if(m_nSADWinSiz < 5)
			m_nSADWinSiz = 5;
		if(m_nSADWinSiz > 21)
			m_nSADWinSiz = 21;
		UpdateData(FALSE);
	}
	else if (m_nID_RAD == IDC_RAD_SGBM)
	{
		UpdateData(TRUE);
		m_nSADWinSiz += (int)pNMUpDown->iDelta * 2;
		if(m_nSADWinSiz % 2 == 0)
			m_nSADWinSiz += 1;
		if(m_nSADWinSiz < 1)
			m_nSADWinSiz = 1;
		if(m_nSADWinSiz > 11)
			m_nSADWinSiz = 11;
		UpdateData(FALSE);
	}
}


/*----------------------------
 * ���� : ����SpeckRangeֵ����ת��ť  ��Ӧ����
 *----------------------------
 * ���� : CStereoVisionDlg::OnDeltaposSpin_SpeckRange
 * ���� : private 
 * ���� : void
 *
 * ���� : NMHDR * pNMHDR
 * ���� : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_SpeckRange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		UpdateData(TRUE);
		m_nSpeckRange += (int)pNMUpDown->iDelta;
		if(m_nSpeckRange < 0)
			m_nSpeckRange = 0;
		if(m_nSpeckRange > 64)
			m_nSpeckRange = 64;
		UpdateData(FALSE);
	}
	else if (m_nID_RAD == IDC_RAD_SGBM)
	{
		UpdateData(TRUE);
		m_nSpeckRange += (int)pNMUpDown->iDelta * 16;
		if(m_nSpeckRange < 0)
			m_nSpeckRange = 0;
		if(m_nSpeckRange > 64)
			m_nSpeckRange = 64;
		UpdateData(FALSE);
	}
}


//////////////////////////////////////////////////////////////////////////
/*----------------------------------
 * ���� :	��ȡ��������ʱ���ڵ��ļ���·��
 *----------------------------------
 * ���� :	CStereoVisionDlg::F_GetAppExecPath
 * ���� :	private 
 * ���� :	��������ʱ���ڵ��ļ���·��
 */
CString CStereoVisionDlg::F_GetAppExecPath()
{
	CString strPath;
	TCHAR path[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	::GetModuleFileName(AfxGetApp()->m_hInstance, path, _MAX_PATH);
	_tsplitpath(path, drive, dir, fname, ext);

	strPath.Empty();
	strPath += CString(drive);
	strPath += CString(dir);

	return strPath;
}


/*----------------------------
 * ���� : ��ʾͼ��
 *		 ��Ҫ���Ƶ�ͼ�� src ���Ƶ� des��Ȼ����Ƶ��ؼ���Ϊ ID �� Picture �ؼ�
 *----------------------------
 * ���� : CStereoVisionDlg::F_ShowImage
 * ���� : private 
 * ���� : void
 *
 * ���� : src	[in]	����ʾͼ��
 * ���� : des	[in]	����ͼ��
 * ���� : ID		[in]	ͼ�񴰿ڿؼ�ID
 */
void CStereoVisionDlg::F_ShowImage(Mat& src, Mat& des, UINT ID)
{
	if (src.empty())
	{
		return;
	}
	// ���㽫ͼƬ���ŵ� Image ��������ı�������
	double wRatio = des.cols / (double)src.cols;
	double hRatio = des.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = des.cols / (double)des.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)( src.cols * scale );
	int nh = (int)( src.rows * scale );

	// Ϊ�˽����ź��ͼƬ���� des �����в�λ�������ͼƬ�� des ���Ͻǵ���������ֵ
	int tlx = (int)((des.cols - nw) / 2);
	int tly = (int)((des.rows - nh) / 2);

	// ���� des �� ROI ������������ͼƬ img
	Mat desRoi = des(Rect(tlx, tly, nw, nh));

	// ���src�ǵ�ͨ��ͼ����ת��Ϊ��ͨ��ͼ��
	if (src.channels() == 1)
	{
		Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// ��ͼƬ src_t �������ţ������뵽 des ��
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// ��ͼƬ src �������ţ������뵽 des ��
		resize( src, desRoi, desRoi.size() );
	}

	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC ->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );	// ��ȡ�ؼ��ߴ�λ��
	CvvImage cimg;
	IplImage cpy = des;
	cimg.CopyOf( &cpy );						// ����ͼƬ
	cimg.DrawToHDC( hDC, &rect );				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}


/*----------------------------
 * ���� : ���浱ǰ������ƥ����������
 *		����������ͼ���Ӳ�ͼ���Ӳ�����
 *----------------------------
 * ���� : CStereoVisionDlg::F_Saveframe
 * ���� : private 
 * ���� : void
 *
 * ���� : Mat & lfImg
 * ���� : Mat & riImg
 * ���� : Mat & lfDisp
 */
void CStereoVisionDlg::F_Saveframe(Mat& lfImg, Mat&riImg, Mat& lfDisp)
{
	// TODO: Add your control notification handler code here
	static int nSavedFrames = 0;
	char lfImgName[128], riImgName[128], lfDispName[128], xmlName[128];
	sprintf_s(lfImgName, "%s\\Imgs\\SaveFrame\\left_%02d.png", m_workDir, nSavedFrames);
	sprintf_s(riImgName, "%s\\Imgs\\SaveFrame\\right_%02d.png", m_workDir, nSavedFrames);
	sprintf_s(lfDispName, "%s\\Imgs\\SaveFrame\\disp_%02d.png", m_workDir, nSavedFrames);
	sprintf_s(xmlName, "%s\\Imgs\\SaveFrame\\disp_%02d.txt", m_workDir, nSavedFrames);
	nSavedFrames++;

	imwrite( lfImgName, lfImg);
	imwrite( riImgName, riImg);
	imwrite( lfDispName, lfDisp);

	FILE* fp;
	fopen_s(&fp, xmlName, "wt");
	fprintf(fp, "%d\n", lfDisp.rows);
	fprintf(fp, "%d\n", lfDisp.cols);
	for(int y = 0; y < lfDisp.rows; y++)
	{
		for(int x = 0; x < lfDisp.cols; x++)
		{
			short disp = lfDisp.at<short>(y, x);	
			fprintf(fp, "%d\n", disp);
		}
	}

	fclose(fp);
	return;
}


/*----------------------------
 * ���� : ��Ե���
 *		 ��ԭͼ�� src ִ�� Canny ��Ե��⣬�����ͼ�� des
 *----------------------------
 * ���� : CStereoVisionDlg::F_EdgeDetectCanny
 * ���� : private 
 * ���� : void
 *
 * ���� : src	[in]	Դͼ��
 * ���� : des	[out]	��Եͼ��
 */
void CStereoVisionDlg::F_EdgeDetectCanny(Mat& src, Mat& des)
{
	Mat gray, edge, edge8u;

	edge = cv::Mat(src.size(), CV_16S);

	// ��Դͼ��תΪ�Ҷ�ͼ��
	if (src.channels() == 1)
		src.copyTo(gray);
	else
		cvtColor( src, gray, CV_RGB2GRAY );

	// ��Ե���
	Sobel(gray, edge, CV_16S, 0, 1);
	edge.convertTo(edge8u, CV_8U);

	// ����Ե���ͼ��ת�����ͼ���ʽ
	if(des.channels() == 1)
		edge8u.copyTo(des);
	else
		cvtColor( edge8u, des, CV_GRAY2BGR );	
}


/*----------------------------
 * ���� : ��ʾ����ͷʵʱ����
 *----------------------------
 * ���� : CStereoVisionDlg::DoShowOrigFrame
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::DoShowOrigFrame(void)
{
	m_CBNMethodList.SetCurSel(0);
	m_ProcMethod = SHOW_ORIGINAL_FRAME;
	SetTimer(1, 50, NULL);	// 50ms ��ʱ��ʾ
}


/*----------------------------
 * ���� : ��֡ͼ����д���
 *----------------------------
 * ���� : CStereoVisionDlg::DoFrameProc
 * ���� : private 
 * ���� : void
 *
 * ���� : src	[in]	Դͼ��
 * ���� : des	[out]	�����ͼ��
 */
void  CStereoVisionDlg::DoFrameProc(Mat& src, Mat& dst)
{
	try
	{
		switch( m_ProcMethod )
		{
		case SHOW_EDGE_IMAGE:
			{
				F_EdgeDetectCanny(src, dst);
			}
			break;
		case SHOW_EQUAL_HISTOGRAM:
			{
				vector<Mat> rgb;
				// �ֽ��������
				split(src, rgb);
				// �Ը����������ν���ֱ��ͼ����
				for (int i=0;i<3;i++)
				{
					equalizeHist(rgb[i], rgb[i]);
				}
				// �ϲ�������
				merge(rgb, dst);
			}
			break;
		case SHOW_CONVERT_COLOR:
			{
				m_nID_RAD = GetCheckedRadioButton(IDC_RAD_ToHSV, IDC_RAD_ToXYZ);
				int type = 
					m_nID_RAD == IDC_RAD_ToHSV ? CV_BGR2HSV :
					m_nID_RAD == IDC_RAD_ToHLS ? CV_BGR2HLS :		
					m_nID_RAD == IDC_RAD_ToLab ? CV_BGR2Lab :	
					m_nID_RAD == IDC_RAD_ToLuv ? CV_BGR2Luv :	
					m_nID_RAD == IDC_RAD_ToYCrCb ? CV_BGR2YCrCb :
					CV_BGR2XYZ ;
				cvtColor(src, dst, type);
			}
			break;
		}
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}

	return;
}


//////////////////////////////////////////////////////////////////////////

/*----------------------------
 * ���� : �˳��Ի���
 *----------------------------
 * ���� : CStereoVisionDlg::OnBnClickedCancel
 * ���� : private 
 * ���� : void
 *
 */
void CStereoVisionDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}



void CStereoVisionDlg::OnBnClickedRadCalibfromcam()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CStereoVisionDlg::OnBnClickedRadDispfromcam()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
