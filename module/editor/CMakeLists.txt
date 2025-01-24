defineModule("Editor")
addModuleDependency("Editor" "Core")
addModuleDependency("Editor" "Game")

defineExecutable("EditorTarget")
addExecutableDependency("EditorTarget" "Editor")