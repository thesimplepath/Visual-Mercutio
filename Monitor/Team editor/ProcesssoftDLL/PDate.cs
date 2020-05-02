using System;

namespace ProcesssoftDLL
{
    class PDate
    {
        public static string GetDateYYYYMMDD()
        {
            DateTime dt = new DateTime();
            dt          = DateTime.Now;

            return dt.Year + "." + dt.Month + "." + dt.Day;
        }
    }
}
