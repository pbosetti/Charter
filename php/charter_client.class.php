<?php

/**
 * Charter client library.
 *
 * @octdoc      c:php/charter_client
 * @copyright   copyright (c) 2011 by Harald Lapp
 * @author      Harald Lapp <harald.lapp@gmail.com>
 */
class charter_client
/**/
{
    const BASE_PORT = 2000;

    protected $id;

    protected $host;

    protected $port;

    protected $delay = 0.005;

    public function __construct($id, $host = '127.0.0.1') {
        $this->id   = $id;
        $this->host = $host;
        $this->port = self::BASE_PORT + $id;
    }
    
    protected function deliver($msg) {
        $sock = stream_socket_client('udp://' . $this->host . ':' . $this->port);
        fwrite($sock, $msg);
        fclose($sock);

        usleep($this->delay);
    }
    
    public function clear() {
        $this->deliver('CLEAR');
    }
    
    public function close() {
        $this->deliver('CLOSE');
    }
    
    public function send(array $data) {
        $msg = 's ' . implode(' ', array_filter($data, function($v) {
            return (is_numeric($v));
        }));
        
        $this->deliver($msg);
    }
    
    public function names(array $names) {
        if (count($names) > 0) {
            $this->deliver('NAMES ' . implode(' ', $names));
        }
    }
    
    public function labels(array $labels) {
        if (count($labels) > 0) {
            $this->deliver('LABELS ' . implode(' ', $labels));
        }
    }
}
