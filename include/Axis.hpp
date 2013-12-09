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
        int m_originyAxis;
        int m_originxAxis;
        sf::VertexArray m_listAxis;
        std::vector<sf::RectangleShape> m_listXGrad;
        std::vector<sf::RectangleShape> m_listYGrad;
        float m_scale;
        float m_graduation;
        sf::RectangleShape m_shapexAxis;
        sf::RectangleShape m_shapeyAxis;

};

#endif // AXIS_HPP
