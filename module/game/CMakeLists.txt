defineModule("Game")
addModuleDependency("Game" "Core")

defineExecutable("GameTarget")
addExecutableDependency("GameTarget" "Game")