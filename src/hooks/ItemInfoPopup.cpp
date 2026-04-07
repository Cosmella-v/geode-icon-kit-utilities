#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/modify/CCLayerColor.hpp>

#include <algorithm>
#include <numeric>

#include <constants.hpp>

#include <hooks/ItemInfoPopup.hpp>
#include <nytelyte.icon_kit_filter_and_sort/include/api/api.hpp>
namespace ikfs = nytelyte::icon_kit_filter_and_sort;

using namespace geode::prelude;

CCLabelBMFont* HookedItemInfoPopup::addAchievementLabel(const char* label) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelBMFont* achievementLabel = CCLabelBMFont::create(label, "goldFont.fnt");
	achievementLabel->setScale(0.55f);
	achievementLabel->setID("achievement-label");
	achievementLabel->setPosition({winSize.width/2, winSize.height/2 + 8.f});
	m_mainLayer->addChild(achievementLabel);
	return achievementLabel;
}

TextArea* HookedItemInfoPopup::addDescriptionArea(const char* description) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	TextArea* textArea = TextArea::create(description, "bigFont.fnt", 1.0f, 600.f, {0.5f, 1.f}, 42.f, false);
	textArea->setAnchorPoint({0.5f, 0.5f});
	textArea->setScale(0.4f);
	textArea->setID("description-area");
	textArea->setPosition({winSize.width/2, winSize.height/2 - 19.f});
	m_mainLayer->addChild(textArea);
	return textArea;
}

CCLabelBMFont* HookedItemInfoPopup::addRandomLabel(const char* label) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelBMFont* randomLabel = CCLabelBMFont::create(label, "chatFont.fnt");
	randomLabel->setScale(0.6f);
	randomLabel->setID("random-label");
	randomLabel->setColor({0, 0, 0});
	randomLabel->setOpacity(75);
	randomLabel->setPosition({winSize.width/2, winSize.height/2 - 57.f});
	m_mainLayer->addChild(randomLabel);
	return randomLabel;
}

const char* HookedItemInfoPopup::pickRandomLabel() {
	const char* randomTextArray[] = {
		"IMPOSSIBRU!",
		"ehehehehehe...",
		"A wild lock appeared!",
		"Prove that you are worthy.",
		"Need. More. Power.",
		"That wont work.",
		"You must do something.",
		"It cannot be done.",
		"You are not ready.",
		"Player used tap.\nIt's not very effective."
	};
	return randomTextArray[
		geode::utils::random::generate(0, sizeof(randomTextArray)/sizeof(const char*))
	];
}

const char* HookedItemInfoPopup::pickRandomAchievementLabel() {
	const char* randomTextArray[] = {
		"Not yet",
		"Not now",
		"Almost there",
		"Soon...",
		"Stay tuned!",
		"Wait for it",
		"Coming soon!",
		"It's cooking",
		"In the oven",
		"Unavailable",
		"Huh?"
	};
	return randomTextArray[
		geode::utils::random::generate(0, sizeof(randomTextArray)/sizeof(const char*))
	];
}

bool HookedItemInfoPopup::init(int icon, UnlockType unlockType) {

	if (!ItemInfoPopup::init(icon, unlockType)) return false;

	if (!Mod::get()->getSettingValue<bool>("disable-item-info-popup-animation-name-changes"))
		if (unlockType == UnlockType::GJItem && m_itemID >= 18 && m_itemID <= 20) {
			CCLabelBMFont *title = m_mainLayer->getChildByType<CCLabelBMFont>(0);
			TextArea* description = m_mainLayer->getChildByType<TextArea>(0);
			title->setString(fmt::format("Animation {}", m_itemID - 17).c_str());
			description->setString("You can <cl>buy</c> this <cg>Animation</c> at the <cp>Mechanic</c>!");
		}

	if (!Mod::get()->getSettingValue<bool>("disable-item-info-popup-wraith-icon-fixes")) {
		if (
			((icon == 321 || icon == 351 || icon == 370) && unlockType == UnlockType::Cube) ||
			((icon == 71  || icon ==  57) && unlockType == UnlockType::Bird)
		) {

			CCLabelBMFont* achievementLabel = static_cast<CCLabelBMFont*>(
				m_mainLayer->getChildByID("achievement-label")
			);

			TextArea* descriptionArea = static_cast<TextArea*>(
				m_mainLayer->getChildByID("description-area")
			);

			CCLabelBMFont* randomLabel = static_cast<CCLabelBMFont*>(
				m_mainLayer->getChildByID("random-label")
			);

			if (achievementLabel)
				achievementLabel->setString("Special Chest");
			else
				addAchievementLabel("Special Chest");

			if (descriptionArea) {
				descriptionArea->setString(
					unlockType == UnlockType::Cube ?
						"You can <cl>find</c> this <cg>Cube</c> in a special <cy>chest</c>!" :
						"You can <cl>find</c> this <cg>UFO</c> in a special <cy>chest</c>!"
				);
				descriptionArea->setPositionY(descriptionArea->getPositionY() + 5.f);
			} else
				addDescriptionArea(
					unlockType == UnlockType::Cube ?
					"You can <cl>find</c> this <cg>Cube</c> in a special <cy>chest</c>!" :
					"You can <cl>find</c> this <cg>UFO</c> in a special <cy>chest</c>!"
				);

			if (!randomLabel) addRandomLabel(pickRandomLabel());
		}
	}

	if (!Mod::get()->getSettingValue<bool>("disable-item-info-popup-221-icon-fixes")) {
		CCLabelBMFont* achievementLabel = static_cast<CCLabelBMFont*>(
			m_mainLayer->getChildByID("achievement-label")
		);

		TextArea* descriptionArea = static_cast<TextArea*>(
			m_mainLayer->getChildByID("description-area")
		);
		if (!achievementLabel && !descriptionArea) {
			addAchievementLabel(pickRandomAchievementLabel());
			const char* description = nullptr;
			switch(unlockType) {
				case UnlockType::Cube: description = "This <cg>Cube</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Ship: description = "This <cg>Ship</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Bird: description = "This <cg>UFO</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Ball: description = "This <cg>Ball</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Dart: description = "This <cg>Wave</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Robot: description = "This <cg>Robot</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Spider: description = "This <cg>Spider</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Swing: description = "This <cg>Swing</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				case UnlockType::Jetpack: description = "This <cg>Jetpack</c> can be <cl>unlocked</c> in update <cy>2.21</c>."; break;
				default: description = "This should be unreachable. If you see this text, report a bug to Icon Kit Utilities by NyteLyte.";
			}
			descriptionArea = addDescriptionArea(description);
			descriptionArea->setPositionY(descriptionArea->getPositionY() - 5.f);
		}
	}

	return true;

}
