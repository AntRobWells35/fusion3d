using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet.Scene;
namespace fusion3dnet.Import
{
    public class ModelImport
    {
        public static GraphEntity ImportEntity(string path)
        {
            Console.WriteLine("Importing:" + path);
            IntPtr handle = dll.LoadEntity(path);
            return new GraphEntity(handle);
        }
    }
}
