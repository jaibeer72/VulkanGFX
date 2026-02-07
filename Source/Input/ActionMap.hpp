#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

namespace Input {

// Simple action/axis bindings container (header-only, minimal for scaffolding)
class ActionMap {
public:
    void bindAction(const std::string& action, int key) { actionBindings_[action] = key; }
    int getActionKey(const std::string& action) const {
        auto it = actionBindings_.find(action);
        return it == actionBindings_.end() ? -1 : it->second;
    }

    void bindAxis(const std::string& axis, int positive, int negative) { axisBindings_[axis] = {positive, negative}; }
    std::pair<int,int> getAxisKeys(const std::string& axis) const {
        auto it = axisBindings_.find(axis);
        return it == axisBindings_.end() ? std::pair<int,int>{-1, -1} : it->second;
    }

    std::vector<std::string> actions() const {
        std::vector<std::string> out;
        out.reserve(actionBindings_.size());
        for (auto &p : actionBindings_) out.push_back(p.first);
        return out;
    }

    std::vector<std::string> axes() const {
        std::vector<std::string> out;
        out.reserve(axisBindings_.size());
        for (auto &p : axisBindings_) out.push_back(p.first);
        return out;
    }

private:
    std::unordered_map<std::string,int> actionBindings_;
    std::unordered_map<std::string,std::pair<int,int>> axisBindings_;
};

} // namespace Input