#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "ButtonPerso.hpp"
#include "ConstrueFunction.hpp"
#include "Enemy.hpp"
#include "GraphView.hpp"
#include "GravityCircle.hpp"
#include "ManageText.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "PanelEditor.hpp"
#include "Point.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


class Editor
{
    public:
        sf::RenderWindow &m_app;
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
        void resize(float scaleX, float scaleY);
        int save(ScreenLink * link);
        void addObject( int x , int y);
        void addCircle(int x, int y);
        void popPoint();
        void deleteGravityCircle(int x, int y);
        void deletePoint(int x , int y);
        ~Editor();

    private:
        Axis m_axis;
        ButtonPerso m_buttonReset;
        ButtonPerso m_buttonSave;
        ButtonPerso m_buttonBack;
        ButtonPerso m_buttonCursor;
        ButtonPerso m_buttonGoalButton;
        ButtonPerso m_buttonCircle;
        ButtonPerso m_buttonNormalButton;
        ButtonPerso m_buttonLeftEnemy;
        ButtonPerso m_buttonPanel;
        sf::Texture m_Buttonpoint;
        sf::Texture m_Buttongoal;
        TypeObject m_creatingType;
        sf::Event m_event;
        ConstrueFunction m_graphModel;
        GraphView   m_graphView;
        bool m_isBack;
        bool m_isNormalPoint;
        bool m_isZoom;
        PanelEditor m_panel;
        bool m_saving;
        bool m_isLeftEnemy;
        sf::Sprite m_spriteBG;
        TextAreaSFML2_0 m_textAreaFunction;
        ManageText m_nbAttemptView;

        unsigned int m_nbAttempt;

        // HAVE TO IMPROVE IT
        sf::Vector2f m_radiusBuilder;
        sf:: View m_viewPerso;

        std::vector<EditorObject*> m_spriteList;
        sf::Clock m_timer;
        sf::Clock m_timerPanel;

        ManageText m_textVerifSave;

};
#endif // EDITOR_H
