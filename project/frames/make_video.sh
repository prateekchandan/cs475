#!/bin/bash
mogrify -flip -format jpg -quality 100 frame_*.ppm
rm *.ppm
ffmpeg -framerate 60 -i frame_%04d.jpg -codec copy input.mkv