#ifndef __AZURITE__BUILT_IN_SOUND_SYSTEMS
#define __AZURITE__BUILT_IN_SOUND_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/SoundComponents.hpp"
#include "Azurite/components/UIComponents.hpp"

namespace Azurite {

    /*
    ** Core system that play audios called by speaker components
    */

    void Sspeaker_player(Game &game);

    /*
    ** System that play speakers if a button owned by the same entity is clicked
    */

    void Sbutton_speaker_activator(CSpeaker &speaker, CButton &button);
}

#endif
