#!/bin/bash -e

cmd="./testFullScreenWordsDetect --jsons_path ../ocr_words1/small_jsons/ --images_path ../ocr_words1/small_images/ --area_threshold 0.25 --word_num_threshold 5 --area_ratio 0.5"
echo $cmd
$cmd
