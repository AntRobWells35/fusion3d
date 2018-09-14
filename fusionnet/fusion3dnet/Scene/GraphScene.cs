using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using fusion3dnet;
namespace fusion3dnet.Scene
{
    public class GraphScene : fusionobj
    {

        public GraphScene() : base(dll.CreateGraph())
        {
        
        }

        public void SetRoot(GraphEntity entity)
        {

            dll.GraphSetRoot(Handle, entity.Handle);

        }
    }
}
