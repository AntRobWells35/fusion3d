using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet;
using fusion3dnet.App;

namespace fusionSample1
{
    class Program
    {

        public class Sample1 : FusionApp
        {
            public Sample1() : base(1024,768,"Fusion3D.Net - Sample 1",false)
            {

            }
        }

        static void Main(string[] args)
        {

            Sample1 app = new Sample1();


        }
    }
}
