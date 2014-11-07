#!/bin/bash
echo "Converting ppm images to jpg images....."
mogrify -flip -format jpg -quality 100 frame_*.ppm
echo "Succussfully Converted.."
rm *.ppm
echo "cleaned.."
echo "making video"
ffmpeg -framerate 60 -i frame_%04d.jpg -codec copy video.mkv
echo "made video on video.mkv"
rm *.jpg
echo "done"
