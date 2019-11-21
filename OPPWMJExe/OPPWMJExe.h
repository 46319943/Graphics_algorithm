// OPPWMJExe.h : main header file for the OPPWMJEXE application
//

#if !defined(AFX_OPPWMJEXE_H__9EA73A7C_D5F4_46F1_8E79_EE4C715C8659__INCLUDED_)
#define AFX_OPPWMJEXE_H__9EA73A7C_D5F4_46F1_8E79_EE4C715C8659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeApp:
// See OPPWMJExe.cpp for the implementation of this class
//

class COPPWMJExeApp : public CWinApp
{
public:
	COPPWMJExeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPPWMJExeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COPPWMJExeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPPWMJEXE_H__9EA73A7C_D5F4_46F1_8E79_EE4C715C8659__INCLUDED_)
