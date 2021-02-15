#include "Azurite/systems/SoundSystems.hpp"

using namespace Azurite;

void Azurite::Sspeaker_player(Game &game)
{
    auto speakers = game.componentsStorage.getComponents<CSpeaker>();

    for (auto &[speaker] : speakers) {
        if (speaker.isPlaying) {
            game.audioModule->get().playSound(speaker.sound, speaker.volume, speaker.pitch, speaker.loop);
            speaker.isPlaying = false;
        }
        if (speaker.isStopping) {
            game.audioModule->get().stopSound(speaker.sound);
            speaker.isStopping = false;
        }
    }
}

void Azurite::Sbutton_speaker_activator(CSpeaker &speaker, CButton &button)
{
    if (button.clicked && !speaker.isPlaying)
        speaker.play();
}
