using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet;

namespace fusion3dnet.App
{
    public class FusionApp
    {

        public FusionApp(int width,int height,string apptitle,bool fullscreen)
        {
            dll.InitFusion(width, height, apptitle, fullscreen);
        }

        public virtual void InitApp()
        {

        }

        public virtual void UpdateApp()
        {

        }

        public virtual void RenderApp()
        {

        }

        public void Run()
        {

            InitApp();

            while (true)
            {
                UpdateApp();
                RenderApp();
                System.Threading.Thread.Sleep(5);
            }

        }

    }
}
