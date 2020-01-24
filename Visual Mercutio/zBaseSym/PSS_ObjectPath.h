/****************************************************************************
 * ==> PSS_ObjectPath ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an object path interface                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObjectPathH
#define PSS_ObjectPathH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASESYMEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Object path interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ObjectPath
{
    public:
        PSS_ObjectPath();
        virtual ~PSS_ObjectPath();

        /**
        * Gets the absolute path
        *@return the absolute path
        */
        virtual inline CString GetAbsolutePath() const;

        /**
        * Sets the absolute path
        *@param path - the absolute path
        */
        virtual inline void SetAbsolutePath(const CString& path);

        /**
        * Checks if paths are equals
        *@param path - path to compare with
        *@return if paths are equals
        */
        virtual inline bool IsEqual(const PSS_ObjectPath& path);

        /**
        * Clears the path
        */
        virtual inline void ClearPath();

        /**
        * Calculates the absolute path
        */
        virtual inline void CalculateAbsolutePath();

        /**
        * Recalculates the absolute path
        */
        virtual inline void RecalculateAbsolutePath();

        /**
        * Adds a member to path
        *@param member - member to add
        */
        virtual void AddMemberToPath(const CString& member);

        /**
        * Gets the root member
        *@return the root member
        */
        virtual CString GetRootMember();

    protected:
        CString m_ObjectPath;
};

//---------------------------------------------------------------------------
// PSS_ObjectPath
//---------------------------------------------------------------------------
CString PSS_ObjectPath::GetAbsolutePath() const
{
    return m_ObjectPath;
}
//---------------------------------------------------------------------------
void PSS_ObjectPath::SetAbsolutePath(const CString& path)
{
    m_ObjectPath = path;
}
//---------------------------------------------------------------------------
bool PSS_ObjectPath::IsEqual(const PSS_ObjectPath& path)
{
    return !m_ObjectPath.Compare((const char*)path.GetAbsolutePath());
}
//---------------------------------------------------------------------------
void PSS_ObjectPath::ClearPath()
{
    m_ObjectPath.Empty();
}
//---------------------------------------------------------------------------
void PSS_ObjectPath::CalculateAbsolutePath()
{}
//---------------------------------------------------------------------------
void PSS_ObjectPath::RecalculateAbsolutePath()
{
    ClearPath();
    CalculateAbsolutePath();
}
//---------------------------------------------------------------------------

#endif
