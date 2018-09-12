using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fusion3dnet
{
    public class fusionobj
    {

        public IntPtr Handle
        {
            get;
            set;
        }

        public fusionobj(IntPtr handle)
        {
            Handle = handle;
        }
        

    }
}
