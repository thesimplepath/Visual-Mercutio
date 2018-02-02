/////////////////////////////////////////////////////////////////////////////
//@doc ZBKeepStringUsage
//@module ZBKeepStringUsage.cpp | Implementation of the <c ZBKeepStringUsage> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 04/2002
// 
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ZBKeepStringUsage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBKeepStringUsage::ZBKeepStringUsage()
{

}

ZBKeepStringUsage::~ZBKeepStringUsage()
{
	// Reset the array of strings
	ResetStringsArray();
}
