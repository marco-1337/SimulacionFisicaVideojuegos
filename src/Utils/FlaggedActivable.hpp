#pragma once

#include <memory>

class FlaggedActivable {
protected:
    std::shared_ptr<bool> enabledFlag;
public:
    FlaggedActivable( std::shared_ptr<bool> enabledFlag = nullptr): 
        enabledFlag((enabledFlag == nullptr) ? std::make_shared<bool>(true) : enabledFlag) {}

    inline bool isEnabled() { return *enabledFlag; }
};