using System;
using System.Xml;
using System.Collections;
using System.IO;
using System.Data ;
using ICSharpCode.SharpZipLib.Zip;

namespace CapsulesTravailDLL
{
    /// <author>Cédric Michelet</author>
    /// <date>09.06.2005</date>
    /// <version>1.0 made by Icare Institute, CH-Sierre</version>
    /// <modification>
    ///		<author></author>
    ///		<date></date>
    ///		<description></description>
    /// </modification>
    /// <summary>
    /// Class to handle an offline file stored into an xml file
    /// </summary>
    public class CapsulesXML
    {
        private DataView _dvTasks; //dataset containing the tasks
        private DataView _dvRules;
        private DataView _dvDecisions;
        private DataView _dvFiles;
        private DataView _dvLivrablesInput; //contain info about the livrables
        private DataView _dvLivrablesLateraux;
        private DataView _dvLivrablesOutput;
        private DataView _dvApplications;
        private DataSet _dsLivrablesInputAttributs; //each table contains infos about 1 livrable
        private DataSet _dsLivrablesLaterauxAttributs;
        private DataSet _dsLivrablesOutputAttributs;
        private ArrayList _casesName; //store the name of the cases inside the xml files
        private ArrayList _filesPath; //store the name of the xml file (linked to _casesName)
        private ArrayList _casesDateWarning; //store the warning date of each cases
        private String _caseName;
        private String _transName;
        private String _procName;
        private String _caseid;
        private String _procid;
        private String _transid;
        private String _currentPath;
        private String _datePeremption;
        private String _dateWarning;
        private String _C_CHECK_MARK = "v";
        private bool _isSendToChief;
        private bool _isTerminate;
        private bool _isBackToSender;
        private bool _isSetToWait;
        private bool _hasBeenSynchronised;
        enum e_last_livrableType {none=0, input=1, lateral=2, output=3};
        private e_last_livrableType _lastLivrableType ;
        private bool _flagUpdateMdated = false ;

        /// getter/setter
        public String    getDatePeremption()               {return _datePeremption;}
        public DataView  getTasksDataView()                {return _dvTasks;}
        public DataView  getRulesDataView()                {return _dvRules;}
        public DataView  getDecisionsDataView()            {return _dvDecisions;}
        public DataView  getFilesDataView()                {return _dvFiles;}
        public DataView  getLivrablesInputDataView()       {return _dvLivrablesInput;}
        public DataView  getLivrablesLaterauxDataView()    {return _dvLivrablesLateraux;}
        public DataView  getLivrablesOutputDataView()      {return _dvLivrablesOutput;}
        public DataView  getApplicationsDataView()         {return _dvApplications;}
        public DataSet   getLivrablesInputAttributs()      {return _dsLivrablesInputAttributs;}
        public DataSet   getLivrablesLaterauxAttributs()   {return _dsLivrablesLaterauxAttributs;}
        public DataSet   getLivrablesOutputAttributs()     {return _dsLivrablesOutputAttributs;}
        public ArrayList getCasesNameList()                {return _casesName;}
        public ArrayList getCasesDateWarning()             {return _casesDateWarning;}
        public String    getPathOfFileAtIndex(int i)       {return (String)_filesPath[i];}
        public int       getNbrOfFiles()                   {return _filesPath.Count;}
        public String    getCaseName()                     {return _caseName;}
        public String    getTransName()                    {return _transName;}
        public String    getProcName()                     {return _procName;}
        public String    getCaseid()                       {return _caseid;}
        public String    getProcid()                       {return _procid;}
        public String    getTransid()                      {return _transid;}
        public bool      getIsSendToChief()                {return _isSendToChief;}
        public void      setIsSendToChief(bool value)      {_isSendToChief = value;}
        public bool      getIsTerminate()                  {return _isTerminate;}
        public void      setIsTerminate(bool value)        {_isTerminate = value;}
        public bool      getIsBackToSender()               {return _isBackToSender;}
        public void      setIsBackToSender(bool value)     {_isBackToSender = value;}
        public bool      getIsSetToWait()                  {return _isSetToWait;}
        public void      setIsSetToWait(bool value)        {_isSetToWait = value;}
        public bool      getHasBeenSynchronised()          {return _hasBeenSynchronised;}
        public void      setHasBeenSynchronised(bool value){_hasBeenSynchronised = value;}

        public CapsulesXML()
        {
            _dvTasks             = new DataView();
            _dvRules             = new DataView();
            _dvDecisions         = new DataView();
            _dvFiles             = new DataView();
            _dvLivrablesInput    = new DataView();
            _dvLivrablesLateraux = new DataView();
            _dvLivrablesOutput   = new DataView();
            _dvApplications      = new DataView();

            // allow only update (no add)
            _dvTasks.AllowNew             = false;
            _dvRules.AllowNew             = false;
            _dvDecisions.AllowNew         = false;
            _dvFiles.AllowNew             = false;
            _dvLivrablesInput.AllowNew    = false;
            _dvLivrablesLateraux.AllowNew = false;
            _dvLivrablesOutput.AllowNew   = false;
            _dvApplications.AllowNew      = false;
            _hasBeenSynchronised          = false;
        }

        /// <summary>
        /// Load all the xml files into the directory capsules.
        /// Open each files, and get the name of the case
        /// </summary>
        /// <param name="repositoryPath"></param>
        public void loadAllFilesInfoIntoList(String repositoryPath)
        {
            try
            {
                // first, expand all compressed archives
                extractAllArchives(repositoryPath);

                XmlTextReader xtr;

                // Application.StartupPath
                DirectoryInfo di = new DirectoryInfo(repositoryPath);

                if (!di.Exists)
                {
                    System.Windows.Forms.MessageBox.Show("Le répertoire 'capsules' est introuvable sur le disque.");
                    return;
                }

                // empty the list of names
                _casesName        = new ArrayList();
                _filesPath        = new ArrayList();
                _casesDateWarning = new ArrayList();

                // get all the xml files
                FileInfo[] rgFiles = di.GetFiles("*.xml");

                // open each file, and extracts the basic infos to display
                foreach (FileInfo fi in rgFiles)
                {
                    xtr = new XmlTextReader(fi.FullName) ;
                    xtr.ReadStartElement("root");

                    //read next tag: case
                    xtr.Read();

                    // add name of the case to the list
                    _casesName.Add(xtr.GetAttribute("name"));

                    // add name of the file to the list
                    _filesPath.Add(fi.FullName);

                    // get the warning date of the case
                    _casesDateWarning.Add(xtr.GetAttribute("dateWarning"));
                    xtr.Close();
                }
            }
            catch(Exception e)
            {
                System.Windows.Forms.MessageBox.Show("Une erreur est survenue lors du chargement d'un fichier : " + e.Message);
            }
        }

        /// <summary>
        /// Get all zip archive and extracts the capsules inside them. Then delete the arhived file.
        /// </summary>
        /// <param name="repositoryPath"></param>
        private void extractAllArchives(String repositoryPath)
        {
            try
            {
                DirectoryInfo di = new DirectoryInfo(repositoryPath);

                if (!di.Exists)
                    return;

                // get all the compressed files
                FileInfo[] rgFiles = di.GetFiles("*.zip");

                // expand each files
                foreach(FileInfo fi in rgFiles)
                {
                    // open the zip
                    ZipInputStream s = new ZipInputStream(File.OpenRead(fi.FullName));

                    ZipEntry theEntry;
                    FileInfo fi2;

                    // go through each file inside the zip
                    while ((theEntry = s.GetNextEntry()) != null)
                    {
                        int    size = 2048;
                        byte[] data = new byte[2048];

                        // ***get the name of the file
                        // extract just the name of the file
                        int pos = theEntry.Name.LastIndexOf("/");

                        if (pos == -1)
                            fi2 = new FileInfo(repositoryPath + "\\" + theEntry.Name);
                        else
                            fi2 = new FileInfo(repositoryPath + "\\" + theEntry.Name.Substring(pos));

                        // create the file on the disk
                        FileStream fs = File.Create(fi2.FullName);

                        // unzip and write the content
                        while (true)
                        {
                            size = s.Read(data, 0, data.Length);

                            if (size > 0)
                                fs.Write(data, 0, size);
                            else
                                break;
                        }

                        fs.Close();
                    }

                    s.Close();

                    // on efface le fichier zip
                    fi.Delete();
                }
            }
            catch(Exception e)
            {
                System.Windows.Forms.MessageBox.Show("Une erreur est survenue lors de la décompression d'une archive : " + e.Message);
            }
        }

        /// <summary>
        /// Load a specific xml file, and get info about it
        /// </summary>
        /// <param name="fileName"></param>
        public void loadFileIntoList(String filePath)
        {
            DataTable     newTable;
            DataColumn    newCol;
            DataRow       newRow;
            XmlTextReader xtr;
            String        tempString;
            int           tableIndex;

            // save the path for later use (save function)
            _currentPath = filePath;

            // *** create the new container for the attributs
            _dsLivrablesInputAttributs    = new DataSet();
            _dsLivrablesLaterauxAttributs = new DataSet();
            _dsLivrablesOutputAttributs   = new DataSet();

            // *** create the table for the tasks
            newTable       = new DataTable("ELEMENTS");
            _dvTasks.Table = newTable;

            // col value
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.Boolean");
            newCol.ColumnName = "mstate";
            newTable.Columns.Add(newCol);

            // col value as text
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mstateTEXT";
            newTable.Columns.Add(newCol);

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mvalue";
            newTable.Columns.Add(newCol);

            // col attribid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "attribid";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // *** create the table for the decisions
            newTable           = new DataTable("ELEMENTS");
            _dvDecisions.Table = newTable;

            // col value
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.Boolean");
            newCol.ColumnName = "mstate";
            newTable.Columns.Add(newCol);

            // col value as text
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mstateTEXT";
            newTable.Columns.Add(newCol);

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mvalue";
            newTable.Columns.Add(newCol);

            // col attribid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "attribid";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // *** create the table for the rules
            newTable       = new DataTable("ELEMENTS");
            _dvRules.Table = newTable;

            // col value
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.Boolean");
            newCol.ColumnName = "mstate";
            newTable.Columns.Add(newCol);

            // col value as text
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mstateTEXT";
            newTable.Columns.Add(newCol);

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mvalue";
            newTable.Columns.Add(newCol);

            // col delivid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "delivid";
            newTable.Columns.Add(newCol);

            // col refid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "refid";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // *** create the table for the files
            newTable = new DataTable("ELEMENTS");
            _dvFiles.Table = newTable;

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "name";
            newTable.Columns.Add(newCol);

            // col login
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "login";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // *** create the table for the input livrables
            newTable                = new DataTable("ELEMENTS");
            _dvLivrablesInput.Table = newTable;

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "name";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // col delivid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "delivid";
            newTable.Columns.Add(newCol);

            // col checked
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "checked";
            newTable.Columns.Add(newCol);

            // *** create the table for the lateral livrables
            newTable                   = new DataTable("ELEMENTS");
            _dvLivrablesLateraux.Table = newTable;

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "name";
            newTable.Columns.Add(newCol);

            // col procname
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "procname";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // col delivid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "delivid";
            newTable.Columns.Add(newCol);

            // col inProgress
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "inProgress";
            newTable.Columns.Add(newCol);

            // col isTerminate
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "isTerminate";
            newTable.Columns.Add(newCol);

            // col isMandatory
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "isMandatory";
            newTable.Columns.Add(newCol);

            // col has been requested
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "requested";
            newTable.Columns.Add(newCol);

            // *** create the table for the output livrables
            newTable                 = new DataTable("ELEMENTS");
            _dvLivrablesOutput.Table = newTable;

            // col name
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "name";
            newTable.Columns.Add(newCol);

            // col procname
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "procname";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // col delivid
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "delivid";
            newTable.Columns.Add(newCol);

            // col isCompleted
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "isCompleted";
            newTable.Columns.Add(newCol);

            // col isMandatory
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "isMandatory";
            newTable.Columns.Add(newCol);

            // col has been requested
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "requested";
            newTable.Columns.Add(newCol);

            // *** create the table for the applications
            newTable              = new DataTable("ELEMENTS");
            _dvApplications.Table = newTable;

            // col checked
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "checked";
            newTable.Columns.Add(newCol);

            // col command
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "name";
            newTable.Columns.Add(newCol);

            // col command
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "command";
            newTable.Columns.Add(newCol);

            // col parameters
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "parameters";
            newTable.Columns.Add(newCol);

            // col mdated
            newCol            = new DataColumn();
            newCol.DataType   = System.Type.GetType("System.String");
            newCol.ColumnName = "mdated";
            newTable.Columns.Add(newCol);

            // *** read the xml file
            FileInfo fi = new FileInfo(filePath);

            // check if the file exists
            if (fi.Exists == false)
                return;

            // open the file
            xtr = new XmlTextReader(fi.FullName);

            // position the pointer on the case
            xtr.ReadStartElement("root");

            //read next tag: case
            xtr.Read();

            // store case info
            _caseid         = xtr.GetAttribute("caseid");
            _procid         = xtr.GetAttribute("procid");
            _transid        = xtr.GetAttribute("transid");
            _caseName       = xtr.GetAttribute("name");
            _procName       = xtr.GetAttribute("procname");
            _transName      = xtr.GetAttribute("transname");
            _datePeremption = xtr.GetAttribute("datePeremption");
            _dateWarning    = xtr.GetAttribute("dateWarning");

            tempString = xtr.GetAttribute("isSendToChief");

            if (tempString == "1")
                _isSendToChief = true;
            else
                _isSendToChief = false;

            tempString = xtr.GetAttribute("isTerminate");

            if (tempString == "1")
                _isTerminate = true;
            else
                _isTerminate = false;

            tempString = xtr.GetAttribute("isBackToSender");

            if (tempString == "1")
                _isBackToSender = true;
            else
                _isBackToSender = false;

            tempString = xtr.GetAttribute("isSetToWait");

            if (tempString == "1")
                _isSetToWait = true;
            else
                _isSetToWait = false;

            tempString = xtr.GetAttribute("hasBeenSynchronised");

            if (tempString == "1")
                _hasBeenSynchronised = true;
            else
                _hasBeenSynchronised = false;

            _lastLivrableType = e_last_livrableType.none;

            //read all next nodes until end of file (EOF)
            do
            {
                // read next node
                xtr.Read();

                // is it an element node?
                if (xtr.NodeType == XmlNodeType.Element)
                {
                    if (xtr.Name == "task")
                    {
                        newRow = _dvTasks.Table.NewRow();

                        if(xtr.GetAttribute("mstate") == "1")
                        {
                            newRow["mstate"]     = true;
                            newRow["mstateTEXT"] = _C_CHECK_MARK;
                        }
                        else
                        {
                            newRow["mstate"]     = false;
                            newRow["mstateTEXT"] = "";
                        }

                        newRow["mvalue"]   = xtr.GetAttribute("mvalue");
                        newRow["mdated"]   = xtr.GetAttribute("mdated");
                        newRow["attribid"] = xtr.GetAttribute("attribid");
                        _dvTasks.Table.Rows.Add(newRow);
                    }

                    if (xtr.Name == "decision")
                    {
                        newRow = _dvDecisions.Table.NewRow();

                        if(xtr.GetAttribute("mstate") == "1")
                        {
                            newRow["mstate"]     = true;
                            newRow["mstateTEXT"] = _C_CHECK_MARK;
                        }
                        else
                        {
                            newRow["mstate"]     = false;
                            newRow["mstateTEXT"] = "";
                        }

                        newRow["mvalue"]   = xtr.GetAttribute("mvalue");
                        newRow["mdated"]   = xtr.GetAttribute("mdated");
                        newRow["attribid"] = xtr.GetAttribute("attribid");
                        _dvDecisions.Table.Rows.Add(newRow);
                    }

                    if (xtr.Name == "rule")
                    {
                        newRow = _dvRules.Table.NewRow();

                        if(xtr.GetAttribute("mstate") == "1")
                        {
                            newRow["mstate"]     = true;
                            newRow["mstateTEXT"] = _C_CHECK_MARK;
                        }
                        else
                        {
                            newRow["mstate"]     = false;
                            newRow["mstateTEXT"] = "";
                        }

                        newRow["mvalue"]  = xtr.GetAttribute("mvalue");
                        newRow["mdated"]  = xtr.GetAttribute("mdated");
                        newRow["delivid"] = xtr.GetAttribute("delivid");
                        newRow["refid"]   = xtr.GetAttribute("refid");
                        _dvRules.Table.Rows.Add(newRow);
                    }

                    if (xtr.Name == "file")
                    {
                        newRow = _dvFiles.Table.NewRow();
                        newRow["name"]   = xtr.GetAttribute("name");
                        newRow["login"]  = xtr.GetAttribute("login");
                        newRow["mdated"] = xtr.GetAttribute("mdated");
                        _dvFiles.Table.Rows.Add(newRow) ;
                    }

                    if (xtr.Name == "livrableInput")
                    {
                        newRow            = _dvLivrablesInput.Table.NewRow();
                        newRow["name"]    = xtr.GetAttribute("name");
                        newRow["delivid"] = xtr.GetAttribute("delivid");
                        newRow["checked"] = xtr.GetAttribute("checked");
                        newRow["mdated"]  = xtr.GetAttribute("mdated");

                        _dvLivrablesInput.Table.Rows.Add(newRow);
                        _lastLivrableType = e_last_livrableType.input;

                        // create a new table for storing the attributs
                        newTable = new DataTable("ELEMENTS_"+_dsLivrablesInputAttributs.Tables.Count);
                        _dsLivrablesInputAttributs.Tables.Add(newTable);

                        // col name
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "name";
                        newTable.Columns.Add(newCol);

                        // col value
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "value";
                        newTable.Columns.Add(newCol);

                        // col mdated
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mdated";
                        newTable.Columns.Add(newCol);

                        // col mflag
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mflag";
                        newTable.Columns.Add(newCol);
                    }

                    if (xtr.Name == "livrableLateral")
                    {
                        newRow                = _dvLivrablesLateraux.Table.NewRow();
                        newRow["name"]        = xtr.GetAttribute("name");
                        newRow["delivid"]     = xtr.GetAttribute("delivid");
                        newRow["inProgress"]  = xtr.GetAttribute("inProgress");
                        newRow["isTerminate"] = xtr.GetAttribute("isTerminate");
                        newRow["isMandatory"] = xtr.GetAttribute("isMandatory");
                        newRow["mdated"]      = xtr.GetAttribute("mdated");
                        newRow["procname"]    = xtr.GetAttribute("procname");

                        // launch a livrable from the capsule
                        if (xtr.GetAttribute("hasBeenRequested")!= null)
                            newRow["requested"] = xtr.GetAttribute("hasBeenRequested");
                        else
                            newRow["requested"] = "0";

                        _dvLivrablesLateraux.Table.Rows.Add(newRow);
                        _lastLivrableType = e_last_livrableType.lateral;

                        // create a new table for storing the attributs
                        newTable = new DataTable("ELEMENTS_"+_dsLivrablesLaterauxAttributs.Tables.Count);
                        _dsLivrablesLaterauxAttributs.Tables.Add(newTable);

                        // col name
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "name";
                        newTable.Columns.Add(newCol);

                        // col value
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "value";
                        newTable.Columns.Add(newCol);

                        // col mdated
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mdated";
                        newTable.Columns.Add(newCol);

                        // col mflag
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mflag";
                        newTable.Columns.Add(newCol);
                    }

                    if (xtr.Name == "livrableOutput")
                    {
                        newRow                = _dvLivrablesOutput.Table.NewRow();
                        newRow["name"]        = xtr.GetAttribute("name");
                        newRow["delivid"]     = xtr.GetAttribute("delivid");
                        newRow["isCompleted"] = xtr.GetAttribute("isCompleted");
                        newRow["mdated"]      = xtr.GetAttribute("mdated");
                        newRow["isMandatory"] = xtr.GetAttribute("isMandatory");
                        newRow["procname"]    = xtr.GetAttribute("procname");

                        // launch a livrable from the capsule
                        if (xtr.GetAttribute("hasBeenRequested")!= null)
                            newRow["requested"] = xtr.GetAttribute("hasBeenRequested");
                        else
                            newRow["requested"] = "0";

                        _dvLivrablesOutput.Table.Rows.Add(newRow);
                        _lastLivrableType = e_last_livrableType.output;

                        // create a new table for storing the attributs
                        newTable = new DataTable("ELEMENTS_"+_dsLivrablesOutputAttributs.Tables.Count);
                        _dsLivrablesOutputAttributs.Tables.Add(newTable);

                        // col name
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "name";
                        newTable.Columns.Add(newCol);

                        // col value
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "value";
                        newTable.Columns.Add(newCol);

                        // col mdated
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mdated";
                        newTable.Columns.Add(newCol);

                        // col mflag
                        newCol            = new DataColumn();
                        newCol.DataType   = System.Type.GetType("System.String");
                        newCol.ColumnName = "mflag";
                        newTable.Columns.Add(newCol);
                    }

                    if (xtr.Name == "attribut")
                    {
                        // is it an attribut for a input livrable?
                        if (_lastLivrableType == e_last_livrableType.input)
                        {
                            tableIndex = _dvLivrablesInput.Table.Rows.Count - 1;

                            // add the attributs
                            newRow           = _dsLivrablesInputAttributs.Tables[tableIndex].NewRow();
                            newRow["name"]   = xtr.GetAttribute("name");
                            newRow["value"]  = xtr.GetAttribute("value");
                            newRow["mdated"] = xtr.GetAttribute("mdated");
                            newRow["mflag"]  = xtr.GetAttribute("mflag");
                            _dsLivrablesInputAttributs.Tables[tableIndex].Rows.Add(newRow);
                        }

                        // is it an attribut for a lateral livrable?
                        if (_lastLivrableType == e_last_livrableType.lateral)
                        {
                            tableIndex = _dvLivrablesLateraux.Table.Rows.Count - 1;

                            // add the attributs
                            newRow           = _dsLivrablesLaterauxAttributs.Tables[tableIndex].NewRow() ;
                            newRow["name"]   = xtr.GetAttribute("name");
                            newRow["value"]  = xtr.GetAttribute("value");
                            newRow["mdated"] = xtr.GetAttribute("mdated");
                            newRow["mflag"]  = xtr.GetAttribute("mflag");

                            _dsLivrablesLaterauxAttributs.Tables[tableIndex].Rows.Add(newRow) ;
                        }

                        // is it an attribut for an output livrable ?
                        if (_lastLivrableType == e_last_livrableType.output)
                        {
                            tableIndex = _dvLivrablesOutput.Table.Rows.Count - 1;

                            // add the attributs
                            newRow           = _dsLivrablesOutputAttributs.Tables[tableIndex].NewRow();
                            newRow["name"]   = xtr.GetAttribute("name");
                            newRow["value"]  = xtr.GetAttribute("value");
                            newRow["mdated"] = xtr.GetAttribute("mdated");
                            newRow["mflag"]  = xtr.GetAttribute("mflag");

                            _dsLivrablesOutputAttributs.Tables[tableIndex].Rows.Add(newRow);
                        }
                    }

                    if (xtr.Name == "application")
                    {
                        newRow               = _dvApplications.Table.NewRow();
                        newRow["checked"]    = xtr.GetAttribute("checked");
                        newRow["name"]       = xtr.GetAttribute("name");
                        newRow["command"]    = xtr.GetAttribute("command");
                        newRow["parameters"] = xtr.GetAttribute("parameters");
                        newRow["mdated"]     = xtr.GetAttribute("mdated");
                        _dvApplications.Table.Rows.Add(newRow);
                    }
                }
            }
            while (!xtr.EOF);

            xtr.Close();

            // track when the checkbox is modified, in order to change the date value
            _dvRules.Table.RowChanged     += new DataRowChangeEventHandler(Row_Changed);
            _dvDecisions.Table.RowChanged += new DataRowChangeEventHandler(Row_Changed);
            _dvTasks.Table.RowChanged     += new DataRowChangeEventHandler(Row_Changed);
        }

        /// <summary>
        /// Track change on rules/decisions/tasks/attributs. When it's check or uncheck, change the mdate
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Row_Changed( object sender, DataRowChangeEventArgs e )
        {
            try
            {
                // do something only if it's a change
                if (e.Action == DataRowAction.Change)
                {
                    // when we do the modification on the mdated, this function is call another time.
                    // to avoid recursive call, we set a flag to see if the function is called because
                    // the user made a modification, or because we change programatically the mdate
                    if (_flagUpdateMdated)
                        _flagUpdateMdated = false;
                    else
                    {
                        _flagUpdateMdated = true;
                        e.Row["mdated"]   = System.DateTime.Now;
                    }
                }
            }
            catch (Exception)
            {
                _flagUpdateMdated = false;
            }
        }

        /// <summary>
        /// Save the info back into the xml file
        /// </summary>
        public void SaveAsXML()
        {
            String   tempString;
            FileInfo fi = new FileInfo(_currentPath);

            // delete the old file
            fi.Delete();

            StreamWriter sw = new StreamWriter(fi.FullName, false, System.Text.Encoding.UTF8);

            // write header
            sw.WriteLine("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
            sw.WriteLine("<root>");

            // write case
            tempString  = "\t<case caseid=\"" + this._caseid + "\" procid=\"" + this._procid + "\" transid=\"" + this._transid + "\" name=\"" + this._caseName + "\" transname=\"" + this._transName + "\" procname=\"";
            tempString += this._procName + "\" datePeremption=\"" + this._datePeremption + "\" dateWarning=\"" + this._dateWarning + "\" isSendToChief=\"";

            if (_isSendToChief)
                tempString += "1";
            else
                tempString += "0";

            tempString += "\" isTerminate=\"";

            if (_isTerminate)
                tempString += "1";
            else
                tempString += "0";

            tempString += "\" isBackToSender=\"";

            if (_isBackToSender)
                tempString += "1";
            else
                tempString += "0";

            tempString += "\" isSetToWait=\"";

            if (_isSetToWait)
                tempString += "1";
            else
                tempString += "0";

            tempString += "\" hasBeenSynchronised=\"";

            if (_hasBeenSynchronised)
                tempString += "1";
            else
                tempString += "0";

            tempString += "\">";
            sw.WriteLine(tempString);

            // write livrables input
            for (int i = 0; i < _dvLivrablesInput.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<livrableInput name=\"";
                tempString += _dvLivrablesInput.Table.Rows[i]["name"];
                tempString += "\" delivid=\"";
                tempString += _dvLivrablesInput.Table.Rows[i]["delivid"];
                tempString += "\" checked=\"";
                tempString += _dvLivrablesInput.Table.Rows[i]["checked"];
                tempString += "\" mdated=\"";
                tempString += _dvLivrablesInput.Table.Rows[i]["mdated"];
                tempString += "\">";
                sw.WriteLine(tempString);

                // write the attributs
                for (int j = 0; j < _dsLivrablesInputAttributs.Tables[i].Rows.Count; ++j)
                {
                    tempString  = "\t\t\t<attribut name=\"";
                    tempString += _dsLivrablesInputAttributs.Tables[i].Rows[j]["name"];
                    tempString += "\" value=\"";
                    tempString += _dsLivrablesInputAttributs.Tables[i].Rows[j]["value"];
                    tempString += "\" mdated=\"";
                    tempString += _dsLivrablesInputAttributs.Tables[i].Rows[j]["mdated"];
                    tempString += "\" mflag=\"";
                    tempString += _dsLivrablesInputAttributs.Tables[i].Rows[j]["mflag"];
                    tempString += "\" />";
                    sw.WriteLine(tempString);
                }

                sw.WriteLine("\t\t</livrableInput>");
            }

            // write livrables lateral
            for(int i=0; i<_dvLivrablesLateraux.Table.Rows.Count; i++)
            {
                tempString  = "\t\t<livrableLateral name=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["name"];
                tempString += "\" delivid=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["delivid"];
                tempString += "\" inProgress=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["inProgress"];
                tempString += "\" isTerminate=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["isTerminate"];
                tempString += "\" mdated=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["mdated"];
                tempString += "\" isMandatory=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["isMandatory"];
                tempString += "\" procname=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["procname"];
                tempString += "\" hasBeenRequested=\"";
                tempString += _dvLivrablesLateraux.Table.Rows[i]["requested"];
                tempString += "\">";
                sw.WriteLine(tempString);

                // write the attributs
                for(int j = 0; j < _dsLivrablesLaterauxAttributs.Tables[i].Rows.Count; ++j)
                {
                    tempString  = "\t\t\t<attribut name=\"";
                    tempString += _dsLivrablesLaterauxAttributs.Tables[i].Rows[j]["name"];
                    tempString += "\" value=\"";
                    tempString += _dsLivrablesLaterauxAttributs.Tables[i].Rows[j]["value"];
                    tempString += "\" mdated=\"";
                    tempString += _dsLivrablesLaterauxAttributs.Tables[i].Rows[j]["mdated"];
                    tempString += "\" mflag=\"";
                    tempString += _dsLivrablesLaterauxAttributs.Tables[i].Rows[j]["mflag"];
                    tempString += "\" />";
                    sw.WriteLine(tempString);
                }

                sw.WriteLine("\t\t</livrableLateral>");
            }

            // write livrables output
            for(int i = 0; i < _dvLivrablesOutput.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<livrableOutput name=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["name"];
                tempString += "\" delivid=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["delivid"];
                tempString += "\" isCompleted=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["isCompleted"];
                tempString += "\" mdated=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["mdated"];
                tempString += "\" isMandatory=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["isMandatory"];
                tempString += "\" procname=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["procname"];
                tempString += "\" hasBeenRequested=\"";
                tempString += _dvLivrablesOutput.Table.Rows[i]["requested"];
                tempString += "\">";
                sw.WriteLine(tempString);

                // write the attributs
                for(int j = 0; j < _dsLivrablesOutputAttributs.Tables[i].Rows.Count; ++j)
                {
                    tempString  = "\t\t\t<attribut name=\"";
                    tempString += _dsLivrablesOutputAttributs.Tables[i].Rows[j]["name"];
                    tempString += "\" value=\"";
                    tempString += _dsLivrablesOutputAttributs.Tables[i].Rows[j]["value"];
                    tempString += "\" mdated=\"";
                    tempString += _dsLivrablesOutputAttributs.Tables[i].Rows[j]["mdated"];
                    tempString += "\" mflag=\"";
                    tempString += _dsLivrablesOutputAttributs.Tables[i].Rows[j]["mflag"];
                    tempString += "\" />";
                    sw.WriteLine(tempString);
                }

                sw.WriteLine("\t\t</livrableOutput>");
            }

            // write tasks
            for(int i = 0; i < _dvTasks.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<task mvalue=\"";
                tempString += _dvTasks.Table.Rows[i]["mvalue"];
                tempString += "\" attribid=\"";
                tempString += _dvTasks.Table.Rows[i]["attribid"];
                tempString += "\" mdated=\"";
                tempString += _dvTasks.Table.Rows[i]["mdated"];
                if((Boolean)_dvTasks.Table.Rows[i]["mstate"])
                    tempString += "\" mstate=\"1\" />";
                else
                    tempString += "\" mstate=\"0\" />";

                sw.WriteLine(tempString);
            }

            // write decisions
            for (int i = 0; i < _dvDecisions.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<decision mvalue=\"";
                tempString += _dvDecisions.Table.Rows[i]["mvalue"];
                tempString += "\" attribid=\"";
                tempString += _dvDecisions.Table.Rows[i]["attribid"];
                tempString += "\" mdated=\"";
                tempString += _dvDecisions.Table.Rows[i]["mdated"];
                if((Boolean)_dvDecisions.Table.Rows[i]["mstate"])
                    tempString += "\" mstate=\"1\" />";
                else
                    tempString += "\" mstate=\"0\" />";

                sw.WriteLine(tempString);
            }

            // write rules
            for (int i = 0; i < _dvRules.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<rule mvalue=\"";
                tempString += _dvRules.Table.Rows[i]["mvalue"];
                tempString += "\" delivid=\"";
                tempString += _dvRules.Table.Rows[i]["delivid"];
                tempString += "\" refid=\"";
                tempString += _dvRules.Table.Rows[i]["refid"];
                tempString += "\" mdated=\"";
                tempString += _dvRules.Table.Rows[i]["mdated"];
                if((Boolean)_dvRules.Table.Rows[i]["mstate"])
                    tempString += "\" mstate=\"1\" />";
                else
                    tempString += "\" mstate=\"0\" />";

                sw.WriteLine(tempString);
            }

            // write files
            for (int i = 0; i < _dvFiles.Table.Rows.Count; ++i)
            {
                tempString  = "\t\t<file name=\"";
                tempString += _dvFiles.Table.Rows[i]["name"];
                tempString += "\"  />";
                sw.WriteLine(tempString);
            }

            // write applications
            for (int i = 0; i < _dvApplications.Table.Rows.Count; ++i)
            {
                tempString = "\t\t<application checked=\"";
                tempString += _dvApplications.Table.Rows[i]["checked"];
                tempString += "\" name=\"";
                tempString += _dvApplications.Table.Rows[i]["name"];
                tempString += "\" command=\"";
                tempString += _dvApplications.Table.Rows[i]["command"];
                tempString += "\" parameters=\"";
                tempString += _dvApplications.Table.Rows[i]["parameters"];
                tempString += "\" mdated=\"";
                tempString += _dvApplications.Table.Rows[i]["mdated"];
                tempString += "\"  />";
                sw.WriteLine(tempString);
            }

            // write footer
            sw.WriteLine("\t</case>");
            sw.WriteLine("</root>");

            sw.Close();
        }

        /// <summary>
        /// Add a new file to the list
        /// </summary>
        /// <param name="name"></param>
        public void addFile(String name)
        {
            DataRow newRow = _dvFiles.Table.NewRow();
            newRow["name"] = name;
            _dvFiles.Table.Rows.Add(newRow);
        }

        /// <summary>
        /// Modify the value of a rule
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        public void setRuleState(int index, bool value)
        {
            _dvRules.Table.Rows[index]["mstate"] = value;

            if (value)
                _dvRules.Table.Rows[index]["mstateTEXT"] = _C_CHECK_MARK;
            else
                _dvRules.Table.Rows[index]["mstateTEXT"] = "";
        }

        /// <summary>
        /// Modify the value of a decisions
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        public void setDecisionState(int index, bool value)
        {
            _dvDecisions.Table.Rows[index]["mstate"] = value;

            if (value)
                _dvDecisions.Table.Rows[index]["mstateTEXT"] = _C_CHECK_MARK;
            else
                _dvDecisions.Table.Rows[index]["mstateTEXT"] = "";
        }

        /// <summary>
        /// Modify the value of a task
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        public void setTaskState(int index, bool value)
        {
            _dvTasks.Table.Rows[index]["mstate"] = value;

            if (value)
                _dvTasks.Table.Rows[index]["mstateTEXT"] = _C_CHECK_MARK;
            else
                _dvTasks.Table.Rows[index]["mstateTEXT"] = "";
        }

        /// <summary>
        /// Delete a specific capsule
        /// </summary>
        /// <param name="index"></param>
        public void deleteCapsuleAtIndex(int index)
        {
            FileInfo f = new FileInfo(this.getPathOfFileAtIndex(index));
            f.Delete();
        }

        /// <summary>
        /// Indicate if the current date is after the peremption date of the capsule
        /// </summary>
        /// <returns></returns>
        public bool isAfterDatePeremption()
        {
            if (_datePeremption == null)
                return false;

            if (_datePeremption == "")
                return false;

            try
            {
                DateTime d = DateTime.Parse(_datePeremption);

                if (d.CompareTo(DateTime.Now) < 0)
                    return true;
                else
                    return false;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
