#include "stdafx.h"
#include "GpuChain.h"


GpuChain::GpuChain()
{
}


GpuChain::~GpuChain()
{
}

void GpuChain::Run() {

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &buffer;

	vkQueueSubmit(FApp->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(FApp->GetGraphicsQueue());

	vkFreeCommandBuffers(AppDev, FApp->GetComPool(), 1, &buffer);

}

void GpuChain::TransistImage(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {


	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		throw std::invalid_argument("unsupported layout transition!");
	}

	vkCmdPipelineBarrier(
		buffer,
		sourceStage, destinationStage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

}

void GpuChain::CopyBufferToImage(MemBuffer * src, VkImage img, int w, int h)
{

	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		(uint32_t)w,
		(uint32_t)h,
		1
	};

	vkCmdCopyBufferToImage(buffer, src->GetBuffer(), img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	

}

void GpuChain::CopyBuffer(MemBuffer * src, MemBuffer * dst)
{

	VkBufferCopy copyRegion = {};
	copyRegion.size = src->GetSize();
	vkCmdCopyBuffer(buffer, src->GetBuffer() , dst->GetBuffer(), 1, &copyRegion);

}

void GpuChain::Copy(MemBuffer *src, MemBuffer *dst) {
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = FusionApp::GetApp()->GetComPool();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(FusionApp::GetApp()->GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkDeviceSize size = src->GetSize();


	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, src->GetBuffer(), dst->GetBuffer(), 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(FusionApp::GetApp()->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(FusionApp::GetApp()->GetGraphicsQueue());

	vkFreeCommandBuffers(FusionApp::GetApp()->GetDevice(), FusionApp::GetApp()->GetComPool(), 1, &commandBuffer);

}

void GpuChain::BeginBufferSingle() {

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = FApp->GetCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(FApp->GetDevice(), &allocInfo, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	else {
		cout << "Allocated command buffers" << endl;
	}

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	if (vkBeginCommandBuffer(buffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}

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


	//vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);


	vkCmdDrawIndexed(buffer, static_cast<uint32_t>(vb->GetIndices().size()), 1, 0, 0, 0);



}

void GpuChain::Render(VertexBuffer *vb, UniformBinder *binder,VkPipelineLayout layout,VkDescriptorSet set)
{

	VkBuffer vertexBuffers[] = { vb->GetBuf() };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(buffer, 0, 1, vertexBuffers, offsets);

	VkBuffer indexBuffer = vb->GetIndexBuf();

	vkCmdBindIndexBuffer(buffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);


	vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &set, 0, nullptr);


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

void GpuChain::EndBufferSingle() {

	vkEndCommandBuffer(buffer);

}