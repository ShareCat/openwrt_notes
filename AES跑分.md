### AES跑分

基于现在留学普遍使用chacha20或aes-128-gcm加密，所以本文会以AES跑分为主导

#### 单线程：
```shell
openssl speed -evp aes-128-gcm
```

#### 多线程：
```shell
openssl speed -multi $(cat /proc/cpuinfo |grep processor | wc -l) -evp aes-128-gcm
```
