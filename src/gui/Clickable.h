//
// Created by evan on 10/13/17.
//

#ifndef NEWTONFRACTALS_CLICKABLE_H
#define NEWTONFRACTALS_CLICKABLE_H


class Clickable : public sf::Drawable {
protected:
    sf::IntRect absoluteBounds;

public:
    virtual bool handleClickAt(float x, float y) = 0;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    virtual sf::IntRect getAbsoluteBounds() {
        return absoluteBounds;
    };

    virtual void setAbsoluteBounds(sf::IntRect _absoluteBounds) {
        absoluteBounds = _absoluteBounds;
    }
};


#endif //NEWTONFRACTALS_CLICKABLE_H
