using System;

namespace ProcesssoftDLL
{
    /// <summary>
    /// Summary description for SQL
    /// </summary>
    public class SQL
    {
        /// <summary>
        /// Escape particular character in order to avoid sql error or sql injection
        /// </summary>
        /// <param name="ToProtect"></param>
        /// <returns></returns>
        public static string escapeString(string ToProtect)
        {
            ToProtect = ToProtect.Replace("'",      "''");   // '    --> ''
            ToProtect = ToProtect.Replace("’",      "''");   // ’    --> ''
            ToProtect = ToProtect.Replace(";",      " ");    // ;    --> blank char
            ToProtect = ToProtect.Replace("\"",     "\"\""); // "    --> ""
            ToProtect = ToProtect.Replace("\u0000", "");     // null --> empty string
            return ToProtect;
        }
    }
}
