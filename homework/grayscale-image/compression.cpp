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

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> image_v)
{
    std::array<std::array<uint8_t, width>, height> decompress_image;
    auto count = 0;
    auto row = 0;

    std::for_each(image_v.begin(), image_v.end(), [&](std::pair<uint8_t, uint8_t> information){
        for(size_t i = count; i < count + static_cast<int>(information.second); i++)
        {
            decompress_image[count][row] = information.first;
            if(count % width == 0)
            {
                row++;
            }
        }
    });

    return decompress_image;
}