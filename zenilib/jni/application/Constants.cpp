
#include "Constants.h"

const float SPEED_OF_GRAVITY = 9.80665f;
const float GROUND_ABSORPTION_COEFFICIENT = 0.3f;
const Zeni::Vector3f GRAVITY_VECTOR = Zeni::Vector3f(0, 0, -SPEED_OF_GRAVITY);
const float PHYSICS_MIN_MOVEMENT_THRESHOLD = .005;
const float HEIGHT_INCREMENT = 10.0;
extern const float SELL_PERCENTAGE = 0.7;