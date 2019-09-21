/****************************************************************************
 * ==> PSS_InputScenarioSet ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input scenario set                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputScenarioSetH
#define PSS_InputScenarioSetH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input scenario set
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_InputScenarioSet : public CObject
{
    public:
        PSS_InputScenarioSet();
        virtual ~PSS_InputScenarioSet();
};

#endif
