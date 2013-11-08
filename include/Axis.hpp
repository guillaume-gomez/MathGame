#ifndef AXIS_HPP
#define AXIS_HPP

class Axis
{
    public:
        Axis(float graduation = 5.0f);
        virtual ~Axis();
        int getxAxis();
        int getyAxis();
        float getScale();
        void setGraduation( float _graduation);
        float getGraducation();

        void draw(sf::RenderWindow& App);

    private:
        int m_OriginyAxis;
        int m_OriginxAxis;
        float m_scale;
        float m_graduation;
        sf::VertexArray m_list_Axis;
        sf::RectangleShape m_ShapexAxis;
        sf::RectangleShape m_ShapeyAxis;
        std::vector<sf::RectangleShape> m_listXGrad;
        std::vector<sf::RectangleShape> m_listYGrad;


};

#endif // AXIS_HPP
