@startuml
abstract AModule {
    -Game &owner
    +void onStart()
    +void onTick()
    +void onStop()
}

AModule <|-- ADisplayModule
abstract ADisplayModule {
    +void drawSprite(const string spriteSheet, unsigned tileId, Transform transform)
    +void drawRectangle(Rectange rectange, Color color)
}

AModule <|-- AInputModule
abstract AInputModule {
    +bool isKeyPressed(unsigned player, Input key)
    +Vector getCursorLocation(unsigned player)
}

AModule <|-- AAudioModule
abstract AAudioModule {
    +void playSound(const string name, float volume, float pitch, bool loop)
    +void stopSound(const string name)
}

AModule <|-- AAssetModule
abstract AAssetModule {
    +void loadAssets(const string dir_path)
    +void loadAsset(const string asset_path)
    +void releaseAssets(const string dir_path)
    +void releaseAsset(const string asset_path)
}
@enduml
