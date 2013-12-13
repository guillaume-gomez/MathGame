#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "ButtonPerso.hpp"
#include "ConstrueFunction.hpp"
#include "GraphView.hpp"
#include "ManageText.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


using namespace sf;


class Editor
{
    public:
        RenderWindow &m_app;
        Editor(sf::RenderWindow& App);
        bool handleInput();
        void draw();
        void zoom();
        void show();
        void reset();
        void resetWindow();
        void move( );
        inline bool isBacked()const { return m_isBack;};
        inline void setBack( bool _b){ m_isBack = _b;};
        inline void setSaving(bool _b){m_saving = _b;};
        void setCenterCamera();
        void managePanel(  int coordMouseX);
        void movePanel ();
        int save(ScreenLink * link);
        void addPoint( int x , int y);
        void popPoint();
        void deletePoint(int x , int y);
        ~Editor();

    private:
        Axis m_axis;
        GraphView m_graphView;
        TextAreaSFML2_0 m_textAreaFunction;
        ButtonPerso m_buttonReset;
        ButtonPerso m_buttonSave;
        ButtonPerso m_buttonBack;
        ButtonPerso m_buttonCursor;
        ButtonPerso m_buttonGoalButton;
        ButtonPerso m_buttonNormalButton;
        ButtonPerso m_buttonPanel;
        bool m_isBack;
        bool m_isAnimLeft;
        bool m_isAnimRight;
        bool m_isZoom;
        bool m_chooseTexture;
        bool m_drawable;
        bool m_saving;

        Sprite m_spriteBG;
        sf::Texture m_Buttonpoint;
        sf::Texture m_Buttongoal;

        View m_viewPerso;
        Event m_event;
        ConstrueFunction m_graphModel;
        std::vector<sf::Sprite> m_spriteList;
        sf::Clock m_timer;
        sf::Clock m_timerPanel;
        ManageText m_textVerifSave;
};
#endif // EDITOR_H
