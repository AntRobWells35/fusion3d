using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fusion3dnet.Data
{
    public class Mesh3D : fusionobj
    {
        public Mesh3D(int vertices,int indices) : base(dll.CreateMesh(vertices,indices))
        {

        }
        public Mesh3D(IntPtr handle)
        {
            Handle = handle;
        }

        public int NumVertices
        {
            get
            {
                return dll.MeshVertexCount(Handle);
            }
        }

        public int NumIndices
        {
            get
            {
                return dll.MeshIndexCount(Handle);
            }
        }

    }
}
