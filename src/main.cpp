#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

struct HookMenuLayer : Modify<HookMenuLayer, MenuLayer> {
	struct Fields {
		bool m_isHidden = false;
		CCMenuItemToggler* m_eyeButton;
		CCMenu* m_eyeMenu;
	};

	bool init() {
		if(!MenuLayer::init())
			return false;
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto on = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("eye_open.png"_spr), CircleBaseColor::Green, CircleBaseSize::Small);
		auto offEye = CCSprite::createWithSpriteFrameName("eye_closed.png"_spr);
		offEye->setOpacity(255 / 2.5);
		
		auto off = CircleButtonSprite::create(offEye, CircleBaseColor::Gray, CircleBaseSize::Small);
		off->setOpacity(255 / 2.5);

		m_fields->m_eyeButton = CCMenuItemToggler::create(on, off, this, menu_selector(HookMenuLayer::onToggleHide));
		m_fields->m_eyeMenu = CCMenu::create();

		m_fields->m_eyeMenu->setPosition({winSize.width - 25, winSize.height - 25});
		m_fields->m_eyeMenu->setID("hide-ui-menu"_spr);

		m_fields->m_eyeMenu->addChild(m_fields->m_eyeButton);
		addChild(m_fields->m_eyeMenu);
		return true;
	}	

	void onToggleHide(CCObject* sender) {
		m_fields->m_isHidden = !m_fields->m_isHidden;
		HookMenuLayer::updateMenu();
	}

	void updateMenu() {
		if(m_fields->m_isHidden) {
			for(int i = 0; i < this->getChildrenCount(); i++) {
				auto node = static_cast<CCNode*>(this->getChildren()->objectAtIndex(i));
				
				if(node->getID() != "main-menu-bg" && node->getID() != "hide-ui-menu"_spr)
					node->setVisible(false);
			}
		} else {
			for(int i = 0; i < this->getChildrenCount(); i++) {
				auto node = static_cast<CCNode*>(this->getChildren()->objectAtIndex(i));
				node->setVisible(true);
			}
		}
	}
};
