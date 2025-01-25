#pragma once

class EditorState
{
public:
    std::weak_ptr<Actor> selectedActor {};
    std::weak_ptr<Actor> draggingActor {};
    std::unique_ptr<Actor> toPlace {};

    int selectedActorFactoryEntry {0};
};