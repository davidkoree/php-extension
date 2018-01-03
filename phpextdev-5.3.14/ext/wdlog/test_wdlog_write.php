<?php
dl('wdlog.so');
$file = 'vshop.log';
$content = 'hello, world!';
wdlog_write($file, $content);
