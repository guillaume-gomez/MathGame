/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "StaticButton.hpp"
#include "ConstrueFunction.hpp"
#include "Enemy.hpp"
#include "GraphView.hpp"
#include "GravityCircle.hpp"
#include "InfoDisplayer.hpp"
#include "ManageText.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "PanelEditor.hpp"
#include "Curves.hpp"
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
        void deletePoint(int x , int y);
        void cameraMoved();
        ~Editor();

    private:
        Axis m_axis;
        TextAreaSFML2_0 m_textAreaFunction;
        GraphView m_graphView;
        StaticButton m_buttonReset;
        StaticButton m_buttonSave;
        StaticButton m_buttonBack;
        StaticButton m_buttonCursor;
        StaticButton m_buttonGoalButton;
        StaticButton m_buttonCircle;
        StaticButton m_buttonNormalButton;
        StaticButton m_buttonLeftEnemy;
        StaticButton m_buttonPanel;
        StaticButton m_buttonInfo;
        StaticButton m_buttonAddFunction;
        sf::Texture m_Buttonpoint;
        sf::Texture m_Buttongoal;
        TypeObject m_creatingType;
        sf::Event m_event;
        ConstrueFunction m_graphModel;
        bool m_isBack;
        bool m_isNormalPoint;
        bool m_isZoom;
        PanelEditor m_panel;
        bool m_saving;
        bool m_isLeftEnemy;
        sf::Sprite m_spriteBG;
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
