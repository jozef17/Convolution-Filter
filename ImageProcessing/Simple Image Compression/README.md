# Simple Image Compression

- Simplified JPEG Compression Algorithm 

![10% Quality](img/demo.gif)

## Encoding
1. Loading image (RGB pixels are converted to YCbCr)
2. Split image into 8 by 8 blocks and aply DCT for every block
3. Apply Quantization on every 8 by 8 block

<p align="center"><img src="img/Encoding.png"></p>

## Decoding
1. Split image into 8 by 8 blocks and aply Dequantization for every block
2. Apply IDCT on every 8 by 8 block
3. Display Result Image

<p align="center"><img src="img/Decoding.png"></p>

## Class Model
<p align="center"><img src="img/Classes.png"></p>

### Pixel
- Stores pixel values in both RGB and YCbCr
- When Pixel value changes, YCbCr / RGB values are automatically updated
- RGB to YCbCr

<p align="center"><img src="img/toYCbCr.png"></p>

- YCbCr to RGB

<p align="center"><img src="img/toRGB.png"></p>

### Image
- Supports loading .rgb or .bpm image formats

## 2-D Discrete cosine transform (DCT)
- Image is split into 8 by 8 blocks
- Calculated for every image block

<p align="center"><img src="img/DCT.png"></p>

## 2-D Inverse Discrete cosine transform (IDCT)
- Image is split into 8 by 8 blocks
- Calculated for every image block

<p align="center"><img src="img/IDCT.png"></p>

# Compile on Linux / Unix
1. Install glfw
```
sudo apt-get update
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```
2. Go to source directory
```
cd ".../Image-Processing/ImageProcessing/Simple Image Compression"
```
3. Compile
```
g++ `find . -type f -name \*.cpp` `find . -type f -name \*.h` -std=c++14 -lglfw -lGL -lpthread -o ./SimpleImageCompressor
```
4. Run
```
./SimpleImageCompressor
```