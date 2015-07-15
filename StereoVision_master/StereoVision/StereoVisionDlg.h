/********************************************************************
	���� :	2012/10/28
	�ļ� :	.\StereoVision\StereoVision\StereoVisionDlg.h
	���� :	StereoVisionDlg
	���� :	��� chenyusiyuan AT 126 DOT com
	
	���� :	�����Ӿ����Գ������ͷ�ļ�
*********************************************************************/

#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "stdlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "camerads.h"

#include "CvvImage.h"
#include "StereoCalib.h"
#include "StereoMatch.h"
#include "PointCloudAnalyzer.h"

using namespace std;
using namespace cv;


// CStereoVisionDlg dialog
class CStereoVisionDlg : public CDialog
{
// Construction
public:
	CStereoVisionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROBOTVISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:

	typedef enum { STEREO_BM, STEREO_SGBM } STEREO_METHOD;
	typedef enum { CALIB_LOAD_CAMERA_PARAMS, CALIB_SINGLE_CAMERA_FIRST, CALIB_STEREO_CAMERAS_DIRECTLY } CALIB_ORDER;
	typedef enum { SHOW_ORIGINAL_FRAME, SHOW_EDGE_IMAGE, SHOW_EQUAL_HISTOGRAM, SHOW_CONVERT_COLOR } FRAME_PROCESS_METHOD;

	struct OptionStereoMatch
	{
		bool			readLocalImage;		//�Ƿ���뱾��ͼ���������ƥ��
		bool			generatePointCloud;	//�Ƿ�������ά����
		bool			useStereoRectify;	//�Ƿ�ʹ��˫ĿУ���㷨
		bool			saveResults;		//�Ƿ񱣴�ÿ֡ͼ��ƥ�����������ļ�
		bool			delayEachFrame;		//�Ƿ���ʱ��ʾƥ��Ч��
		bool			showColorDisparity;	//�Ƿ���ʾ��ɫ�Ӳ�ͼ
		STEREO_METHOD	stereoMethod;		//ѡ�������ƥ���㷨
		StereoCalib::RECTIFYMETHOD	rectifyMethod;		//ѡ���˫ĿУ���㷨
	};

	struct OptionCameraCalib
	{
		int				numberBoards;		//���̼�����
		int				flagCameraCalib;	//��Ŀ�����־��
		int				flagStereoCalib;	//˫Ŀ�����־��
		int				numberFrameSkip;	//�ǵ����֡������
		bool			doStereoCalib;		//�Ƿ����˫Ŀ�궨
		bool			readLocalImage;		//�Ƿ�ӱ��ض�������ͼƬ
		bool			loadConerDatas;		//�Ƿ�ӱ��ض���ǵ���������
		double			squareSize;			//���̷����С
		cv::Size		cornerSize;			//���̽ǵ���
		CALIB_ORDER		calibOrder;			//������������
		StereoCalib::RECTIFYMETHOD	rectifyMethod;		//ѡ���˫ĿУ���㷨
	};
	
	/***
	 *	ȫ��˽�б���
	 */
	//CCameraDS lfCam;
	//CCameraDS riCam;
	VideoCapture lfCam;
	VideoCapture riCam;
	cv::Mat m_lfImage;
	cv::Mat m_riImage;
	cv::Mat m_disparity;
	StereoCalib m_stereoCalibrator;
	StereoMatch m_stereoMatcher;
	int m_lfCamID;
	int m_riCamID;
	int m_nCamCount;
	int m_ProcMethod;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImageChannels;
	CString m_workDir;

#pragma region �ؼ���������
	int m_nCornerSize_X;
	int m_nCornerSize_Y;
	int m_nBoards;
	int m_nDelayTime;
	int m_nMinDisp;
	int m_nMaxDisp;
	int m_nSADWinSiz;
	int m_nTextThres;
	int m_nDisp12MaxDiff;
	int m_nPreFiltCap;
	int m_nUniqRatio;
	int m_nSpeckRange;
	int m_nSpeckWinSiz;
	UINT m_nID_RAD;
	BOOL m_bFullDP;
	BOOL m_bSaveFrame;
	float m_nSquareSize;
	double m_ObjectWidth;
	double m_ObjectHeight;
	double m_ObjectDistance;
	double m_ObjectDisparity;

	CButton* m_pCheck;
	CComboBox m_CBNCamList;
	CComboBox m_CBNMethodList;
	CComboBox m_CBNResolution;
	CSpinButtonCtrl m_spinMinDisp;
	CSpinButtonCtrl m_spinMaxDisp;
	CSpinButtonCtrl m_spinSADWinSiz;
	CSpinButtonCtrl m_spinTextThres;
	CSpinButtonCtrl m_spinDisp12MaxDiff;
	CSpinButtonCtrl m_spinPreFiltCap;
	CSpinButtonCtrl m_spinUniqRatio;
	CSpinButtonCtrl m_spinSpeckRange;
	CSpinButtonCtrl m_spinSpeckWinSiz;
#pragma endregion �ؼ���������

	/***
	 *	���ܺ���
	 */
	void DoShowOrigFrame(void);
	void DoStereoCalib(void);
	void DoFrameProc(Mat& src, Mat& dst);
	void DoParseOptionsOfCameraCalib(OptionCameraCalib& opt);
	void DoParseOptionsOfStereoMatch(OptionStereoMatch& opt);
	void DoClearParamsOfStereoMatch(void);
	vector<CStringA> DoSelectFiles(LPCTSTR	lpszDefExt, DWORD	dwFlags, LPCTSTR	lpszFilter, LPCWSTR	lpstrTitle, LPCWSTR	lpstrInitialDir);
	void DoUpdateStateBM(void);
	void DoUpdateStateSGBM(int imgChannels);

	CString F_GetAppExecPath();
	void F_Gray2Color(Mat& gray_mat, Mat& color_mat);
	void F_Saveframe(Mat& lfImg, Mat&riImg, Mat& lfDisp);
	void F_ShowImage(Mat& src, Mat& des, UINT ID);
	void F_EdgeDetectCanny(Mat& src, Mat& des);

	
	/***
	 *	����ؼ���Ϣ��Ӧ����
	 */
	afx_msg void OnCbnSelchgCbn1Camlist();
	afx_msg void OnBnClkRunCam();
	afx_msg void OnBnClkStopCam();
	afx_msg void OnCbnSelchgCbn2Methodlist();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClkDefaultCamCalibParam();
	afx_msg void OnBnClkDefaultStereoParam();
	afx_msg void OnBnClkRad_BM();
	afx_msg void OnBnClkRad_SGBM();
	afx_msg void OnDeltaposSpin_MaxDisp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin_SADWinSiz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin_SpeckRange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClk_DoCompDisp();
	afx_msg void OnBnClk_StopDispComp();
	afx_msg void OnBnClk_DoCameraCalib();
	afx_msg void OnBnClk_ExitCameraCalib();
	afx_msg void OnCbnSelchangeCbnResolution();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedRadCalibfromcam();
	afx_msg void OnBnClickedRadDispfromcam();
};
