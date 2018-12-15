/////////////////////////////////////////////////////////////////////////////
//@doc ZUSystemOption
//@module ZUSystemOption.cpp | Implementation of the <c ZUSystemOption> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com

#include <StdAfx.h>

// ZUSystemOption
#include "ZUSystemOption.h"

// JMR-MODIF - le 19 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZUSystemOption
ZUSystemOption::ZUSystemOption( CString IniFile, CString SectionName )
    : m_IniFile        ( IniFile ),
      m_SectionName    ( SectionName )
{
}

ZUSystemOption::~ZUSystemOption()
{
}

BOOL ZUSystemOption::Create( CString IniFile, CString SectionName )
{
    m_IniFile        = IniFile;
    m_SectionName    = SectionName;

    return TRUE;
}

// Read option methods
CString ZUSystemOption::ReadOption( CString EntityKey, LPCTSTR DefaultValue /*= NULL*/ )
{
    char Buffer[300];

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   ( DefaultValue != NULL ) ? DefaultValue : _T( "" ),
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return CString( Buffer );
}

CString ZUSystemOption::ReadOption( CString EntityKey, CString DefaultValue /*= ""*/ )
{
    char Buffer[300];

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   (const char*)DefaultValue,
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return CString( Buffer );
}

int ZUSystemOption::ReadOption( CString EntityKey, int DefaultValue /*= 0*/ )
{
    char    Buffer[50];
    char    DefaultValueBuffer[50];

    sprintf( DefaultValueBuffer, _T( "%d" ), DefaultValue );

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   DefaultValueBuffer,
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return atoi( Buffer );
}

bool ZUSystemOption::ReadOption( CString EntityKey, bool DefaultValue /*= false*/ )
{
    char    Buffer[50];
    char    DefaultValueBuffer[50];

    sprintf( DefaultValueBuffer, _T( "%d" ), (int)DefaultValue );

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   DefaultValueBuffer,
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return ( atoi( Buffer ) == 0 ) ? false : true;
}

double ZUSystemOption::ReadOption( CString EntityKey, double DefaultValue /*= 0*/ )
{
    char    Buffer[50];
    char    DefaultValueBuffer[50];

    sprintf( DefaultValueBuffer, _T( "%f" ), DefaultValue );

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   DefaultValueBuffer,
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return atof( Buffer );
}

float ZUSystemOption::ReadOption( CString EntityKey, float DefaultValue /*= 0*/ )
{
    char    Buffer[50];
    char    DefaultValueBuffer[50];

    sprintf( DefaultValueBuffer, _T( "%f" ), DefaultValue );

    if ( !GetPrivateProfileString( (const char*)m_SectionName,
                                   (const char*)EntityKey,
                                   DefaultValueBuffer,
                                   Buffer,
                                   sizeof( Buffer ),
                                   (const char*)m_IniFile ) )
    {
        return DefaultValue;
    }

    return (float)atof( Buffer );
}

// Write option methods
BOOL ZUSystemOption::WriteOption( CString EntityKey, LPCTSTR Value )
{
    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      ( Value != NULL ) ? Value : _T( "" ),
                                      (const char*)m_IniFile );
}

BOOL ZUSystemOption::WriteOption( CString EntityKey, CString Value )
{
    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      (const char*)Value,
                                      (const char*)m_IniFile );
}

BOOL ZUSystemOption::WriteOption( CString EntityKey, int Value )
{
    char ValueBuffer[50];

    sprintf( ValueBuffer, _T( "%d" ), Value );

    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      (const char*)ValueBuffer,
                                      (const char*)m_IniFile );
}

BOOL ZUSystemOption::WriteOption( CString EntityKey, bool Value )
{
    char ValueBuffer[50];

    sprintf( ValueBuffer, _T( "%d" ), (int)Value );

    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      (const char*)ValueBuffer,
                                      (const char*)m_IniFile );
}

BOOL ZUSystemOption::WriteOption( CString EntityKey, double Value )
{
    char ValueBuffer[50];

    sprintf( ValueBuffer, _T( "%f" ), Value );

    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      (const char*)ValueBuffer,
                                      (const char*)m_IniFile );
}

BOOL ZUSystemOption::WriteOption( CString EntityKey, float Value )
{
    char ValueBuffer[50];

    sprintf( ValueBuffer, _T( "%f" ), Value );

    return WritePrivateProfileString( (const char*)m_SectionName,
                                      (const char*)EntityKey,
                                      (const char*)ValueBuffer,
                                      (const char*)m_IniFile );
}
