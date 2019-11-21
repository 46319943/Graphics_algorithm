// OPPWMJExeDoc.cpp : implementation of the COPPWMJExeDoc class
//

#include "stdafx.h"
#include "OPPWMJExe.h"

#include "OPPWMJExeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeDoc

IMPLEMENT_DYNCREATE(COPPWMJExeDoc, CDocument)

BEGIN_MESSAGE_MAP(COPPWMJExeDoc, CDocument)
	//{{AFX_MSG_MAP(COPPWMJExeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeDoc construction/destruction

COPPWMJExeDoc::COPPWMJExeDoc()
{
	// TODO: add one-time construction code here

}

COPPWMJExeDoc::~COPPWMJExeDoc()
{
}

BOOL COPPWMJExeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeDoc serialization

void COPPWMJExeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeDoc diagnostics

#ifdef _DEBUG
void COPPWMJExeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COPPWMJExeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeDoc commands
