//
//  SystemEvents.cpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 03/09/2023.
//

#include "../../Utils/Events/Public/Event.hpp"

namespace SystemEvents {
    static Event<> SystemStartEvent;
    static Event<> SystemStopEvent;
}
