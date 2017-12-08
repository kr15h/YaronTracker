# Web Interface for Projection Box

Launch local PHP server to test it. Change the `upload_tmp_dir` in `/php/php.ini` to an absolute path on your system.

```
php -S 127.0.0.1:8080 -c php/php.ini
```

Access interface via `http://localhost:8080/`


## PHP File Uploads

Set the upload filesize limit. Change the following settings in `/php/php.ini`. Use K for kilobytes, M for mega and G for giga. No letter at the end means it's plain bytes.

Note: if you are using Apache 2 on Raspberry Pi, the path to ini file is `/etc/php5/apache2/php.ini`.

```
file_uploads = On
post_max_size=2G
upload_max_filesize=2G
```