#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>

struct HookedFLAlertLayer : geode::Modify<HookedFLAlertLayer, FLAlertLayer> {

  struct Fields {
    // if these are not nullopt, then we are either an ItemInfoPopup or a More Icons MoreInfoPopup
    std::optional<UnlockType> unlockType;
    std::optional<int> itemID;
    std::optional<std::string> itemIDMI;

    // this is for More Icons texture cache management
    std::optional<int> requestID;
    ~Fields();
  };

  void addItemInfoPopupArrows(bool);
  void onPrevNext(CCObject*);

};
