#include <Geode/Geode.hpp>
#include <algorithm>

#include <constants.hpp>
#include <popups/PlayerOptionsPopup.hpp>
#include <utils/LinkedCCMenu.hpp>
#include <utils/CCMenuItemTogglerSpoof.hpp>

using namespace geode::prelude;

void PlayerOptionsPopup::toggleOption(CCObject *sender) {
	CCMenuItemToggler *toggler = static_cast<CCMenuItemToggler *>(sender);
	std::string gameVariableStr = fmt::format("{:04}", toggler->getTag());
	GameManager::get()->setGameVariable(gameVariableStr.c_str(), !toggler->isToggled());
}

void PlayerOptionsPopup::addOption(const char* name, int option) {

	CCMenuItemToggler *toggler = createTogglerWithStandardSpritesSpoofOn(this, menu_selector(PlayerOptionsPopup::toggleOption));
	toggler->setTag(option);
	toggler->setScale(0.8f);
	toggler->setLayoutOptions(AxisLayoutOptions::create()->setAutoScale(false));

	CCLabelBMFont* label = CCLabelBMFont::create(name, "bigFont.fnt");
	float maxScale = 0.375f;
	if (label->getContentSize().width * maxScale > (m_size.width - 2*HORIZONTAL_BORDER_SIZE - 40 - toggler->getContentSize().width/0.8f)) {
		maxScale = (m_size.width - 2*HORIZONTAL_BORDER_SIZE - 40 - toggler->getContentSize().width/0.8f) / label->getContentSize().width;
	}
	label->setLayoutOptions(AxisLayoutOptions::create()->setBreakLine(true)->setSameLine(true)->setScaleLimits({}, maxScale));

	std::string gameVariableStr = fmt::format("{:04}", option);
	toggler->toggle(GameManager::get()->getGameVariable(gameVariableStr.c_str()));

	m_buttonMenu->addChild(toggler);
	m_buttonMenu->addChild(label);
}

void PlayerOptionsPopup::addOptionInfo(int tag, const char* description) {
	InfoAlertButton *infoButton = InfoAlertButton::create("Info", description, 0.5f);
	CCMenuItemToggler *button = static_cast<CCMenuItemToggler *>(m_buttonMenu->getChildByTag(tag));
	auto [x, y] = button->getScaledContentSize() / 2;
	auto [bx, by] = infoButton->getContentSize() / 2;
	infoButton->setPosition(button->getPosition() - CCPoint{x, -y} - CCPoint{bx, -by});
	m_buttonMenu->addChild(infoButton);
}

bool PlayerOptionsPopup::init() {
	if (!Popup::init(260.f, 210.f)) return false;

	this->setTitle("Player Options");

	float titleMargin = m_bgSprite->boundingBox().getMaxY() - m_title->boundingBox().getMaxY() - VERTICAL_BORDER_SIZE;
	float titleHeight = m_title->getScale()*m_title->getContentSize().height;
	float realTitleHeight = 2*titleMargin + titleHeight;
	float separatorHeight = 1;

	CCLayerColor* separator = CCLayerColor::create({ 0, 0, 0, 50 }, m_size.width - 2*HORIZONTAL_BORDER_SIZE, separatorHeight);
	separator->setPosition(HORIZONTAL_BORDER_SIZE, m_title->boundingBox().getMinY() - titleMargin);

	m_buttonMenu = CCMenu::create();
	m_buttonMenu->setLayout(RowLayout::create()->setAxisAlignment(AxisAlignment::Start)->setGrowCrossAxis(true)->setAutoScale(true)->setGap(10.f));
	m_buttonMenu->setContentSize({m_size.width - 2*HORIZONTAL_BORDER_SIZE - 40, 0});

	m_buttonMenu->setPosition(m_size/2 - CCPoint{0, realTitleHeight/2});

	addOption("Default Mini Icon", 60);
	addOption("Switch Spider Teleport Color", 61);
	addOption("Switch Dash Fire Color", 62);
	addOption("Switch Wave Trail Color", 96);

	m_buttonMenu->updateLayout();
	m_buttonMenu->setLayout(nullptr);
	float topTogglerMax = m_buttonMenu->getChildByIndex<InfoAlertButton*>(0)->boundingBox().getMaxY();

	addOptionInfo(60, "Sets player icon in mini mode to default.");
	float topInfoButtonMax = m_buttonMenu->getChildByIndex<InfoAlertButton*>(-1)->boundingBox().getMaxY();
	addOptionInfo(61, "Toggles between main and secondary color for the\nteleport effect in spider mode.");
	addOptionInfo(62, "Toggles between main and secondary color for the\nfire effect from dash orbs.");
	addOptionInfo(96, "Toggles between main and secondary color for the\ntrail in wave mode.");

	m_buttonMenu->setPositionY(m_buttonMenu->getPositionY() - (topInfoButtonMax - topTogglerMax)/2);

	m_mainLayer->addChild(m_buttonMenu);
	m_mainLayer->addChild(separator);

	m_mainLayer->addChild(LinkedCCMenu::createLinked(m_mainLayer));

	return true;
}

PlayerOptionsPopup* PlayerOptionsPopup::create() {
	auto ret = new PlayerOptionsPopup();
	if (ret && ret->init()) { ret->autorelease(); return ret; }
	delete ret; return nullptr;
}
