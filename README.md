# Blur-detection-with-FFT-in-C
![output image]( https://qengineering.eu/images/LenaBlur.png ) <br/>
This is a C++ implementation of the blur detection written in Python.<br/> 
https://github.com/whdcumt/BlurDetection. <br/><br/>
Paper: http://www.cse.cuhk.edu.hk/leojia/all_final_papers/blur_detect_cvpr08.pdf <br/><br/>
As known, blur is the lack of detailed features in an image. Detailed features have high energy in the high-frequency Fourier spectrum. As to blurry regions (clouds, for instance) have high energy levels in the low frequencies. Based on this fact, the blur detecting is built. After removing the low frequencies, the energy of the remaining high part is measured. The higher, the sharper the image mus be. Please note, the output depends on the picture at hand.
