//------------------------------------------------------------------------------
// <copyright file="ColorBasics.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <strsafe.h>
#include "resource.h"
#include "ColorBasics.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv\cv.hpp"
#include <typeinfo>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
using namespace cv;

ofstream outFile;  //default IO file. Replaces items in file. If file does not exist creates new file

static const float c_JointThickness = 3.0f;
static const float c_TrackedBoneThickness = 6.0f;
static const float c_InferredBoneThickness = 1.0f;
static const float c_HandSize = 30.0f;
int FrameNumber = 0;

boolean tracked = false;

/// <summary>
/// Entry point for the application
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="hPrevInstance">always 0</param>
/// <param name="lpCmdLine">command line arguments</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
/// <returns>status</returns>
int APIENTRY wWinMain(    
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
    )
{
	char name[256] = { '\0' };
	sprintf(name, "datapoints.csv");

	outFile = ofstream(name);
	// Write the header -- Joint Position
	outFile << "Frame_Number" << ",";
	outFile << "Time_Stamp" << ",";
	outFile << "SpineBase_x" << ",";
	outFile << "SpineBase_y" << ",";
	outFile << "SpineBase_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "SpineMid_x" << ",";
	outFile << "SpineMid_y" << ",";
	outFile << "SpineMid_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "Neck_x" << ",";
	outFile << "Neck_y" << ",";
	outFile << "Neck_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "Head_x" << ",";
	outFile << "Head_y" << ",";
	outFile << "Head_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ShoulderLeft_x" << ",";
	outFile << "ShoulderLeft_y" << ",";
	outFile << "ShoulderLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ElbowLeft_x" << ",";
	outFile << "ElbowLeft_y" << ",";
	outFile << "ElbowLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "WristLeft_x" << ",";
	outFile << "WristLeft_y" << ",";
	outFile << "WristLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HandLeft_x" << ",";
	outFile << "HandLeft_y" << ",";
	outFile << "HandLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ShoulderRight_x" << ",";
	outFile << "ShoulderRight_y" << ",";
	outFile << "ShoulderRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ElbowRight_x" << ",";
	outFile << "ElbowRight_y" << ",";
	outFile << "ElbowRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "WristRight_x" << ",";
	outFile << "WristRight_y" << ",";
	outFile << "WristRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HandRight_x" << ",";
	outFile << "HandRight_y" << ",";
	outFile << "HandRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HipLeft_x" << ",";
	outFile << "HipLeft_y" << ",";
	outFile << "HipLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "KneeLeft_x" << ",";
	outFile << "KneeLeft_y" << ",";
	outFile << "KneeLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "AnkleLeft_x" << ",";
	outFile << "AnkleLeft_y" << ",";
	outFile << "AnkleLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "FootLeft_x" << ",";
	outFile << "FootLeft_y" << ",";
	outFile << "FootLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HipRight_x" << ",";
	outFile << "HipRight_y" << ",";
	outFile << "HipRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "KneeRight_x" << ",";
	outFile << "KneeRight_y" << ",";
	outFile << "KneeRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "AnkleRight_x" << ",";
	outFile << "AnkleRight_y" << ",";
	outFile << "AnkleRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "FootRight_x" << ",";
	outFile << "FootRight_y" << ",";
	outFile << "FootRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "SpineShoulder_x" << ",";
	outFile << "SpineShoulder_y" << ",";
	outFile << "SpineShoulder_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HandTipLeft_x" << ",";
	outFile << "HandTipLeft_y" << ",";
	outFile << "HandTipLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ThumbLeft_x" << ",";
	outFile << "ThumbLeft_y" << ",";
	outFile << "ThumbLeft_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "HandTipRight_x" << ",";
	outFile << "HandTipRight_y" << ",";
	outFile << "HandTipRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "ThumbRight_x" << ",";
	outFile << "ThumbRight_y" << ",";
	outFile << "ThumbRight_z" << ",";
	outFile << "ScreenX" << ",";
	outFile << "ScreenY" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << "Start_Joint" << ",";
	outFile << "End_Joint" << ",";
	outFile << "Absolute_Orientation_x" << ",";
	outFile << "Absolute_Orientation_y" << ",";
	outFile << "Absolute_Orientation_z" << ",";
	outFile << "Hierarchical_Orientation_x" << ",";
	outFile << "Hierarchical_Orientation_y" << ",";
	outFile << "Hierarchical_Orientation_z" << ",";
	outFile << std::endl;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//ofstream outFile;  //default IO file. Replaces items in file. If file does not exist creates new file
    CColorBasics application;

    application.Run(hInstance, nShowCmd);
}

/// <summary>
/// Constructor
/// </summary>
CColorBasics::CColorBasics() :
    m_hWnd(NULL),
    m_nStartTime(0),
    m_nLastCounter(0),
    m_nFramesSinceUpdate(0),
    m_fFreq(0),
    m_nNextStatusTime(0LL),
    m_bSaveScreenshot(false),
    m_pKinectSensor(NULL),
    m_pColorFrameReader(NULL),
    m_pD2DFactory(NULL),
    m_pDrawColor(NULL),
    m_pColorRGBX(NULL),

	// Body Reader Function
	m_pBodyFrameReader(NULL),
	m_pCoordinateMapper(NULL)
{
    LARGE_INTEGER qpf = {0};
    if (QueryPerformanceFrequency(&qpf))
    {
        m_fFreq = double(qpf.QuadPart);
    }

    // create heap storage for color pixel data in RGBX format
    m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];
}
  

/// <summary>
/// Destructor
/// </summary>
CColorBasics::~CColorBasics()
{
    // clean up Direct2D renderer
    if (m_pDrawColor)
    {
        delete m_pDrawColor;
        m_pDrawColor = NULL;
    }

    if (m_pColorRGBX)
    {
        delete [] m_pColorRGBX;
        m_pColorRGBX = NULL;
    }

    // clean up Direct2D
    SafeRelease(m_pD2DFactory);

    // done with color frame reader
    SafeRelease(m_pColorFrameReader);

	// done with body frame reader
	SafeRelease(m_pBodyFrameReader);

    // close the Kinect Sensor
    if (m_pKinectSensor)
    {
        m_pKinectSensor->Close();
    }

    SafeRelease(m_pKinectSensor);
}

/// <summary>
/// Creates the main window and begins processing
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
int CColorBasics::Run(HINSTANCE hInstance, int nCmdShow)
{
    MSG       msg = {0};
    WNDCLASS  wc;

    // Dialog custom window class
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon         = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_APP));
    wc.lpfnWndProc   = DefDlgProcW;
    wc.lpszClassName = L"ColorBasicsAppDlgWndClass";

    if (!RegisterClassW(&wc))
    {
        return 0;
    }

    // Create main application window
    HWND hWndApp = CreateDialogParamW(
        NULL,
        MAKEINTRESOURCE(IDD_APP),
        NULL,
        (DLGPROC)CColorBasics::MessageRouter, 
        reinterpret_cast<LPARAM>(this));

    // Show window
    ShowWindow(hWndApp, nCmdShow);

    // Main message loop
    while (WM_QUIT != msg.message)
    {
        Update();

        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if (hWndApp && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

    }

	outFile.close();
    return static_cast<int>(msg.wParam);
}

/// <summary>
/// Main processing function
/// </summary>
void CColorBasics::Update()
{
    if (!m_pColorFrameReader)
    {
        return;
    }

    IColorFrame* pColorFrame = NULL;

    HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);

    if (SUCCEEDED(hr))
    {
        INT64 nTime = 0;
        IFrameDescription* pFrameDescription = NULL;
		IBodyFrame* pBodyFrame = NULL;
        int nWidth = 0;
        int nHeight = 0;
        ColorImageFormat imageFormat = ColorImageFormat_None;
        UINT nBufferSize = 0;
        RGBQUAD *pBuffer = NULL;

        hr = pColorFrame->get_RelativeTime(&nTime);

        if (SUCCEEDED(hr))
        {
            hr = pColorFrame->get_FrameDescription(&pFrameDescription);
        }

        if (SUCCEEDED(hr))
        {
            hr = pFrameDescription->get_Width(&nWidth);
        }

        if (SUCCEEDED(hr))
        {
            hr = pFrameDescription->get_Height(&nHeight);
        }

        if (SUCCEEDED(hr))
        {
            hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
        }

        if (SUCCEEDED(hr))
        {
            if (imageFormat == ColorImageFormat_Bgra)
            {
                hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
            }
            else if (m_pColorRGBX)
            {
                pBuffer = m_pColorRGBX;
                nBufferSize = cColorWidth * cColorHeight * sizeof(RGBQUAD);
                hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);            
            }
            else
            {
                hr = E_FAIL;
            }
        }

        if (SUCCEEDED(hr))
        {
            ProcessColor(nTime, pBuffer, nWidth, nHeight);
        }

        SafeRelease(pFrameDescription);

		if (!m_pBodyFrameReader)
		{
			return;
		}

		hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

		if (SUCCEEDED(hr))
		{

			IBody* ppBodies[BODY_COUNT] = { 0 };

			if (SUCCEEDED(hr))
			{
				hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
			}

			if (SUCCEEDED(hr))
			{
				ProcessBody(nTime, BODY_COUNT, ppBodies);
			}

			for (int i = 0; i < _countof(ppBodies); ++i)
			{
				SafeRelease(ppBodies[i]);
			}
		}

		if (tracked == true) {

			WCHAR szScreenshotPath[MAX_PATH];
			// Retrieve the path to My Photos
			GetScreenshotFileName(szScreenshotPath, _countof(szScreenshotPath));

			// Write out the bitmap to disk
			HRESULT hr = SaveBitmapToFile(reinterpret_cast<BYTE*>(pBuffer), nWidth, nHeight, sizeof(RGBQUAD) * 8, szScreenshotPath);
		}

		SafeRelease(pBodyFrame);
    }
	
    SafeRelease(pColorFrame);

	// Process BodyFrame
	/*if (!m_pBodyFrameReader)
	{
		return;
	}
	
	IBodyFrame* pBodyFrame = NULL;

	hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;

		hr = pBodyFrame->get_RelativeTime(&nTime);

		IBody* ppBodies[BODY_COUNT] = { 0 };

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
		}

		if (SUCCEEDED(hr))
		{
			ProcessBody(nTime, BODY_COUNT, ppBodies);
		}

		for (int i = 0; i < _countof(ppBodies); ++i)
		{
			SafeRelease(ppBodies[i]);
		}
	}

	SafeRelease(pBodyFrame);*/
}

/// <summary>
/// Handles window messages, passes most to the class instance to handle
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CColorBasics::MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CColorBasics* pThis = NULL;
    
    if (WM_INITDIALOG == uMsg)
    {
        pThis = reinterpret_cast<CColorBasics*>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<CColorBasics*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->DlgProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

/// <summary>
/// Handle windows messages for the class instance
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CColorBasics::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);



    switch (message)
    {
        case WM_INITDIALOG:
        {
            // Bind application window handle
            m_hWnd = hWnd;

            // Init Direct2D
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

            // Create and initialize a new Direct2D image renderer (take a look at ImageRenderer.h)
            // We'll use this to draw the data we receive from the Kinect to the screen
            m_pDrawColor = new ImageRenderer();
            HRESULT hr = m_pDrawColor->Initialize(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), m_pD2DFactory, cColorWidth, cColorHeight, cColorWidth * sizeof(RGBQUAD)); 
            if (FAILED(hr))
            {
                SetStatusMessage(L"Failed to initialize the Direct2D draw device.", 10000, true);
            }

            // Get and initialize the default Kinect sensor
            InitializeDefaultSensor();
        }
        break;

        // If the titlebar X is clicked, destroy app
        case WM_CLOSE:
			Processvideo();
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            // Quit the main message pump
            PostQuitMessage(0);
            break;

        // Handle button press
        case WM_COMMAND:
            // If it was for the screenshot control and a button clicked event, save a screenshot next frame 
            if (IDC_BUTTON_SCREENSHOT == LOWORD(wParam) && BN_CLICKED == HIWORD(wParam))
            {
                m_bSaveScreenshot = true;
            }
            break;
    }

    return FALSE;
}

/// <summary>
/// Initializes the default Kinect sensor
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT CColorBasics::InitializeDefaultSensor()
{
    HRESULT hr;
	
    hr = GetDefaultKinectSensor(&m_pKinectSensor);
    if (FAILED(hr))
    {
        return hr;
    }

    if (m_pKinectSensor)
    {
        // Initialize the Kinect and get the color reader
        IColorFrameSource* pColorFrameSource = NULL;
		IBodyFrameSource* pBodyFrameSource = NULL;

        hr = m_pKinectSensor->Open();

        if (SUCCEEDED(hr))
        {
            hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
        }

        if (SUCCEEDED(hr))
        {
            hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
        }

        SafeRelease(pColorFrameSource);

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
		}

		SafeRelease(pBodyFrameSource);
    }

    if (!m_pKinectSensor || FAILED(hr))
    {
        SetStatusMessage(L"No ready Kinect found!", 10000, true);
        return E_FAIL;
    }

    return hr;
}

/// <summary>
/// Handle new color data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// </summary>
void CColorBasics::ProcessColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight) 
{
    if (m_hWnd)
    {
        if (!m_nStartTime)
        {
            m_nStartTime = nTime;
        }

        double fps = 0.0;

        LARGE_INTEGER qpcNow = {0};
        if (m_fFreq)
        {
            if (QueryPerformanceCounter(&qpcNow))
            {
                if (m_nLastCounter)
                {
                    m_nFramesSinceUpdate++;
                    fps = m_fFreq * m_nFramesSinceUpdate / double(qpcNow.QuadPart - m_nLastCounter);
                }
            }
        }

        WCHAR szStatusMessage[64];
        StringCchPrintf(szStatusMessage, _countof(szStatusMessage), L" FPS = %0.2f    Time = %I64d", fps, (nTime - m_nStartTime));

        if (SetStatusMessage(szStatusMessage, 1000, false))
        {
            m_nLastCounter = qpcNow.QuadPart;
            m_nFramesSinceUpdate = 0;
        }
    }

    // Make sure we've received valid data
    if (pBuffer && (nWidth == cColorWidth) && (nHeight == cColorHeight))
    {
        // Draw the data with Direct2D
        m_pDrawColor->Draw(reinterpret_cast<BYTE*>(pBuffer), cColorWidth * cColorHeight * sizeof(RGBQUAD));

        if (m_bSaveScreenshot)
        {
            WCHAR szScreenshotPath[MAX_PATH];

            // Retrieve the path to My Photos
            GetScreenshotFileName(szScreenshotPath, _countof(szScreenshotPath));

            // Write out the bitmap to disk
            HRESULT hr = SaveBitmapToFile(reinterpret_cast<BYTE*>(pBuffer), nWidth, nHeight, sizeof(RGBQUAD) * 8, szScreenshotPath);

            WCHAR szStatusMessage[64 + MAX_PATH];
            if (SUCCEEDED(hr))
            {
                // Set the status bar to show where the screenshot was saved
                StringCchPrintf(szStatusMessage, _countof(szStatusMessage), L"Screenshot saved to %s", szScreenshotPath);
            }
            else
            {
                StringCchPrintf(szStatusMessage, _countof(szStatusMessage), L"Failed to write screenshot to %s", szScreenshotPath);
            }

            SetStatusMessage(szStatusMessage, 5000, true);

            // toggle off so we don't save a screenshot again next frame
            m_bSaveScreenshot = false;
        }
    }
}

/// <summary>
/// Handle new body data
/// <param name="nTime">timestamp of frame</param>
/// <param name="nBodyCount">body data count</param>
/// <param name="ppBodies">body data in frame</param>
/// </summary>
void CColorBasics::ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies)
{
	if (m_hWnd)
	{
		HRESULT hr = EnsureDirect2DResources();

		if (SUCCEEDED(hr) && m_pRenderTarget && m_pCoordinateMapper)
		{
			/*m_pRenderTarget->BeginDraw();
			m_pRenderTarget->Clear();*/

			RECT rct;
			GetClientRect(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), &rct);
			int width = rct.right;
			int height = rct.bottom;

			for (int i = 0; i < nBodyCount; ++i)
			{
				IBody* pBody = ppBodies[i];
				if (pBody)
				{
					BOOLEAN bTracked = false;
					hr = pBody->get_IsTracked(&bTracked);

					if (SUCCEEDED(hr) && bTracked)
					{
						Joint joints[JointType_Count];
						D2D1_POINT_2F jointPoints[JointType_Count];
						HandState leftHandState = HandState_Unknown;
						HandState rightHandState = HandState_Unknown;

						pBody->get_HandLeftState(&leftHandState);
						pBody->get_HandRightState(&rightHandState);

						hr = pBody->GetJoints(_countof(joints), joints);
						if (SUCCEEDED(hr))
						{
							if (tracked == true) {
								outFile << FrameNumber << ",";
								outFile << 0 << ",";
								FrameNumber++;
								for (int j = 0; j < _countof(joints); ++j)
								{
									//jointPoints[j] = BodyToScreen(joints[j].Position, width, height);
									OutputJoints(joints[j]);
								}
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 1 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 20 << ",";
								outFile << 2 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 2 << ",";
								outFile << 3 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 20 << ",";
								outFile << 4 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 4 << ",";
								outFile << 5 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 5 << ",";
								outFile << 6 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 6 << ",";
								outFile << 7 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 20 << ",";
								outFile << 8 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 8 << ",";
								outFile << 9 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 9 << ",";
								outFile << 10 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 10 << ",";
								outFile << 11 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 12 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 12 << ",";
								outFile << 13 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 13 << ",";
								outFile << 14 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 14 << ",";
								outFile << 15 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 16 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 16 << ",";
								outFile << 17 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 17 << ",";
								outFile << 18 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 18 << ",";
								outFile << 19 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 20 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 7 << ",";
								outFile << 21 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 7 << ",";
								outFile << 22 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 11 << ",";
								outFile << 23 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 11 << ",";
								outFile << 24 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << 0 << ",";
								outFile << std::endl;
							}
							tracked = true;

							//DrawBody(joints, jointPoints);

							/*DrawHand(leftHandState, jointPoints[JointType_HandLeft]);
							DrawHand(rightHandState, jointPoints[JointType_HandRight]);*/
						}
					}
				}
			}

		}

	}
}
/// <summary>
/// Set the status bar message
/// </summary>
/// <param name="szMessage">message to display</param>
/// <param name="showTimeMsec">time in milliseconds to ignore future status messages</param>
/// <param name="bForce">force status update</param>
bool CColorBasics::SetStatusMessage(_In_z_ WCHAR* szMessage, DWORD nShowTimeMsec, bool bForce)
{
    INT64 now = GetTickCount64();

    if (m_hWnd && (bForce || (m_nNextStatusTime <= now)))
    {
        SetDlgItemText(m_hWnd, IDC_STATUS, szMessage);
        m_nNextStatusTime = now + nShowTimeMsec;

        return true;
    }

    return false;
}

/// <summary>
/// Get the name of the file where screenshot will be stored.
/// </summary>
/// <param name="lpszFilePath">string buffer that will receive screenshot file name.</param>
/// <param name="nFilePathSize">number of characters in lpszFilePath string buffer.</param>
/// <returns>
/// S_OK on success, otherwise failure code.
/// </returns>
HRESULT CColorBasics::GetScreenshotFileName(_Out_writes_z_(nFilePathSize) LPWSTR lpszFilePath, UINT nFilePathSize)
{
    WCHAR* pszKnownPath = NULL;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &pszKnownPath);

    if (SUCCEEDED(hr))
    {
        // Get the time
        WCHAR szTimeString[MAX_PATH];
        GetTimeFormatEx(NULL, 0, NULL, L"hh'-'mm'-'ss", szTimeString, _countof(szTimeString));

        // File name will be KinectScreenshotColor-HH-MM-SS.bmp
        StringCchPrintfW(lpszFilePath, nFilePathSize, L"%s\\FrameNumber-%d.bmp", pszKnownPath, FrameNumber);
    }

    if (pszKnownPath)
    {
        CoTaskMemFree(pszKnownPath);
    }

    return hr;
}

/// <summary>
/// Save passed in image data to disk as a bitmap
/// </summary>
/// <param name="pBitmapBits">image data to save</param>
/// <param name="lWidth">width (in pixels) of input image data</param>
/// <param name="lHeight">height (in pixels) of input image data</param>
/// <param name="wBitsPerPixel">bits per pixel of image data</param>
/// <param name="lpszFilePath">full file path to output bitmap to</param>
/// <returns>indicates success or failure</returns>
HRESULT CColorBasics::SaveBitmapToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath)
{
    DWORD dwByteCount = lWidth * lHeight * (wBitsPerPixel / 8);

    BITMAPINFOHEADER bmpInfoHeader = {0};

    bmpInfoHeader.biSize        = sizeof(BITMAPINFOHEADER);  // Size of the header
    bmpInfoHeader.biBitCount    = wBitsPerPixel;             // Bit count
    bmpInfoHeader.biCompression = BI_RGB;                    // Standard RGB, no compression
    bmpInfoHeader.biWidth       = lWidth;                    // Width in pixels
    bmpInfoHeader.biHeight      = -lHeight;                  // Height in pixels, negative indicates it's stored right-side-up
    bmpInfoHeader.biPlanes      = 1;                         // Default
    bmpInfoHeader.biSizeImage   = dwByteCount;               // Image size in bytes

    BITMAPFILEHEADER bfh = {0};

    bfh.bfType    = 0x4D42;                                           // 'M''B', indicates bitmap
    bfh.bfOffBits = bmpInfoHeader.biSize + sizeof(BITMAPFILEHEADER);  // Offset to the start of pixel data
    bfh.bfSize    = bfh.bfOffBits + bmpInfoHeader.biSizeImage;        // Size of image + headers

    // Create the file on disk to write to
    HANDLE hFile = CreateFileW(lpszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Return if error opening file
    if (NULL == hFile) 
    {
        return E_ACCESSDENIED;
    }

    DWORD dwBytesWritten = 0;
    
    // Write the bitmap file header
    if (!WriteFile(hFile, &bfh, sizeof(bfh), &dwBytesWritten, NULL))
    {
        CloseHandle(hFile);
        return E_FAIL;
    }
    
    // Write the bitmap info header
    if (!WriteFile(hFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &dwBytesWritten, NULL))
    {
        CloseHandle(hFile);
        return E_FAIL;
    }
    
    // Write the RGB Data
    if (!WriteFile(hFile, pBitmapBits, bmpInfoHeader.biSizeImage, &dwBytesWritten, NULL))
    {
        CloseHandle(hFile);
        return E_FAIL;
    }    

    // Close the file
    CloseHandle(hFile);
    return S_OK;
}

/// <summary>
/// Ensure necessary Direct2d resources are created
/// </summary>
/// <returns>S_OK if successful, otherwise an error code</returns>
HRESULT CColorBasics::EnsureDirect2DResources()
{
	HRESULT hr = S_OK;

	if (m_pD2DFactory && !m_pRenderTarget)
	{
		RECT rc;
		GetWindowRect(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), &rc);

		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		D2D1_SIZE_U size = D2D1::SizeU(width, height);
		D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();
		rtProps.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE);
		rtProps.usage = D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;

		// Create a Hwnd render target, in order to render to the window set in initialize
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			rtProps,
			D2D1::HwndRenderTargetProperties(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), size),
			&m_pRenderTarget
		);

		if (FAILED(hr))
		{
			SetStatusMessage(L"Couldn't create Direct2D render target!", 10000, true);
			return hr;
		}

		// light green
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.27f, 0.75f, 0.27f), &m_pBrushJointTracked);

		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &m_pBrushJointInferred);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &m_pBrushBoneTracked);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &m_pBrushBoneInferred);

		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 0.5f), &m_pBrushHandClosed);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 0.5f), &m_pBrushHandOpen);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 0.5f), &m_pBrushHandLasso);
	}

	return hr;
}

/// <summary>
/// Dispose Direct2d resources 
/// </summary>
void CColorBasics::DiscardDirect2DResources()
{
	SafeRelease(m_pRenderTarget);

	SafeRelease(m_pBrushJointTracked);
	SafeRelease(m_pBrushJointInferred);
	SafeRelease(m_pBrushBoneTracked);
	SafeRelease(m_pBrushBoneInferred);

	SafeRelease(m_pBrushHandClosed);
	SafeRelease(m_pBrushHandOpen);
	SafeRelease(m_pBrushHandLasso);
}

/// <summary>
/// Converts a body point to screen space
/// </summary>
/// <param name="bodyPoint">body point to tranform</param>
/// <param name="width">width (in pixels) of output buffer</param>
/// <param name="height">height (in pixels) of output buffer</param>
/// <returns>point in screen-space</returns>
D2D1_POINT_2F CColorBasics::BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height)
{
	// Calculate the body's position on the screen
	DepthSpacePoint depthPoint = { 0 };
	m_pCoordinateMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);

	float screenPointX = static_cast<float>(depthPoint.X * width) / cDepthWidth;
	float screenPointY = static_cast<float>(depthPoint.Y * height) / cDepthHeight;

	return D2D1::Point2F(screenPointX, screenPointY);
}

/// <summary>
/// Output Joints
/// </summary>
/// <param name="pJoints">joint data</param>
void CColorBasics::OutputJoints(const Joint pJoints)
{
	outFile << pJoints.Position.X << ",";
	outFile << pJoints.Position.Y << ",";
	outFile << pJoints.Position.Z << ",";
	outFile << 0 << ",";
	outFile << 0 << ",";
}
/// <summary>
/// Draws a body 
/// </summary>
/// <param name="pJoints">joint data</param>
/// <param name="pJointPoints">joint positions converted to screen space</param>
void CColorBasics::DrawBody(const Joint* pJoints, const D2D1_POINT_2F* pJointPoints)
{
	// Draw the bones

	// Torso
	DrawBone(pJoints, pJointPoints, JointType_Head, JointType_Neck);
	DrawBone(pJoints, pJointPoints, JointType_Neck, JointType_SpineShoulder);
	DrawBone(pJoints, pJointPoints, JointType_SpineShoulder, JointType_SpineMid);
	DrawBone(pJoints, pJointPoints, JointType_SpineMid, JointType_SpineBase);
	DrawBone(pJoints, pJointPoints, JointType_SpineShoulder, JointType_ShoulderRight);
	DrawBone(pJoints, pJointPoints, JointType_SpineShoulder, JointType_ShoulderLeft);
	DrawBone(pJoints, pJointPoints, JointType_SpineBase, JointType_HipRight);
	DrawBone(pJoints, pJointPoints, JointType_SpineBase, JointType_HipLeft);

	// Right Arm    
	DrawBone(pJoints, pJointPoints, JointType_ShoulderRight, JointType_ElbowRight);
	DrawBone(pJoints, pJointPoints, JointType_ElbowRight, JointType_WristRight);
	DrawBone(pJoints, pJointPoints, JointType_WristRight, JointType_HandRight);
	DrawBone(pJoints, pJointPoints, JointType_HandRight, JointType_HandTipRight);
	DrawBone(pJoints, pJointPoints, JointType_WristRight, JointType_ThumbRight);

	// Left Arm
	DrawBone(pJoints, pJointPoints, JointType_ShoulderLeft, JointType_ElbowLeft);
	DrawBone(pJoints, pJointPoints, JointType_ElbowLeft, JointType_WristLeft);
	DrawBone(pJoints, pJointPoints, JointType_WristLeft, JointType_HandLeft);
	DrawBone(pJoints, pJointPoints, JointType_HandLeft, JointType_HandTipLeft);
	DrawBone(pJoints, pJointPoints, JointType_WristLeft, JointType_ThumbLeft);

	// Right Leg
	DrawBone(pJoints, pJointPoints, JointType_HipRight, JointType_KneeRight);
	DrawBone(pJoints, pJointPoints, JointType_KneeRight, JointType_AnkleRight);
	DrawBone(pJoints, pJointPoints, JointType_AnkleRight, JointType_FootRight);

	// Left Leg
	DrawBone(pJoints, pJointPoints, JointType_HipLeft, JointType_KneeLeft);
	DrawBone(pJoints, pJointPoints, JointType_KneeLeft, JointType_AnkleLeft);
	DrawBone(pJoints, pJointPoints, JointType_AnkleLeft, JointType_FootLeft);

	// Draw the joints
	/*for (int i = 0; i < JointType_Count; ++i)
	{
		D2D1_ELLIPSE ellipse = D2D1::Ellipse(pJointPoints[i], c_JointThickness, c_JointThickness);

		if (pJoints[i].TrackingState == TrackingState_Inferred)
		{
			m_pRenderTarget->FillEllipse(ellipse, m_pBrushJointInferred);
		}
		else if (pJoints[i].TrackingState == TrackingState_Tracked)
		{
			m_pRenderTarget->FillEllipse(ellipse, m_pBrushJointTracked);
		}
	}*/
}

/// <summary>
/// Draws one bone of a body (joint to joint)
/// </summary>
/// <param name="pJoints">joint data</param>
/// <param name="pJointPoints">joint positions converted to screen space</param>
/// <param name="pJointPoints">joint positions converted to screen space</param>
/// <param name="joint0">one joint of the bone to draw</param>
/// <param name="joint1">other joint of the bone to draw</param>
void CColorBasics::DrawBone(const Joint* pJoints, const D2D1_POINT_2F* pJointPoints, JointType joint0, JointType joint1)
{
	TrackingState joint0State = pJoints[joint0].TrackingState;
	TrackingState joint1State = pJoints[joint1].TrackingState;

	// If we can't find either of these joints, exit
	if ((joint0State == TrackingState_NotTracked) || (joint1State == TrackingState_NotTracked))
	{
		return;
	}

	// Don't draw if both points are inferred
	if ((joint0State == TrackingState_Inferred) && (joint1State == TrackingState_Inferred))
	{
		return;
	}

	// We assume all drawn bones are inferred unless BOTH joints are tracked
	if ((joint0State == TrackingState_Tracked) && (joint1State == TrackingState_Tracked))
	{
		//m_pRenderTarget->DrawLine(pJointPoints[joint0], pJointPoints[joint1], m_pBrushBoneTracked, c_TrackedBoneThickness);
		ofstream myfile;
		myfile.open("example.txt");
		myfile << pJoints[joint0].Position.X;
		myfile << pJoints[joint0].Position.Y;
		myfile << pJoints[joint0].Position.Z;
		myfile << "WTH is going on";
		myfile.close();
	}
	else
	{
		//m_pRenderTarget->DrawLine(pJointPoints[joint0], pJointPoints[joint1], m_pBrushBoneInferred, c_InferredBoneThickness);
		ofstream myfile;
		myfile.open("example.txt");
		myfile << pJoints[joint0].Position.X;
		myfile << pJoints[joint0].Position.Y;
		myfile << pJoints[joint0].Position.Z;
		myfile << "WTF is going on";
		myfile.close();
	}
}

/// <summary>
/// Draws a hand symbol if the hand is tracked: red circle = closed, green circle = opened; blue circle = lasso
/// </summary>
/// <param name="handState">state of the hand</param>
/// <param name="handPosition">position of the hand</param>
void CColorBasics::DrawHand(HandState handState, const D2D1_POINT_2F& handPosition)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(handPosition, c_HandSize, c_HandSize);

	switch (handState)
	{
	case HandState_Closed:
		m_pRenderTarget->FillEllipse(ellipse, m_pBrushHandClosed);
		break;

	case HandState_Open:
		m_pRenderTarget->FillEllipse(ellipse, m_pBrushHandOpen);
		break;

	case HandState_Lasso:
		m_pRenderTarget->FillEllipse(ellipse, m_pBrushHandLasso);
		break;
	}
}

/// <summary>
/// process video
/// </summary>

int CColorBasics::Processvideo()
{
	string imageName = "C:\\Users/Yuhan/Pictures/FrameNumber-0.bmp";
	Mat image;
	image = imread(imageName);
	VideoWriter out;
	out.open("Video/video.avi", CV_FOURCC('M','J','P','G'), 15, Size(1920,1080));
	//namedWindow("edges", 1);

	for (int i = 0;; i++) {
		imageName = "C:\\Users/Yuhan/Pictures/FrameNumber-" + std::to_string(i) + ".bmp";
		image = imread(imageName);
		if (image.empty()) {
			break;
		}
		//cvtColor(image, edges, CV_BGR2GRAY);
		//imshow("edges", edges);
		out.write(image);
	}
	//destroyWindow("edges");
	return 1;
}