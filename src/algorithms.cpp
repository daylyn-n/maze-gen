#include "../include/algorithms.hpp"
#include "../include/grid.hpp"
#include <stack>
#include <random>

struct node { int nx, ny; Directions dir; };
namespace {
Directions opposite(Directions d) {
    switch (d) {
        case Directions::N: return Directions::S;
        case Directions::S: return Directions::N;
        case Directions::E: return Directions::W;
        case Directions::W: return Directions::E;
    }
    return Directions::N;
}
}
static void drawGrid(sf::RenderWindow& window, const Grid& grid, int hx = -1, int hy = -1, float alpha = 1.f)
{
    constexpr float padding = 40.f;
    constexpr float borderThickness = LINE_THICK;
    constexpr float gridWidth  = WIDTH  - 2 * padding;
    constexpr float gridHeight = HEIGHT - 2 * padding;

    const float cellW = gridWidth / grid.getWidth();
    const float cellH = gridHeight / grid.getHeight();
    constexpr float t = 2.f;

    // border for the grid
    sf::RectangleShape border(sf::Vector2f(gridWidth, gridHeight));
    border.setPosition(padding, padding);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(borderThickness);
    window.draw(border);

    // Highlight current cell (draw before walls so lines stay visible)
    if (hx >= 0 && hy >= 0)
    {
        sf::RectangleShape marker({cellW - 6.f, cellH - 6.f});
        marker.setPosition(padding + hx * cellW + 3.f, padding + hy * cellH + 3.f);
        marker.setFillColor(sf::Color(255, 80, 80, static_cast<sf::Uint8>(alpha * 200)));
        window.draw(marker);
    }

    for (int y {}; y < grid.getHeight(); y++)
    {
        for (int x {}; x < grid.getWidth(); x++)
        {

            const Cell& c = grid.getCell(x, y);
            const sf::Vector2f o{padding + x * cellW, padding + y * cellH};

            auto line = [&](sf::Vector2f pos, sf::Vector2f size)
            {
                sf::RectangleShape r(size);
                r.setPosition(pos);
                r.setFillColor(sf::Color::White);
                window.draw(r);
            };

            if (c.hasWall(Directions::N)) line({o.x, o.y}, {cellW, t});
            if (c.hasWall(Directions::S)) line({o.x, o.y + cellH - t}, {cellW, t});
            if (c.hasWall(Directions::W)) line({o.x, o.y}, {t, cellH});
            if (c.hasWall(Directions::E)) line({o.x + cellW - t, o.y}, {t, cellH});
        }
    }
}


void dfsMaze(Grid& grid, int startX, int startY)
{
    std::mt19937 rng{std::random_device{}()};
    std::stack<std::pair<int,int>> st;
    st.push({startX, startY});
    grid.getCell(startX, startY).visited = true;

    while (!st.empty())
    {
        auto [x, y] = st.top();
        st.pop();

        // Collect unvisited neighbors with their direction
        std::vector<node> neighbours;

        if (y > 0 && !grid.getCell(x, y-1).visited)
           neighbours.push_back({x, y-1, Directions::N});

        if (y+1 < grid.getHeight() && !grid.getCell(x, y+1).visited)
         neighbours.push_back({x, y+1, Directions::S});

        if (x > 0 && !grid.getCell(x-1, y).visited)
           neighbours.push_back({x-1, y, Directions::W});
           
        if (x+1 < grid.getWidth() && !grid.getCell(x+1, y).visited)
          neighbours.push_back({x+1, y, Directions::E});

        if (neighbours.empty()) continue;

        // Shuffle neighbors
        std::shuffle(neighbours.begin(), neighbours.end(), rng);

        for (const auto& nb : neighbours)
        {
            if (!grid.getCell(nb.nx, nb.ny).visited)
            {
                // Carve passage
                grid.getCell(x, y).removeWall(nb.dir);
                grid.getCell(nb.nx, nb.ny).removeWall(opposite(nb.dir));

                grid.getCell(nb.nx, nb.ny).visited = true;
                st.push({nb.nx, nb.ny});
            }
        }
    }
}

void dfsMazeAnimation(Grid& grid,int startX, int startY)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DFS MAZE ANIMATION");
    window.setFramerateLimit(60);

    std::mt19937 rng{std::random_device{}()};
    std::vector<std::pair<int,int>> st;
    st.emplace_back(startX, startY);
    grid.getCell(startX, startY).visited = true;

    sf::Clock clock;
    sf::Clock blinkClock;
    const float stepTime = 0.02f;
    bool running = true;

    auto step = [&]() -> bool {
        if (st.empty()) return false;

        auto [x, y] = st.back();

        std::vector<node> neighbours;
        if (y > 0 && !grid.getCell(x, y-1).visited)
            neighbours.push_back({x,   y-1, Directions::N});
        if (y+1 < grid.getHeight() && !grid.getCell(x, y+1).visited)
            neighbours.push_back({x,   y+1, Directions::S});
        if (x > 0 && !grid.getCell(x-1, y).visited)
            neighbours.push_back({x-1, y,   Directions::W});
        if (x+1 < grid.getWidth() && !grid.getCell(x+1, y).visited)
            neighbours.push_back({x+1, y,   Directions::E});

        if (neighbours.empty())
        {
         st.pop_back();
         return !st.empty();
        }

        std::shuffle(neighbours.begin(), neighbours.end(), rng);
        const auto nb = neighbours.front();

        grid.getCell(x, y).removeWall(nb.dir);
        grid.getCell(nb.nx, nb.ny).removeWall(opposite(nb.dir));
        grid.getCell(nb.nx, nb.ny).visited = true;

        st.emplace_back(nb.nx, nb.ny);
        return true;
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                running = !running;
        }

        if (running && clock.getElapsedTime().asSeconds() >= stepTime)
        {
            clock.restart();
            running = step();
        }

        // Blink alpha: smooth pulse 0..1
        float alpha = 0.5f * (std::sin(blinkClock.getElapsedTime().asSeconds() * 6.0f) + 1.0f);

        // Current cell to highlight
        int hx = st.empty() ? -1 : st.back().first;
        int hy = st.empty() ? -1 : st.back().second;

        window.clear(sf::Color::Black);
        drawGrid(window, grid, hx, hy, alpha);
        window.display();
    }
}

void solver(Grid& grid, int startX, int startY)
{

}
