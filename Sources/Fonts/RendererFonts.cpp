#include "RendererFonts.hpp"

#include "Models/VertexDefault.hpp"
#include "Scenes/Scenes.hpp"
#include "Uis/Uis.hpp"
#include "Text.hpp"

namespace acid
{
RendererFonts::RendererFonts(const Pipeline::Stage &pipelineStage) :
	RenderPipeline(pipelineStage),
	m_pipeline(pipelineStage, { "Shaders/Fonts/Font.vert", "Shaders/Fonts/Font.frag" }, { VertexDefault::GetVertexInput() })
{
}

void RendererFonts::Render(const CommandBuffer &commandBuffer)
{
	auto camera = Scenes::Get()->GetCamera();
	m_uniformScene.Push("projection", camera->GetProjectionMatrix());
	m_uniformScene.Push("view", camera->GetViewMatrix());

	m_pipeline.BindPipeline(commandBuffer);

	for (const auto &screenObject : Uis::Get()->GetObjects())
	{
		if (!screenObject->IsEnabled())
		{
			continue;
		}

		auto object = dynamic_cast<Text *>(screenObject);

		if (object != nullptr)
		{
			object->CmdRender(commandBuffer, m_pipeline, m_uniformScene);
		}
	}
}
}
