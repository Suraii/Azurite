#include "Azurite/systems/UISystems.hpp"

using namespace Azurite;

void Azurite::Sbutton_sprite_updater(CSprite &sprite, CButton &button)
{
    sprite.id = (button.clicked) ? button.clickedId : (
        (button.hovered) ? button.hoveredId : button.idleId
    );
}

static bool point_in_rect(Vector2D point, Vector2D origin, Vector2D size)
{
    return (
        point.x > origin.x && point.x < origin.x + size.x
        &&
        point.y > origin.y && point.y < origin.y + size.y
    );
}

void Azurite::Sbutton_params_updater(Game &game)
{
    auto components = game.componentsStorage.getComponents<CButton, CTransform2D, CCollisionBox>();
    auto &inputModule = game.inputModule->get();
    bool buf;

    for (auto &[button, transform, cbox] : components) {
        if (point_in_rect(inputModule.getCursorLocation(), transform.location,
        {cbox.size.x * transform.scale.x, cbox.size.y * transform.scale.y})) {
            button.hovered = true;
            buf = inputModule.getInputStatus(Input::MOUSE_LEFT_CLICK);
            if (button.clicked && !buf) {
                button.action(game);
                button.triggered = true;
            }
            button.clicked = buf;
        } else {
            button.hovered = false;
            button.clicked = false;
        }
    }
}

void Azurite::Sinput_action_invoker(Azurite::Game& game)
{
    auto components = game.componentsStorage.getComponents<CInputAction>();
    auto &inputModule = game.inputModule->get();

    for (auto &[iact] : components)
        if (!inputModule.getInputStatus(iact.input))
            iact.ready = true;
        else if (iact.ready) {
            iact.action(game);
            iact.ready = false;
        }
}
