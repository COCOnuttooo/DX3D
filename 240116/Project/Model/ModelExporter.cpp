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