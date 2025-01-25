#pragma once

#include "raylib.h"


class InputManager
{

public:
    static InputManager* get();

    Vector3 gyroscope;


    // Singleton Part
protected:
    InputManager() = default;
    InputManager(InputManager &other) = delete;
    void operator=(const InputManager &) = delete;

    static InputManager* instance;
};

inline InputManager* InputManager::get() {
    if (instance == nullptr)
        instance = new InputManager();
    return instance;
}