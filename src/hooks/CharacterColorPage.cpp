#include <hooks/CharacterColorPage.hpp>

using namespace geode::prelude;

void HookedCharacterColorPage::onModify(auto& self) {
	// this may skip calling the original entirely (holding shift shows the item info popup, regardless of select status),
	// so make sure they don't unintentionally call any hooks if we don't intend to call the original
	Result<> result = self.setHookPriority("CharacterColorPage::onPlayerColor", Priority::First);
	if (!result) log::error("Failed to set hook priority, some mods may not run their functions.");
}

void HookedCharacterColorPage::onPlayerColor(CCObject *sender) {
	if (Mod::get()->getSettingValue<bool>("disable-shift-clicking-on-icons")) return CharacterColorPage::onPlayerColor(sender);

	CCMenuItemSpriteExtra *item = static_cast<CCMenuItemSpriteExtra *>(sender);
	int itemID = item ? item->getTag() : -1;

	// hold shift when clicking an icon to always open the icon popup, rather than selecting it, even if the icon is unlocked and unselected
	if (!CCDirector::get()->getKeyboardDispatcher()->getShiftKeyPressed()) return CharacterColorPage::onPlayerColor(sender);

	m_delegate->showUnlockPopup(itemID, m_colorMode == 0 ? UnlockType::Col1 : UnlockType::Col2);
}

void HookedCharacterColorPage::createColorMenu() {

	CharacterColorPage::createColorMenu();
	CCNode* white = m_buttonMenu->getChildByTag(12);
	if (!white) return;
	CCNode* whiteSprite = white->getChildByIndex(0);
	if (!whiteSprite) return;

	ColorChannelSprite* player2GlowSprite = ColorChannelSprite::create();
	player2GlowSprite->setColor(GameManager::get()->colorForIdx(activeColorForMode(1)));
	player2GlowSprite->setScale(0.65f);
	player2GlowSprite->setPosition(whiteSprite->getPosition());
	CCLabelBMFont* col2Text = CCLabelBMFont::create("Col2", "bigFont.fnt");
	col2Text->setScale(0.3f);
	col2Text->setPosition(player2GlowSprite->getContentSize()/2);
	player2GlowSprite->addChild(col2Text);

	CCMenuItemSpriteExtra* player2GlowButton = CCMenuItemSpriteExtra::create(player2GlowSprite, this, menu_selector(CharacterColorPage::onPlayerColor));

	player2GlowButton->setTag(-1);
	player2GlowButton->setID("-1");
	player2GlowButton->setPosition({white->getPositionX() - 24.f, white->getPositionY()});
	m_buttonMenu->addChild(player2GlowButton);
	player2GlowButton->setVisible(false);
	player2GlowButton->setEnabled(false);
	m_fields->player2GlowButton = player2GlowButton;

	// maybe this should be done after init, but the cursors already seem to exist here
	// i assume this function gets called during init, but the cursors got initialized before it got called
	// so this should be fine
	CCNode* glowCursor = static_cast<CCNode*>(m_cursors->objectAtIndex(2));
	glowCursor->setPosition(m_buttonMenu->convertToWorldSpace(m_fields->player2GlowButton->getPosition()));
}

void HookedCharacterColorPage::onMode(CCObject* sender) {
	CharacterColorPage::onMode(sender);

	if (!m_fields->player2GlowButton || m_fields->player2GlowButton->getChildrenCount() < 1) return;

	if (m_colorMode == 2) {
		Mod* separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
		bool secondPlayerSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);

		int activeColor2 = secondPlayerSelected ? separateDualIcons->getSavedValue("color2", 1) : activeColorForMode(1);
		m_fields->player2GlowButton->getChildByIndex<ColorChannelSprite*>(0)->setColor(GameManager::get()->colorForIdx(activeColor2));
		if (!Mod::get()->getSettingValue<bool>("hide-glow-col2-button")) {
			m_fields->player2GlowButton->setVisible(true);
			m_fields->player2GlowButton->setEnabled(true);
		}

		int activeGlowColor = secondPlayerSelected ? separateDualIcons->getSavedValue("colorglow", 1) : activeColorForMode(2);
		if (activeGlowColor == -1) {
			CCNode* glowCursor = static_cast<CCNode*>(m_cursors->objectAtIndex(2));
			glowCursor->setPosition(m_buttonMenu->convertToWorldSpace(m_fields->player2GlowButton->getPosition()));
		}
	} else {
		m_fields->player2GlowButton->setVisible(false);
		m_fields->player2GlowButton->setEnabled(false);
	}
}
