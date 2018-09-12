#include "stdafx.h"
#include "ModelImport.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



ModelImport::ModelImport()
{
}


ModelImport::~ModelImport()
{
}

Mesh3D * ModelImport::ImportObj(string path) {

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str())) {
		throw std::runtime_error(err);
	}
	return nullptr;
//	Mesh3D * mesh = new Mesh3D();
	//return mesh;


}


const struct aiScene* scene = NULL;
int scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

/* current rotation angle */
static float angle = 0.f;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

/* ---------------------------------------------------------------------------- */
void get_bounding_box_for_node(const struct aiNode* nd,
	 aiVector3D* min,
	 aiVector3D* max,
	 aiMatrix4x4* trafo
) {
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo, &nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		 aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			 aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp, trafo);

			min->x = aisgl_min(min->x, tmp.x);
			min->y = aisgl_min(min->y, tmp.y);
			min->z = aisgl_min(min->z, tmp.z);

			max->x = aisgl_max(max->x, tmp.x);
			max->y = aisgl_max(max->y, tmp.y);
			max->z = aisgl_max(max->z, tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n], min, max, trafo);
	}
	*trafo = prev;
}

/* ---------------------------------------------------------------------------- */
void get_bounding_box( aiVector3D* min, aiVector3D* max)
{
	 aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);


	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode, min, max, &trafo);
}

void color4_to_float4( aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void CopyNode(Entity * ent,aiNode * node)
{

	cout << "Importing:" << node->mName.C_Str() << endl;

	cout << "  Meshes:" << node->mNumMeshes << endl;

	for (int i = 0; i < node->mNumMeshes; i++) {
			
	
	
		aiMesh * m1 = scene->mMeshes[node->mMeshes[i]];

		Mesh3D * m = new Mesh3D(m1->mNumVertices, m1->mNumFaces*3);

		VertexBuffer * vb = m->GetVB();

		cout << "Vertices:" << m1->mNumVertices << " Indices:" << m1->mNumFaces << endl;

		for (int v = 0; v < m1->mNumVertices; v++) {
			
			aiVector3D pos, norm, uv0, bi, tan;

			pos = {};
			norm = {};
			uv0 = {};
			bi = {};
			tan = {};

			pos = m1->mVertices[v];
			if (m1->mNormals != NULL) {
				norm = m1->mNormals[v];
			}
			if (m1->mBitangents != NULL) {
				bi = m1->mBitangents[v];
			}

			if (m1->mTangents != NULL) {
				tan = m1->mTangents[v];
			}

			if (m1->mTextureCoords[0] != NULL) {
				uv0 = m1->mTextureCoords[0][v];
			}

			Vertex nv = {};

			nv.pos = { pos.x,pos.y,pos.z };
			nv.norm = { norm.x,norm.y,norm.z };
			nv.uv0 = { uv0.x,1.0f-uv0.y,uv0.z };
			nv.binorm = { bi.x,bi.y,bi.z };
			nv.tangent = { tan.x,tan.y,tan.z };

			vb->SetVertex(v, nv);

		}

		int ii = 0;
		for (int t = 0; t< m1->mNumFaces; t++) {

			aiFace * face = &m1->mFaces[t];

			int i1, i2, i3;

			i1 = face->mIndices[0];
			i2 = face->mIndices[1];
			i3 = face->mIndices[2];

			vb->SetIndex(ii++, i1);
			vb->SetIndex(ii++, i2);
			vb->SetIndex(ii++, i3);
			



		}
		vb->CreateBuffer();
		ent->AddMesh(m);
		m->Finalize();
	}

	for (int n = 0; n < node->mNumChildren; ++n)
	{
		
		
		Entity * newent = new Entity();
		ent->AddSub(newent);
		CopyNode(newent,node->mChildren[n]);

	}

}

Entity * ModelImport::ImportEntity(string path) {

	Entity * ent = new Entity();

	scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	CopyNode(ent, scene->mRootNode);
	


	return ent;
}