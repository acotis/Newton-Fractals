//
// Created by evan on 9/2/17.
//

#ifndef NEWTONFRACTALS_FRACTALCONSTANTS_H
#define NEWTONFRACTALS_FRACTALCONSTANTS_H


namespace FractalConstants {
    const float ASPECT_RATIO = 1.77777f; // 16:9

    // Sizes of the image in memory (LQ, HQ, HD, 4k)
    const unsigned int IMG_WIDTHS[] = {160, 720, 1920, 4000};
    const unsigned int IMG_HEIGHTS[] = {(unsigned int) (IMG_WIDTHS[0]/ASPECT_RATIO),
                                        (unsigned int) (IMG_WIDTHS[1]/ASPECT_RATIO),
                                        (unsigned int) (IMG_WIDTHS[2]/ASPECT_RATIO),
                                        (unsigned int) (IMG_WIDTHS[3]/ASPECT_RATIO)};

    // Size of the image shown on the screen
    const unsigned int DISPLAY_WIDTH = 800;
    const unsigned int DISPLAY_HEIGHT = (unsigned int) (DISPLAY_WIDTH/ASPECT_RATIO);

    // Ratios of display size to image size (LQ, HQ, HD, 4k)
    const float DISPLAY_SHRINKS[] = {(DISPLAY_WIDTH+.0f)/IMG_WIDTHS[0],
                                     (DISPLAY_WIDTH+.0f)/IMG_WIDTHS[1],
                                     (DISPLAY_WIDTH+.0f)/IMG_WIDTHS[2],
                                     (DISPLAY_WIDTH+.0f)/IMG_WIDTHS[3]};

    // Size of the visible portion of the complex plane
    const float VIEW_WIDTH = 3.2;
    const float VIEW_HEIGHT = VIEW_WIDTH/ASPECT_RATIO;
}


#endif //NEWTONFRACTALS_FRACTALCONSTANTS_H
