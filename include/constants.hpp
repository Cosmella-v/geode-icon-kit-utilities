#pragma once

#include <Geode/Geode.hpp>

enum class PathType { Fire = 1, Ice, Poison, Shadow, Lava, Earth, Blood, Metal, Light, Souls };

constexpr UnlockType ICON_TO_UNLOCK[] = {
  [static_cast<int>(IconType::Cube)] = UnlockType::Cube,
  [static_cast<int>(IconType::Ship)] = UnlockType::Ship,
  [static_cast<int>(IconType::Ball)] = UnlockType::Ball,
  [static_cast<int>(IconType::Ufo)] = UnlockType::Bird,
  [static_cast<int>(IconType::Wave)] = UnlockType::Dart,
  [static_cast<int>(IconType::Robot)] = UnlockType::Robot,
  [static_cast<int>(IconType::Spider)] = UnlockType::Spider,
  [static_cast<int>(IconType::Swing)] = UnlockType::Swing,
  [static_cast<int>(IconType::Jetpack)] = UnlockType::Jetpack,
  [static_cast<int>(IconType::DeathEffect)] = UnlockType::Death,
  [static_cast<int>(IconType::Special)] = UnlockType::Streak,
  [static_cast<int>(IconType::Item)] = UnlockType::GJItem,
  [static_cast<int>(IconType::ShipFire)] = UnlockType::ShipFire
};

constexpr IconType UNLOCK_TO_ICON[] = {
  [static_cast<int>(UnlockType::Cube)] = IconType::Cube,
  [static_cast<int>(UnlockType::Ship)] = IconType::Ship,
  [static_cast<int>(UnlockType::Ball)] = IconType::Ball,
  [static_cast<int>(UnlockType::Bird)] = IconType::Ufo,
  [static_cast<int>(UnlockType::Dart)] = IconType::Wave,
  [static_cast<int>(UnlockType::Robot)] = IconType::Robot,
  [static_cast<int>(UnlockType::Spider)] = IconType::Spider,
  [static_cast<int>(UnlockType::Swing)] = IconType::Swing,
  [static_cast<int>(UnlockType::Jetpack)] = IconType::Jetpack,
  
  [static_cast<int>(UnlockType::Death)] = IconType::DeathEffect,
  [static_cast<int>(UnlockType::Streak)] = IconType::Special,
  [static_cast<int>(UnlockType::GJItem)] = IconType::Item,
  [static_cast<int>(UnlockType::ShipFire)] = IconType::ShipFire
};

#define IS_NORMAL_ICON_TYPE(iconType) (iconType <= IconType::Jetpack)
#define IS_NORMAL_UNLOCK_TYPE(unlockType) (\
  unlockType == UnlockType::Cube ||\
  unlockType == UnlockType::Ship ||\
  unlockType == UnlockType::Bird ||\
  unlockType == UnlockType::Ball ||\
  unlockType == UnlockType::Dart ||\
  unlockType == UnlockType::Spider ||\
  unlockType == UnlockType::Robot ||\
  unlockType == UnlockType::Swing ||\
  unlockType == UnlockType::Jetpack\
)

constexpr const char * ICON_NAMES[] = {
  [static_cast<int>(UnlockType::Cube)] = "Cube",
  [static_cast<int>(UnlockType::Ship)] = "Ship",
  [static_cast<int>(UnlockType::Ball)] = "Ball",
  [static_cast<int>(UnlockType::Bird)] = "UFO",
  [static_cast<int>(UnlockType::Dart)] = "Wave",
  [static_cast<int>(UnlockType::Robot)] = "Robot",
  [static_cast<int>(UnlockType::Spider)] = "Spider",
  [static_cast<int>(UnlockType::Swing)] = "Swing",
  [static_cast<int>(UnlockType::Jetpack)] = "Jetpack",
  [static_cast<int>(UnlockType::Death)] = "Death Effect",
  [static_cast<int>(UnlockType::Streak)] = "Trail",
  [static_cast<int>(UnlockType::GJItem)] = "Item",
  [static_cast<int>(UnlockType::ShipFire)] = "Ship Fire",
  [static_cast<int>(UnlockType::Col1)] = "Color 1",
  [static_cast<int>(UnlockType::Col2)] = "Color 2",
  [0] = "NULL"
};

constexpr int STREAK_UNLOCK_ORDER[] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
};

constexpr int SHIP_FIRE_UNLOCK_ORDER[] = {
  1,
  2,
  3,
  4,
  5,
  6,
};

// there are other items, but these are the ones shown in the icon kit as animations
constexpr int ITEM_UNLOCK_ORDER[] = {
  18,
  19,
  20,
};

constexpr int DEATH_EFFECT_UNLOCK_ORDER[] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
};

constexpr int COLOR_UNLOCK_ORDER[] = {
  // the red group
  51, 19, 48, 9,
  37, 53, 54, 55,
  25, 56, 57, 58,
  
  // the orange group
  62, 63, 10, 29,
  26, 59, 60, 61,
  30, 64, 65, 66,
  
  // the yellow group
  70, 42, 11, 27,
  71, 14, 31, 45,
  46, 67, 68, 69,
  
  // the green group
  72, 73, 0, 1,
  105, 28, 32, 20,
  2, 38, 79, 80,
  
  // the light blue group
  74, 75, 44, 3,
  40, 76, 77, 78,
  33, 21, 81, 82,
  
  // the dark blue group
  83, 16, 4, 5,
  22, 39, 84, 50,
  34, 85, 86, 87,
  106, 88, 89, 90,
  
  // the purple group
  52, 41, 6, 35,
  47, 23, 92, 93,
  49, 95, 96, 97,
  
  // the magenta group
  98, 8, 36, 103,
  7, 13, 24, 104,
  43, 99, 100, 101,

  // the grayscale group
  12, 91, 17, 102, 18, 94, 15,
};

constexpr std::span<const int> SPECIAL_UNLOCK_ORDER[] = {
  [static_cast<int>(UnlockType::Streak)] = STREAK_UNLOCK_ORDER,
  [static_cast<int>(UnlockType::ShipFire)] = SHIP_FIRE_UNLOCK_ORDER,
  [static_cast<int>(UnlockType::GJItem)] = ITEM_UNLOCK_ORDER,
  [static_cast<int>(UnlockType::Death)] = DEATH_EFFECT_UNLOCK_ORDER,
  [static_cast<int>(UnlockType::Col1)] = COLOR_UNLOCK_ORDER,
  [static_cast<int>(UnlockType::Col2)] = COLOR_UNLOCK_ORDER,
};

constexpr std::pair<const int, const UnlockType> SHARDS_OF_POWER_UNLOCK_ORDER[] = {
  { 95, UnlockType::Cube},   { 24, UnlockType::Ball},  {  9, UnlockType::Robot},  { 29, UnlockType::Ship},   {  2, UnlockType::Death},  // fire
  { 84, UnlockType::Cube},   { 26, UnlockType::Ball},  {  6, UnlockType::Spider}, { 31, UnlockType::Ship},   {  9, UnlockType::Death},  // ice
  { 22, UnlockType::Ball},   { 20, UnlockType::Bird},  {105, UnlockType::Cube},   {  5, UnlockType::Spider}, {  4, UnlockType::Death},  // poison
  { 20, UnlockType::Dart},   { 28, UnlockType::Ship},  { 26, UnlockType::Bird},   { 17, UnlockType::Robot},  {  5, UnlockType::Death},  // shadow
  { 14, UnlockType::Dart},   { 92, UnlockType::Cube},  {  7, UnlockType::Robot},  {  9, UnlockType::Spider}, {  6, UnlockType::Death},  // lava
  { 98, UnlockType::Cube},   { 22, UnlockType::Bird},  { 34, UnlockType::Ship},   { 13, UnlockType::Robot},  {  7, UnlockType::Death},  // tier 1
  { 32, UnlockType::Spider}, {352, UnlockType::Cube},  { 43, UnlockType::Dart},   {156, UnlockType::Ship},   { 54, UnlockType::Robot},  // earth
  {165, UnlockType::Cube},   { 43, UnlockType::Robot}, { 15, UnlockType::Swing},  { 59, UnlockType::Dart},   { 45, UnlockType::Spider}, // blood
  {235, UnlockType::Cube},   { 50, UnlockType::Dart},  {108, UnlockType::Ship},   {117, UnlockType::Bird},   { 25, UnlockType::Spider}, // metal
  { 74, UnlockType::Bird},   { 57, UnlockType::Robot}, { 55, UnlockType::Spider}, {438, UnlockType::Cube},   {102, UnlockType::Ball},   // light
  { 78, UnlockType::Ship},   { 78, UnlockType::Ball},  { 35, UnlockType::Spider}, {395, UnlockType::Cube},   {148, UnlockType::Bird},   // soul
  {388, UnlockType::Cube},   {106, UnlockType::Ball},  { 62, UnlockType::Dart},   { 84, UnlockType::Bird},   { 20, UnlockType::Death},  // tier 2
};

constexpr std::pair<const int, const UnlockType> PATH_OF_FIRE_UNLOCK_ORDER[] = {
  {213, UnlockType::Cube},
  {48,  UnlockType::Col1},
  {236, UnlockType::Cube},
  {54,  UnlockType::Col1},
  {60,  UnlockType::Dart},
  {51,  UnlockType::Col2},
  {35,  UnlockType::Robot},
  {143, UnlockType::Ship},
  {46,  UnlockType::Dart},
  {55,  UnlockType::Robot},
  {79,  UnlockType::Bird},
  //{19, UnlockType::Swing}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_ICE_UNLOCK_ORDER[] = {
  {49, UnlockType::Spider},
  {47, UnlockType::Col2},
  {394, UnlockType::Cube},
  {44, UnlockType::Col1},
  {66, UnlockType::Ball},
  {106, UnlockType::Col1},
  {130, UnlockType::Ship},
  {135, UnlockType::Bird},
  {29, UnlockType::Robot},
  {76, UnlockType::Ball},
  {99, UnlockType::Ship},
  //{48, UnlockType::Robot}
};
constexpr std::pair<const int, const UnlockType> PATH_OF_POISON_UNLOCK_ORDER[] = {
  {274, UnlockType::Cube},
  {73, UnlockType::Col2},
  {42, UnlockType::Robot},
  {79, UnlockType::Col2},
  {8, UnlockType::Swing},
  {80, UnlockType::Col1},
  {276, UnlockType::Cube},
  {57, UnlockType::Spider},
  {121, UnlockType::Bird},
  {110, UnlockType::Ball},
  {342, UnlockType::Cube},
  //{146, UnlockType::Bird}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_SHADOW_UNLOCK_ORDER[] = {
  {188, UnlockType::Cube},
  {93, UnlockType::Col1},
  {232, UnlockType::Cube},
  {99, UnlockType::Col2},
  {36, UnlockType::Spider},
  {96, UnlockType::Col2},
  {141, UnlockType::Ship},
  {72, UnlockType::Dart},
  {61, UnlockType::Ball},
  {385, UnlockType::Cube},
  {127, UnlockType::Ship},
  //{40, UnlockType::Robot}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_LAVA_UNLOCK_ORDER[] = {
  {60, UnlockType::Ship},
  {56, UnlockType::Col2},
  {239, UnlockType::Cube},
  {51, UnlockType::Col1},
  {47, UnlockType::Bird},
  {57, UnlockType::Col1},
  {429, UnlockType::Cube},
  {47, UnlockType::Robot},
  {79, UnlockType::Ball},
  {221, UnlockType::Cube},
  {28, UnlockType::Spider},
  //{94, UnlockType::Ship}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_EARTH_UNLOCK_ORDER[] = {
  {227, UnlockType::Cube},
  {65, UnlockType::Col1},
  {79, UnlockType::Ship},
  {68, UnlockType::Col2},
  {102, UnlockType::Bird},
  {45, UnlockType::Col1},
  {32, UnlockType::Robot},
  {53, UnlockType::Dart},
  {77, UnlockType::Ball},
  {23, UnlockType::Spider},
  {247, UnlockType::Cube},
  //{91, UnlockType::Ship}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_BLOOD_UNLOCK_ORDER[] = {
  {431, UnlockType::Cube},
  {54, UnlockType::Col2},
  {92, UnlockType::Ball},
  {53, UnlockType::Col2},
  {23, UnlockType::Swing},
  {57, UnlockType::Col2},
  {81, UnlockType::Dart},
  {53, UnlockType::Spider},
  {127, UnlockType::Bird},
  {237, UnlockType::Cube},
  {83, UnlockType::Ball},
  //{98, UnlockType::Ship}
};

constexpr std::pair<const int, const UnlockType> PATH_OF_METAL_UNLOCK_ORDER[] = {
  {217, UnlockType::Cube},
  {102, UnlockType::Col1},
  {51, UnlockType::Spider},
  {94, UnlockType::Col2},
  {105, UnlockType::Ball},
  {91, UnlockType::Col2},
  {150, UnlockType::Ship},
  {85, UnlockType::Bird},
  {299, UnlockType::Cube},
  {56, UnlockType::Robot},
  {44, UnlockType::Spider},
  //{359, UnlockType::Cube}
};
constexpr std::pair<const int, const UnlockType> PATH_OF_LIGHT_UNLOCK_ORDER[] = {
  {93, UnlockType::Ball},
  {71, UnlockType::Col2},
  {415, UnlockType::Cube},
  {105, UnlockType::Col1},
  {20, UnlockType::Spider},
  {62, UnlockType::Col2},
  {162, UnlockType::Ship},
  {84, UnlockType::Dart},
  {42, UnlockType::Spider},
  {329, UnlockType::Cube},
  {114, UnlockType::Ship},
  //{66, UnlockType::Robot}
};
constexpr std::pair<const int, const UnlockType> PATH_OF_SOULS_UNLOCK_ORDER[] = {
  {172, UnlockType::Cube},
  {95, UnlockType::Col1},
  {60, UnlockType::Robot},
  {100, UnlockType::Col2},
  {178, UnlockType::Cube},
  {103, UnlockType::Col1},
  {39, UnlockType::Robot},
  {58, UnlockType::Dart},
  {93, UnlockType::Bird},
  {68, UnlockType::Ball},
  {24, UnlockType::Spider},
  //{36, UnlockType::Swing}
};

constexpr std::span<const std::pair<const int, const UnlockType>> PATHS_UNLOCK_ORDER[] = {
  [static_cast<int>(PathType::Fire)] = PATH_OF_FIRE_UNLOCK_ORDER,
  [static_cast<int>(PathType::Ice)] = PATH_OF_ICE_UNLOCK_ORDER,
  [static_cast<int>(PathType::Poison)] = PATH_OF_POISON_UNLOCK_ORDER,
  [static_cast<int>(PathType::Shadow)] = PATH_OF_SHADOW_UNLOCK_ORDER,
  [static_cast<int>(PathType::Lava)] = PATH_OF_LAVA_UNLOCK_ORDER,
  [static_cast<int>(PathType::Earth)] = PATH_OF_EARTH_UNLOCK_ORDER,
  [static_cast<int>(PathType::Blood)] = PATH_OF_BLOOD_UNLOCK_ORDER,
  [static_cast<int>(PathType::Metal)] = PATH_OF_METAL_UNLOCK_ORDER,
  [static_cast<int>(PathType::Light)] = PATH_OF_LIGHT_UNLOCK_ORDER,
  [static_cast<int>(PathType::Souls)] = PATH_OF_SOULS_UNLOCK_ORDER,
};

const float VERTICAL_BORDER_SIZE = 5.f;
const float HORIZONTAL_BORDER_SIZE = 3.25f;
const float TOGGLER_WIDTH_RATIO = 31.f/35.f;
const float TOGGLER_HEIGHT_RATIO = 31.f/34.5f;
