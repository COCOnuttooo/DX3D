#include "Framework.h"
#include "ModelExporter.h"
ModelExporter::ModelExporter(string name)
	:name(name)
{
	importer = new Assimp::Importer;

	importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
	importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS);

	scene = importer->ReadFile("_ModelData/FBX/" + name + ".fbx",
		aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	assert(scene != nullptr);
}

ModelExporter::~ModelExporter()
{
	delete importer;
}

void ModelExporter::ExportMaterial()
{
     ReadMaterial();
    WriteMaterial();
}

void ModelExporter::ReadMaterial()
{
	for (UINT i = 0; i < scene->mNumMaterials; i++)
	{
        aiMaterial* srcMaterial = scene->mMaterials[i];
        Material* material = new Material();

        material->SetName(srcMaterial->GetName().C_Str());

        MaterialData* data = &material->GetBuffer()->data;

        aiColor3D color;
        srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        data->diffuse = Vector4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
        data->specular = Vector4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
        data->ambient = Vector4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
        data->emissive = Vector4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_SHININESS, data->shininess);

        aiString file;
        srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
        material->SetDiffuseMap(CreateTexture(file.C_Str()));
        file.Clear();

        srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
        material->SetSpecularMap(CreateTexture(file.C_Str()));
        file.Clear();

        srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
        material->SetNormalMap(CreateTexture(file.C_Str()));
        file.Clear();

        materials.push_back(material);
	}
}

void ModelExporter::WriteMaterial()
{
    string savePath = "_ModelData/Material/" + name + "/";
    string fileName = "MaterialList.list";

    CreateFolder(savePath);
    BinaryWriter data(savePath + fileName);

    data.WriteData(materials.size());

    for (Material* material : materials)
    {
        string path = savePath + material->GetName() + ".mat";

        material->Save(ToWString(path));

        data.WriteData(path);
        delete material;
    }
    materials.clear();
}

void ModelExporter::ReadMesh(aiNode* node)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        MeshData* mesh = new MeshData();

        mesh->name = node->mName.C_Str();

        UINT index = node->mMeshes[i];

        aiMesh* srcMesh = scene->mMeshes[index];

        mesh->materialIndex = srcMesh->mMaterialIndex;

        UINT startVertex = mesh->vertices.size();

        /////////////////////////////////
       /* vector<VertexWeights> vertexWeights;
        vertexWeights.resize(srcMesh->mNumVertices);

        ReadBone(srcMesh, vertexWeights);*/
        /////////////////////////////////


        mesh->vertices.resize(srcMesh->mNumVertices);

        for (UINT j = 0; j < srcMesh->mNumVertices; j++)
        {
            ModelVertex vertex;

            memcpy(&vertex.pos, &srcMesh->mVertices[j], sizeof(Vector3));

            if (srcMesh->HasTextureCoords(0))
                memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][j], sizeof(Vector2));

            if (srcMesh->HasNormals())
                memcpy(&vertex.normal, &srcMesh->mNormals[j], sizeof(Vector3));

            if (srcMesh->HasTangentsAndBitangents())
                memcpy(&vertex.tangent, &srcMesh->mTangents[j], sizeof(Vector3));

            //if (!vertexWeights.empty())
            //{
            //    vertexWeights[j].Normalize();

            //    vertex.indices.x = vertexWeights[j].indices[0];
            //    vertex.indices.y = vertexWeights[j].indices[1];
            //    vertex.indices.z = vertexWeights[j].indices[2];
            //    vertex.indices.w = vertexWeights[j].indices[3];

            //    vertex.weights.x = vertexWeights[j].weights[0];
            //    vertex.weights.y = vertexWeights[j].weights[1];
            //    vertex.weights.z = vertexWeights[j].weights[2];
            //    vertex.weights.w = vertexWeights[j].weights[3];
            //}



            mesh->vertices[j] = vertex;
        }

        for (UINT j = 0; j < srcMesh->mNumFaces; j++)
        {
            aiFace& face = srcMesh->mFaces[j];

            for (UINT k = 0; k < face.mNumIndices; k++)
            {
                mesh->indices.push_back(face.mIndices[k] + startVertex);
            }
        }

        meshes.push_back(mesh);
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ReadMesh(node->mChildren[i]);
    }
}

void ModelExporter::ExportMesh()
{
    ReadMesh(scene->mRootNode);
}

void ModelExporter::WriteMesh()
{
}

wstring ModelExporter::CreateTexture(string file)
{
    if (file.length() == 0)
        return L"";

    string fileName = GetFileName(file);

    const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str());

    string path = "_Texture/Model/" + name + "/" + fileName;

    CreateFolder(path);

    if (PathFileExistsA(path.c_str()))
        return ToWString(path);

    if (texture == nullptr)
        return L"";

    if (texture->mHeight < 1)
    {
        BinaryWriter data(ToWString(path));
        data.WriteData(texture->pcData, texture->mWidth);
    }
    else
    {
        Image image;
        image.width = texture->mWidth;
        image.height = texture->mHeight;
        image.pixels = (uint8_t*)texture->pcData;
        image.rowPitch = image.width * 4;
        image.slicePitch = image.width * image.height * 4;

        SaveToWICFile(image, WIC_FLAGS_NONE, GetWICCodec(WIC_CODEC_PNG), ToWString(path).c_str());
    }

    return ToWString(path);
}
