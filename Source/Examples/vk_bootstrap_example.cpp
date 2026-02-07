#include <iostream>
#include <VkBootstrap.h>
#include <GLFW/glfw3.h>

int main() {
    // Init GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "vk-bootstrap example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Build Vulkan instance (vk-bootstrap)
    vkb::InstanceBuilder builder;
    auto inst_ret = builder.set_app_name("vk-bootstrap example").request_validation_layers().use_default_debug_messenger().build();
    if (!inst_ret) {
        std::cerr << "Failed to create Vulkan instance: " << inst_ret.error().message() << "\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    vkb::Instance vkb_inst = inst_ret.value();

    // Create surface from GLFW window
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult surf_res = glfwCreateWindowSurface(vkb_inst.instance, window, nullptr, &surface);
    if (surf_res != VK_SUCCESS) {
        std::cerr << "Failed to create window surface: " << surf_res << "\n";
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Select physical device
    vkb::PhysicalDeviceSelector selector{ vkb_inst };
    auto phys_ret = selector.set_surface(surface).select();
    if (!phys_ret) {
        std::cerr << "Failed to select physical device: " << phys_ret.error().message() << "\n";
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Create logical device
    vkb::DeviceBuilder device_builder{ phys_ret.value() };
    auto dev_ret = device_builder.build();
    if (!dev_ret) {
        std::cerr << "Failed to create device: " << dev_ret.error().message() << "\n";
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    vkb::Device vkb_device = dev_ret.value();

    // Create swapchain - pass surface in constructor
    vkb::SwapchainBuilder swapchain_builder{ vkb_device, surface };
    auto swap_ret = swapchain_builder.build();
    if (!swap_ret) {
        std::cerr << "Failed to create swapchain: " << swap_ret.error().message() << "\n";
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    auto swap = swap_ret.value();

    // Get image views for framebuffers
    auto image_views_ret = swap.get_image_views();
    if (!image_views_ret) {
        std::cerr << "Failed to get swapchain image views: " << image_views_ret.error().message() << "\n";
        vkb::destroy_swapchain(swap);
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    auto image_views = image_views_ret.value();

    VkDevice device = vkb_device.device;

    // --- Create a simple render pass with one color attachment ---
    VkAttachmentDescription color_attachment{};
    color_attachment.format = swap.image_format;
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment_ref{};
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment_ref;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo render_pass_info{};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &color_attachment;
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &dependency;

    VkRenderPass render_pass;
    if (vkCreateRenderPass(device, &render_pass_info, nullptr, &render_pass) != VK_SUCCESS) {
        std::cerr << "Failed to create render pass\n";
        swap.destroy_image_views(image_views);
        vkb::destroy_swapchain(swap);
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // --- Create framebuffers ---
    std::vector<VkFramebuffer> framebuffers(image_views.size());
    for (size_t i = 0; i < image_views.size(); ++i) {
        VkImageView attachments[] = { image_views[i] };
        VkFramebufferCreateInfo framebuffer_info{};
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = render_pass;
        framebuffer_info.attachmentCount = 1;
        framebuffer_info.pAttachments = attachments;
        framebuffer_info.width = swap.extent.width;
        framebuffer_info.height = swap.extent.height;
        framebuffer_info.layers = 1;

        if (vkCreateFramebuffer(device, &framebuffer_info, nullptr, &framebuffers[i]) != VK_SUCCESS) {
            std::cerr << "Failed to create framebuffer " << i << "\n";
            // Cleanup created framebuffers
            for (size_t j = 0; j < i; ++j) vkDestroyFramebuffer(device, framebuffers[j], nullptr);
            vkDestroyRenderPass(device, render_pass, nullptr);
            swap.destroy_image_views(image_views);
            vkb::destroy_swapchain(swap);
            vkb::destroy_device(vkb_device);
            vkb::destroy_surface(vkb_inst, surface);
            vkb::destroy_instance(vkb_inst);
            glfwDestroyWindow(window);
            glfwTerminate();
            return -1;
        }
    }

    // --- Create command pool & buffers ---
    uint32_t graphics_family = vkb_device.get_queue_index(vkb::QueueType::graphics).value();
    VkCommandPoolCreateInfo pool_info{};
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = graphics_family;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VkCommandPool command_pool;
    if (vkCreateCommandPool(device, &pool_info, nullptr, &command_pool) != VK_SUCCESS) {
        std::cerr << "Failed to create command pool\n";
        for (auto fb : framebuffers) vkDestroyFramebuffer(device, fb, nullptr);
        vkDestroyRenderPass(device, render_pass, nullptr);
        swap.destroy_image_views(image_views);
        vkb::destroy_swapchain(swap);
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::vector<VkCommandBuffer> command_buffers(framebuffers.size());
    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool = command_pool;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

    if (vkAllocateCommandBuffers(device, &alloc_info, command_buffers.data()) != VK_SUCCESS) {
        std::cerr << "Failed to allocate command buffers\n";
        vkDestroyCommandPool(device, command_pool, nullptr);
        for (auto fb : framebuffers) vkDestroyFramebuffer(device, fb, nullptr);
        vkDestroyRenderPass(device, render_pass, nullptr);
        swap.destroy_image_views(image_views);
        vkb::destroy_swapchain(swap);
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Record command buffers: just clear the color
    for (size_t i = 0; i < command_buffers.size(); ++i) {
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(command_buffers[i], &begin_info);

        VkClearValue clear_color = { {{0.2f, 0.4f, 0.6f, 1.0f}} };
        VkRenderPassBeginInfo rp_begin{};
        rp_begin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rp_begin.renderPass = render_pass;
        rp_begin.framebuffer = framebuffers[i];
        rp_begin.renderArea.offset = {0, 0};
        rp_begin.renderArea.extent = swap.extent;
        rp_begin.clearValueCount = 1;
        rp_begin.pClearValues = &clear_color;

        vkCmdBeginRenderPass(command_buffers[i], &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
        // No drawing commands, just a clear
        vkCmdEndRenderPass(command_buffers[i]);

        if (vkEndCommandBuffer(command_buffers[i]) != VK_SUCCESS) {
            std::cerr << "Failed to record command buffer " << i << "\n";
        }
    }

    // Create semaphores for sync
    VkSemaphoreCreateInfo sem_info{};
    sem_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    VkSemaphore image_available_semaphore;
    VkSemaphore render_finished_semaphore;
    if (vkCreateSemaphore(device, &sem_info, nullptr, &image_available_semaphore) != VK_SUCCESS ||
        vkCreateSemaphore(device, &sem_info, nullptr, &render_finished_semaphore) != VK_SUCCESS) {
        std::cerr << "Failed to create semaphores\n";
        // cleanup
        vkFreeCommandBuffers(device, command_pool, static_cast<uint32_t>(command_buffers.size()), command_buffers.data());
        vkDestroyCommandPool(device, command_pool, nullptr);
        for (auto fb : framebuffers) vkDestroyFramebuffer(device, fb, nullptr);
        vkDestroyRenderPass(device, render_pass, nullptr);
        swap.destroy_image_views(image_views);
        vkb::destroy_swapchain(swap);
        vkb::destroy_device(vkb_device);
        vkb::destroy_surface(vkb_inst, surface);
        vkb::destroy_instance(vkb_inst);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Get queues
    VkQueue graphics_queue = vkb_device.get_queue(vkb::QueueType::graphics).value();
    VkQueue present_queue = vkb_device.get_queue(vkb::QueueType::present).value();

    // Main loop: present a cleared color until the window is closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        uint32_t image_index = 0;
        VkResult acquire_res = vkAcquireNextImageKHR(device, swap.swapchain, UINT64_MAX, image_available_semaphore, VK_NULL_HANDLE, &image_index);
        if (acquire_res != VK_SUCCESS) {
            std::cerr << "Failed to acquire next image: " << acquire_res << "\n";
            break;
        }

        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        VkSubmitInfo submit_info{};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.waitSemaphoreCount = 1;
        submit_info.pWaitSemaphores = &image_available_semaphore;
        submit_info.pWaitDstStageMask = waitStages;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffers[image_index];
        submit_info.signalSemaphoreCount = 1;
        submit_info.pSignalSemaphores = &render_finished_semaphore;

        if (vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE) != VK_SUCCESS) {
            std::cerr << "Failed to submit draw command buffer\n";
            break;
        }

        VkPresentInfoKHR present_info{};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = &render_finished_semaphore;
        present_info.swapchainCount = 1;
        present_info.pSwapchains = &swap.swapchain;
        present_info.pImageIndices = &image_index;

        vkQueuePresentKHR(present_queue, &present_info);

        // Wait until presentation is done (simple example)
        vkQueueWaitIdle(present_queue);
    }

    // Wait for device before cleanup
    vkDeviceWaitIdle(device);

    // Cleanup
    vkDestroySemaphore(device, image_available_semaphore, nullptr);
    vkDestroySemaphore(device, render_finished_semaphore, nullptr);
    vkFreeCommandBuffers(device, command_pool, static_cast<uint32_t>(command_buffers.size()), command_buffers.data());
    vkDestroyCommandPool(device, command_pool, nullptr);
    for (auto fb : framebuffers) vkDestroyFramebuffer(device, fb, nullptr);
    vkDestroyRenderPass(device, render_pass, nullptr);
    swap.destroy_image_views(image_views);
    vkb::destroy_swapchain(swap);
    vkb::destroy_device(vkb_device);
    vkb::destroy_surface(vkb_inst, surface);
    vkb::destroy_instance(vkb_inst);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}