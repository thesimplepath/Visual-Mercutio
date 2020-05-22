/*****************************************************************************
 * ==> Interface ITable -----------------------------------------------------*
 * ***************************************************************************
 * Description : Basic interface for Table Classes.                          *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Data;
using System.Data.OleDb;

namespace Visual_Mercutio_Reports_Manager.Database
{
    interface ITable
    {
        #region Properties interface

        /// <summary>
        /// Interface for get database container
        /// </summary>
        DataTable Table
        {
            get;
        }

        /// <summary>
        /// Interface for SELECT command
        /// </summary>
        string SelectCommand
        {
            get;
        }

        /// <summary>
        /// Interface for INSERT command
        /// </summary>
        string InsertCommand
        {
            get;
        }

        /// <summary>
        /// Interface for UPDATE command
        /// </summary>
        string UpdateCommand
        {
            get;
        }

        /// <summary>
        /// Interface for DELETE command
        /// </summary>
        string DeleteCommand
        {
            get;
        }

        #endregion

        #region Functions interface

        /// <summary>
        /// Pure virtual function for Tables interface
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        bool Connect();

        /// <summary>
        /// Pure virtual function for Tables interface
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        bool Disconnect();

        /// <summary>
        /// Pure virtual function for Tables interface
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        bool GetTable();

        /// <summary>
        /// Pure virtual function for Tables interface
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        bool UpdateTable();

        #endregion
    }
}
