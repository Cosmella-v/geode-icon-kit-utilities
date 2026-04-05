#include <hooks/CCLayerColor.hpp>
#include <hooks/FLAlertLayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

class MoreInfoPopup : public CCObject {};

bool HookedCCLayerColor::initWithColor(ccColor4B const& color, GLfloat width, GLfloat height) {
	if (!CCLayerColor::initWithColor(color, width, height)) return false;

	if (typeinfo_cast<ItemInfoPopup*>(this)) queueInMainThread([thisWeakRef = WeakRef(this)]{
		if (!thisWeakRef.valid()) return;
		Ref<HookedCCLayerColor> thisRef = thisWeakRef.lock();
		if (Mod::get()->getSettingValue<bool>("disable-item-info-popup-arrows")) return;
		CCScene* scene = CCScene::get();
		GJGarageLayer* garage = scene->getChildByType<GJGarageLayer>(-1);
		GJPathPage* pathPage = scene->getChildByType<GJPathPage>(-1);
		ShardsPage* shardsPage = scene->getChildByType<ShardsPage>(-1);
		// the only 3 things we support thus far for arrows:
		// - garage icons, including colors and special items
		// - shards of power unlocks
		// - path unlocks
		if (!garage && !pathPage && !shardsPage) return;

		// TODO: replace the line below with another modify_cast, if my improvement to modify_cast gets merged
		ItemInfoPopup* self = static_cast<ItemInfoPopup*>(static_cast<CCLayerColor*>(thisRef.data()));
		HookedFLAlertLayer* hookedSelf = modify_cast<HookedFLAlertLayer*>(self);

		hookedSelf->addItemInfoPopupArrows(false);
		hookedSelf->m_fields->unlockType = self->m_unlockType;
		hookedSelf->m_fields->itemID = self->m_itemID;
	});
	else queueInMainThread([thisWeakRef = WeakRef(this)]{
		if (!thisWeakRef.valid()) return;
		Ref<HookedCCLayerColor> thisRef = thisWeakRef.lock();

		if (thisRef.data()->getID() != "MoreInfoPopup") return;
		if (Mod::get()->getSettingValue<bool>("disable-item-info-popup-arrows")) return;

		HookedFLAlertLayer* self = modify_cast<HookedFLAlertLayer*>(static_cast<CCLayerColor*>(thisRef.data()));
		CCMenuItemSpriteExtra* iconButton = static_cast<CCMenuItemSpriteExtra*>(self->m_buttonMenu->getChildByID("icon-button"));

		if(IconInfo* info = more_icons::getNodeInfo(iconButton)) {
			self->addItemInfoPopupArrows(true);
			self->m_fields->unlockType = GameManager::get()->iconTypeToUnlockType(info->getType());
			self->m_fields->itemIDMI = info->getName();
		}
	});

	return true;
}

