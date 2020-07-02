# Blur-detection-with-FFT-in-C
![output image]( https://qengineering.eu/images/LenaBlur.png ) <br/><br/>
This is a C++ implementation of the blur detection written in Python.<br/> 
https://github.com/whdcumt/BlurDetection. <br/><br/>
Paper: http://www.cse.cuhk.edu.hk/leojia/all_final_papers/blur_detect_cvpr08.pdf <br/><br/>
As known, blur is the lack of detailed features in an image. Detailed features have the most energy in the high-frequency Fourier spectrum. As to blurry regions (clouds, for instance), which have energy levels in low frequencies. This fact lets the blur detecting work. After removing the low frequencies, the energy of the remaining high part is measured. The higher output, the sharper the image must be. Please note, you should have OpenCV installed.
