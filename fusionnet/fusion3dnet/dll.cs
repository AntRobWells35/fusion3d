using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace fusion3dnet
{

    public class dll
    {
        [DllImport("fusiondll.dll")]
        public static extern void InitFusion(int w,int h,string title,bool full);
    }
}
