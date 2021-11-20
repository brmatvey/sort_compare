#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "query_factory.h"

namespace draw {

// axis color
inline static const sf::Color axis_color = sf::Color::White;

// curves color
inline static const std::vector<sf::Color> curves_color = {sf::Color::Blue,
                                                           sf::Color::Red,
                                                           sf::Color::Green,
                                                           sf::Color::Yellow,
                                                           sf::Color::Cyan,
                                                           sf::Color::Magenta,
                                                           sf::Color(255,128,0),
                                                           sf::Color(128,128,128)};

// Used to convert engineering scale to pixels
struct Scale {
    double min;
    double max;
};

struct ScaleSettings {
    Scale x_old;
    Scale y_old;
    Scale x_new;
    Scale y_new;

    // round off scale
    // scale must be a multiple of 1, 2, 2.5, 5
    void roundOff();
};

// round off scale
// scale must be a multiple of 1, 2, 2.5, 5
double adjustScale(double value);

// rescale from oldscaleto new scale
int rescale(double in, Scale old_sc, Scale new_sc);

// rescale and convert engineering scale to pixels
sf::Vector2f rescaleToPixels(const ScaleSettings& settings, double x, double y);

// vector - complexity in ms
// settings - drawing settings
// step - step along the abscissa
sf::VertexArray getCurve(const std::vector<double>& vector, const ScaleSettings& settings, int step, sf::Color color);

// draw axis, grid, scales
void axis(sf::RenderWindow& window, ScaleSettings scale_set);

// draw legend
void legend(sf::RenderWindow& window, ScaleSettings scale_set, const std::map<sort::Type, std::vector<double>>& map);

// draw the plot
void plot(const std::map<sort::Type, std::vector<double>>& map, int step);

// Defines the scale of the graph
ScaleSettings findScale(const std::map<sort::Type, std::vector<double>>& map, int step);

// make text
sf::Text makeText(const sf::Font& font, std::string str, sf::Vector2f label_offset);

} // namespace draw
