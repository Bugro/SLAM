import numpy as np
import copy


class Slam:

    def __init__(self):
        """ Inialization """

        self.depth_table = list()

        # Create lookup table for raw depth
        for i in range(0, 2048):
            self.depth_table.append(self.depth_to_meter(i))



    def depth_to_meter(self, depth):
        """ Convert raw depth to millimeter """

        meter = 0
        if depth < 2047:
            meter = int(round(1000.0 / ((depth * -0.00307) + 3.33)))

        return meter



    def depth_to_image(self, depth):
        """ Convert depth to greyscale image """

        img = copy.copy(depth)
        np.clip(img, 0, 2**10 - 1, img)
        img >>= 2
        img = img.astype(np.uint8)
 
        return img



    def depth_to_real_world(self, depth):
        """ Convert depth to xyz coordinate """

        real_world = list()

        for i in range(0, 640):
            for j in range(0, 480):
                z = self.depth_table[depth[j, i]]
                x = (i - 320) * (z - 100) * 0.0021
                y = (j - 240) * (z - 100) * 0.0021

                real_world.append( (x, y, z) )

        return real_world

