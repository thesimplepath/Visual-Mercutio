//## begin module%345A3A4401AE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%345A3A4401AE.cm

//## begin module%345A3A4401AE.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%345A3A4401AE.cp

//## Module: TmplFile%345A3A4401AE; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplFile.cpp

//## begin module%345A3A4401AE.additionalIncludes preserve=no
//## end module%345A3A4401AE.additionalIncludes

//## begin module%345A3A4401AE.includes preserve=yes
#include <StdAfx.h>
//## end module%345A3A4401AE.includes

// TmplFile
#include "TmplFile.h"
//## begin module%345A3A4401AE.declarations preserve=no
//## end module%345A3A4401AE.declarations

//## begin module%345A3A4401AE.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_SERIAL(ZDTemplateFile, CObject, def_Version)
//## end module%345A3A4401AE.additionalDeclarations


// Class ZDTemplateFile 




ZDTemplateFile::ZDTemplateFile(const ZDTemplateFile &right)
  //## begin ZDTemplateFile::ZDTemplateFile%copy.hasinit preserve=no
      : m_Persistent(FALSE)
  //## end ZDTemplateFile::ZDTemplateFile%copy.hasinit
  //## begin ZDTemplateFile::ZDTemplateFile%copy.initialization preserve=yes
  //## end ZDTemplateFile::ZDTemplateFile%copy.initialization
{
  //## begin ZDTemplateFile::ZDTemplateFile%copy.body preserve=yes
	*this = right;
  //## end ZDTemplateFile::ZDTemplateFile%copy.body
}

ZDTemplateFile::ZDTemplateFile (CString Filename)
  //## begin ZDTemplateFile::ZDTemplateFile%878377696.hasinit preserve=no
      : m_Persistent(FALSE)
  //## end ZDTemplateFile::ZDTemplateFile%878377696.hasinit
  //## begin ZDTemplateFile::ZDTemplateFile%878377696.initialization preserve=yes
  //## end ZDTemplateFile::ZDTemplateFile%878377696.initialization
{
  //## begin ZDTemplateFile::ZDTemplateFile%878377696.body preserve=yes
  	// Create the object
  	Create( Filename );
  //## end ZDTemplateFile::ZDTemplateFile%878377696.body
}


ZDTemplateFile::~ZDTemplateFile()
{
  //## begin ZDTemplateFile::~ZDTemplateFile%.body preserve=yes
  //## end ZDTemplateFile::~ZDTemplateFile%.body
}


const ZDTemplateFile & ZDTemplateFile::operator=(const ZDTemplateFile &right)
{
  //## begin ZDTemplateFile::operator=%.body preserve=yes
	m_Filename = right.m_Filename;
	m_Stamp = right.m_Stamp;
	m_Persistent = right.m_Persistent;
	return *this;
  //## end ZDTemplateFile::operator=%.body
}



//## Other Operations (implementation)
BOOL ZDTemplateFile::Create (CString Filename)
{
  //## begin ZDTemplateFile::Create%878377697.body preserve=yes
  	// Save the filename
  	m_Filename = Filename;
  	
	if (!m_Stamp.ReadFromFile( m_Filename ))
		return FALSE;
	return m_Persistent = ( m_Stamp.GetInternalVersion() != -1 && m_Stamp.GetFileType() == TemplateType ) ? TRUE : FALSE;
  //## end ZDTemplateFile::Create%878377697.body
}

CArchive& operator >> (CArchive& ar, ZDTemplateFile& TemplateFile)
{
  //## begin ZDTemplateFile::operator >>%927987842.body preserve=yes
	ar >> TemplateFile.m_Filename;
    ar >> TemplateFile.m_Stamp;
	return ar;
  //## end ZDTemplateFile::operator >>%927987842.body
}

CArchive& operator << (CArchive& ar, ZDTemplateFile& TemplateFile)
{
  //## begin ZDTemplateFile::operator <<%927987843.body preserve=yes
	ar << TemplateFile.m_Filename;
    ar << TemplateFile.m_Stamp;
	return ar;
  //## end ZDTemplateFile::operator <<%927987843.body
}

ZDTemplateFile* ZDTemplateFile::Clone ()
{
  //## begin ZDTemplateFile::Clone%927987844.body preserve=yes
	ZDTemplateFile*	pTemplateFile = new ZDTemplateFile( *this );
	return pTemplateFile;
  //## end ZDTemplateFile::Clone%927987844.body
}

void ZDTemplateFile::Serialize (CArchive& ar)
{
  //## begin ZDTemplateFile::Serialize%927987848.body preserve=yes
	if (ar.IsStoring())
	{	// Write the elements
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
  //## end ZDTemplateFile::Serialize%927987848.body
}

// Additional Declarations
  //## begin ZDTemplateFile%345A3A01035C.declarations preserve=yes
  //## end ZDTemplateFile%345A3A01035C.declarations

//## begin module%345A3A4401AE.epilog preserve=yes
//## end module%345A3A4401AE.epilog
