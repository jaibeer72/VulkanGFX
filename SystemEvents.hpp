//
//  SystemEvents.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 03/09/2023.
//

#ifndef SystemEvents_hpp
#define SystemEvents_hpp
#include "../../Utils/Events/Public/Event.hpp"

public static class SystemEvents
{
public:
    static Event<> SystemStartEvent;
    static Event<> SystemStopEvent;
}

#endif /* SystemEvents_hpp */
