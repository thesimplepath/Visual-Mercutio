using System.Text;

namespace ProcesssoftDLL
{
    /// <summary>
    /// Interface allowing the user to implement the MD5 encryption
    /// </summary>
    public class MD5Crypt
    {
        public MD5Crypt()
        {}

        public string GetMD5(string s)
        {
            string retval = "";
            MD5    md     = MD5CryptoServiceProvider.Create();
            byte[] hash;

            ASCIIEncoding enc    = new ASCIIEncoding();
            byte[]        buffer = enc.GetBytes(s);
            hash                 = md.ComputeHash(buffer);

            foreach(byte b in hash)
                retval += b.ToString("x2");

            return retval;
        }
    }
}
