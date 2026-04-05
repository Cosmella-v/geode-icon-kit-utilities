#include <Geode/Geode.hpp>

#include <hooks/GJGarageLayer.hpp>
#include <popups/PlayerOptionsPopup.hpp>
#include <constants.hpp>

#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

void HookedGJGarageLayer::onModify(auto& self) {
  // these may skip calling the original entirely (holding shift shows the item info popup, regardless of select status),
  // so make sure they don't unintentionally call any hooks if we don't intend to call the original
  Result<> result = self.setHookPriority("GJGarageLayer::onSelect", Priority::First);
  if (!result) log::error("Failed to set hook priority, some mods may not run their functions.");
  result = self.setHookPriority("GJGarageLayer::onToggleItem", Priority::First);
  if (!result) log::error("Failed to set hook priority, some mods may not run their functions.");
}

void HookedGJGarageLayer::showUnlockPopup(int itemID, UnlockType unlockType) {
  if (itemID == -1 && unlockType == UnlockType::Col2) {
    Mod* separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    bool secondPlayerSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    itemID = secondPlayerSelected ? separateDualIcons->getSavedValue("color2", 1) : GameManager::get()->getPlayerColor2();
  }
  bool fixSupporterIconDialogBoxBug = !Mod::get()->getSettingValue<bool>("unfix-supporter-icon-dialog-box-bug");
  bool fixMeltdownSupporterIconDialogBoxBug = !Mod::get()->getSettingValue<bool>("unfix-meltdown-supporter-icon-dialog-box-bug");
  if (unlockType != UnlockType::Cube)
    return GJGarageLayer::showUnlockPopup(itemID, unlockType);
  if ((fixSupporterIconDialogBoxBug && itemID == 13) || (fixMeltdownSupporterIconDialogBoxBug && itemID == 71))
    ItemInfoPopup::create(itemID, UnlockType::Cube)->show();
  else
    GJGarageLayer::showUnlockPopup(itemID, unlockType);
}
  
// shift clicking on icons, for animations
void HookedGJGarageLayer::onToggleItem(CCObject *sender) {
  if (Mod::get()->getSettingValue<bool>("disable-shift-clicking-on-icons")) return GJGarageLayer::onToggleItem(sender);
  CCMenuItemSpriteExtra *item = static_cast<CCMenuItemSpriteExtra *>(sender);
  int itemID = item ? item->getTag() : -1;
  // hold shift when clicking to always open the item info popup, rather than selecting the animation, even if the animation is unlocked
  // unlocking it prevents you from opening the popup at all in vanilla (there is no reason for you to open it anyway but lol)
  if (itemID != -1 && CCDirector::get()->getKeyboardDispatcher()->getShiftKeyPressed())
    showUnlockPopup(itemID, UnlockType::GJItem);
  else GJGarageLayer::onToggleItem(sender);
}
  
void HookedGJGarageLayer::onSelect(CCObject *sender) {
  if (Mod::get()->getSettingValue<bool>("disable-shift-clicking-on-icons")) return GJGarageLayer::onSelect(sender);

  CCMenuItemSpriteExtra *item = static_cast<CCMenuItemSpriteExtra *>(sender);
  int itemID = item ? item->getTag() : -1;

  // hold shift when clicking an icon to always open the icon popup, rather than selecting it, even if the icon is unlocked and unselected
  if (!CCDirector::get()->getKeyboardDispatcher()->getShiftKeyPressed()) return GJGarageLayer::onSelect(sender);
  
  IconInfo* iconInfo = more_icons::getNodeInfo(item);
  if (iconInfo) {
    if (FLAlertLayer* popup = more_icons::createInfoPopup(iconInfo))
      popup->show();
  } else {
    showUnlockPopup(itemID, ICON_TO_UNLOCK[static_cast<int>(item->m_iconType)]);
  }
}
  
void HookedGJGarageLayer::onPlayerOptions(CCObject *) {
  PlayerOptionsPopup::create()->show();
}
  
void HookedGJGarageLayer::createPlayerOptionsButton() {
  CCNode* backMenu = getChildByID("back-menu");
  if (!backMenu) return;
  CCMenuItemSpriteExtra* playerOptionsButton = CCMenuItemSpriteExtra::create(
    CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png"),
    this,
    menu_selector(HookedGJGarageLayer::onPlayerOptions)
  );
  playerOptionsButton->setID("player-options-button"_spr);
  backMenu->addChild(playerOptionsButton);
  backMenu->updateLayout();
}

bool HookedGJGarageLayer::init() {
  if (!GJGarageLayer::init()) return false;
  if (!Mod::get()->getSettingValue<bool>("hide-player-options-button")) createPlayerOptionsButton();
  return true;
}
