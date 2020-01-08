/****************************************************************************
 * ==> PSS_UserRoleEntity --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user role entity                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserRoleEntityH
#define PSS_UserRoleEntityH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif

// processsoft
#include "PSS_UserEntity.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* User role entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserRoleEntity : public PSS_UserEntity
{
    DECLARE_SERIAL(PSS_UserRoleEntity)

    public:
        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent entity, root entity if NULL
        */
        PSS_UserRoleEntity(const CString& name = "", const CString& description = "", PSS_UserEntity* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserRoleEntity(const PSS_UserRoleEntity& other);

        virtual ~PSS_UserRoleEntity();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UserRoleEntity& operator = (const PSS_UserRoleEntity& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_UserEntity* Clone() const;

        /**
        * Checks if the properties are shown
        *@return true if the properties are shown, otherwise false
        */
        virtual bool ShowProperties() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif
};

#endif
