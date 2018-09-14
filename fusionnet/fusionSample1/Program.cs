using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet;
using fusion3dnet.App;
using fusion3dnet.Scene;
using fusion3dnet.Import;

namespace fusionSample1
{
    class Program
    {

        public class Sample1 : FusionApp
        {
            public Sample1() : base(1024,768,"Fusion3D.Net - Sample 1",false)
            {

                Scene1 = new GraphScene();
                Console.WriteLine("Importing mesh.");
                Ent1 = ModelImport.ImportEntity("c:/media/chalet.obj");
                Scene1.SetRoot(Ent1);
                Console.WriteLine("Imported: Sub:" + Ent1.SubCount);
                var e2 = Ent1.GetSub(0);
                Console.WriteLine("meshes:" + e2.MeshCount);
                Console.WriteLine("Verts:" + e2.GetMesh(0).NumVertices + " Indices:" + e2.GetMesh(0).NumIndices);


            }

            GraphScene Scene1;
            GraphEntity Ent1;

        }

        static void Main(string[] args)
        {

            Sample1 app = new Sample1();
            while (true)
            {

            }

        }
    }
}
