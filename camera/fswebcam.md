连续采集20帧，按照5帧每秒的速度，裁剪到需要的尺寸

```shell
fswebcam -d /dev/video0 --no-banner -F 20 --fps 5 -r 3840x2880 --crop 3840x172 0,1354 --save ./data/{1..20}.jpg
```
