//
// Created by evan on 9/2/17.
//

#ifndef NEWTONFRACTALS_FRACTALCONSTANTS_H
#define NEWTONFRACTALS_FRACTALCONSTANTS_H


namespace FractalConstants {
    const float ASPECT_RATIO = 1.77777f; // 16:9

    const unsigned int IMG_WIDTH = 1600; // Size of the pixel array in memory
    const unsigned int IMG_HEIGHT = (unsigned int) (IMG_WIDTH/ASPECT_RATIO);

    const unsigned int DISPLAY_WIDTH = 800; // Size of the image shown on the screen
    const unsigned int DISPLAY_HEIGHT = (unsigned int) (DISPLAY_WIDTH/ASPECT_RATIO);

    const float DISPLAY_SHRINK = (DISPLAY_WIDTH+.0f)/IMG_WIDTH; // Ratio of display size to image size

    const float VIEW_WIDTH = 3.2; // Size of the visible portion of the complex plane
    const float VIEW_HEIGHT = VIEW_WIDTH/ASPECT_RATIO;
}


#endif //NEWTONFRACTALS_FRACTALCONSTANTS_H
