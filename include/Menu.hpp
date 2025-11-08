#pragma once  
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <string>

class Menu {
public:
    struct MenuItem {
        MenuItem(const std::string& t, std::function<void()> a) : text(t), action(a) {}
        std::string text;
        std::function<void()> action;
    };
    Menu(const std::string& title, int titleCharSize = 72, int itemCharSize = 42);
    void addMenuItem(const std::string& text, std::function<void()> action);
    void moveUp();
    void moveDown();
    void executeSelectedAction();
    void draw(sf::RenderWindow& window);
private:
    sf::Font m_font;
    sf::Text m_titleText;
    std::vector<sf::Text> m_displayTexts;
    std::vector<MenuItem> m_menuItems;
    int m_selectedIdx;
    
    int m_windowSizeX;
    int m_windowSizeY;
    int m_titleCharSize;
    int m_itemCharSize;
    
    void updateHighlighted(int newIdx, int oldIdx);
    void centerOrigin(sf::Text& text);
};