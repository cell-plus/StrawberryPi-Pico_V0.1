# StrawberryPi-Pico
土壌水分センサー・ポンプ・LEDを搭載した植物栽培特化型デバイス「StrawberryPi-Pico」

======V0.1.0-202501=========

・回路図　：https://image-pro.easyeda.com/pullimages/08d8bb2dcfd34de89ee88f67925cd60f.webp

・PCB図面　：https://image-pro.easyeda.com/pullimages/37ff79a8831c460f9f59f0e0ebcc0b90.webp

※NPNトランジスタの電流容量が足りていないのでポンプが正常に動作しない不具合あり。

=========================

======V0.1.1-202501=========

・変更点：NPNトランジスタの代わりにNchMOSFETに変更

　　　　-部品レイアウト、回路パターンの見直し

・回路図　：https://image-pro.easyeda.com/pullimages/9387c33788cf4fc8a83c969c9d6c46e4.webp

・PCB図面　：https://image-pro.easyeda.com/pullimages/377ebdb155c84c82ad2521dfd787f0dc.webp

========================

 

以下の物は別途入手してください。

・ウォーターポンプ　：https://amzn.asia/d/5MyBmeY

・静電容量式土壌水分センサー　：https://amzn.asia/d/6kMGpRw

・NeoPixel LEDテープ　：https://amzn.asia/d/j20iAux

　

　
　
ウォーターポンプはデュポンコネクタ等で配線加工してください。(メス,二つ口)

　　参考：https://amzn.asia/d/89GqBZK

　　

　　

　　

    
 ★使い方★
 
・BOOTボタンを押しながら、USBケーブルをパソコンに接続。

・PCではRP2040-Zeroをストレージとして認識。

・UF2ファイルをダウンロードして、ストレージに保存。

　　　https://circuitpython.org/board/raspberry_pi_pico/

・次にArduino IDEの環境設定。

　・ボードライブラリの追加。
 
　　IDE：ファイル>基本設定>追加のボードマネージャのURLに、( https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json )　を入力し適用。
  
　　IDE：ボードマネージャ>「RP2040」で検索>「Raspberry Pi Pico/RP2040/RP2350　by Earle F. Philhower」　をインストール。

・ボードの選択。

　IDE：ツール>ボード>Raspberry Pi Pico/RP2040/RP2350>Waveshare RP2040 Zero

　　　を選択。

・環境設定完了。

・あとは好きなプログラムを入れて遊んでください。

　まずはmain.inoなど。。。　https://github.com/cell-plus/StrawberryPi-Pico/blob/main/main.ino

 
