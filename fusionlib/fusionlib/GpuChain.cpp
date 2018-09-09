#include "stdafx.h"
#include "GpuChain.h"


GpuChain::GpuChain()
{
}


GpuChain::~GpuChain()
{
}

void GpuChain::BeginBuffer() {

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = FApp->GetCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(FApp->GetDevice(), &allocInfo,&buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	else {
		cout << "Allocated command buffers" << endl;
	}

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	if (vkBeginCommandBuffer(buffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}


}

void GpuChain::BeginRender(VkFramebuffer * fb,GraphicsPipeline *gp) {

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = FApp->GetRenderPass();
	renderPassInfo.framebuffer = *fb;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = FApp->GetSwapExtent();

	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *gp->GetGraphicsPipeline());


}

void GpuChain::Render(VertexBuffer * vb) {

	VkBuffer vertexBuffers[] = { vb->GetBuf() };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(buffer, 0, 1, vertexBuffers, offsets);

	VkBuffer indexBuffer = vb->GetIndexBuf();

	vkCmdBindIndexBuffer(buffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

	vkCmdDrawIndexed(buffer, static_cast<uint32_t>(vb->GetIndices().size()), 1, 0, 0, 0);



}

void GpuChain::EndRender() {
	vkCmdEndRenderPass(buffer);
}

void GpuChain::EndBuffer() {
	if (vkEndCommandBuffer(buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
	else {
		cout << "Recorded command buffer end" << endl;
	}
}