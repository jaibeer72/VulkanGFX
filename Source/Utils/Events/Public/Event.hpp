//
//  Event.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 03/09/2023.
//

#ifndef Event_hpp
#define Event_hpp

#include <functional>
#include <vector>
#include <iostream>
#include <algorithm> // for std::remove_if

template <typename... Args>
class Event {
private:
    std::vector<std::function<void(Args...)>> listeners;

public:
    void AddListener(const std::function<void(Args...)>& listener) {
        listeners.push_back(listener);
    }

    void RemoveListener(const std::function<void(Args...)>& listener) {
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [&](const std::function<void(Args...)>& l) {
                return l.target_type() == listener.target_type();
            }), listeners.end());
    }

    void Invoke(Args... args) {
        for(auto& listener : listeners) {
            listener(args...);
        }
    }
};

#endif /* Event_hpp */

