#include <map>
#include <type_traits>

#include <glimac/SDLWindowManager.hpp>

#include <class/Character.hpp>
#include <class/AssetManager.hpp>
#include <class/Model.hpp>

using namespace glimac;

namespace UP
{

Character::Character(const std::string &name)
    : GameObject(glm::vec3(0.f, 0.f, 0.f),
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f,
                 name),
      _health(1),
      _sideState(CENTER),
      _verticalState(RUNNING){};

void Character::event(const SDL_Event &e)
{
  switch (e.type)
  {
  case SDL_KEYDOWN:
    /* left/right and up/down player */
    keyDownHandler(e.key.keysym.sym);
    break;

  case SDL_KEYUP:
    /* left/right and up/down player */
    keyUpHandler(e.key.keysym.sym);
    break;
  }
}

void Character::keyDownHandler(const int &key)
{
  /* left and right player */
  if (key == SDLK_RIGHT)
  {
    _sideState = RIGHT;
  }
  if (key == SDLK_LEFT)
  {
    _sideState = LEFT;
  }
  /* up player */
  if (key == SDLK_UP)
  {
    _verticalState = JUMPING;
  }
}

void Character::keyUpHandler(const int &key)
{
  /* left and right player */
  if (key == SDLK_RIGHT)
  {
    _sideState = CENTER;
  }
  if (key == SDLK_LEFT)
  {
    _sideState = CENTER;
  }
  /* up player */
  if (key == SDLK_UP)
  {
    _verticalState = RUNNING;
  }
}

void Character::forwardMove()
{
  addPosX(speedX());
}

void Character::move()
{
  forwardMove();
  sideMove(_sideState);
  sideMove(_verticalState);
}

void Character::sideMove(const int &side)
{
  switch (side)
  {
  case CENTER:
    if (_position[Y] < 0)
    {
      setPosY(_position[Y] + _speed[Y]);
    }
    else if (_position[Y] > 0)
    {
      setPosY(_position[Y] - _speed[Y]);
    }
    break;
  case LEFT:
    if (_position[Y] > -2)
    {
      setPosY(_position[Y] - _speed[Y]);
    }
    break;
  case RIGHT:
    if (_position[Y] < 2)
    {
      setPosY(_position[Y] + _speed[Y]);
    }
    break;
  }
}

void Character::verticalMove(const int &movement)
{
  switch (movement)
  {
  case RUNNING:
    if (_position[Z] < 0)
    {
      setPosZ(_position[Z] + _speed[Z]);
    }
    else if (_position[Z] > 0)
    {
      setPosZ(_position[Z] - _speed[Z]);
    }
    break;
  case JUMPING:
    if (_position[Z] < 2)
    {
      setPosZ(_position[Z] + _speed[Z]);
    }
    break;
  }
}

void Character::addBonus(const Bonus &bonus)
{
  time_t startingTime = time(NULL);
  std::map<unsigned int, time_t>::iterator it;
  it = _activeBonuses.find(bonus.getBonusType());
  if (it == _activeBonuses.end())
  {
    useBonus(bonus.getBonusType(), startingTime);
  }
  else
  {
    it->second = startingTime;
  }
}

void Character::deleteConsumedBonus(const Bonus &bonus)
{
  std::map<unsigned int, time_t>::iterator it;
  for (it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    if ((it->first) == bonus.getBonusType())
    {
      _activeBonuses.erase(it);
      break;
    }
  }
}

void Character::deleteExpiredBonuses()
{
  time_t currentTime = time(NULL);
  std::map<unsigned int, time_t>::iterator it;
  for (it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    int expirationTime = (it->second) + BONUS_DURATION;
    if (currentTime == expirationTime)
    {
      _activeBonuses.erase(it);
    }
  }
}

bool Character::collision(const Character &p2)
{
  if ((int)_position[X] == (int)p2._position[X] && (int)_position[Y] == (int)p2._position[Y] && (int)_position[Z] == (int)p2._position[Z])
  {
    loseHealth(1);
  }
}

void Character::loseHealth(const unsigned int &value)
{
  setHealth(_health - value);
}

void Character::display() const
{
  _model->draw();
  //std::cout << _position << std::endl;
}

void Character::reset()
{
  // Directly Copied from the constructor
  // TAKE CARE
  GameObject::reset();
  _health = 1;
  _sideState = CENTER;
  _verticalState = RUNNING;
  _activeBonuses.clear();
  setSpeed(glm::vec3(0.0001f, 0.0001f, 0.0001f));
  _scale = 0.1f;

}


} // namespace UP
