#ifndef EDITOR_H
#define EDITOR_H

#include "SFML/Graphics.hpp"
using namespace sf;
#include "Axis.hpp"
#include "ConstrueFunction.hpp"
#include "GraphView.hpp"
#include "ManageText.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "ButtonPerso.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"

#include <fstream>
#include <sstream>



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
        View m_viewPerso;
        Event m_event;
        Axis m_axis;
        ConstrueFonction m_graphModel;
        GraphView   m_graphView;
        TextAreaSFML2_0 m_textAreaFunction;
        ButtonPerso m_buttonReset;
        ButtonPerso m_buttonSave;
        ButtonPerso m_buttonBack;
        ButtonPerso m_buttonCursor;
        ButtonPerso m_buttonGoalButton;
        ButtonPerso m_buttonNormalButton;
        ButtonPerso m_buttonPanel;
        std::vector<sf::Sprite> m_spriteList;
        sf::Texture m_Buttonpoint;
        sf::Texture m_Buttongoal;
        ManageText m_textVerifSave;
        bool m_isBack;
        bool m_isAnimLeft;
        bool m_isAnimRight;
        bool m_isZoom;
        bool m_chooseTexture;
        bool m_drawable;
        bool m_saving;
        sf::Clock m_timer;
        sf::Clock m_timerPanel;

        Sprite m_spriteBG;

};

#endif // EDITOR_H
