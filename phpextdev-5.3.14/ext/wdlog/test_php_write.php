<?php
$file = 'vshop.log';
$content = 'hello, world!';
file_put_contents($file, $content . "\n", FILE_APPEND);
