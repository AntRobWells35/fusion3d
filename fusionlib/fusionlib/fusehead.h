#pragma once

#include "Texture2D.h"
#include "Uniforms.h"
#include "UniformBuffer.h"
#include "UniformBinder.h"
#include "Common.h"
#include "MemBuffer.h"
#include "GpuChain.h"
#include "Geo.h"
#include "FusionApp.h"
#include "GraphicsPipeline.h"
#include "GraphNode.h"
#include "GraphRenderer.h"
#include "GraphScene.h"
#include "MultiPassRenderer.h"
#include "Effect.h"
#include "VertexBuffer.h"
#include "Mesh3D.h"
#include "ModelImport.h"

#define FApp FusionApp::GetApp()
#define AppDev FusionApp::GetApp()->GetDevice()