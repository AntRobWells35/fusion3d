using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet.Data;
namespace fusion3dnet.Scene
{
    public class GraphEntity : fusionobj
    {
        public GraphEntity() : base(dll.CreateEntity())
        {

        }
        public GraphEntity(IntPtr handle)
        {
            Handle = handle;
        }
        public int SubCount
        {
            get
            {
                return dll.EntitySubCount(Handle);
            }
        }
        public int MeshCount
        {
            get
            {
                return dll.EntityMeshCount(Handle);
            }
        }

        public GraphEntity GetSub(int id)
        {
            return new GraphEntity(dll.EntityGetSub(Handle,id));
        }

        public Mesh3D GetMesh(int id)
        {
            return new Mesh3D(dll.EntityGetMesh(Handle, id));
        }

        public void AddMesh(Mesh3D mesh)
        {
            dll.EntityAddMesh(Handle, mesh.Handle);
        }


    }
}
