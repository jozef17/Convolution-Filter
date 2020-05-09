# Simple Image Compression

- Simplified JPEG Compression Algorithm 

## Pixel
- Stores pixel values in both RGB and YCbCr
- RGB to YCbCr

<p align="center"><img src="img/toYCbCr.png"></p>

- YCbCr to RGB

<p align="center"><img src="img/toRGB.png"></p>

## Image
- Supoports loading .rgb or .bpm image formats

## 2-D Discrete cosine transform (DCT)
- Image is split into 8 by 8 blocks
- Calculated for every image block

<p align="center"><img src="img/DCT.png"></p>

## 2-D Inverse Discrete cosine transform (IDCT)
- Image is split into 8 by 8 blocks
- Calculated for every image block

<p align="center"><img src="img/IDCT.png"></p>
