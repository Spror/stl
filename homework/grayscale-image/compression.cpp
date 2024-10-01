#include "compression.hpp"
#include <algorithm>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height> image_a)
{
    std::vector<std::pair<uint8_t, uint8_t>> compressed_image;

    for(const auto & row : image_a)
    {
        uint8_t current_value = row[0];
        uint8_t count = 0;

        std::for_each(row.begin(), row.end(), [&](auto pixel){
            if(pixel == current_value)
            {
                count++;
            }
            else
            {
                compressed_image.emplace_back(current_value, count);
                count = 1;
                current_value = pixel;
            }
            
        });

        compressed_image.emplace_back(current_value, count);
    }

    return compressed_image;
}