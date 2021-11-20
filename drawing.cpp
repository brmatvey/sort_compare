#include "drawing.h"
#include <cmath>
#include <sstream>
#include <iomanip>

int draw::rescale(double in, Scale old_sc, Scale new_sc) {
    double tangens = (new_sc.max - new_sc.min) / (old_sc.max - old_sc.min);
    double offset = (in - old_sc.min) * tangens;
    return offset + new_sc.min;
}

sf::Vector2f draw::rescaleToPixels(const ScaleSettings& settings, double x, double y) {
    return sf::Vector2f(rescale(x, settings.x_old, settings.x_new), rescale(y, settings.y_old, settings.y_new));
}

// vector - complexity in ms
// settings - drawing settings
// step - step along the abscissa
sf::VertexArray draw::getCurve(const std::vector<double>& vector, const ScaleSettings& settings, int step, sf::Color color) {
    int x = 0;
    sf::VertexArray result(sf::LinesStrip, vector.size());
    for (int i = 0; i < vector.size(); ++i) {
        result[i].position = rescaleToPixels(settings, x, vector[i]);
        result[i].color = color;
        x += step;
    }
    return result;
}

// resource asqusition is initiatization
sf::Text draw::makeText(const sf::Font& font, std::string str, sf::Vector2f label_offset) {
    sf::Text text;
    text.setFont(font);
    text.setString(std::move(str));
    text.setCharacterSize(12);
    text.setFillColor(axis_color);
    text.move(std::move(label_offset));
    return text;
}

void draw::axis(sf::RenderWindow& window, ScaleSettings scale_set) {
    // download font
    sf::Font font;
    if (!font.loadFromFile("Gidole-Regular.ttf")) {
        using namespace std::literals;
        throw std::logic_error("font not found"s);
    }
    double x = 0;
    double y = 0;
    // abscissa axis
    for (int i = 0; i < 5; ++i) {
        // line
        sf::VertexArray vertical_line(sf::LinesStrip, 2);
        vertical_line[0].position = rescaleToPixels(scale_set, x, 0);
        vertical_line[1].position = rescaleToPixels(scale_set, x, scale_set.y_old.max);
        vertical_line[0].color = axis_color;
        vertical_line[1].color = axis_color;
        window.draw(std::move(vertical_line));
        // text
        std::stringstream ss_x;
        ss_x << std::fixed << std::setprecision(0) << x;
        sf::Vector2f label_offset_x = rescaleToPixels(scale_set, x, 0);
        label_offset_x.y += 5.0;
        window.draw(makeText(font, ss_x.str(), std::move(label_offset_x)));
        // increment
        x += scale_set.x_old.max / 4.0;

        // line
        sf::VertexArray horizontal_line(sf::LinesStrip, 2);
        horizontal_line[0].position = rescaleToPixels(scale_set, 0, y);
        horizontal_line[1].position = rescaleToPixels(scale_set, scale_set.x_old.max, y);
        horizontal_line[0].color = axis_color;
        horizontal_line[1].color = axis_color;
        window.draw(std::move(horizontal_line));
        // text
        std::stringstream ss_y;
        ss_y << std::fixed << std::setprecision(1) << y;
        sf::Vector2f label_offset_y = rescaleToPixels(scale_set, 0, y);
        label_offset_y.x -= 30.0;
        label_offset_y.y -= 15.0;
        window.draw(makeText(font, ss_y.str(), std::move(label_offset_y)));
        // increment
        y += scale_set.y_old.max / 4.0;
    }
}

void draw::legend(sf::RenderWindow& window, ScaleSettings scale_set, const std::map<sort::Type, std::vector<double>>& map) {
    int i = 0;
    // first label here
    sf::Vector2f label_offset(scale_set.x_new.max + 20.0, scale_set.y_new.max);
    for (const auto& [type, _] : map) {
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("Gidole-Regular.ttf")) {
            using namespace std::literals;
            throw std::logic_error("font not found"s);
        }
        text.setFont(font);
        text.setString(sort::typeToString(type));
        text.setCharacterSize(16);
        text.setFillColor(curves_color[i]);
        text.move(label_offset);
        label_offset.y += 20.0;
        window.draw(std::move(text));
        i = (i >= curves_color.size()) ? 0 : i + 1;
    }
}

double draw::adjustScale(double value) {
    // degree of
    double dgr = floor(std::log10(value));
    // senior number
    double s_n = value / std::pow(10.0, dgr);
    // factor
    double factor = 1;
    if (s_n == 1) {
        factor = 1;
    } else if (s_n > 1 && s_n <= 2) {
        factor = 2;
    } else if (s_n > 2 && s_n <= 2.5) {
        factor = 2.5;
    } else if (s_n > 2.5 && s_n <= 5) {
        factor = 5;
    } else {
        factor = 10.0;
    }
    return factor * std::pow(10.0, dgr);
}

void draw::ScaleSettings::roundOff() {
    // abscissa axis
    x_old.max = adjustScale(x_old.max);
    // ordinate axis
    y_old.max = adjustScale(y_old.max);
}

draw::ScaleSettings draw::findScale(const std::map<sort::Type, std::vector<double>>& map, int step) {

    double max_y = *std::max_element(map.at(sort::Type::Bubble).begin(), map.at(sort::Type::Bubble).end());
    double max_x = map.at(sort::Type::Bubble).size() * step;

    // create scales
    ScaleSettings scale_set;
    scale_set.x_old = { 0, max_x };
    scale_set.x_new = { 40, 500 };
    scale_set.y_old = { 0, max_y };
    scale_set.y_new = { 360, 40 };
    scale_set.roundOff();

    return scale_set;
}

void draw::plot(const std::map<sort::Type, std::vector<double>>& map, int step) {
    // displaying the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sort algorithms complexity", sf::Style::Default, settings);
    ScaleSettings scale_set = findScale(map, step);

    // This code was in the SFML example. Slowly.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color(48,48,48));
        axis(window, scale_set);
        legend(window, scale_set, map);
        int i = 0;
        for (const auto& [type, vector] : map) {
            auto curve = getCurve(vector, scale_set, step, curves_color[i]);
            window.draw(std::move(curve));
            i = (i >= curves_color.size()) ? 0 : i + 1;
        }
        window.display();
    }
}
