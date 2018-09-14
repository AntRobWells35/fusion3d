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

        [DllImport("fusiondll.dll")]
        public static extern IntPtr CreateEntity();

        [DllImport("fusiondll.dll")]
        public static extern IntPtr LoadEntity(string path);

        [DllImport("fusiondll.dll")]
        public static extern IntPtr CreateGraph();

        [DllImport("fusiondll.dll")]
        public static extern void GraphSetRoot(IntPtr graph, IntPtr ent);

        [DllImport("fusiondll.dll")]
        public static extern int EntitySubCount(IntPtr ent);

        [DllImport("fusiondll.dll")]
        public static extern IntPtr EntityGetMesh(IntPtr ent, int m);

        [DllImport("fusiondll.dll")]
        public static extern IntPtr EntityGetSub(IntPtr ent, int e);

        [DllImport("fusiondll.dll")]
        public static extern int EntityMeshCount(IntPtr ent);

        [DllImport("fusiondll.dll")]
        public static extern IntPtr CreateMesh(int vertices, int indices);

        [DllImport("fusiondll.dll")]
        public static extern void EntityAddMesh(IntPtr ent, IntPtr mesh);

        [DllImport("fusiondll.dll")]
        public static extern int MeshVertexCount(IntPtr mesh);

        [DllImport("fusiondll.dll")]
        public static extern int MeshIndexCount(IntPtr mesh);
    }
}
