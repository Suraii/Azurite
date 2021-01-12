#include "Game.hpp"

using namespace Azurite;

Game::Game() : stateMachine(*this), componentsStorage(*this)
{}

Game::~Game()
{}
