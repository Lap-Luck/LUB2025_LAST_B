defineModule("Editor")
addModuleDependency("Editor" "CoreEditor")
addModuleDependency("Editor" "Game")

defineExecutable("EditorTarget")
addExecutableDependency("EditorTarget" "Editor")