#include "ShootingRangeSystems.hpp"

void Sbutton_sprite_updater(Azurite::CSprite &sprite, CButton &button)
{
    sprite.id = (button.clicked) ? button.clickedId : (
        (button.hovered) ? button.hoveredId : button.idleId
    );
}

static bool point_in_rect(Azurite::Vector2D point, Azurite::Vector2D origin, Azurite::Vector2D size)
{
    return (
        point.x > origin.x && point.x < origin.x + size.x
        &&
        point.y > origin.y && point.y < origin.y + size.y
    );
}

void Sbutton_params_updater(Azurite::Game &game)
{
    auto components = game.componentsStorage.getComponents<CButton, Azurite::CTransform2D, Azurite::CCollisionBox>();
    auto &inputModule = game.inputModule->get();
    bool buf;

    for (auto &[button, transform, cbox] : components) {
        if (point_in_rect(inputModule.getCursorLocation(), transform.location,
        {cbox.size.x * transform.scale.x, cbox.size.y * transform.scale.y})) {
            button.hovered = true;
            buf = inputModule.getInputStatus(Azurite::Input::MOUSE_LEFT_CLICK);
            if (button.clicked && !buf)
                button.action(game);
            button.clicked = buf;
        } else {
            button.hovered = false;
            button.clicked = false;
        }
    }
}
