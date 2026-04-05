#include <hooks/FLAlertLayer.hpp>
#include <nytelyte.icon_kit_filter_and_sort/include/api/api.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <constants.hpp>
#include <numeric>
namespace ikfs = nytelyte::icon_kit_filter_and_sort;

using namespace geode::prelude;

enum ItemInfoPopupButtonAction { Previous, Next };

HookedFLAlertLayer::Fields::~Fields() {
	if (requestID)
		more_icons::unloadIcons(requestID.value());
}

void HookedFLAlertLayer::addItemInfoPopupArrows(bool isGeodePopup) {
	FLAlertLayer* to = static_cast<FLAlertLayer*>(this);
	CCNode* background = to->m_mainLayer->getChildByID("background");
	if (!background) return;

	CCSprite *prevSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	CCSprite *nextSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	nextSprite->setFlipX(true);

	CCMenuItemSpriteExtra *prev = CCMenuItemSpriteExtra::create(
		prevSprite, to, menu_selector(HookedFLAlertLayer::onPrevNext)
	);
	CCMenuItemSpriteExtra *next = CCMenuItemSpriteExtra::create(
		nextSprite, to, menu_selector(HookedFLAlertLayer::onPrevNext)
	);
	prev->setTag(ItemInfoPopupButtonAction::Previous);
	next->setTag(ItemInfoPopupButtonAction::Next);

	CCSize size = background->getContentSize();
	float bottomBG = background->boundingBox().getMinY();
	float bottomMenu = to->m_buttonMenu->boundingBox().getMinY();
	float pad = 25.f;
	if (isGeodePopup) {
		prev->setPosition({-pad, size.height/2 - (bottomMenu - bottomBG)});
		next->setPosition({size.width + pad, size.height/2 - (bottomMenu - bottomBG)});
	} else {
		prev->setPosition({-size.width/2 - pad, size.height/2 - (bottomMenu - bottomBG)});
		next->setPosition({size.width/2 + pad, size.height/2 - (bottomMenu - bottomBG)});
	}

	to->m_buttonMenu->addChild(prev);
	to->m_buttonMenu->addChild(next);
}

void HookedFLAlertLayer::onPrevNext(CCObject *sender) {
	CCMenuItemSpriteExtra* button = static_cast<CCMenuItemSpriteExtra*>(sender);
	ItemInfoPopupButtonAction action = static_cast<ItemInfoPopupButtonAction>(button->getTag());

	CCScene* scene = CCScene::get();
	GJGarageLayer *garage = scene->getChildByType<GJGarageLayer>(-1);
	GJPathPage *pathPage = scene->getChildByType<GJPathPage>(-1);
	ShardsPage *shardsPage = scene->getChildByType<ShardsPage>(-1);

	if (!garage && !pathPage && !shardsPage) return;

	GJPathSprite *pathSprite = nullptr;
	if (pathPage)
		pathSprite = pathPage->m_mainLayer->getChildByType<GJPathSprite>(-1);

	UnlockType unlockType = *m_fields->unlockType;
	ikfs::Icon itemID = m_fields->itemID ? ikfs::Icon{*m_fields->itemID} : ikfs::Icon{*m_fields->itemIDMI};

	// this is rebuilt on each new popup; we don't keep track of any state
	// it shouldn't be too much of a problem, there are like 500 or so vanilla icons
	// and i doubt that MI users--once i add MI support--are going to have thousands
	// of icons for an optimization that keeps track of state to become necessary
	// i may add it if it does but, for now, this entire thing is O(n),
	// where n is the number of icons
	std::vector<std::pair<const ikfs::Icon, const UnlockType>> finalIcons;

	if (pathSprite)
		for (const std::pair<const int, const UnlockType>& icon : PATHS_UNLOCK_ORDER[pathSprite->m_pathNumber])
			finalIcons.emplace_back(ikfs::Icon{icon.first}, icon.second);
	else if (shardsPage)
		for (const std::pair<const int, const UnlockType>& icon : SHARDS_OF_POWER_UNLOCK_ORDER)
			finalIcons.emplace_back(ikfs::Icon{icon.first}, icon.second);
	else if (!IS_NORMAL_UNLOCK_TYPE(unlockType)) {
		// Vanilla
		for (const int& icon : SPECIAL_UNLOCK_ORDER[static_cast<int>(unlockType)])
			finalIcons.emplace_back(ikfs::Icon{icon}, unlockType);
		// More Icons
		if (std::vector<IconInfo>* result = more_icons::getIcons(GameManager::get()->unlockTypeToIconType(int(unlockType))))
			for (const IconInfo& iconInfo : *result)
				finalIcons.emplace_back(ikfs::Icon{iconInfo.getName()}, unlockType);
	}
	else {
		// Get order from Icon Kit Filter & Sort, if it doesn't exist, it's the vanilla order, and then More Icons icons in their standard order
		for (
			ikfs::Icon orderedIconID : (
				ikfs::getAllIconsInOrder(unlockType).unwrapOrElse([unlockType](){
					IconType iconType = GameManager::get()->unlockTypeToIconType(int(unlockType));
					int count = GameManager::get()->countForType(iconType);
					std::vector<ikfs::Icon> order;
					// Vanilla
					for (int i = 1; i < count; i++)
						order.emplace_back(i);
					// More Icons
					if (std::vector<IconInfo>* result = more_icons::getIcons(iconType))
						for (const IconInfo& iconInfo : *result)
							order.emplace_back(iconInfo.getName());
					return order;
				})
			)
		)
			finalIcons.push_back({orderedIconID, unlockType});
	}

	std::pair<ikfs::Icon, UnlockType> newItem{{0}, static_cast<UnlockType>(0)};
	std::vector<std::pair<const ikfs::Icon, const UnlockType>>::iterator p_first = finalIcons.begin();
	std::vector<std::pair<const ikfs::Icon, const UnlockType>>::iterator p_last = finalIcons.end() - 1;
	std::vector<std::pair<const ikfs::Icon, const UnlockType>>::iterator p_current = std::find(p_first, p_last + 1, std::pair<ikfs::Icon, UnlockType>{itemID, unlockType});
	if (p_current == p_last + 1) return;
	if (action == ItemInfoPopupButtonAction::Next) {
		if (p_current != p_last) newItem = *(p_current+1);
		if (p_current == p_last) newItem = *p_first;
	} else {
		if (p_current != p_first) newItem = *(p_current-1);
		if (p_current == p_first) newItem = *p_last;
	}

	removeFromParent();
	FLAlertLayer* popup = nullptr;
	if (newItem.first.isVanillaIcon()) {
		popup = ItemInfoPopup::create(*newItem.first.getVanillaIcon(), newItem.second);
	} else {
		int requestID = GameManager::get()->getIconRequestID();
		IconInfo* info = more_icons::getIcon(*newItem.first.getMoreIconsIcon(), GameManager::get()->unlockTypeToIconType(int(newItem.second)));
		// MI doesn't load the icons when a popup is opened, it just relies on them already being loaded by the icon kit, when you are on the correct page
		// since the arrows allow you to open a popup of an icon that isn't actually on the current page, we need to load it into the texture cache manually
		// the fields destructor of HookedFLAlertLayer then unloads it, so that we don't accidentally keep it in the cache forever
		more_icons::loadIcon(info, requestID);
		popup = more_icons::createInfoPopup(info);
		static_cast<HookedFLAlertLayer*>(popup)->m_fields->requestID = requestID;
	}
	popup->m_noElasticity = true;
	popup->show();
}
